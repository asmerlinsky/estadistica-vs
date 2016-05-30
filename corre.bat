gcc envolvente_templados.c -lm -o envtempl
::Ejecutable templado numerador m
::con este formato de nombres, van a bien correr los scripts en python, sino hay que ponerse a cambiarlos.
envtempl emg1.Sound 1 3
envtempl emg2.Sound 1 3
envtempl emg3.Sound 1 3
envtempl emg4.Sound 1 3
envtempl emg5.Sound 1 3
envtempl emg6.Sound 1 3
envtempl emg7.Sound 1 3
gcc emgs_correlation_templates.c -lm -o correlacionsueno
::Ejecutable     archivo-a-procesar templado    numerador   m
correlacionsueno ZF-MCV_2015-12-04_06_51_28_vs_19_band.Sound envolvente.emg1.Sound.dat 1 3
correlacionsueno ZF-MCV_2015-12-04_06_51_28_vs_19_band.Sound envolvente.emg2.Sound.dat 1 3
correlacionsueno ZF-MCV_2015-12-04_06_51_28_vs_19_band.Sound envolvente.emg3.Sound.dat 1 3
correlacionsueno ZF-MCV_2015-12-04_06_51_28_vs_19_band.Sound envolvente.emg4.Sound.dat 1 3
correlacionsueno ZF-MCV_2015-12-04_06_51_28_vs_19_band.Sound envolvente.emg5.Sound.dat 1 3
correlacionsueno ZF-MCV_2015-12-04_06_51_28_vs_19_band.Sound envolvente.emg6.Sound.dat 1 3
correlacionsueno ZF-MCV_2015-12-04_06_51_28_vs_19_band.Sound envolvente.emg7.Sound.dat 1 3
:: los argumentos del script son: numerador m cantidadtemplados(tienen que estar ordenados del 1 al #detemplados que haya)
py figuras_correlaciones_todos_emgs.py 1 3 7
::py figurastemplados.py 7 ::aca introduzco cantidad de templados que procese y saca figuras solo de los templados
