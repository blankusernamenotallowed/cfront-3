@echo off
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat" >nul 2>&1
cl /nologo /c /FAcs        /Fazz_facs.asm  /Fozz1.obj zz.c >nul 2>&1
cl /nologo /c /FA          /Fazz_fa.asm    /Fozz2.obj zz.c >nul 2>&1
cl /nologo /c /FA /GS- /O2 /Fazz_lean.asm  /Fozz3.obj zz.c >nul 2>&1
