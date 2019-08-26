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

data=zeros([60,128,512],Float)
epq_array=zeros([58],Float)


file0=open("../experiments/steps")
for i in file0:
    x=i.split()
    for k in range(58):
        epq_array[k]=float(x[k])
file0.close()

path="/data/wimmer/mu/jahresdaten/all_data/step_files/"


def f(m,v,q):
    return (0.5*m/(6.0221415*10.**26.)*(v*1000.)**2)*(6.24150974*10.**15.)/q


v_int_array=range(345,800,10)
steps=range(60)
for v_int in v_int_array:
    epq=f(4,v_int,2)
    print epq
    nepq=100.
    for i in range(58):
        if (nepq > (abs(epq-epq_array[i]))):
            nepq=abs(epq-epq_array[i])
            #print nepq
            epqstep=i
    for step in range(epqstep+2,60):
        print step, v_int, epqstep
        file0=open(path+str(v_int)+"_he/step_"+str(step)+"_o_cme")
        l=0
        k=0
        for i in file0:
            x=i.split()
            if (len(x)>0):
                data[step,k,l]+=float(x[2])
                l+=1
            if (l == 512):
                l=0
                k+=1
        file0.close()
for step in range(60):
    print "writing step ", step
    file1=open(path+"all_under_he_speed+2/step_"+str(step)+"_o_cme","w")
    for i in range(128):
        for j in range(512):
            file1.write(str(i+1))
            file1.write("   ")
            file1.write(str(j+1))
            file1.write("   ")
            file1.write(str(data[step,i,j]))
            file1.write("   ")
            if (data[step,i,j]>0.):
                file1.write(str((data[step,i,j])**0.5))
            else:
                file1.write("1")
            file1.write("\n")
        file1.write("\n")
    file1.close()
