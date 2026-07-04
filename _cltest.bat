@echo off
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat" >nul 2>&1
where cl
cl /nologo /c /FAcs /Fazoo_ext.asm /Fozoo_ext.obj zoo_ext.c
echo EXITCODE=%errorlevel%
