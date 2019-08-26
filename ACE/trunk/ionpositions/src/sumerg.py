#!/usr/bin/python
import sys
from scipy import zeros, exp,sqrt,mean
#from scipy import zeros, Float, matrixmultiply,exp,sqrt,mean
from Gnuplot import Gnuplot, GridData, Data

def writeion(file,name,xpos,ypos,sigxp,sigxm,sigyp,sigym,velocity,mass,charge,fiterg,normerg):
    file.write("%s\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\n" %(name,xpos,ypos,sigxp,sigxm,sigyp,sigym,velocity,mass,charge,fiterg,normerg))

dim=58

path="/data/ivar/berger/ionpositions/2004041_12m/"

sumlist=open(path+"sumerg.in")
ergfilename="sumergfm0.dat"

# sumerg.dat wird erzeugt
s=sumlist.readline()
erg=open(path+ergfilename,"w")
k=s.split()
add=open(path+k[0])
for i in range(dim):
    s=add.readline()
    k=s.split()
    print k
    numions=int(k[5])
    erg.write(s)
    s=add.readline()
    erg.write(s)
    for j in range(numions):
        s=add.readline()
        k=s.split()
        writeion(erg,k[0],float(k[1]),float(k[2]),float(k[3]),float(k[4]),float(k[5]),float(k[6]),float(k[7]),float(k[8]),float(k[9]),0.,0.)
erg.close()
add.close()
sumlist.close()
sumlist=open(path+"sumerg.in")
for filenr in range(118):
#for s in sumlist:
    s=sumlist.readline()
    k=s.split()
    print "reading ",k[0]
    add=open(path+k[0])
    ergin=open(path+ergfilename)
    tmperg=open(path+"tmperg.dat","w")
    for i in range(dim):
        s1=add.readline()
        k1=s1.split()
        s2=ergin.readline()
        k2=s2.split()
        numions=int(k2[5])
        tmperg.write(s2)
        s1=add.readline()
        s2=ergin.readline()
        tmperg.write(s2)
        for j in range(numions):
            s1=add.readline()
            k1=s1.split()
            s2=ergin.readline()
            k2=s2.split()
#            if (float(k1[10]>0.)):
            #if (float(k1[10]>0. and float(k1[10]!=0.5))):
            val1=float(k2[10])+float(k1[10])
            val2=float(k2[11])+float(k1[11])
#            else:
#                val1=float(k2[10])
#                val2=float(k2[10])
#            print float(k2[10])," + ",float(k1[10])," = ", val 
            writeion(tmperg,k1[0],float(k1[1]),float(k1[2]),float(k1[3]),float(k1[4]),float(k1[5]),float(k1[6]),float(k1[7]),float(k1[8]),float(k1[9]),val1,val2)
    add.close()
    ergin.close()
    tmperg.close()
    erg=open(path+ergfilename,"w")
    tmperg=open(path+"tmperg.dat")
    for s in tmperg:
        erg.write(s)

    erg.close()
    tmperg.close()

