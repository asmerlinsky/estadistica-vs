# estadistica-vs

##*Recordar*
* Tratar de tener siempre los mismos parámetros 
* En emgs_correlation_templates.c
** siempre pasar los templados ya filtrados


##*Los parámetros que cambié quedaron en*##

* aa.tau=1./1500.
* savgol-> m=3

##*comandos para cmd*
* gcc envolvente_templados.c -lm -o envtempl & envtempl.exe emg1.Sound & envtempl.exe emg2.Sound
