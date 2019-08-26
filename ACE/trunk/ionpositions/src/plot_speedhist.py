#!/usr/bin/python
import sys
from scipy import zeros, sqrt,mean
from numpy import float
from Gnuplot import Gnuplot, GridData, Data

summe=0.
summe2=0.
hist=[]
hist2=[]
for i in range(31,72):
    name="/data/ivar/berger/Regensburg/2005/"+str(i*10)+"/axlv2_sumspeed_0"+str(i*10)+"-0"+str((i+1)*10)+".dat"
    f=open(name)
    s=f.readline()
    k=s.split()
    name2="/data/ivar/berger/Regensburg/2002/"+str(i*10)+"/axlv2_sumspeed_0"+str(i*10)+"-0"+str((i+1)*10)+".dat"
    f2=open(name2)
    s2=f2.readline()
    k2=s2.split()
    summe+=float(k[2])/(5.*24.)
    summe2+=float(k2[2])/(5.*24.)
    hist.append([float(i*10),float(k[2])/(5.*24.),float(k2[2])/(5.*24.)])
    hist2.append([float(i*10),float(k[2])/(5.*24.),float(k2[2])/(5.*24.)])
    f.close()
    f2.close()

#for i in range(len(hist)/2):
#    hist[i*2][1]+=hist[i*2+1][1]
#for i in range(len(hist)/2):
#    hist[i+len(hist)/2][1]+=0.

gphist=Data(hist)
gphist.set_option_colonsep("using", "1:2")
gphist.set_option_colonsep("title",  "'2005'")
gphist2=Data(hist2)
gphist2.set_option_colonsep("using", "1:3")
gphist2.set_option_colonsep("lt","3")
gphist2.set_option_colonsep("title",  "'2002'")

gp=Gnuplot()
gp.plot(gphist,gphist2)

print "summe2005 = ",summe
print "summe2002 = ",summe2
