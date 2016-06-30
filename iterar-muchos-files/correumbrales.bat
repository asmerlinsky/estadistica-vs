cd C:\Users\Agustin\Documents\Facultad\Tesis\newfolder

py FILTRO.py

@echo off
xcopy FILTRADOS C:\Users\Agustin\Documents\Facultad\Tesis\estadistica-vs\iterar-muchos-files\FILTRADOS /i

cd C:\Users\Agustin\Documents\Facultad\Tesis\estadistica-vs\iterar-muchos-files

gcc envolvente_templados.c -lm -O2 -o envtempl
if %errorlevel% neq 0 exit /b %errorlevel%

copy envtempl.exe FILTRADOS\envtempl.exe
if %errorlevel% neq 0 exit /b %errorlevel%

@echo 0    1    2    3    4 > resultados.dat
@echo 0    1    2 > datatemplados.dat
::Ejecutable templado numerador m
::con este formato de nombres, van a bien correr los scripts en python, sino hay que ponerse a cambiarlos.


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
  REM aca debería agregar el archivo que busca ruido
  set /a a=!a!+1
)

py segmentosruido.py

@echo on
