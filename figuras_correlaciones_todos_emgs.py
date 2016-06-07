#tengo que pasarle por linea de comando numerador m canttemp
import matplotlib.pyplot as plt
import numpy as np
import sys


envvs=np.loadtxt(sys.argv[1])
envvs=envvs/np.max(envvs)
canttemp=int(sys.argv[4])
corremg=[np.loadtxt('corremg1.'+sys.argv[1]+'.dat')]

for i in range(1,canttemp): #cargo los templados
    corremg.append(np.loadtxt('corremg'+str(i+1)+'.'+sys.argv[1]+'.dat'))

tau="{:.5f}".format(float(sys.argv[2])/1500) 
m=sys.argv[3]

#m='4'
#tau='0.006'
for i in range(0,len(corremg)): #hace una figura de correlacion por cada templado
    plt.figure()
    plt.title('correlacion emg'+str(i+1))
    plt.plot(envvs,label='envolvente señal')
    plt.axvline(x=37362,color='g',linewidth=2)
    plt.axvline(x=75103,color='g',linewidth=2)    
    plt.axvline(x=91851,color='g',linewidth=2) 
    plt.axvline(x=121752,color='g',linewidth=2)
    plt.axvline(x=151726,color='g',linewidth=2)    
    plt.axvline(x=183196,color='g',linewidth=2)
    plt.axvline(x=231453,color='g',linewidth=2)   
    plt.plot(corremg[i][:,1],'r',label='correlacion, m='+m+'tau='+tau,linewidth=1)
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
