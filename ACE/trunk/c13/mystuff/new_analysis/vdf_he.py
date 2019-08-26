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
#from functions import *
from libacepy.frange import frange
import random


Float=float
matrixmultiply=dot
gp=Gnuplot()

vel=zeros([58],Float)
height=zeros([58],Float)
height2=zeros([58],Float)
tcp=zeros([58],Float)
p1=zeros([58],Float)
p2=zeros([58],Float)
p3=zeros([58],Float)
p4=zeros([58],Float)
p5=zeros([58],Float)

file0=open("hsf_results/linear/v_int_40/hsf_all_with_v")
for i in file0:
    x=i.split()
    vel[int(x[1])]=float(x[12])
    height[int(x[1])]=float(x[4])
file0.close()

ion="He2+"
file1=open("/data/wimmer/mu/appendix/000/"+ion+".p1")
l=0
for i in file1:
    x=i.split()
    p1[l]=float(x[1])
    l+=1
file1.close()

file2=open("/data/wimmer/mu/appendix/000/"+ion+".p2")
l=0
for i in file2:
    x=i.split()
    p2[l]=float(x[1])
    l+=1
file2.close()

file3=open("/data/wimmer/mu/appendix/000/"+ion+".p3")
l=0
for i in file3:
    x=i.split()
    p3[l]=float(x[1])
    l+=1
file3.close()

file4=open("/data/wimmer/mu/appendix/000/"+ion+".p4")
l=0
for i in file4:
    x=i.split()
    p4[l]=float(x[1])
    l+=1
file4.close()

file5=open("/data/wimmer/mu/appendix/000/"+ion+".p5")
l=0
for i in file5:
    x=i.split()
    p5[l]=float(x[1])
    l+=1
file5.close()

for i in range(58):
    tcp[i]=p1[i]*p2[i]*p3[i]*p5[i]

for i in range(58):
    height2[i]=height[i]/tcp[i]

file6=open("vdf_360","w")
for i in range(58):
    if not (int(height2[i]) == 0):
        file6.write(str(vel[i]))
        file6.write("   ")
        file6.write(str(height2[i]))
        file6.write("\n")
file6.close()
gp("kl(x)=(1+((x-x0)**2/(k1*s1**2)))**(-k1)")
gp("kr(x)=(1+((x-x0)**2/(k2*s2**2)))**(-k2)")
gp("k(x)=x<=x0? A*kl(x):A*kr(x)")
gp("A=5.e7")
gp("s1=10")
gp("s2=10")
gp("k1=5.")
gp("k2=5.")
gp("x0=360.")
gp("set xrange[250:500]")
gp("fit k(x) 'vdf_360' u 1:2 via A,x0,s1,s2,k1,k2")
gp("plot A**-1*k(x), 'vdf_360' u 1:($2/A)")
