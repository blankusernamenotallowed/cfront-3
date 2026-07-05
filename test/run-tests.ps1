<#
  cfront test suite — dead simple.
  For each test/fixtures/NAME.C that has a NAME.expected:
      1. cfront:  C++ -> C
      2. MSVC:    C   -> NAME.exe   (linked with cfront_rt.c)
      3. run it and compare stdout to NAME.expected
  A NAME.xfail marker means "known to fail" (e.g. the template 64-bit bug).

  Usage:  powershell -ExecutionPolicy Bypass -File test\run-tests.ps1
#>
$ErrorActionPreference = 'Stop'
if (Get-Variable PSNativeCommandUseErrorActionPreference -EA SilentlyContinue) {
    $PSNativeCommandUseErrorActionPreference = $false
}

$here     = Split-Path -Parent $MyInvocation.MyCommand.Path
$root     = Split-Path -Parent $here
$fixtures = Join-Path $here 'fixtures'
$build    = Join-Path $here 'build'
$rt       = Join-Path $here 'cfront_rt.c'
$bash     = 'C:\msys64\usr\bin\bash.exe'
New-Item -ItemType Directory -Force $build | Out-Null

# make cl.exe available (import the VS build env once)
if (-not (Get-Command cl.exe -ErrorAction SilentlyContinue)) {
    $vswhere = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
    $vs = & $vswhere -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath
    if (-not $vs) { $vs = & $vswhere -latest -property installationPath }
    cmd /c "`"$vs\VC\Auxiliary\Build\vcvars64.bat`" >nul 2>&1 && set" |
        ForEach-Object { if ($_ -match '^([^=]+)=(.*)$') { Set-Item "env:$($matches[1])" $matches[2] } }
}

function To-Msys([string]$p) {
    $f = (Resolve-Path -LiteralPath $p).Path
    return '/' + $f.Substring(0,1).ToLower() + ($f.Substring(2) -replace '\\','/')
}
$msysRoot = To-Msys $root

$pass = 0; $fail = 0; $xfail = 0
foreach ($src in (Get-ChildItem $fixtures -Filter *.C | Sort-Object Name)) {
    $name    = $src.BaseName
    $expFile = Join-Path $fixtures "$name.expected"
    if (-not (Test-Path $expFile)) { continue }              # no expected -> skip
    $isXfail = Test-Path (Join-Path $fixtures "$name.xfail")
    $cOut    = Join-Path $build "$name.c"
    $exe     = Join-Path $build "$name.exe"
    Remove-Item $exe -ErrorAction SilentlyContinue

    # 1) cfront: C++ -> C  (pipefail so a cfront crash fails the pipeline)
    $msysSrc = To-Msys $src.FullName
    $bashCmd = @"
set -o pipefail
export PATH=/c/msys64/usr/bin:`$PATH
cd '$msysRoot'
gcc -Du3b -U__GNUC__ -D__cfront__ -D__cplusplus=1 -D__signed__= -D__null=0 -E \
    -I incl -D__CFRONT_ANSI_OPT -Dc_plusplus=1 -D__cplusplus=1 '$msysSrc' 2>/dev/null \
  | ./cfront.exe +L +f'$($src.Name)' +a1 2>/dev/null \
  | grep -v '^#'
"@
    $cText = & $bash -lc $bashCmd
    $transpiled = ($LASTEXITCODE -eq 0)
    if ($transpiled) { [System.IO.File]::WriteAllLines($cOut, [string[]]$cText) }

    # 2) MSVC: C -> exe
    if ($transpiled) {
        Push-Location $build
        & cl.exe /nologo /w "/Fe:$exe" $cOut $rt /link /subsystem:console *> "$build\$name.cl.log"
        Pop-Location
    }

    # 3) run + compare
    $ok = $false; $got = '(build failed)'
    if (Test-Path $exe) {
        $got = ((& $exe 2>&1) -join "`n") -replace "`r",''
        $got = $got.TrimEnd()
        $exp = ((Get-Content -Raw $expFile) -replace "`r",'').TrimEnd()
        $ok  = ($got -eq $exp)
    }

    if ($isXfail) {
        if ($ok) { Write-Host "XPASS $name   (now passes - remove the .xfail marker!)" -ForegroundColor Yellow }
        else     { Write-Host "xfail $name   (known failure)" -ForegroundColor DarkGray; $xfail++ }
    }
    elseif ($ok) {
        Write-Host "PASS  $name" -ForegroundColor Green; $pass++
    }
    else {
        Write-Host "FAIL  $name" -ForegroundColor Red; $fail++
        if (Test-Path $exe) {
            Write-Host "        expected: $exp"
            Write-Host "        got:      $got"
        } else {
            Write-Host "        (cfront or MSVC build failed; see test\build\$name.cl.log)"
        }
    }
}

Write-Host ''
Write-Host "Summary: $pass passed, $fail failed, $xfail xfail" -ForegroundColor Cyan
if ($fail -gt 0) { exit 1 } else { exit 0 }
