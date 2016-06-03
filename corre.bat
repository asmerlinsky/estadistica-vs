gcc envolvente_templados.c -lm -o envtempl
if %errorlevel% neq 0 exit /b %errorlevel%

::Ejecutable templado numerador m
::con este formato de nombres, van a bien correr los scripts en python, sino hay que ponerse a cambiarlos.
envtempl emg1.Sound 5 4
envtempl emg2.Sound 5 4
envtempl emg3.Sound 5 4
envtempl emg4.Sound 5 4
envtempl emg5.Sound 5 4
envtempl emg6.Sound 5 4
envtempl emg7.Sound 5 4
gcc emgs_correlation_templates.c -lm -o correlacionsueno
if %errorlevel% neq 0 exit /b %errorlevel%
::Ejecutable     archivo-a-procesar templado    numerador   m
correlacionsueno ZF-MCV_2015-12-04_06_51_28_vs_19_band.Sound envolvente.emg1.Sound.dat 5 4
correlacionsueno ZF-MCV_2015-12-04_06_51_28_vs_19_band.Sound envolvente.emg2.Sound.dat 5 4
correlacionsueno ZF-MCV_2015-12-04_06_51_28_vs_19_band.Sound envolvente.emg3.Sound.dat 5 4
correlacionsueno ZF-MCV_2015-12-04_06_51_28_vs_19_band.Sound envolvente.emg4.Sound.dat 5 4
correlacionsueno ZF-MCV_2015-12-04_06_51_28_vs_19_band.Sound envolvente.emg5.Sound.dat 5 4
correlacionsueno ZF-MCV_2015-12-04_06_51_28_vs_19_band.Sound envolvente.emg6.Sound.dat 5 4
correlacionsueno ZF-MCV_2015-12-04_06_51_28_vs_19_band.Sound envolvente.emg7.Sound.dat 5 4
:: los argumentos del script son: numerador m cantidadtemplados(tienen que estar ordenados del 1 al #detemplados que haya)
py figuras_correlaciones_todos_emgs.py 5 4 7
::py figurastemplados.py 7 ::aca introduzco cantidad de templados que procese y saca figuras solo de los templados
