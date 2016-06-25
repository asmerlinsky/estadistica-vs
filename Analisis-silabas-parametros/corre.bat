gcc envolvente_templados.c -lm -o envtempl
if %errorlevel% neq 0 exit /b %errorlevel%

:: Ejecutable templado numerador m
:: con este formato de nombres, van a bien correr los scripts en python, sino hay que ponerse a cambiarlos.
for /r %%i in (emg*.Sound) DO (
    envtempl %%~ni.Sound 10 4
)



gcc emgs_correlation_templates.c -lm -O3 correlacionsueno
if %errorlevel% neq 0 exit /b %errorlevel%
::Ejecutable     archivo-a-procesar templado    numerador   m

@echo off
set count=0
for %%x in (envolvente.emg*.dat) do set /a count+=1
echo %count%
setlocal EnableDelayedExpansion
set a=1
:: Ejecutable templado numerador m
:: con este formato de nombres, van a bien correr los scripts en python, sino hay que ponerse a cambiarlos.
for /r %%i in (envolvente.emg*.dat) DO (
    echo !a! de %count% archivos
    correlacionsueno ZF-MCV_2015-12-02_11_48_01_vs_18_band.Sound %%~ni.dat 10 4
    set /a a=!a!+1
)

                 

:: los argumentos del script son: -archivovs -numerador -m
:: ver que el archivo de señal completa en el script sea el que sea quiere comparar
py figuras_correlaciones_todos_emgs.py ZF-MCV_2015-12-02_11_48_01_vs_18_band.Sound ZF-MCV_2015-12-02_11_48_01_s_18_band.Sound 10 4 
