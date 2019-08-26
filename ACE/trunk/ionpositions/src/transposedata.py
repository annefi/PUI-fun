#!/usr/bin/python
from scipy import zeros
from numpy import float

xdim=512
ydim=128
dim=58

et_mat_in=zeros([xdim,ydim],float)
et_mat_out=zeros([ydim,xdim],float)

infile=open("/home/ivar/berger/projects/ionpositions/binneddata/axlv2_sumwhol_asp_00.0-15.0_bin.dat")
outfile=open("/home/ivar/berger/projects/ionpositions/binneddata/axlv2_sumwhol_asp_00.0-15.0.dat","w")

s=infile.readline()
outfile.write("*****\n")
for step in range(dim):
    print "step ",step
    s=infile.readline()
    outfile.write("%i\t%i\n"%(ydim,xdim))
    for i in range(xdim):
        s=infile.readline()
        k=s.split()
        for j in range(ydim):
            et_mat_out[j][i]=float(k[j])
    for i in range(ydim):
        for j in range(xdim):
            outfile.write("%.2f "%(float(et_mat_out[i][j])))
        outfile.write("\n")

infile.close()
outfile.close()

        
