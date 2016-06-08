# -*- coding: utf-8 -*-
"""
Created on Wed Apr 20 15:08:17 2016

@author: Agustin
"""
import matplotlib.pyplot as plt
import numpy as np
import sys
from pylab import *
import scipy.signal as signal
from math import *


fn=22000
#signal.buttord(wp, ws, gpass, gstop, analog=False)
b1,a1 = signal.butter(15,1700/fn, btype='lowpass', analog=False, output='ba')
wd1,hd1 = signal.freqz(b1,a1)
r1=np.linspace(-100,100,10)
l1=150*ones(10)
l2=3000*ones(10)


plt.figure(1)
plt.plot(wd1*(fn/pi), 20 * np.log10(abs(hd1)), 'b')
plt.plot(l1,r1,'r')
plt.plot(l2,r1,'r')
plt.ylabel('Amplitude [dB]', color='b')
plt.xlabel('Frequency [rad/sample]')
plt.xlim(0,4000)
plt.ylim(-20,10)
plt.grid()

t = np.linspace(0,1, 100000)
x = np.r_[np.zeros(1000),np.sin(2 * np.pi * 3000 * t)]
x1 = np.r_[np.zeros(1000),np.sin(2 * np.pi * 3500 * t)]
x2 = np.r_[np.zeros(1000),np.sin(2 * np.pi * 4500 * t)]
x3 = np.r_[np.zeros(1000),np.sin(2 * np.pi *10000 * t)]
#xhigh = np.r_[np.zeros(1000),np.sin(2 * np.pi * 150 * t)]
#x = xlow + xhigh
t = np.linspace(0,0.1, 101000)



y = signal.filtfilt(b1,a1, x)
y1 = signal.filtfilt(b1,a1, x1)
y2 = signal.filtfilt(b1,a1, x2)
y3 = signal.filtfilt(b1,a1, x3)
y = signal.filtfilt(b1,a1, y)
y1 = signal.filtfilt(b1,a1, y1)
y2 = signal.filtfilt(b1,a1, y2)
y3 = signal.filtfilt(b1,a1, y3)
#y = signal.filtfilt(b1,a1, y)
#y1 = signal.filtfilt(b1,a1, y1)
#y2 = signal.filtfilt(b1,a1, y2)
#y3 = signal.filtfilt(b1,a1, y3)


plt.figure(2)
plt.plot(t, x, 'b^', linestyle='-')
plt.plot(t,y,'r', linestyle='-')
plt.ylim(-1.5,1.5)
plt.grid()

plt.figure(3)
plt.plot(t, x1, 'b^', linestyle='-')
plt.plot(t,y1,'r', linestyle='-')
plt.ylim(-1.5,1.5)
plt.grid()

plt.figure(4)
plt.plot(t, x2, 'b^', linestyle='-')
plt.plot(t,y2,'r', linestyle='-')
plt.ylim(-1.5,1.5)
plt.grid()

plt.figure(5)
plt.plot(t, x3, 'b^', linestyle='-')
plt.plot(t,y3,'r', linestyle='-')
plt.ylim(-1.5,1.5)
plt.grid()
plt.show(block=True)

