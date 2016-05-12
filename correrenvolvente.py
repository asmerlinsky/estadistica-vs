import os
import matplotlib.pyplot as plt
import subprocess
import re
import sys
import numpy as np

os.system("gcc envolvente.c -lm -o envolvente")

a=subprocess.check_output("./envolvente")
a=a.decode(sys.stdout.encoding)
print(a)
lista=re.findall('(?<=\s)(.*?)(?=\s)',a)
nomarchivos=[s for s in lista if ('.dat' in s) or ('.Sound' in s)]
numeros=re.findall(r"(?<=\s)[-+]?\d*\.\d+|[-+]?\d+(?=\s)",a)
tau=numeros[0]
canto=np.abs(np.loadtxt(nomarchivos[0]))
envolvente=np.loadtxt(nomarchivos[1])
maxcan=np.amax(canto)
maxenv=np.amax(envolvente)
canto=canto/maxcan
envolvente=envolvente/maxenv

umbral=np.ones(int(len(envolvente)/1000))
umbral=umbral*(np.std(envolvente))
xumbral=np.linspace(0,len(envolvente),len(umbral))

plt.figure(1)
plt.title('tau='+tau)
plt.xlim(0,len(envolvente))
plt.plot(canto)
plt.plot(envolvente,'r')
plt.plot(xumbral,umbral,'g')
plt.show(block=True)
