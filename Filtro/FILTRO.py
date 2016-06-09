import sys
import os
import shutil
import glob
from scipy.io import wavfile
import scipy.signal as signal
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

################################################## FILTRADO
                 
for j in range(0,len(directorios)):
    wavs=glob.glob(os.path.join(directorios[j],'*vs*.wav'))
    destino=os.path.join(directorios[j],'FILTRADOS')
    for musculo in wavs:
        fs,data=wavfile.read(musculo)
        if fn is not fs/2:
            fn=fs/2
            a1,a2 = signal.butter(6,40/fn, btype='highpass', analog=False, output='ba')
            b1,b2 = signal.butter(15,3000/fn, btype='lowpass', analog=False, output='ba')

        datafilt=signal.filtfilt(b1,b2,data)
        datafilt=signal.filtfilt(b1,b2,datafilt)
        datafilt=signal.filtfilt(a1,a2,datafilt)
        datafilt=signal.filtfilt(a1,a2,datafilt)
        
        try:
            np.savetxt(os.path.join(destino,os.path.splitext(os.path.basename(musculo))[0]+'.Sound'),datafilt/np.max(np.abs(datafilt)), fmt='%1.14f')
           
        except:
            os.mkdir(destino)
            np.savetxt(os.path.join(destino,os.path.splitext(os.path.basename(musculo))[0]+'.Sound'),datafilt/np.max(np.abs(datafilt)),fmt='%1.14f')


