# estadistica-vs
1. Para correr **envolvente_templados.c**
··* Pasar como argumento por linea de comando: **Templadoaprocesar**(yaduplicado) **numerador**(deltau) **golord**  
2. Para correr **emgs_correlation_templates.c**  
··* Pasar como argumento por linea de comando: **archivoaprocesar** **templadoprocesado**(sinduplicar-sale así del programa anterior) **numerador**(del tau) **golord**
##*Recordar*
* Tratar de tener siempre los mismos parámetros (más facil ahora que los meto por linea de comando)
* En emgs_correlation_templates.c
* Chequear que coincidan tau y m en los programas 
* siempre pasar los templados ya filtrados
* Cuando los procese en python tengo que
··* guardarlos con .Sound
··* ~~y duplicarlos para no perder tantos datos~~
··* ~~Los programas no duplican nada. Tengo que hacerlo en python si quiero.~~
··* Cambie el programa, ahora no necesito duplicarlos



##*comandos para cmd*
* gcc envolvente_templados.c -lm -o envtempl & envtempl.exe emg1.Sound & envtempl.exe emg2.Sound
* envtempl.exe emg1.Sound numerador golord
* gcc emgs_correlation_templates.c -lm -o correlacionsueno
* correlacionsueno.exe ZF-MCV_2015-12-01_13_13_49_vs_29_band.Sound envolvente.emg1.Sound.dat numerador golord

## Calendario

##### 23/05/16
 Voy a volver a extraer los templados a ver si mejoro la estadísitica con unos más adecuados. El emg1 está bien, el resto habría que ver.

##### 24/05/16

Consultar:
* Donde comienzan los for, en 0, ó 1?

##### 26/05/16
Los templados que quedan ahora son de ZF-MCV_2015-12-03_07_10_22_vs_5_band   
Cambie el programa. Ahora los templados no tiene que entrar duplicados

##### 27/05/19
Meto tau y m por linea de comando  