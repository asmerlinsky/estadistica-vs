REM cd C:\Users\Agustin\Documents\Facultad\Tesis\newfolder

REM py FILTRO.py

REM xcopy FILTRADOS C:\Users\Agustin\Documents\Facultad\Tesis\estadistica-vs\iterar-muchos-files\FILTRADOS /i

REM cd C:\Users\Agustin\Documents\Facultad\Tesis\estadistica-vs\iterar-muchos-files

gcc envolvente_templados.c -lm -O2 -o envtempl
if %errorlevel% neq 0 exit /b %errorlevel%

copy envtempl.exe FILTRADOS\envtempl.exe
if %errorlevel% neq 0 exit /b %errorlevel%


::Ejecutable templado numerador m
::con este formato de nombres, van a bien correr los scripts en python, sino hay que ponerse a cambiarlos.

@echo off
set count=0
for %%x in (FILTRADOS/ZF*.Sound) do set /a count+=1
echo %count%


for /r %%i in (emg*.Sound) DO (
    envtempl %%~ni.Sound
)

cd FILTRADOS

for /r %%i in (ZF*.Sound) DO (
    envtempl %%~ni.Sound
)
    
cd ..
gcc  emgs_correlation_templates-umbrales.c -lm -O2 -o umbrales
if %errorlevel% neq 0 exit /b %errorlevel%
setlocal EnableDelayedExpansion
set a=1
FOR  /r %%b in (FILTRADOS/envolvente.ZF*.dat) DO (
  FOR /r %%c in (envolvente.emg*.Sound.dat) DO (
    echo !a! de %count% archivos
    
    umbrales %%~nb.dat %%~nc.dat 
  )
  set /a a=!a!+1
)
@echo on

