<#
.SYNOPSIS
    Build cfront-3 (if needed) and use it to translate/compile/run a C++ file.

.DESCRIPTION
    Runs the 1991 cfront C++-to-C translator through a native MSYS2 login shell.
    Launching from PowerShell gives the MSYS2 processes a clean Windows
    environment, avoiding the git-bash <-> MSYS2 runtime handoff problems.

.PARAMETER TestFile
    A .C (C++) file. If omitted, a built-in polymorphism demo (demo/shapes.C) is used.

.EXAMPLE
    powershell -ExecutionPolicy Bypass -File cfront.ps1
    powershell -ExecutionPolicy Bypass -File cfront.ps1 -TestFile myprog.C
#>
param([string]$TestFile = "")

$ErrorActionPreference = "Stop"
$Root = Split-Path -Parent $MyInvocation.MyCommand.Path
$Bash = "C:\msys64\usr\bin\bash.exe"
if (-not (Test-Path $Bash)) { throw "MSYS2 bash not found at $Bash" }

# Generate the demo file if none supplied: a class hierarchy with virtual
# functions, so the generated C shows the vtables cfront builds.
if ($TestFile -eq "") {
    $TestFile = Join-Path $Root "demo\shapes.C"
    @'
#include <stdio.h>

class Shape {
public:
    virtual double area()       { return 0; }
    virtual const char* name()  { return "shape"; }
    void describe() { printf("%-8s area = %g\n", name(), area()); }
};

class Circle : public Shape {
    double r;
public:
    Circle(double radius) { r = radius; }
    double area()      { return 3.14159 * r * r; }
    const char* name() { return "circle"; }
};

class Square : public Shape {
    double s;
public:
    Square(double side) { s = side; }
    double area()      { return s * s; }
    const char* name() { return "square"; }
};

main()
{
    Shape* shapes[2];
    shapes[0] = new Circle(2.0);
    shapes[1] = new Square(3.0);
    for (int i = 0; i < 2; i++)
        shapes[i]->describe();          // virtual dispatch
    return 0;
}
'@ | Set-Content -Encoding ASCII $TestFile
}

# Windows path -> MSYS path (C:\a\b -> /c/a/b)
function To-Msys([string]$p) {
    $p = (Resolve-Path $p).Path
    return "/" + $p.Substring(0,1).ToLower() + ($p.Substring(2) -replace "\\","/")
}
$msysRunner = To-Msys (Join-Path $Root "cfront-run.sh")
$msysTest   = To-Msys $TestFile

Write-Host "Running cfront-3 on $TestFile ..." -ForegroundColor Cyan
& $Bash -lc "bash '$msysRunner' '$msysTest'"
