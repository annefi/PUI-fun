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


    
    
f=open("/home/kleopatra/mu/daten/giessen/swxli493.pha")
p=open("/home/kleopatra/mu/daten/giessen/swxli12.pha")

print "loading data"

data=zeros([1024,256],Float)
data2=zeros([1024,256],Float)
ssd=zeros([3],Float)


#read data from f
for i in range(3):
    f.readline()

for i in f:
    s=i.split()
    data[int(s[1]),int(s[0])]+=1
    if int(s[2]) == 1:
        ssd[0]+=1
    if int(s[2]) == 2:
        ssd[1]+=1   
    if int(s[2]) == 3:
        ssd[2]+=1

print ssd[0]
print ssd[1]
print ssd[2]   

#read data from p
#for i in range(3):
#    p.readline()

#for i in p:
#    s=i.split()
#    data[int(s[1]),int(s[0])]+=1

datagrid=GridData(data)
data2grid=GridData(data)

gp=Gnuplot()
gp("set logscale z")
gp("set zrange[1:80]")
#gp("set palette rgbformula -3,-3,-3")
#gp("test palette")
gp("set xrange[350:650]")
gp("set yrange[0:50]")

gp("set pm3d map")
gp.splot(datagrid,data2grid)
#gp("set term postscript")
#gp("set outp X11")
#gp("set data style line")
#gp("set xrange[580:800]")
#gp.plot(summe,corrsumme)
#gp.plot(summe,corrsumme, corrsumme_left)

#example how to write a file

#cfile=open("ramp.corr", "w")
#for i in range(1024):
#    for j in range(1024):
#        cfile.write("%f\t" % corrmtx_norm[i,j])
#    cfile.write("\n")
    

