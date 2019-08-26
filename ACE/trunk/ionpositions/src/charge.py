#!/usr/bin/python
from scipy import zeros, Float, matrixmultiply,exp,sqrt,mean,median
from Gnuplot import Gnuplot, GridData, Data

e_nuc=[5.,10.,15.,20.,25.,30.,35.]
charge=[0.05,0.15,0.21,0.3,0.36,0.42,0.48]


cfile=open("tmpcharge.dat", "w")
for i in range(7):
    cfile.write("%f\t" % e_nuc[i])
    cfile.write("%f\t" % charge[i])
    cfile.write("\n")
cfile.close()

gp=Gnuplot()
#gp=("set xrange[0.:50.]")
#gp=("set yrange[0.:0.5]")
gp("a=1.")
gp("b=0.1")
gp("f(x)=a*x+b")
gp("fit f(x) 'tmpcharge.dat' using 1:2 via a,b")
gp("plot 'tmpcharge.dat' using 1:2,f(x)")
