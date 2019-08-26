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


Float=float
matrixmultiply=dot
gp=Gnuplot()

res=zeros([58,30,7],Float)
he_pos=zeros([58,2],Float)
epq_array=zeros([58],Float)


def f(m,v,q):
    return (0.5*m/(6.0221415*10.**26.)*(v*1000.)**2)*(6.24150974*10.**15.)/q


file0=open("../experiments/steps")
for i in file0:
    x=i.split()
    for k in range(58):
        epq_array[k]=float(x[k])
file0.close()

gp("g1(x)=bg+G1*exp(-0.5*((x-x1)/sg1)**2)")
gp("k1(x)=bg+G1*(1+((x-x1)**2/(kappa1*sk1**2)))**-(kappa1)")
gp("k2(x)=bg+G1*(1+((x-x1)**2/(kappa2*sk2**2)))**-(kappa2)")
gp("f(x)=x<x1? k1(x):k2(x)")
gp("bg=0")
gp("x1=167")
gp("kappa1=5")
gp("kappa2=3")
gp("sk1=2")
gp("sk2=2")
gp("sg1=2")
gp("G1=40050")
#gp("set xrange[140:180]")
step=47
ech=8

l=0
filex=open("/home/kleopatra/mu/Desktop/swics/efficiencies/lars/aspeff/002/He2+_eff")
for i in filex:
    xx=i.split()
    for j in range(1,3):
        he_pos[l,j-1]=float(xx[j])+1
    l+=1
"""
v_int_array=range(345,350,10)
file1=open("hkf_all_step_"+str(step),"a")
for v_int in v_int_array:
    epq=f(4,v_int,2)
    print epq
    nepq=100.
    for i in range(58):
        if (nepq > (abs(epq-epq_array[i]))):
            nepq=abs(epq-epq_array[i])
            #print nepq
            epqstep=i
    print epqstep
"""
if (1):
    path="/data/wimmer/mu/jahresdaten/all_data/step_files/all/e_files/"
    for step in range(30,50):
        file2=open("hkf_results/hkf_all_step_"+str(step),"w")
        x1=he_pos[step-1,1]
        #gp("set xrange["+str(x1-10)+":"+str(x1+15)+"]")
        file2.write("# step     ECH     ToF-Pos    Höhe        Kappa-Links     Kappa-Rechts    Sigma-Links     Sigma-Rechts    Chi-Quadrat      Theo-Pos-ECH  Theo-Pos-TCH  ")
        file2.write("\n")
        for ech in range(8,13):
            gp("bg=0")
            gp("x1="+str(x1))
            gp("kappa1=10")
            gp("kappa2=3")
            gp("sk1=3")
            gp("sk2=3")
            gp("G1=300500")
            for i in range(10):
                gp("set xrange[x1-4*sk1:x1+4*sk2)]")
                gp("fit f(x) '"+path+"all_step_"+str(step)+"_e"+str(ech)+"' u 1:2:3 via G1")
                gp("fit f(x) '"+path+"all_step_"+str(step)+"_e"+str(ech)+"' u 1:2:3 via x1,G1,kappa1,kappa2,sk1,sk2")
                gp("plot '"+path+"all_step_"+str(step)+"_e"+str(ech)+"' u 1:2:3 w e, f(x)")
            res[step,ech,0]=float(str(gp.eval("x1")))
            res[step,ech,1]=float(str(gp.eval("G1")))
            res[step,ech,2]=float(str(gp.eval("kappa1")))
            res[step,ech,3]=float(str(gp.eval("kappa2")))
            res[step,ech,4]=float(str(gp.eval("sk1")))
            res[step,ech,5]=float(str(gp.eval("sk2")))
            res[step,ech,6]=float(str(gp.eval("FIT_STDFIT")))
            
            file2.write(str(step))
            file2.write("   ")
            file2.write(str(ech))
            file2.write("   ")
            for i in range(7):
                file2.write(str(res[step,ech,i]))
                file2.write("   ")
            for i in range(2):
                file2.write(str(he_pos[step,i]))
                file2.write("   ")
            file2.write("\n")
        file2.close()

