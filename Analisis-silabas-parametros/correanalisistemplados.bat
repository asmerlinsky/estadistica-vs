gcc envolvente_templados.c -lm -O3 envtempl
if %errorlevel% neq 0 exit /b %errorlevel%

:: Ejecutable templado numerador m
:: con este formato de nombres, van a bien correr los scripts en python, sino hay que ponerse a cambiarlos.
for /r %%i in (emg*.Sound) DO (
    envtempl %%~ni.Sound 10 4
)
:: los argumentos son -criterio -cantidadtemplados
py figurastemplados.py 2 7