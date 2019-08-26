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
import random
Float=float
gp=Gnuplot()
data=zeros([128,512],Float)

for v_int in range(345,846,10):
    for step in range(60):
        print "v_int = ", v_int, "step = ", step
        data=zeros([128,512],Float)
        file0=open("/data/kleopatra/mu/jahresdaten/all_data/step_files/"+str(v_int)+"_he/step_"+str(step))
        l=0
        k=0
        for i in file0:
            x=i.split()
            data[l,k]=float(x[2])
            k+=1
            if (k==512):
                l+=1
                k=0
        file0.close
        file1=open("/data/kleopatra/mu/jahresdaten/all_data/step_files/"+str(v_int)+"_he/step_"+str(step)+"_we","w")
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