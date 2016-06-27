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
    #envolvente=np.loadtxt('envolvente.'+archivo+'.dat')
    #corr7=np.loadtxt('corremg2-7.envolvente.'+archivo+'.dat')
    #envolvente/=np.max(envolvente)
    r=np.zeros(len(lugares))
    devstd=np.zeros(len(lugares))
    
    for i in range(len(lugares)):
        r[i]=stats.probplot(vs[lugares[i]:lugares[i]+1000], dist="norm")[1][-1]
        devstd[i]=np.std(vs[lugares[i]:lugares[i]+1000])


    
    plt.figure()
    plt.title(archivo)
    plt.scatter(lugares[np.logical_and(r>umbralr,devstd<umbralstd)],r[np.logical_and(r>umbralr,devstd<umbralstd)])
    
    for i in lugares[np.logical_and(r>umbralr,devstd<umbralstd)]:
        plt.axvline(x=i,color='g',linewidth=2)
        plt.axvline(x=i+1000,**kwargs)
    
    
    for i in lugares:
            vsmean=np.mean(np.abs(vs[i:i+1000]))
            plt.plot(([i,(i+1000)]),([vsmean,vsmean]),linewidth=2)
     
    plt.plot(([i,len(lugares)]),([umbralstd,umbralstd]),'r',linewidth=2,label="umbral desv est")
    plt.plot([], [], label='segmentos de ruido', **kwargs)
    plt.plot(vs)
    plt.legend()
    #plt.plot(envolvente) 
    #plt.plot(corr7[:,0][corr7[:,1]>0.6],corr7[:,1][corr7[:,1]>0.6],marker='o',ms=2,ls='None',label='correlacion 7')



plt.show(block=True)