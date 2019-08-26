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
from libacepy.frange import frange
import random

Float=float
matrixmultiply=dot
gp=Gnuplot()

data=zeros([128,512],Float)


for year in range(2001,2008):
    path="/data/wimmer/mu/jahresdaten/"+str(year)+"_data/step_files/"
    v_int_array=range(345,850,10)
    steps=range(60)
    for step in steps:
        data=zeros([128,512],Float)
        for v_int in v_int_array:
            print step, v_int
            file0=open(path+str(v_int)+"_he/step_"+str(step)+"_o_cme")
            l=0
            k=0
            for i in file0:
                x=i.split()
                if (len(x)>0):
                    data[k,l]+=float(x[2])
                    l+=1
                if (l == 512):
                    l=0
                    k+=1
            file0.close()
        file1=open(path+"all/step_"+str(step)+"_o_cme","w")
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
        file1.close()
