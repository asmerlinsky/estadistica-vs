# estadistica-vs

##*Recordar*
* Tratar de tener siempre los mismos parámetros 
* En emgs_correlation_templates.c
** siempre pasar los templados ya filtrados
* Cuando los procese en python tengo que
** guardarlos con .Sound
** ~~y duplicarlos para no perder tantos datos~~
** ~~Los programas no duplican nada. Tengo que hacerlo en python si quiero.~~
** Cambie el programa, ahora no necesito duplicarlos


##*Los parámetros que tengo que chequear*##
*que coincidan en envolvente_templados.c y emgs_correlation_templates.c*
* aa.tau=1./1500.
* savgol-> m=3

##*comandos para cmd*
* gcc envolvente_templados.c -lm -o envtempl & envtempl.exe emg1.Sound & envtempl.exe emg2.Sound
* envtempl.exe emg1.Sound
* gcc emgs_correlation_templates.c -lm -o correlacionsueno
* correlacionsueno.exe ZF-MCV_2015-12-01_13_13_49_vs_29_band.Sound envolvente.emg1.Sound.dat 

## Calendario

##### 23/05/16
 Voy a volver a extraer los templados a ver si mejoro la estadísitica con unos más adecuados. El emg1 está bien, el resto habría que ver.

##### 24/05/16

Consultar:
* Donde comienzan los for, en 0, ó 1?

##### 26/05/16
Los templados que quedan ahora son de ZF-MCV_2015-12-03_07_10_22_vs_5_band
Cambie el programa. Ahora los templados no tiene que entrar duplicados
