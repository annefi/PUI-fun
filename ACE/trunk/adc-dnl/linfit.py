#!/usr/bin/python
from scipy import zeros, Float,matrixmultiply
from Gnuplot import Gnuplot, GridData

j=0
f=open("rampg.pha")
# ignore header
f.readline()
f.readline()
f.readline()

xdim=0

for k in f:
    xdim+=1

data=zeros([xdim])



j=-1
f=open("rampg.pha")
# ignore header
f.readline()
f.readline()
f.readline()

for i in f:
    j+=1
    s=i.split()
    data[j]=int(s[1])
    

#cfile=open("tmp.dat", "w")
#for i in range(xdim):
#    cfile.write("%i\t" % i)
#    cfile.write("%f\t" % data[i])
#    cfile.write("\n")

def tstep2bin1(tstep):
    a = 0.000553296
    b = 108.071
    return a*tstep+b

for i in range(xdim):
    if ((tstep2bin1(i)+8.<float(data[i]))):
        data[i]=int(tstep2bin1(i))
        print "corrected step",i
    if ((tstep2bin1(i)-8.>float(data[i]))):
        data[i]=int(tstep2bin1(i))
        print "corrected step",i

#cfile=open("tmp.dat", "w")
#for i in range(xdim):
#    cfile.write("%i\t" % i)
#    cfile.write("%f\t" % data[i])
#    cfile.write("\n")


funct=zeros([xdim],Float)

for i in range(xdim):
    funct[i]=tstep2bin1(i)


#Final set of parameters            Asymptotic Standard Error
#=======================            ==========================
#
#a               = -7.61996e-12     +/- 2.396e-15    (0.03145%)
#b               = 0.000565656      +/- 4.014e-09    (0.0007097%)
#c               = 104.733          +/- 0.00141      (0.001346%)

def tstep2bin2(tstep):
    a = -7.61996e-12     
    b = 0.000565656      
    c = 104.733          

    return a*tstep*tstep+b*tstep+c

funct2=zeros([xdim],Float)

for i in range(xdim):
    funct2[i]=tstep2bin2(i)



gp=Gnuplot()
gp("c=1.")
gp("a=1.")
gp("b=1.")
#gp("set outp X11")
#gp("f(x)=a*x**2+b*x+c")
#gp("fit f(x) 'tmp.dat' via a,b,c")
gp("set data style dots")
gp("set xrange[500000:1000000]")
gp.plot(data,funct2)
    

