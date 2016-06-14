REM gcc envolvente_templados.c -lm -o envtempl
REM if %errorlevel% neq 0 exit /b %errorlevel%

REM :: Ejecutable templado numerador m
REM :: con este formato de nombres, van a bien correr los scripts en python, sino hay que ponerse a cambiarlos.
REM for /r %%i in (emg*.Sound) DO (
    REM envtempl %%~ni.Sound 10 4
REM )



gcc emgs_correlation_templates.c -lm -o correlacionsueno
if %errorlevel% neq 0 exit /b %errorlevel%
::Ejecutable     archivo-a-procesar templado    numerador   m

:: Ejecutable templado numerador m
:: con este formato de nombres, van a bien correr los scripts en python, sino hay que ponerse a cambiarlos.
for /r %%i in (envolvente.emg*.dat) DO (
    correlacionsueno ZF-MCV_2015-12-03_07_10_22_vs_5_band.Sound %%~ni.dat 10 4
)

                 

:: los argumentos del script son: -archivovs -numerador -m
:: ver que el archivo de señal completa en el script sea el que sea quiere comparar
py figuras_correlaciones_todos_emgs.py ZF-MCV_2015-12-03_07_10_22_vs_5_band.Sound 10 4 
