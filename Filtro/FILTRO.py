import sys
import os
import shutil
import glob
from scipy.io import wavfile
import scipy.signal as signal
import scipy.stats as stats
import numpy as np

######################################PASA ALTO##
fn = 44150/2
a1, a2 = signal.butter(6, 40/fn, btype='highpass', analog=False, output='ba')
######################################PASA BAJO##
b1, b2 = signal.butter(15, 3000/fn, btype='lowpass', analog=False, output='ba')

########################################GENERAR LISTA DIRECTORIOS


carpetaactual = os.getcwd()

directorios=[]
directorios.append(carpetaactual)
[directorios.append(os.path.join(carpetaactual,x)) for x in next(os.walk('.'))[1] if 'FILTRADOS' not in x]
base=len(directorios)
if len(directorios)!=0:
    for j in range(1,len(directorios)):
        [directorios.append(os.path.join(directorios[j],x)) for x in next(os.walk(directorios[j]))[1] if ('FILTRADOS' not in x) and (x not in directorios)]

    for j in range(base,len(directorios)):
        [directorios.append(os.path.join(directorios[j],x)) for x in next(os.walk(directorios[j]))[1] if ('FILTRADOS' not in x) and (x not in directorios)]

directorios=list(set(directorios))

################################################## FILTRAD Y SETEO DE UMBRAL

lugares=np.linspace(1000,120000,80,dtype=int)
umbral=0.998
r=np.zeros(len(lugares))
                 
for j in range(0,len(directorios)):
    wavs=glob.glob(os.path.join(directorios[j],'*vs*.wav'))
    destino=os.path.join(directorios[j],'FILTRADOS')
    n=0
    try:
        file = open(os.path.join(destino,'umbralruido.dat'),  'w+')
    except:
        os.mkdir(destino)
        file = open(os.path.join(destino,'umbralruido.dat'),  'w+')
    for musculo in wavs:
        devstd=[]
        fs,data=wavfile.read(musculo)
        if fn is not fs/2:
            fn=fs/2
            a1,a2 = signal.butter(6,40/fn, btype='highpass', analog=False, output='ba')
            b1,b2 = signal.butter(15,3000/fn, btype='lowpass', analog=False, output='ba')

        datafilt=signal.filtfilt(b1,b2,data)
        datafilt=signal.filtfilt(b1,b2,datafilt)
        datafilt=signal.filtfilt(a1,a2,datafilt)
        datafilt=signal.filtfilt(a1,a2,datafilt)     
        
        
        np.savetxt(os.path.join(destino,os.path.splitext(os.path.basename(musculo))[0]+'.Sound'),datafilt/np.max(np.abs(datafilt)), fmt='%1.14f')
           
        
        for i in range(len(lugares)):
            r[i]=stats.probplot(datafilt[lugares[i]:lugares[i]+1000], dist="norm")[1][-1]
            if r[i]>umbral:
                devstd.append(np.std(datafilt[lugares[i]:lugares[i]+1000]))
            
        stdmedia8=8*np.mean(devstd)
           
        if np.isnan(stdmedia8) or (stdmedia8>0.055):
            stdmedia8=0.05
        
        file.write(str(n)+'\t'+os.path.basename(musculo)+'\t'+str(stdmedia8)+'\n')
        n+=1
        
    file.close()
            
            
            
