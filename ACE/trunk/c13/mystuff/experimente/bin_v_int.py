#!/usr/bin/python
from os import system
from scipy.linalg import inv
from scipy import zeros, dot
from numpy import float
from Gnuplot import Gnuplot, GridData
from math import sin,cos,tan,asin,acos,atan,exp,pi
from os import popen2
from sys import stdin
import random
from scipy.integrate import quad
from Gnuplot.func_ext import *
from functions import *
from libacepy.frange import frange
import random

Float=float
matrixmultiply=dot
gp=Gnuplot()

data=zeros([128,512],Float)

path="/data/wimmer/mu/jahresdaten/all_data/step_files/"
path2="/data/wimmer/mu/jahresdaten/all_data/step_files/"

interval=int(20)
v2_int_array=range(340+interval,850,interval*2)
for v2_int in v2_int_array:
    system("mkdir "+path2+str(v2_int)+"_"+str(interval)+"_he")

v_int_array=range(345,840,10)
steps=range(60)
for step in steps:
    ll=0
    kk=0
    data=zeros([128,512],Float)
    for v_int in v_int_array:
        v2_int=v2_int_array[kk]
        print step, v_int, v2_int, kk
        file0=open(path+str(v_int)+"_he/step_"+str(step)+"_o_cme")
        l=0
        k=0
        for i in file0:
            x=i.split()
            if (len(x) > 0):
                data[k,l]+=float(x[2])
                l+=1
            if (l == 512):
                l=0
                k+=1
        file0.close()
        ll+=1
        if (ll == int(interval/5)):
            file1=open(path2+str(v2_int)+"_"+str(interval)+"_he/step_"+str(step)+"_o_cme","w")
            for i in range(128):
                for j in range(512):
                    file1.write(str(i+1))
                    file1.write("   ")
                    file1.write(str(j+1))
                    file1.write("   ")
                    file1.write(str(data[i,j]))
                    file1.write("   ")
                    if (data[i,j]>0.):
                        file1.write(str((data[i,j])**0.5))
                    else:
                        file1.write("1")
                    file1.write("\n")
                file1.write("\n")
            ll=0
            kk+=1
            data=zeros([128,512],Float)
