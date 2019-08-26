#!/usr/bin/python
from scipy import zeros, Float,matrixmultiply
from Gnuplot import Gnuplot, GridData

def tstep2bin1(tstep):
    a = 0.000553296
    b = 108.071
    return a*tstep+b

# Final set of parameters            Asymptotic Standard Error
# =======================            ==========================

# a               = 0.000553296      +/- 3.522e-09    (0.0006365%)
# b               = 108.071          +/- 0.003299     (0.003052%)


def tstep2bin2(tstep):
    a = -7.61996e-12     
    b = 0.000565656      
    c = 104.733          
    return a*tstep*tstep+b*tstep+c



j=0
#f=open("ramp1_cut.pha")
f=open("rampg.pha")
# ignore header
f.readline()
f.readline()
f.readline()

# ignore bogus data
# for i in range(2623): f.readline()

corrmtx=zeros([1024, 1024])
corrmtx_end=zeros([1024,1024],Float)
#for i in f:
#    j+=1
#    s=i.split()
#    corrmtx[int(s[1]), int(tstep2bin1(j))]+=1

for i in f:
    j+=1
    s=i.split()
    if (int(tstep2bin2(j))<int(s[1])+8):
        if (int(tstep2bin2(j))>int(s[1])-8):
            corrmtx[int(s[1]),int(tstep2bin2(j))]+=1
#            corrmtx[int(tstep2bin1(j)),int(s[1])]+=1.


corrmtx_norm=zeros([1024, 1024], Float)
corrmtx_norm2=zeros([1024,1024],Float)

for i in range(1024):
    s=sum(corrmtx[i])
    if (s!=0):
        corrmtx_norm[i]=corrmtx[i]/float(s)
        print "Sum for line #", i, ":", s

for i in range(1024):
    corrmtx_norm2[i]=corrmtx_norm[1023-i]

for i in range(1024):
    for j in range(1024):
        corrmtx_end[i][j]=corrmtx_norm2[1023-j][i]


proj_z=zeros(1024)
proj_s=zeros(1024)


for i in range(1024):
    proj_z[i]=sum(corrmtx[i])

for i in range(1024):
    for j in range(1024):
        proj_s[i]+=corrmtx[j][i]

cmgd=GridData(corrmtx_norm)

gp=Gnuplot()
gp("set pm3d map")

cfile=open("ramp.corr", "w")
for i in range(1024):
    for j in range(1024):
        cfile.write("%f\t" % corrmtx_end[i][j])

    cfile.write("\n")
    

