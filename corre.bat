gcc envolvente_templados.c -lm -o envtempl
envtempl emg1.Sound
envtempl emg2.Sound
envtempl emg3.Sound
envtempl emg4.Sound
envtempl emg5.Sound
gcc emgs_correlation_templates.c -lm -o correlacionsueno
correlacionsueno ZF-MCV_2015-12-01_13_13_49_vs_29_band.Sound envolvente.emg1.Sound.dat
py figuras_p_correlaciones.py