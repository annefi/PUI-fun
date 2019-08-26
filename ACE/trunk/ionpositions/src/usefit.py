#!/usr/bin/python
from scipy import zeros, Float, matrixmultiply,exp,sqrt,sin
from Gnuplot import Gnuplot, GridData, Data

# Program to add fitdata to ion_pos.dat file


dim=58

def exptpos1(step):
    a = -0.00476164
    b = -959.584   
    c = 1040.95    
    d = -0.103916  
    e = 0.79389  
    f = -7.35022    
    return b*exp(a*step)+c
#+d*sin(e*step+f)

#def exptpos1(step):
#    a = -0.003538
#    b = -1283.57
#    c = 1364.98
#    return b*exp(a*step)+c

def exptpos2(step):
    a = -0.0506351
    b = -76.9247
    c = 172.981
    d = 0.356002  
    e = 0.194379    
    f = -5.83995    
    return b*exp(a*step)+c
#+d*sin(e*step+f)

#def exptpos2(step):
#    a = -0.0506339
#    b = -76.9244
#    c = 172.981
#    return b*exp(a*step)+c

def expepos1(step):
    a = -0.151852
    b = 33.2131
    c = 7.98771
    return b*exp(a*step)+c

def expepos2(step):
    a = -0.0860719
    b = 16.1329
    c = 7.97259
    return b*exp(a*step)+c

tposfit=zeros([58],Float)
eposfit=zeros([58],Float)

for i in range(11):
    tposfit[i]=exptpos1(i)
    eposfit[i]=expepos1(i)

for i in range(11,dim):
    tposfit[i]=exptpos2(i)
    eposfit[i]=expepos2(i)


f=open("/home/asterix/berger/projects/ionpositions/ion_pos.dat")
outfile=open("/home/asterix/berger/projects/ionpositions/ion_pos_fit.dat","w")


for i in range(dim):
    line=f.readline()
    outfile.write(line)
    line=f.readline()
    outfile.write(line)
    line=f.readline()
    linedat=line.split()
    linedat[3]=str(tposfit[i])
    linedat[4]=str(eposfit[i])
    for j in range(len(linedat)):
        outfile.write("%s\t" % linedat[j])
    outfile.write("\n")
    line=f.readline()
    outfile.write(line)
    line=f.readline()
    outfile.write(line)


for i in range(6):
    line=f.readline()
    outfile.write(line)

outfile.close()


