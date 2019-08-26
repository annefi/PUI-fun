#!/usr/bin/python
from scipy import zeros, exp,sqrt,mean
from Gnuplot import Gnuplot, GridData, Data
from sys import stdin
from random import random

def writeion(line,name,xpos,ypos,sigxp,sigxm,sigyp,sigym,velocity,mass,charge,peakh):
    line=("%s\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\n" %(name,xpos,ypos,sigxp,sigxm,sigyp,sigym,velocity,mass,charge,peakh))


dim=58
xdim=512
ydim=128
ionname=''
mode=0

dorandom=0
usestep=30
nrdatasets=1000
maxcounts=200

f=open("/home/ivar/berger/projects/ionpositions/ion_para.dat")
print "loading ion_para.dat"

for step in range(usestep-1):
    s=f.readline()
    k=s.split()
    s=f.readline()
    numberions=int(k[5])
    for ion in range(numberions):
        s=f.readline()

parafile=[]
s=f.readline()
k=s.split()
linetmp="Step : "+str(k[2])+ " Numberions : "+k[5]+"\n"
parafile.append(linetmp)
s=f.readline()
parafile.append(s)
numberions=int(k[5])
linetmp=""
for ion in range(numberions):
    s=f.readline()
    k=s.split()
    if (not dorandom):
        print "Enter Peakhigh for ",k[0]," : "
        tmpval=0
        tmpval=stdin.readline()
    else:
        tmpval=int(random()*maxcounts)
    linetmp=("%s\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\n" %(k[0],float(k[1]),float(k[2]),float(k[3]),float(k[4]),float(k[5]),float(k[6]),float(k[7]),float(k[8]),float(k[9]),float(tmpval)))
    parafile.append(linetmp)

if (not dorandom):
    out=open("o8n7c6para30_1000.dat","w")
else:
    out=open("randompara30_1000.dat","w")

for step in range(nrdatasets):
    linetmp="Step : "+str(step)+ " Numberions : "+str(numberions)+"\n"
    out.write(linetmp)
    for i in range(numberions+2):
        if (i!=0):
            out.write(parafile[i])

out.close()
