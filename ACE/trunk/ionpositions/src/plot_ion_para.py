#!/usr/bin/python
import sys
from scipy import zeros, sqrt,mean
from numpy import float
from Gnuplot import Gnuplot, GridData, Data

dim=58
xdim=512
ydim=128
our=1
if (our):
    ion_names=["He2+","C4+","C6+","N5+","N7+","O6+","O8+","Ne8+","Mg9+","Mg11+","Si10+","S10+","Fe11+","Ca10+"]
else:
    ion_names=["He2+","C4+","C6+","N5+","N7+","O6+","O8+","20Ne8+","Mg9+","Mg11+","Si10+","S10+","Fe11+"]
ionpos=[]
for ion in ion_names:
    ionpos.append([])

if (our):
    paraname1="/data/ivar/berger/testco/ion_para.dat"
else:
    paraname1="/data/ivar/berger/work/oneyeardata/2004/axlv2_fmcomp.dat"

points1=[]

f=open(paraname1)
if (our):
    for step in range(58):
        s=f.readline()
        k=s.split()
        s=f.readline()
        for k in range(int(k[5])):
            s=f.readline()
            k2=s.split()
            for ion in range(len(ion_names)):
                if (ion_names[ion]==k2[0]):
                    ionpos[ion].append([float(k2[1])+1.,float(k2[2])+1.])
else:
    s=f.readline()
    s=f.readline()
    s=f.readline()
    for s in f:
        k=s.split()
        for ion in range(len(ion_names)):
            if (ion_names[ion]==k[2]):
                ionpos[ion].append([(float(k[3])+0.5)/2.,(float(k[5])+0.5)/2.])
                

f.close()

plotionpos=[]
for ion in range(len(ionpos)):
    tmpion=Data(ionpos[ion])
    if (ion_names[ion]!="20Ne8+"):
        tmpion.set_option_colonsep("title","'%s'"%(ion_names[ion]))
    else:
        tmpion.set_option_colonsep("title","'Ne8+'")
    plotionpos.append(tmpion)

    
yrange=[0,127]
xrange=[50,300]
gp=Gnuplot()
gp("set mouse")
gp("set xlabel 'Time-of-Flight Channel'")
gp("set ylabel 'Energy Channel' ")
gp("set xrange[%i:%i]" % (xrange[0],xrange[1]))
gp("set yrange[%i:%i]" % (yrange[0],yrange[1]))

gp.plot(plotionpos[0])
for ion in range(len(ionpos)-1):
    gp.replot(plotionpos[ion+1])
        
if (our):
    gp("set title 'New improved Ion Positions'")
else:
    gp("set title 'Hefti Ion Positions'")
gp("set term postscript color 18 lw 2 eps")
#gp("set outp 'positions.ps'")
if (our):
    gp.hardcopy("positions.ps",color=True, fontsize=18)
else:
    gp.hardcopy("positionshefti.ps",color=True, fontsize=18)
    

