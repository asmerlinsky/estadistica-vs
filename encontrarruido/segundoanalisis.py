import numpy as np 
import matplotlib.pyplot as plt
import scipy.stats as stats
import matplotlib.gridspec as gridspec
import glob

files=glob.glob('ZF*')
lugares=np.linspace(1000,120000,80,dtype=int)
umbral=0.998
kwargs = {'color': 'r', 'linewidth': 2}
for archivo in files:
    vs=np.loadtxt(archivo)
    envolvente=np.loadtxt('envolvente.'+archivo+'.dat')
    corr7=np.loadtxt('corremg2-4.envolvente.'+archivo+'.dat')
    r=np.zeros(len(lugares))
    devstd=[]
    i=0
    for puntos in lugares:
        if np.std(vs[puntos:puntos+1000])<0.01:        
            r[i]=stats.probplot(vs[puntos:puntos+1000], dist="norm")[1][-1]
        i+=1
            #if (r[i]>umbral:
            #    devstd.append(np.std(vs[lugares[i]:lugares[i]+1000]))
    lugruido=lugares[r>umbral] #me quedo con los lugares que superan el umbral
    mediaruido=np.zeros(len(lugruido))
    i=0
    
    if not lugruido.any():
        umbralenv=3*0.01*0.0103
        print("no hay lugar con r>umbralajuste")
    else:
        for puntos in lugruido:
            mediaruido[i]=np.mean(np.abs(vs[puntos:puntos+1000]))
            i+=1 
        umbralenv=3*np.mean(mediaruido)*0.0103
        

    fig=plt.figure()
    fig.suptitle(archivo)
    ax1 = fig.add_subplot(121)
    ax2 = fig.add_subplot(122)
    
    ax1.plot(([0,len(vs)]),([umbralenv/np.max(envolvente),umbralenv/np.max(envolvente)]),'g',linewidth=2)
    
    if lugruido.any():
        for i in lugruido:
                ax1.plot(([i,(i+1000)]),([0.9,0.9]),**kwargs)
        
        ax1.plot([], [], label='segmentos de ruido', **kwargs)
            
    ax1.plot(vs)
    ax1.plot(envolvente/np.max(envolvente)) 
    ax1.plot(corr7[:,0][corr7[:,1]>0.6],corr7[:,1][corr7[:,1]>0.6],marker='o',ms=2,ls='None',label='correlacion 7')
    
    
    
    ax1.legend()
    
    
    ax2.plot(envolvente)
    ax2.plot(([0,len(vs)]),([umbralenv,umbralenv]),'g',linewidth=2)
    for puntos in lugares:
        media=np.mean(envolvente[puntos:puntos+1000])
        ax2.plot(([puntos,puntos+1000]),([media,media]),**kwargs)
    
    ax2.plot([], [], label='promedio envolvente', **kwargs)
    ax2.plot(corr7[:,0][corr7[:,1]>0.6],corr7[:,1][corr7[:,1]>0.6]*np.max(envolvente),marker='o',ms=2,ls='None',label='correlacion 7')
    ax2.legend()

    



plt.show(block=True)