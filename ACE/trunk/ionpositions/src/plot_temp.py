#!/usr/bin/python
from scipy import zeros, sqrt,mean
from Gnuplot import Gnuplot, GridData, GnuplotOpts,Data
from numpy import float
from libacepy.readdata import readflux,readres
from libacepy.fluxes import getmaxflux

pathl=open("pathlist2.in")
ion_list=[]
s=pathl.readline()
p=s.split()
liste=open(p[0]+"list.in")
s=liste.readline()
s=liste.readline()
k=s.split()
listeion=readres(p[0]+"res_"+k[0])
for ion in range(len(listeion)-1):
    ion_list.append(listeion[ion+1][0])
print ion_list
pathl.close()
liste.close()

ion_list=["He2+","O6+","O7+","C4+","C5+","C6+","N7+","Fe11+"]

swepamv=[]
swepamt=[]
swepamd=[]
swepamr=[]
swepamin=open("Swepamd279-289y200516min.dat")
for s in swepamin:
    k=s.split()
    swepamv.append([float(k[0]),float(k[4])])
    swepamt.append([float(k[0]),float(k[2])])
    swepamd.append([float(k[0]),float(k[1])])
    swepamr.append([float(k[0]),float(k[3])])

plotswepamv=Data(swepamv)
plotswepamt=Data(swepamt)
plotswepamd=Data(swepamd)
plotswepamr=Data(swepamr)
plotswepamv.set_option_colonsep("title",  "'SWEPAM H1+'")
plotswepamt.set_option_colonsep("title",  "'SWEPAM H1+'")
plotswepamd.set_option_colonsep("title",  "'SWEPAM H1+'")
plotswepamr.set_option_colonsep("title",  "'SWEPAM He2+/H1+'")

pathl=open("pathlist2.in")
data=[]
print "readinding data"
for s in pathl:
    p=s.split()
    liste=open(p[0]+"list.in")
    s2=liste.readline()
    for s2 in liste:
        filen=s2.split()
        tmpdata=readres(p[0]+"res_"+filen[0])
        data.append(tmpdata)
    print "finished reading",p[0]

plotvel=[]
for ion in range(len(ion_list)):
    tmpvelplot=[]
    for time in range(len(data)):
        for ion2 in range(len(data[time])):
            if (ion_list[ion]==data[time][ion2][0]):
                tmpvelplot.append([(279.+time*5.*0.00833),data[time][ion2][1]])
    plotvel.append(Data(tmpvelplot))


plottemp=[]
for ion in range(len(ion_list)):
    tmptempplot=[]
    for time in range(len(data)):
        for ion2 in range(len(data[time])):
            if (ion_list[ion]==data[time][ion2][0]):
                tmptempplot.append([(279.+time*5.*0.00833),data[time][ion2][3]])
    plottemp.append(Data(tmptempplot))

plotdens=[]
for ion in range(len(ion_list)):
    tmpdensplot=[]
    for time in range(len(data)):
        for ion2 in range(len(data[time])):
            if (ion_list[ion]==data[time][ion2][0]):
                tmpdensplot.append([(279.+time*5.*0.00833),data[time][ion2][7]])
    plotdens.append(Data(tmpdensplot))

for ion in range(len(ion_list)):
    plottemp[ion].set_option_colonsep("title",  "'%s'" %(ion_list[ion]))
    plotdens[ion].set_option_colonsep("title",  "'%s'" %(ion_list[ion]))
    plotvel[ion].set_option_colonsep("title",  "'%s'" %(ion_list[ion]))


gp=Gnuplot()
gp("set logscale y")
#gp("set yrange[0.00001:100]")
gp.plot(plotswepamd)
for ion in range(len(plotdens)):
    gp.replot(plotdens[ion])
gp.replot(plotswepamr)
gp("set xlabel 'DoY'")
gp("set ylabel 'Density [1/cm^{3}]'")
gp("set title ''")
gp("set term postscript color 18 lw 3 eps")
gp.hardcopy("density.ps", color=True, fontsize=18)

"""
gp.plot(plotswepamt)
for ion in range(len(plottemp)):
    gp.replot(plottemp[ion])
gp("set xlabel 'DoY'")
gp("set ylabel 'T [K]'")
gp("set title ''")
gp("set term postscript color 18 lw 3 eps")
gp.hardcopy("temperature.ps", color=True, fontsize=18)
"""
"""
gp("unset logscale y")
gp("set yrange[250:800]")
gp.plot(plotswepamv)
for ion in range(len(plotvel)):
    gp.replot(plotvel[ion])
gp("set xlabel 'DoY'")
gp("set ylabel 'V [Km/s]'")
gp("set title ''")
gp("set term postscript color 18 lw 3 eps")
gp.hardcopy("velocity.ps", color=True, fontsize=18)
"""
