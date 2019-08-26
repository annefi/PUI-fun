import sys
from scipy import zeros, sqrt,mean
from numpy import float
from Gnuplot import Gnuplot, GridData, Data

ion_names = ["O6+"]
paraname1="/data/ivar/berger/testco/ion_para.dat"

ion = 0

mass=zeros([len(ion_names)],float)
charge=zeros([len(ion_names)],float)
points1=[]
xerrorp=[]
xerrorm=[]
yerrorp=[]
yerrorm=[]


f=open(paraname1)

for step in range(1,59):
    s=f.readline()
    k=s.split()
    s=f.readline()
    numpoints1=int(k[5])
    ionda=0
    for i in range(numpoints1):
        s=f.readline()
        m=s.split()
        if (m[0]==ion_names[ion]):
           ionda=1
           points1.append([float(m[1]),float(m[2])])
    if (not ionda):
           points1.append([0.,0.,0.,0.,0.,0.,0.])
           mass[ion]=0.
           charge[ion]=0.

f.close()

for i in range(len(points1)):
    print "%4.1f   %2.1f" % (points1[i][0], points1[i][1])
