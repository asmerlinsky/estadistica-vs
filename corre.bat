gcc envolvente_templados.c -lm -o envtempl
envtempl emg1.Sound 1 3
envtempl emg2.Sound 1 3
envtempl emg3.Sound 1 3
envtempl emg4.Sound 1 3
envtempl emg5.Sound 1 3
envtempl emg6.Sound 1 3
envtempl emg7.Sound 1 3
gcc emgs_correlation_templates.c -lm -o correlacionsueno
correlacionsueno ZF-MCV_2015-12-04_06_51_28_vs_19_band.Sound envolvente.emg7.Sound.dat 1 3
py figuras_p_correlaciones.py 1 3
::py figurastemplados.py 7 ::aca introduzco cantidad de templados que procese