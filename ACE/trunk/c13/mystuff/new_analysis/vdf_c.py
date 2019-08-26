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

vel_c12=zeros([58],Float)
height_c12=zeros([58],Float)
height2_c12=zeros([58],Float)
tcp_c12=zeros([58],Float)
vel_c13=zeros([58],Float)
height_c13=zeros([58],Float)
height2_c13=zeros([58],Float)
tcp_c13=zeros([58],Float)
p1=zeros([58],Float)
p2=zeros([58],Float)
p3=zeros([58],Float)
p4=zeros([58],Float)
p5=zeros([58],Float)

file0=open("results/360")
for i in file0:
    x=i.split()
    height_c12[int(x[0])]=float(x[2])
    height_c13[int(x[0])]=float(x[3])
    vel_c12[int(x[0])]=float(x[4])
    vel_c13[int(x[0])]=float(x[5])
file0.close()

ion="C6+"
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
    tcp_c12[i]=p1[i]*p2[i]*p3[i]*p5[i]

for i in range(58):
    height2_c12[i]=height_c12[i]/tcp_c12[i]


ion="13C6+"
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
    tcp_c13[i]=p1[i]*p2[i]*p3[i]*p5[i]

for i in range(58):
    height2_c13[i]=height_c13[i]/tcp_c13[i]



file6=open("results/vdf_c_360","w")
for i in range(58):
    if not (int(height2_c12[i]) == 0):
        file6.write(str(height2_c12[i]))
        file6.write("   ")
        file6.write(str(height2_c13[i]))
        file6.write("   ")
        file6.write(str(vel_c12[i]))
        file6.write("   ")
        file6.write(str(vel_c13[i]))
        file6.write("\n")
file6.close()
gp("kl(x)=(1+((x-x0)**2/(k1*s1**2)))**(-k1)")
gp("kr(x)=(1+((x-x0)**2/(k2*s2**2)))**(-k2)")
gp("k(x)=x<=x0? A*kl(x):A*kr(x)")
gp("A=4.e4")
gp("s1=10")
gp("s2=10")
gp("k1=5.")
gp("k2=5.")
gp("x0=360.")
gp("set xrange[300:450]")
gp("fit k(x) 'results/vdf_c_360' u 3:1 via A")
gp("fit k(x) 'results/vdf_c_360' u 3:1 via s1,s2")
gp("fit k(x) 'results/vdf_c_360' u 3:1 via A,x0,s1,s2,k1,k2")
gp("plot A**-1*k(x), 'results/vdf_c_360' u 3:($1/A)")
gp("set zrange [0:*]")
gp("fit k(x) 'results/vdf_c_360' u 4:2 via A,x0")
gp("plot A**-1*k(x), 'results/vdf_c_360' u 4:($2/A)")
