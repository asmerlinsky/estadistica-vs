import numpy as np 
import matplotlib.pyplot as plt
import scipy.stats as stats
import matplotlib.gridspec as gridspec
import glob

files=glob.glob('ZF*')
lugares=np.linspace(1000,120000,80,dtype=int)
umbralr=0.99#8
umbralstd=0.01
kwargs = {'color': 'g', 'linewidth': 2}
for archivo in files:
    vs=np.loadtxt(archivo)
    envolvente=np.loadtxt('envolvente.'+archivo+'.dat')
    #corr7=np.loadtxt('corremg2-7.envolvente.'+archivo+'.dat')
    #envolvente/=np.max(envolvente)
    r=np.zeros(len(lugares))
    devstd=np.zeros(len(lugares))
    
    for i in range(len(lugares)):
        r[i]=stats.probplot(vs[lugares[i]:lugares[i]+1000], dist="norm")[1][-1]
        devstd[i]=np.std(vs[lugares[i]:lugares[i]+1000])

    fig=plt.figure()
    fig.suptitle(archivo)
    ax1 = fig.add_subplot(121)
    ax2 = fig.add_subplot(122)
    

    ax1.scatter(lugares[np.logical_and(r>umbralr,devstd<umbralstd)],r[np.logical_and(r>umbralr,devstd<umbralstd)])
    
    vsmean=np.zeros(len(lugares[np.logical_and(r>umbralr,devstd<umbralstd)]))
    j=0
    for i in lugares[np.logical_and(r>umbralr,devstd<umbralstd)]:
        ax1.axvline(x=i,color='g',linewidth=2)
        ax1.axvline(x=i+1000,**kwargs)
        vsmean[j]=np.mean(np.abs(vs[i:i+1000]))
        j+=1
   
    
    for i in lugares:
            media=np.mean(np.abs(vs[i:i+1000]))
            ax1.plot(([i,(i+1000)]),([media,media]),linewidth=2)
            
     
    ax1.plot(([i,len(lugares)]),([umbralstd,umbralstd]),'r',linewidth=2,label="umbral desv est")
    ax1.plot([], [], label='segmentos de ruido', **kwargs)
    ax1.plot(vs)
    ax1.legend()
    
    
    ax2.plot(envolvente)
    ax2.plot(([i,len(lugares)]),([2*np.mean(vsmean)*0.0103,2*np.mean(vsmean)*0.0103]),'r',linewidth=2,label="umbral desv est")
    for i in lugares:
        envmean=np.mean(envolvente[i:i+1000])
        ax2.plot(([i,(i+1000)]),([envmean,envmean]),linewidth=2)
    print("umbral envolvente=%1.8f en archivo %s" % (2*np.mean(vsmean)*0.0103,archivo))
        
    #plt.plot(envolvente) 
    #plt.plot(corr7[:,0][corr7[:,1]>0.6],corr7[:,1][corr7[:,1]>0.6],marker='o',ms=2,ls='None',label='correlacion 7')



plt.show(block=True)