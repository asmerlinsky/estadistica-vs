import os
import matplotlib.pyplot as plt
import subprocess
import re
import sys
import numpy as np

os.system("gcc emgs_correlation_templates_long1.generic.c -lm -o convolucion")

a=subprocess.check_output("./convolucion")
a=a.decode(sys.stdout.encoding)
print(a)
lista=re.findall('(?<=\s)(.*?)(?=\s)',a)
nomarchivos=[s for s in lista if ('.dat' in s)]
senal=np.abs(np.loadtxt(nomarchivos[0]))
silaba=np.loadtxt(nomarchivos[1])
convolucion=np.loadtxt(nomarchivos[2])
maxsenal=np.amax(senal)
maxenv=np.amax(envolvente)
canto=canto/maxcan
envolvente=envolvente/maxenv

plt.figure(1)
plt.title("envolvente del canto(vs)")
plt.plot(canto)

plt.figure(2)
plt.title("envolvente de la 1º sílaba")
plt.plot(silaba)

plt.figure(3)
plt.title("convolución")
plt.plot(convolucion)
plt.plot(canto)
plt.show(block=True)