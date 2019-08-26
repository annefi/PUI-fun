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

data1=zeros([99,12],Float)
data2=zeros([58,10],Float)
data3=zeros([58,10,10],Float)
error=zeros([58,6],Float)

file0=open("hsf")
l=0
for i in file0:
    x=i.split()
    for j in range(12):
        data1[l,j]=float(x[j])
    l+=1
file0.close()

file1=open("hsf2")
l=0
for i in file1:
    x=i.split()
    for j in range(10):
        data2[l,j]=float(x[j])
    l+=1
file1.close()

for k in range(22,52):
    for i in range(len(data1)):
        if (data1[i,1]==data2[k,0]):
            t=0
            for l in (range(5,10)+[11]):
                error[k,t]+=(data1[i,l]-data2[k,l-2])**2
                t+=1

for k in range(22,52):
    print k, (error[k,0])**0.5/data2[k,3]*100.

