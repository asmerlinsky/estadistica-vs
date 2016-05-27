gcc envolvente_templados.c -lm -o envtempl
envtempl emg1.Sound 30 4
envtempl emg2.Sound 30 4
envtempl emg3.Sound 30 4
envtempl emg4.Sound 30 4
envtempl emg5.Sound 30 4
envtempl emg6.Sound 30 4
envtempl emg7.Sound 30 4
gcc emgs_correlation_templates.c -lm -o correlacionsueno
correlacionsueno ZF-MCV_2015-12-03_07_10_22_vs_5_band.Sound envolvente.emg6.Sound.dat 30 4
py figuras_p_correlaciones.py 30 4