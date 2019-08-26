#!/usr/bin/python
from scipy import zeros, sqrt,mean
from Gnuplot import Gnuplot, GridData, GnuplotOpts,Data
from numpy import float
from libacepy.readdata import readflux,readres

GnuplotOpts.prefer_fifo_data=0
GnuplotOpts.prefer_inline_data=0

parain="/data/wimmer/berger/cir/2005279_1h/res_axlv2_et_slices_279_250.dat"
filein="/data/wimmer/berger/cir/2005279_1h/flux_axlv2_et_slices_279_250.dat"
data=readflux(filein)
para=readres(parain)

hepara=[]
for ion in range(len(para)):
    if (para[ion][0]=="He2+"):
        hepara.append([para[ion][1]*1000.,para[ion][3],para[ion][6]])

hedata=[]
for step in range(len(data)):
    for ion in range(len(data[step])):
        if (data[step][ion][0]=="He2+"):
            hedata.append([data[step][ion][7]*1000.,data[step][ion][13]])

print hepara
print hedata
heplotdata=Data(hedata)
gp=Gnuplot()
#gp("set logscale x")
gp("set logscale y")
gp("set xrange[250000.:500000.]")
gp("set yrange[0.0000000001:0.0001]")
gp("pi = 3.14159265")
gp("kb = 1.38065*10.**(-23)")
gp("u = 1.660538*10.**(-27)")
gp("m = 4.*u")
gp("T=%f"%(hepara[0][1]))
gp("x0=%f"%(hepara[0][0]))
gp("ph = %f"%(hepara[0][2]))
gp("f(x)= ph*sqrt(m/(2.*pi*kb*T))*exp(-(m*(x-x0)**2.)/(2.*kb*T))")
gp("set xlabel 'V [m/s]'")
gp("set ylabel 'density [1/cm^{3}]'")
gp("set title 'VDF He2+ (1 hour data)'")
gp.plot(heplotdata,"f(x) t 'Fit : Vbulk=%.2fkm/s, T=%.0fK, Dens=%.3f1/cm^{3}'"%(hepara[0][0]/1000.,hepara[0][1],hepara[0][2]))
gp("set term postscript color 18 lw 3 eps")
gp.hardcopy("vdf.ps", color=True, fontsize=18)
