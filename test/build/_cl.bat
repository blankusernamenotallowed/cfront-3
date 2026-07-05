@echo off
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat" >nul 2>&1
cl /nologo /w /Fe:test\build\10_virtual.exe test\build\10_virtual.c test\cfront_rt.c /link /subsystem:console >test\build\10.cl.log 2>&1
echo EXIT=%errorlevel%
