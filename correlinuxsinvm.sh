#!/bin/bash
gcc envolvente_templados.c -lm -o envtempl.exe
./envtempl.exe emg1.Sound
./envtempl.exe emg2.Sound
./envtempl.exe emg3.Sound
./envtempl.exe emg4.Sound
./envtempl.exe emg5.Sound
gcc emgs_correlation_templates_sinvm.c -lm -o correlacionsueno.exe
./correlacionsueno.exe ZF-MCV_2015-12-01_13_13_49_vs_29_band.Sound envolvente.emg1.Sound.dat
python3 figuras_p_correlaciones.py
