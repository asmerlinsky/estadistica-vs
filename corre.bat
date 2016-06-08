gcc envolvente_templados.c -lm -o envtempl
if %errorlevel% neq 0 exit /b %errorlevel%

::Ejecutable templado numerador m
::con este formato de nombres, van a bien correr los scripts en python, sino hay que ponerse a cambiarlos.
envtempl emg21.Sound 10 4
envtempl emg22.Sound 10 4
envtempl emg23.Sound 10 4
envtempl emg24.Sound 10 4
envtempl emg25.Sound 10 4
envtempl emg26.Sound 10 4
envtempl emg27.Sound 10 4
gcc emgs_correlation_templates.c -lm -o correlacionsueno
if %errorlevel% neq 0 exit /b %errorlevel%
::Ejecutable     archivo-a-procesar templado    numerador   m
                 
correlacionsueno ZF-MCV_2015-12-03_07_10_22_vs_5_band.Sound envolvente.emg21.Sound.dat 10 4
correlacionsueno ZF-MCV_2015-12-03_07_10_22_vs_5_band.Sound envolvente.emg22.Sound.dat 10 4
correlacionsueno ZF-MCV_2015-12-03_07_10_22_vs_5_band.Sound envolvente.emg23.Sound.dat 10 4
correlacionsueno ZF-MCV_2015-12-03_07_10_22_vs_5_band.Sound envolvente.emg24.Sound.dat 10 4
correlacionsueno ZF-MCV_2015-12-03_07_10_22_vs_5_band.Sound envolvente.emg25.Sound.dat 10 4
correlacionsueno ZF-MCV_2015-12-03_07_10_22_vs_5_band.Sound envolvente.emg26.Sound.dat 10 4
correlacionsueno ZF-MCV_2015-12-03_07_10_22_vs_5_band.Sound envolvente.emg27.Sound.dat 10 4
:: los argumentos del script son: -numerador -m -criterio -cantidadtemplados(tienen que estar ordenados del 1 al #detemplados que haya)
:: ver que el archivo de señal completa en el script sea el que sea quiere comparar
py figuras_correlaciones_todos_emgs.py ZF-MCV_2015-12-03_07_10_22_vs_5_band.Sound 10 4 2 7
::py figurastemplados.py 1 7 ::aca introduzco criterio y cantidad de templados que procese y saca figuras solo de los templados
:: for %%a in (*) do echo %%a para hacer algo variando %%a