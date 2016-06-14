#tengo que pasarle por linea de comando numerador m canttemp
import matplotlib.pyplot as plt
import numpy as np
import sys
import glob
import re

templados=glob.glob('envolvente.emg*.dat')
perio=[]
[perio.append(re.search('envolvente.emg(.+?).Sound.dat', templado).group(1)) for templado in templados]
envvs=np.loadtxt(sys.argv[1])
envvs=envvs/np.max(envvs)
corremg=[np.loadtxt('corremg'+perio[0]+'.'+sys.argv[1]+'.dat')]

for i in range(1,len(templados)): #cargo los templados
    print(templados[i])
    corremg.append(np.loadtxt('corremg'+perio[i]+'.'+sys.argv[1]+'.dat'))

tau="{:.5f}".format(float(sys.argv[2])/1500) 
m=sys.argv[3]


#m='4'
#tau='0.006'
for i in range(0,len(corremg)): #hace una figura de correlacion por cada templado
    plt.figure()
    plt.title('correlacion emg'+perio[i])
    plt.plot(envvs,label='envolvente señal')
    plt.axvline(x=108147,color='g',linewidth=2)
    plt.axvline(x=29225,color='g',linewidth=2)    
    plt.axvline(x=47940,color='g',linewidth=2) 
    plt.axvline(x=82903,color='g',linewidth=2)
    plt.axvline(x=290710,color='g',linewidth=2)    
    plt.axvline(x=324235,color='g',linewidth=2)
    plt.axvline(x=340948,color='g',linewidth=2)        
    plt.axvline(x=371903,color='g',linewidth=2)
    plt.axhline(y=0.8,color='b',linewidth=2)
    plt.plot(corremg[i][:,1][corremg[i][:,1]>0.5],'r',label='correlacion, m='+m+'tau='+tau,linewidth=1)
    plt.legend(loc=4)

#fig = plt.figure() Esta parte mete todas las figuras en una sola ventana
#fig.suptitle("Correlaciones, m="+m+", tau="+tau, fontsize=16)
#for i in range(0,len(corremg)):
#    ax = plt.subplot(str(len(corremg))+"1"+str(i+1))
#    ax.set_title("correlacion"+str(i+1))
#    #ax.plot(hilbemg[i])
#    ax.plot(envvs,label='envolvente señal')
#    ax.plot(corremg[i][:,1],'r',label='correlacion',linewidth=1)

plt.show(block=True)
