#!/usr/bin/python
from os import system
from sys import stdin
from scipy.linalg import inv
from scipy import zeros, dot
from numpy import float
from Gnuplot import Gnuplot, GridData

Float=float
matrixmultiply=dot
a=1.
x=zeros([33,2],Float)

def f(m,v,q):
    e=(0.5*m/(6.0221415*10.**26.)*(v*1000.)**2)*(6.24150974*10.**15.)
    print m,v,q,e/q
    

for i in range(100):
    f(13.,300.+i,6.)
    f(12.,300.+i,6.)
    f(16.,300.+i,7.)