cd C:\Users\Agustin\Documents\Facultad\Tesis\newfolder

py FILTRO.py

xcopy FILTRADOS C:\Users\Agustin\Documents\Facultad\Tesis\estadistica-vs\iterar-muchos-files\FILTRADOS /i

cd C:\Users\Agustin\Documents\Facultad\Tesis\estadistica-vs\iterar-muchos-files

gcc envolvente_templados.c -lm -o envtempl
if %errorlevel% neq 0 exit /b %errorlevel%

copy envtempl.exe FILTRADOS\envtempl.exe
if %errorlevel% neq 0 exit /b %errorlevel%


::Ejecutable templado numerador m
::con este formato de nombres, van a bien correr los scripts en python, sino hay que ponerse a cambiarlos.

@echo off
set count=0
for %%x in (FILTRADOS/ZF*.Sound) do set /a count+=1
echo %count%


for /r %i in (emg*.Sound) DO (
    envtempl %~ni.Sound
)

cd FILTRADOS

for /r %%i in (ZF*.Sound) DO (
    envtempl %%~ni.Sound
)
    
cd ..
gcc emgs_correlation_templates.c -lm -O3 correlacionsueno
if %errorlevel% neq 0 exit /b %errorlevel%
setlocal EnableDelayedExpansion
set a=1
FOR  /r %%b in (FILTRADOS/envolvente.ZF*.dat) DO (
  FOR /r %%c in (envolvente.emg*.Sound.dat) DO (
    echo !a! de %count% archivos
    
    correlacionsueno %%~nb.dat %%~nc.dat 
  )
  set /a a=!a!+1
)
@echo on

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
REM gcc emg_check_correlacion.c -lm -o corrcheck
REM if %errorlevel% neq 0 exit /b %errorlevel%

REM FOR  /r %%b in (FILTRADOS/corremg26*.dat) DO (
  
    REM corrcheck %%~nb.dat 26 0.745

REM )



::Ejecutable     archivo-a-procesar templado    numerador   m
                 

:: los argumentos del script son: -numerador -m -criterio -cantidadtemplados(tienen que estar ordenados del 1 al #detemplados que haya)
:: ver que el archivo de señal completa en el script sea el que sea quiere comparar


::py figuras_correlaciones_todos_emgs.py ZF-MCV_2015-12-03_07_10_22_vs_5_band.Sound 10 4 2 7


::py figurastemplados.py 1 7 ::aca introduzco criterio y cantidad de templados que procese y saca figuras solo de los templados
:: for %%a in (*) do echo %%a para hacer algo variando %%a


if %errorlevel% neq 0 exit /b %errorlevel%
setlocal EnableDelayedExpansion
set a=1
for  /r %b in (FILTRADOS/envolvente.ZF*.dat) DO (
  for /r %c in (envolvente.emg*.Sound.dat) DO (
    echo !a! de %count% archivos
    
    umbrales %~nb.dat %~nc.dat 
  )
  set /a a=!a!+1
)
