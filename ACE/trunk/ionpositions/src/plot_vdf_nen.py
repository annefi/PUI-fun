#!/usr/bin/python
from scipy import zeros, sqrt,mean
from Gnuplot import Gnuplot, GridData, GnuplotOpts,Data
from numpy import float
from math import pi
GnuplotOpts.prefer_fifo_data=0
GnuplotOpts.prefer_inline_data=0

ergpath="/data/wimmer/ace/1hdata/2007/030/"
#ergname=ergpath+"erg_axlv2_2007002_004_1h.dat"

dim=58

ion_name="Ne7+"
ion_name2="O6+"

ergl=open(ergpath+"list.in")
s=ergl.readline()
k=s.split()
numberfiles=int(k[0])

ionvelarr=[]
allfiles=[]
dcounts=[]
sumcounts=[]
for s1 in ergl:
    k=s1.split()
    resname=ergpath+"res_"+k[0]
    ergname=ergpath+"flux_"+k[0]
    f=open(resname)
    s=f.readline()
    k=s.split()
    while (k[0]!=ion_name2):
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
        counts.append([(float(k[0])),float(k[1]),float(k[2])])
    maxdens=0.
    for i in range(len(counts)):
        if (counts[i][1]>maxdens):
            maxdens=counts[i][1]
            #    if (maxdens!=0.):
            #        for i in range(len(counts)):
            #            counts[i][1]=counts[i][1]/maxdens
            #            counts[i][2]=counts[i][2]/maxdens
    ionvelarr.append(ionvel)
    dcounts.append(counts)
    plotcounts=Data(counts)
    allfiles.append(plotcounts)
    f.close()

offs=10
for step in range(dim):
    tmpcounts=0.
    tmperrors=0.
    for i in range(1):
        tmpcounts+=dcounts[i+offs][step][1]
        tmperrors+=dcounts[i+offs][step][2]**2
    sumcounts.append([dcounts[offs][step][0],tmpcounts,sqrt(tmperrors)])

plotsumcounts=Data(sumcounts)
plotsumcounts.set_option_colonsep("using", "1:2:3")
plotsumcounts.set_option_colonsep("with", "errorbars")

i=18
j=20
allfiles[i].set_option_colonsep("title", "'Data 18:00-19:00'")
allfiles[j].set_option_colonsep("title", "'Data 20:00-21:00'")
allfiles[i].set_option_colonsep("with", "errorbars")
allfiles[j].set_option_colonsep("with", "errorbars")
allfiles[i].set_option_colonsep("using", "1:2:3")
allfiles[j].set_option_colonsep("using", "1:2:3")
print "ionvel = ",ionvel
gp=Gnuplot()
gp("set log y")
#gp("set log x")
#gp("set xrange[250:400]")
#gp("set xrange[0.8:1.5]")
gp("set yrange[1e-1:1e5]")
gp("set xlabel 'V/V_{Bulk}'")
gp("set ylabel 'Differential Density [cm^{-3}m^{-1}s^{1}]'")
gp("ph=1000")
gp("x0=%f/1.035"%(ionvelarr[offs]))
gp("vth=.03*x0")
gp("f(x)= ph*sqrt(1./(2.*pi*sqrt(vth)))*exp(-((x-x0)**2.)/(2.*vth**2))")
#gp("fit f(x) '"+allfiles[i].filename+"' using 1:2 via ph")
#gp("fit f(x) '"+allfiles[i].filename+"' using 1:2 via vth")
gp("ph2=10")
gp("x02=%f"%(ionvelarr[offs]))
gp("vth2=.03*x0")
gp("g(x)= ph2*sqrt(1./(2.*pi*sqrt(vth2)))*exp(-((x-x02)**2.)/(2.*vth2**2))")
gp("h(x)=f(x)+g(x)")
gp("fit h(x) '"+plotsumcounts.filename+"' using 1:2:3 via ph,ph2")
gp("fit h(x) '"+plotsumcounts.filename+"' using 1:2:3 via vth,vth2")
first=1
#gp("set xrange[0.9:5.]")
#gp("set yrange[1e-12:1e-6]")
#gp("set xtics 1,2")

gp.plot(plotsumcounts,"h(x)","f(x)","g(x)")
#gp.plot(allfiles[i],"h(x)")
#gp.replot(allfiles[j],"g(x) title 'Maxwell-Fit 20:00-21:00'")
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
                      
                      
