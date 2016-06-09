gcc envolvente_templados.c -lm -o envtempl
if %errorlevel% neq 0 exit /b %errorlevel%

::Ejecutable templado numerador m
::con este formato de nombres, van a bien correr los scripts en python, sino hay que ponerse a cambiarlos.

@echo off
set count=0
for %%x in (FILTRADOS/ZF*.Sound) do set /a count+=1
echo %count%
@echo on


for /r %%i in (emg*.Sound) do (
    envtempl %%~ni.Sound
)

gcc emgs_correlation_templates.c -lm -o correlacionsueno
if %errorlevel% neq 0 exit /b %errorlevel%
set a=0
FOR  /r %%b in (FILTRADOS/ZF*.Sound) DO (
  FOR /r %%a in (envolvente.emg*.Sound.dat) DO (
    echo %a% de %count% archivos
    
    correlacionsueno %%~nb.Sound %%~na.dat 
  )
  set /a a=%a%+1
)


::Ejecutable     archivo-a-procesar templado    numerador   m
                 

:: los argumentos del script son: -numerador -m -criterio -cantidadtemplados(tienen que estar ordenados del 1 al #detemplados que haya)
:: ver que el archivo de señal completa en el script sea el que sea quiere comparar


::py figuras_correlaciones_todos_emgs.py ZF-MCV_2015-12-03_07_10_22_vs_5_band.Sound 10 4 2 7


::py figurastemplados.py 1 7 ::aca introduzco criterio y cantidad de templados que procese y saca figuras solo de los templados
:: for %%a in (*) do echo %%a para hacer algo variando %%a