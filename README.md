# estadistica-vs
1. Para correr **envolvente_templados.c**
  * Pasar como argumento por linea de comando: **Templadoaprocesar** #~~(yaduplicado)~~ **numerador**(deltau) **golord*
2. Para correr **emgs_correlation_templates.c**
  * Pasar como argumento por linea de comando: **archivoaprocesar** **templadoprocesado**(sinduplicar-sale así del programa anterior) **numerador**(del tau) **golord**
3. Para correr correlinux(o corre.bat en windows), si se quiere cambiar el archivo a correlacionar, hay que cambiar también el archivo en figurastemplados.py y figuras_correlaciones_todos_emgs 


##*Recordar*
* Tratar de tener siempre los mismos parámetros (más facil ahora que los meto por linea de comando)  
* En emgs_correlation_templates.c  
  * Chequear que coincidan tau y m en los programas  
  * siempre pasar los templados ya filtrados  
* Cuando los procese en python tengo que  
  * guardarlos con .Sound(todavia me falta)  
  * ~~y duplicarlos para no perder tantos datos~~  
  * ~~Los programas no duplican nada. Tengo que hacerlo en python si quiero.~~  
  * Cambie el programa, ahora no necesito duplicarlos  



###*comandos para cmd*
* gcc envolvente_templados.c -lm -o envtempl & envtempl.exe emg1.Sound & envtempl.exe emg2.Sound  
* envtempl.exe emg1.Sound numerador golord  
* gcc emgs_correlation_templates.c -lm -o correlacionsueno  
* correlacionsueno.exe ZF-MCV_2015-12-01_13_13_49_vs_29_band.Sound envolvente.emg1.Sound.dat numerador golord  

### Calendario

##### 23/05/16
 Voy a volver a extraer los templados a ver si mejoro la estadística con unos más adecuados. El emg1 está bien, el resto habría que ver.  


##### 26/05/16
Los templados que quedan ahora son de ZF-MCV_2015-12-03_07_10_22_vs_5_band   
Cambie el programa. Ahora los templados no tiene que entrar duplicados  

##### 27/05/16
Meto tau y m por linea de comando  

##### 30/05/16
Los templados que estám ahora corresponden a *ZF-MCV_2015-12-04_06_51_28_vs_19_band.Sound*  
cambié los programas para calcular las correlaciones de todas las silabas  
agregué un script en python para graficarlas.  
emgs_correlations_templates.c ahora hace el archivo ccs.dat para guardar cuantas veces correlacionó cada sílaba.  

##### 03/06/16
Los templados ahora van sin duplicar. Creo que el mejor tau es el que había.  
Probé los templados que saqué de vs19 en vs5. Algunos dan bien. Otros tengo que buscarme otro templado (S1). a S6 le tengo que bajar el umbral, con S3 capaz también sirva eso, aunque puedo buscar otra.  S4 correlaciona por todos lados por la forma misma del templado.  

##### 05/06/16
Probe con tau=10/1500. No hubo gran diferencia. Definitivamente tengo que cambiar S1, pero tengo que ver cómo la elijo y qué hago con S4

#####08/06/16
Arreglé el problema del filtro y guardo los archivos filtrados como .Sound. Separé el análisis de sílabas y parámetros y los de iteración para hacer estadística. 
Corren en windows y linux, pero hay que cambiar lineas según (capaz puedo ver más adelante alguna forma de dejarlo compatible con ambos, pero ya fue.

#####12/06/16
Cambios
* emg_check_correlacion.c levanta correlaciones y las pasa a resultados (me había equivocado un umbral así que hice esto)  
* corrre.bat de carpeta iterar tiene el conteo bien.  
* ahora calculo todas las envolventes primero y despues hago correlaciones, para no guardar la envolvente para cada templado.

##### 14/06/16
cambie archivos de analisis-silabas-parametros para que sean un poco más genericos y poder correrlos con la nueva nomeclatura



