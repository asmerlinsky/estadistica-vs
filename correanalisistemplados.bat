gcc envolvente_templados.c -lm -o envtempl
if %errorlevel% neq 0 exit /b %errorlevel%

:: Ejecutable templado numerador m
:: con este formato de nombres, van a bien correr los scripts en python, sino hay que ponerse a cambiarlos.
envtempl emg21.Sound 10 4
envtempl emg22.Sound 10 4
envtempl emg23.Sound 10 4
envtempl emg24.Sound 10 4
envtempl emg25.Sound 10 4
envtempl emg26.Sound 10 4
envtempl emg27.Sound 10 4
:: los argumentos son -criterio -cantidadtemplados
py figurastemplados.py 2 7