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
data2=zeros([128,512],Float)
data3=zeros([128,512],Float)
year=2001
v_int=345
for year in range(2001,2008):
    for v_int in range(345,850,10):
        for i in range(60):
            path1="/data/wimmer/mu/jahresdaten/"+str(year)+"_data/step_files/"+str(v_int)+"_he/step_"+str(i)
            path2="/data/wimmer/mu/jahresdaten/"+str(year)+"_data/step_files/"+str(v_int)+"_he/cme_step_"+str(i)
            path3="/data/wimmer/mu/jahresdaten/"+str(year)+"_data/step_files/"+str(v_int)+"_he/step_"+str(i)+"_o_cme"
            data=zeros([128,512],Float)
            data2=zeros([128,512],Float)
            data3=zeros([128,512],Float)
            print year, v_int, i
            file1=open(path1)
            l=0
            k=0
            for i in file1:
                x=i.split()
                data[k,l]+=float(x[2])
                l+=1
                if (l == 512):
                    l=0
                    k+=1
            file1.close()

            file2=open(path2)
            l=0
            k=0
            for i in file2:
                x=i.split()
                data2[k,l]+=float(x[2])
                l+=1
                if (l == 512):
                    l=0
                    k+=1
            file2.close()

            for i in range(128):
                for j in range(512):
                    data3[i,j]=data[i,j]-data2[i,j]


            file3=open(path3,"w")
            for i in range(128):
                for j in range(512):
                    file3.write(str(i+1))
                    file3.write("   ")
                    file3.write(str(j+1))
                    file3.write("   ")
                    file3.write(str(data3[i,j]))
                    file3.write("   ")
                    if (data3[i,j]>0.):
                        file3.write(str((data3[i,j])**0.5))
                    else:
                        file3.write("1")
                    file3.write("\n")
                file3.write("\n")
