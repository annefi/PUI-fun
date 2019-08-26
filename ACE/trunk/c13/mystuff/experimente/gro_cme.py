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

file0=open("cme_2001.dat")
l=0
for i in file0:
    l+=1
data=zeros([l,4],Float)

file0=open("cme_2001.dat")
l=0
for i in file0:
    x=i.split()
    print x[2][0], x[2][1], x[2][3], x[2][4], x[4][0], x[4][1], x[4][3], x[4][4]
    data[l,0]=float(x[2][0]+x[2][1])
    data[l,1]=float(x[2][3]+x[2][4])
    data[l,2]=float(x[4][0]+x[4][1])
    data[l,3]=float(x[4][3]+x[4][4])
    l+=1