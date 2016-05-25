gcc envolvente_templados.c -lm -o envtempl
envtempl.exe emg1.Sound
envtempl.exe emg2.Sound
envtempl.exe emg3.Sound
envtempl.exe emg4.Sound
envtempl.exe emg5.Sound
gcc emgs_correlation_templates.c -lm -o correlacionsueno
correlacionsueno.exe ZF-MCV_2015-12-01_13_13_49_vs_29_band.Sound envolvente.emg1.Sound.dat
py figuras_p_correlaciones.py