#!/usr/bin/python
from scipy import zeros, sqrt,mean
from Gnuplot import Gnuplot, GridData, GnuplotOpts,Data
from numpy import float
from math import pi
GnuplotOpts.prefer_fifo_data=0
GnuplotOpts.prefer_inline_data=0

ergpath="/data/wimmer/ace/1hdata/2007/029/"
#ergname=ergpath+"erg_axlv2_2007002_004_1h.dat"

dim=58

ion_name="Ne7+"

ergl=open(ergpath+"list.in")
s=ergl.readline()
k=s.split()
numberfiles=int(k[0])

allfiles=[]
for s1 in ergl:
    k=s1.split()
    resname=ergpath+"res_"+k[0]
    ergname=ergpath+"flux_"+k[0]
    f=open(resname)
    s=f.readline()
    k=s.split()
    while (k[0]!=ion_name):
        s=f.readline()
        k=s.split()
    ionvel=float(k[1])
    f.close()
    counts=[]
    f=open(ergname)
    k=["*"]
    while (k[0]!=ion_name):
        s=f.readline()
        k=s.split()
    s=f.readline()
    s=f.readline()
    s=f.readline()
    for step in range(dim):
        s=f.readline()
        k=s.split()
        counts.append([float(k[0])/ionvel,float(k[7]),float(k[8])])
    maxdens=0.
    for i in range(len(counts)):
        if (counts[i][1]>maxdens):
            maxdens=counts[i][1]
#    if (maxdens!=0.):
#        for i in range(len(counts)):
#            counts[i][1]=counts[i][1]/maxdens
#            counts[i][2]=counts[i][2]/maxdens

    plotcounts=Data(counts)
    allfiles.append(plotcounts)
    f.close()


i=18
j=20
allfiles[i].set_option_colonsep("title", "'Data 18:00-19:00'")
allfiles[j].set_option_colonsep("title", "'Data 20:00-21:00'")
allfiles[i].set_option_colonsep("with", "errorbars")
allfiles[j].set_option_colonsep("with", "errorbars")
allfiles[i].set_option_colonsep("using", "1:2:3")
allfiles[j].set_option_colonsep("using", "1:2:3")
gp=Gnuplot()
gp("set log y")
gp("set log x")
gp("set xrange[0.9:2.]")
gp("set yrange[1e-12:1e-6]")
gp("set xlabel 'V/V_{Bulk}'")
gp("set ylabel 'Differential Density [cm^{-3}m^{-1}s^{1}]'")
gp("ph=1.e-6")
gp("x0=1.")
gp("vth=.15*x0")
gp("f(x)= ph*sqrt(1./(2.*pi*sqrt(vth)))*exp(-((x-x0)**2.)/(2.*vth**2))")
gp("fit f(x) '"+allfiles[i].filename+"' using 1:2 via ph")
gp("fit f(x) '"+allfiles[i].filename+"' using 1:2 via vth")
gp("ph2=1.e-6")
gp("x02=1.")
gp("vth2=.15*x0")
gp("g(x)= ph2*sqrt(1./(2.*pi*sqrt(vth2)))*exp(-((x-x02)**2.)/(2.*vth2**2))")
gp("fit g(x) '"+allfiles[j].filename+"' using 1:2 via ph2")
gp("fit g(x) '"+allfiles[j].filename+"' using 1:2 via vth2")
first=1
gp("set xrange[0.9:5.]")
gp("set yrange[1e-12:1e-6]")
gp("set xtics 1,2")

gp.plot(allfiles[i],"f(x) title 'Maxwell-Fit 18:00-19:00'")
gp.replot(allfiles[j],"g(x) title 'Maxwell-Fit 20:00-21:00'")
gp("set term postscript color 18 lw 2 eps")
gp.hardcopy("vdfs.ps",color=True, fontsize=18)
#for k in range(23):
#    gp.replot(allfiles[i+k+1])

#for i in range(len(allfiles)):
#    if (first):
#        gp.plot(allfiles[i])
#        first=0
#    else:
#        gp.replot(allfiles[i])
                      
                      
