import numpy as np 
import matplotlib.pyplot as plt
import scipy.stats as stats
import matplotlib.gridspec as gridspec
import glob

files=glob.glob('ZF*')
lugares=np.linspace(1000,120000,80,dtype=int)
umbral=0.998
for archivo in files:
    vs=np.loadtxt(archivo)
    envolvente=np.loadtxt('envolvente.'+archivo+'.dat')
    corr7=np.loadtxt('corremg2-7.envolvente.'+archivo+'.dat')
    envolvente/=np.max(envolvente)
    r=np.zeros(len(lugares))
    devstd=[]
    for i in range(len(lugares)):
        r[i]=stats.probplot(vs[lugares[i]:lugares[i]+1000], dist="norm")[1][-1]
        if r[i]>umbral:
            devstd.append(np.std(vs[lugares[i]:lugares[i]+1000]))



    stdmedia8=8*np.mean(devstd)
    print("el archivo es",archivo)
    print("la 8*desviacion estandar media es", stdmedia8)
    if np.isnan(stdmedia8) or (stdmedia8>0.055):
        stdmedia8=0.05
     
    
    plt.figure()
    plt.title(archivo)
    plt.scatter(lugares[r>umbral],r[r>umbral])
    # for i in lugares:
            # plt.axvline(x=i,color='g',linewidth=1)
            # plt.axvline(x=i+2000,color='g',linewidth=1)
            
    plt.plot(vs)
    plt.plot(envolvente) 
    plt.plot(corr7[:,0][corr7[:,1]>0.6],corr7[:,1][corr7[:,1]>0.6],marker='o',ms=2,ls='None',label='correlacion 7')
    plt.axhline(y=stdmedia8,color='r',linewidth=1,label="8stdmedia="+str(stdmedia8))
    plt.legend()



plt.show(block=True)