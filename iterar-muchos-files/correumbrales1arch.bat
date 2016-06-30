cls

@echo off

@echo 0    1    2    3    4 > resultados.dat
@echo 0    1 > longtemp.dat

set count=0
for %%x in (FILTRADOS/ZF*.Sound) do set /a count+=1
echo tengo %count% archivos


gcc  emgs_correlation_templates-corr1arch.c -lm -O2 -o 1arch
if %errorlevel% neq 0 exit /b %errorlevel%

setlocal EnableDelayedExpansion
set a=1
FOR  /r %%b in (FILTRADOS/envolvente.ZF*.dat) DO (
  FOR /r %%c in (envolvente.emg*.Sound.dat) DO (
    echo !a! de %count% archivos
    
    1arch %%~nb.dat %%~nc.dat 
  )
  REM aca debería agregar el archivo que busca ruido
  set /a a=!a!+1
)

@echo on
echo %TIME%

