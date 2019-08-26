#!/usr/bin/python
from scipy.linalg import inv
from scipy import zeros, Float, matrixmultiply
from Gnuplot import Gnuplot, GridData

def tstep2bin1(tstep):
    a = 0.000553296
    b = 108.071
    return a*tstep+b

# Final set of parameters            Asymptotic Standard Error
# =======================            ==========================

# a               = 0.000553296      +/- 3.522e-09    (0.0006365%)
# b               = 108.071          +/- 0.003299     (0.003052%)


f=open("/home/ivar/berger/projects/SWICS/trunk/adc-dnl/ramp.corr")
print "loading ramp.corr"
corrmat=zeros([1024,1024],Float)

j=-1
for k in f:
    j+=1
    s=k.split()
    print j
    print len(s)
    if (len(s)>1):
        for l in range(len(s)):
        
            corrmat[j][l]=float(s[l])

#for i in range(1024):
#    m=0
#    for j in range(1024):
#        if (corrmat[i][j]!=0.):
#            m=1
#
#    if (m==0):
#        print i+1,".zeile diag=1"
#        corrmat[i][i]=1.
    
#f=open("/data/ivar/work/oneyeardata/2001/axlv2_sumwhol_asp_07.0-08.0.dat")
f=open("/home/kleopatra/mu/daten/giessen/swxli14.pha")
p=open("/home/kleopatra/mu/daten/giessen/swxli12.pha")

print "loading 2001 data"
data=zeros([1024,256],Float)
summe=zeros([1024],Float)
data2=zeros([1024,256],Float)

#read flight data
#for i in range(30):
#    # ignore header
#    k=f.readline()
#    
#    for j in range(1024):
#        k=f.readline()
#        s=k.split()
#        for l in range(256):
#            data[j][l]=float(s[l])
for i in range(3):
    f.readline()

for i in f:
    s=i.split()
    data[int(s[1]),int(s[0])]+=1

for i in range(3):
    p.readline()

for i in p:
    s=i.split()
    data[int(s[1]),int(s[0])]+=1



for i in range(1024):
    for j in range(256):
        summe[i]+=data[i][j]

f=open("/data/ivar/work/oneyeardata/2002/axlv2_sumwhol_asp_07.0-08.0.dat")
print "2"
data2=zeros([1024,256],Float)
summe2=zeros([1024],Float)

for i in range(30):
    # ignore header
    k=f.readline()

    for j in range(1024):
        k=f.readline()
        s=k.split()
        for l in range(256):
            data2[j][l]=float(s[l])

for i in range(1023):
    for j in range(256):
        summe2[i]+=data2[i][j]


# f=open("/data/ivar/work/oneyeardata/2003/axlv2_sumwhol_asp_07.0-08.0.dat")
# print "3"
# data3=zeros([1024,256],Float)
# summe3=zeros([1024],Float)

# for i in range(30):
#     # ignore header
#     k=f.readline()
    
#     for j in range(1024):
#         k=f.readline()
#         s=k.split()
#         for l in range(256):
#             data3[j][l]=float(s[l])

# for i in range(1024):
#     for j in range(256):
#         summe3[i]+=data3[i][j]

# f=open("/data/ivar/work/oneyeardata/2004/axlv2_sumwhol_asp_07.0-08.0.dat")
# print "4"
# data4=zeros([1024,256],Float)
# summe4=zeros([1024],Float)

# for i in range(30):
#     # ignore header
#     k=f.readline()
    
#     for j in range(1024):
#         k=f.readline()
#         s=k.split()
#         for l in range(256):
#             data4[j][l]=float(s[l])

# for i in range(1024):
#     for j in range(256):
#         summe4[i]+=data4[i][j]

#corrsumme=matrixmultiply(summe,corrmat)
corrsumme=matrixmultiply(summe,corrmat)
corrsumme2=matrixmultiply(summe2,corrmat)
corrsumme3=zeros([1024],Float)

for i in range(0,1022):
    corrsumme3[i]=corrsumme[i+2]

cmgd=GridData(data)
data2grid=GridData(data)

gp=Gnuplot()
#gp("set logscale z")
#gp("set zrange[1:80]")
#gp("set palette rgbformula -3,-3,-3")
#gp("test palette")
#gp("set xrange[400:800]")
#gp("set yrange[0:50]")

gp("set pm3d map")
gp.splot(cmgd,data2grid)
gp("set term postscript color")
gp("set outp 'correct.ps'")
gp("set data style line")
gp("set xrange[500:600]")
gp.plot(summe,corrsumme)
#gp.plot(summe,corrsumme, corrsumme_left)

#cfile=open("ramp.corr", "w")
#for i in range(1024):
#    for j in range(1024):
#        cfile.write("%f\t" % corrmtx_norm[i,j])
#    cfile.write("\n")
    

