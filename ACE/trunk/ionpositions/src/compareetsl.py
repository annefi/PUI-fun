#!/usr/bin/python
from scipy import zeros,exp
from Gnuplot import Gnuplot,GnuplotOpts,Data,GridData
from numpy import float,log

GnuplotOpts.prefer_fifo_data=0
GnuplotOpts.prefer_inline_data=0

path1="/data/wimmer/berger/testing/2007001_12m/"
path2="/data/wimmer/berger/testing/2007001_1h/"
path3="/data/wimmer/berger/testing/2007001_1d/"

etsl12m=zeros([58,128,512],float)
etsl1h=zeros([58,128,512],float)
etsl1d=zeros([58,128,512],float)

etsl1dm12m=zeros([58,128,512],float)
etsl1dm1h=zeros([58,128,512],float)

listin=open(path1+"list.in")
s=listin.readline()
k=s.split()
print k[0]
for s in listin:
    k=s.split()
    print path1+k[0]
    ergin=open(path1+k[0])
    for i in range(5):
        ergin.readline()
    for step in range(58):
        s2=ergin.readline()
        for col in range(128):
            s2=ergin.readline()
            k2=s2.split()
            for lin in range(512):
                etsl12m[step][col][lin]+=float(k2[lin])
    ergin.close()
listin.close()

listin=open(path2+"list.in")
s=listin.readline()
k=s.split()
print k[0]
for s in listin:
    k=s.split()
    print path2+k[0]
    ergin=open(path2+k[0])
    for i in range(5):
        ergin.readline()
    for step in range(58):
        s2=ergin.readline()
        for col in range(128):
            s2=ergin.readline()
            k2=s2.split()
            for lin in range(512):
                etsl1h[step][col][lin]+=float(k2[lin])
    ergin.close()
listin.close()

listin=open(path3+"list.in")
s=listin.readline()
k=s.split()
print k[0]
for s in listin:
    k=s.split()
    print path3+k[0]
    ergin=open(path3+k[0])
    for i in range(5):
        ergin.readline()
    for step in range(58):
        s2=ergin.readline()
        for col in range(128):
            s2=ergin.readline()
            k2=s2.split()
            for lin in range(512):
                etsl1d[step][col][lin]+=float(k2[lin])
    ergin.close()
listin.close()

for step in range(58):
    for col in range(128):
        for lin in range(512):
            etsl1dm12m[step][col][lin]=etsl1d[step][col][lin]-etsl12m[step][col][lin]
            etsl1dm1h[step][col][lin]=etsl1d[step][col][lin]-etsl1h[step][col][lin]

diffpl12m=[]
GridData(etsl1dm12m)
diffpl1h=[]
for step in range(58):
    diffpl12m.append(GridData(etsl1dm12m))
    diffpl1h.append(GridData(etsl1dm1h))
gp("set pm3d map explicit")
gp=Gnuplot()
gp.splot(diffpl12m[45])
