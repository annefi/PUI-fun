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

plottemp=[]
for ion in range(len(ion_list)):
    tmptempplot=[]
    for time in range(len(data)):
        for ion2 in range(len(data[time])):
            if (ion_list[ion]==data[time][ion2][0]):
                tmptempplot.append([(279.+time*5.*0.00833),data[time][ion2][3]])
    plottemp.append(Data(tmptempplot))

plotdens=[]
plotdensout=[]
for ion in range(len(ion_list)):
    tmpdensplot=[]
    for time in range(len(data)):
        for ion2 in range(len(data[time])):
            if (ion_list[ion]==data[time][ion2][0]):
                tmpdensplot.append([(279.+time*5.*0.00833),data[time][ion2][7],data[time][ion2][3],data[time][ion2][1],data[time][ion2][1]])
    plotdens.append(Data(tmpdensplot))
    plotdensout.append(tmpdensplot)

for ion in range(len(ion_list)):
    plottemp[ion].set_option_colonsep("title",  "'%s'" %(ion_list[ion]))
    plotdens[ion].set_option_colonsep("title",  "'%s'" %(ion_list[ion]))


                
for ion in range(len(ion_list)):
    datafile=open(ion_list[ion]+".dat","w")
    for time in range(len(plotdensout[ion])):
        for i in range(len(plotdensout[ion][time])):
            if (plotdensout[ion][time][i]!=0.):
                datafile.write("%.4f\t"%(plotdensout[ion][time][i]))
            else:
                datafile.write("%s\t"%("nan"))
        datafile.write("\n")
                             
    datafile.close()
"""
gp=Gnuplot()
gp("set logscale y")
gp.plot(plotdens[0])
for ion in range(len(plotdens)-1):
    gp.replot(plotdens[ion+1])
"""
