#!/usr/bin/python
from scipy import zeros
from Gnuplot import Gnuplot, GridData, Data
from numpy import float

xdim=512
ydim=128
neq=58

sumdata=zeros([neq,xdim,ydim],float)

#the next two lines are used if aspectangle intervalls are summed up
#filenamebase="axlv2_sumwhol_asp_"      
#filenameend="_bin.dat"

filenamebase="axlv2_sumwhol_21_"

listin=open("/home/ivar/berger/projects/ionpositions/src/sumlist.dat")


for i in range(3):
#the next ten lines are used if aspectangle intervalls are summed up
#    if i < 10:
#        if i+1 < 10:
#            tmpname="0"+str(i)+".0-0"+str(i+1)+".0"
#        else:
#            tmpname="0"+str(i)+".0-"+str(i+1)+".0"
#        
#    else:
#        tmpname=str(i)+".0-"+str(i+1)+".0"
#    filename=filenamebase+tmpname+filenameend
#    f=open("/home/asterix/berger/projects/ionpositions/"+filename)


    s=listin.readline()
    k=s.split()
    filename=k[0]
    f=open("/home/ivar/berger/projects/ionpositions/binneddata/"+filename)

    for i in range(neq):
        f.readline()
        for l in range(xdim):
            linestr=f.readline()
            linedat=linestr.split()
#            print len(linedat)
            for  m in range(ydim):
                sumdata[i][l][m]+=float(linedat[m])
    f.close()

cfile=open(filenamebase+"sum.dat", "w")

for i in range(neq):
    cfile.write("%d\t" % xdim)
    cfile.write("%d\t" % ydim)
    cfile.write("\n")
    for j in range(xdim):
        for l in range(ydim):
            cfile.write("%f\t" % sumdata[i][j][l])
        cfile.write("\n")
cfile.close()


    
    
    
