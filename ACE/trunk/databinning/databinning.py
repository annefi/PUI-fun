#!/usr/bin/python
from scipy import zeros 
from numpy import float
neq=58
XDIM_DATA=1024
YDIM_DATA=256
XBIN=2
YBIN=2
XDIM=XDIM_DATA/XBIN
YDIM=YDIM_DATA/YBIN
print XDIM,YDIM
plot_mat=zeros([XDIM,YDIM],float)
#pathr="/home/ivar/berger/projects/SWICS/trunk/america/runs/2004_041_1d/"
#pathw="/home/ivar/berger/projects/SWICS/trunk/databinning/"

liste=open("databinning.in")
s=liste.readline()
k=s.split()
pathr=k[0]
print "pathr = ",pathr
s=liste.readline()
k=s.split()
pathw=k[0]
print "pathw = ",pathw
s=liste.readline()
k=s.split()
year=k[0]
intervall=k[1]
for s in liste:
    k=s.split()
    namer=pathr+k[0]
    print "reading ",k[0]
    namew=pathw + "axlv2_"+ year + k[0][16:23]+"_"+intervall+".dat"    
    
#namer=pathr + "axlv2_et_slices_079_957.dat"
#namew=pathw + "axlv2_"+ year + k[0][17:23]+"_"+intervall+".dat"    
    f=open(namer)    
    et_mat_bin=zeros([neq,XDIM,YDIM_DATA],float)
    et_mat_bin_xy=zeros([neq,XDIM,YDIM],float)
    for i in range(neq):
#        print "reading step",i
        read_et_mat_tmp=zeros([XDIM_DATA,YDIM_DATA],float)
        line=f.readline()
        line=f.readline()
        line=f.readline()
        line=f.readline()
        for j in range(XDIM_DATA):
            line=f.readline()
            linedat=line.split()
            for k in range(YDIM_DATA):
                read_et_mat_tmp[j][k]=float(linedat[k])                
        for l in range(YDIM_DATA):
            et_mat_bin[i][0][l]=read_et_mat_tmp[0][l]
            for m in range(1,XDIM-1):
                for k in range(XBIN): 
                    et_mat_bin[i][m][l]+=read_et_mat_tmp[(m*XBIN)-k][l]                   
        for l in range(XDIM):
            et_mat_bin_xy[i][l][0]=et_mat_bin[i][l][0]
            for m in range(1,YDIM-1):
                for k in range(YBIN):
                    et_mat_bin_xy[i][l][m]+=et_mat_bin[i][l][(m*YBIN)-k]
    f.close()
    cfile=open(namew,"w")
    print "writing = ",namew
    for i in range(neq):
        cfile.write("%d\t" % XDIM)
        cfile.write("%d\t" % YDIM)
        cfile.write("\n")
        for j in range(XDIM):
            for k in range(YDIM):
                cfile.write("%f\t" % et_mat_bin_xy[i][j][k])
            cfile.write("\n")
    cfile.close()
