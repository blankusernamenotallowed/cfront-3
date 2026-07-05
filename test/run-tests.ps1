<#
  cfront test suite — dead simple, authentic runtime.
  For each test/fixtures/NAME.C that has a NAME.expected:
      build it with the real cfront pipeline:
          cpp -> cfront -> gcc -> munch -> link libC.a      (the ./CC driver)
      run the .exe and compare stdout to NAME.expected.
  This is the faithful runtime: global constructors/destructors actually run
  (munch collects the __sti__/__std__ functions; _main walks them).
  A NAME.xfail marker means "known failure" (e.g. the template 64-bit bug).

  Usage:  powershell -ExecutionPolicy Bypass -File test\run-tests.ps1
#>
# the CC driver writes harmless notes to stderr (e.g. "which: no tcc"); don't
# let PowerShell treat native-command stderr as a terminating error.
$ErrorActionPreference = 'Continue'
if (Get-Variable PSNativeCommandUseErrorActionPreference -EA SilentlyContinue) {
    $PSNativeCommandUseErrorActionPreference = $false
}

$here     = Split-Path -Parent $MyInvocation.MyCommand.Path
$root     = Split-Path -Parent $here
$fixtures = Join-Path $here 'fixtures'
$build    = Join-Path $here 'build'
$bash     = 'C:\msys64\usr\bin\bash.exe'
New-Item -ItemType Directory -Force $build | Out-Null

function WinToMsys([string]$p) {
    return '/' + $p.Substring(0,1).ToLower() + ($p.Substring(2) -replace '\\','/')
}
$msysRoot = WinToMsys $root

$pass = 0; $fail = 0; $xfail = 0
foreach ($src in (Get-ChildItem $fixtures -Filter *.C | Sort-Object Name)) {
    $name    = $src.BaseName
    $expFile = Join-Path $fixtures "$name.expected"
    if (-not (Test-Path $expFile)) { continue }              # no expected -> skip
    $isXfail = Test-Path (Join-Path $fixtures "$name.xfail")
    $exe     = Join-Path $build "$name.exe"
    Remove-Item $exe -ErrorAction SilentlyContinue

    # authentic pipeline via the CC driver, then clean the stray transpile file
    $msysSrc    = WinToMsys $src.FullName
    $msysExeBase = WinToMsys (Join-Path $build $name)
    $bashCmd = @"
export PATH=/c/msys64/usr/bin:`$PATH
cd '$msysRoot'
./CC '$msysSrc' -o '$msysExeBase'
rm -f '$name..c' '$name.o' 2>/dev/null
"@
    & $bash -lc $bashCmd *> (Join-Path $build "$name.build.log")

    # run + compare
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
            Write-Host "        (cfront/gcc build failed; see test\build\$name.build.log)"
        }
    }
}

Write-Host ''
Write-Host "Summary: $pass passed, $fail failed, $xfail xfail" -ForegroundColor Cyan
if ($fail -gt 0) { exit 1 } else { exit 0 }
