gcc envolvente_templados.c -lm -o envtempl
if %errorlevel% neq 0 exit /b %errorlevel%

::Ejecutable templado numerador m
::con este formato de nombres, van a bien correr los scripts en python, sino hay que ponerse a cambiarlos.
envtempl emg1.Sound 10 4
envtempl emg2.Sound 10 4
envtempl emg3.Sound 10 4
envtempl emg4.Sound 10 4
envtempl emg5.Sound 10 4
envtempl emg6.Sound 10 4
envtempl emg7.Sound 10 4

py figurastemplados.py 7