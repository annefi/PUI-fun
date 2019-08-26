#!/usr/bin/python
from scipy import zeros, sqrt,mean
from Gnuplot import Gnuplot, GridData, GnuplotOpts,Data
from numpy import float
from math import atan

GnuplotOpts.prefer_fifo_data=0
GnuplotOpts.prefer_inline_data=0

def getbulkdens(data):
    diff=100.
    bulkpos=0
    for i in range(len(data)):
        if (sqrt((1.-data[i][0])**2)<diff):
            diff=sqrt((1.-data[i][0])**2)
            bulkpos=i
    return data[bulkpos][1]

def gettaildens(data):
    tailsum=0.
    for i in range(len(data)):
        if (data[i][0]>=1.5 and data[i][0]<=1.69):
            tailsum+=data[i][1]
    return tailsum



dim=58

ion_name=["He2+","O6+","Ne8+","Mg9+","Si10+","Fe11+"]
ion_name=["O7+","O6+"]
#ergpath="/data/wimmer/ace/12mdata/2007/"
ergpath="/data/wimmer/ace/1hdata/2007/"
startdoy=1
stopdoy=60
allionmuflux=[]
for ion in range(len(ion_name)):
    allmuflux=[]
    for doy in range(startdoy,stopdoy+1):
        print doy
        if (doy<10):
            doystr="00"+str(doy)
        if (doy>9 and doy<100):
            doystr="0"+str(doy)
        if (doy>99):
            doystr=str(doy)
        ergdaypath=ergpath+doystr+"/"

        ergl=open(ergdaypath+"list.in")
        s=ergl.readline()
        k=s.split()
        numberfiles=int(k[0])

        # load data
        mudayflux=[]
        hour=0
        for s1 in ergl:
            hour+=1
            k=s1.split()
            resname=ergdaypath+"res_"+k[0]
            ergname=ergdaypath+"flux_"+k[0]
            f=open(resname)
            s=f.readline()
            k=s.split()
            while (k[0]!=ion_name[ion]):
                s=f.readline()
                k=s.split()
            muflux=[float(k[7]),float(k[9])]
            f.close()
            mudayflux.append(muflux)
        allmuflux.append(mudayflux)
    
    allionmuflux.append(allmuflux)

muratio=[]
mu1=[]
mu2=[]
for i in range(len(allionmuflux[0])):
    for j in range(len(allionmuflux[0][i])):
        time=float(startdoy)+float(i)+float(j)/24.+1./48.
        if (allionmuflux[1][i][j][0]!=0. and allionmuflux[0][i][j][0]!=0.):
            muratio.append([time,sqrt((((allionmuflux[0][i][j][0]+allionmuflux[0][i][j][1])/(allionmuflux[1][i][j][0]+allionmuflux[1][i][j][1])-(allionmuflux[0][i][j][0]/allionmuflux[1][i][j][0]))/(allionmuflux[0][i][j][0]/allionmuflux[1][i][j][0]))**2)])
            mu1.append([time,(allionmuflux[0][i][j][1]/allionmuflux[0][i][j][0])])
            mu2.append([time,(allionmuflux[1][i][j][1]/allionmuflux[1][i][j][0])])
plotratio=Data(muratio)
plotmu1=Data(mu1)
plotmu2=Data(mu2)
# calculate tail/bulk
#for sp in plotspth:
#    sp.set_option_colonsep("with", "lines ls 3")
#plotspth.set_option_colonsep("with", "lines")
#gp=Gnuplot()
#gp.plot(plotvel,plotmach)
#gp("set log y")
#gp("set log x")
#first=1
#i=1
#gp.plot(dayfiles[i])
#for k in range(4):
#    gp.replot(dayfiles[i+k+1])

gp2=Gnuplot()
gp2("set log y")
gp2("set format y '10^{%T}'")

gp2("set xrange[1:60]")
gp2("set xlabel 'DoY 2007")
gp2("set ylabel 'relative flux error'")
#gp2("set ylabel 'Solar Wind Speed [km^{1}s^{-1}]")
plotratio.set_option_colonsep("with", "lines")
plotratio.set_option_colonsep("title", "'O^{7+}/O^{6+}'")
plotmu1.set_option_colonsep("with", "lines")
plotmu1.set_option_colonsep("title", "'O^{7+}'")
plotmu2.set_option_colonsep("with", "lines")
plotmu2.set_option_colonsep("title", "'O^{6+}'")
gp2.plot(plotratio,plotmu1,plotmu2)
#gp2("set yrange[1.e-7:1.]")
#first=1
#for i in range(len(plotspth)):
#    plotspth[i].set_option_colonsep("title", "'%s'"%(ion_name[i]))
#    if (first==1):
#        plotspth[i].set_option_colonsep("with", "lines")
#        gp2.plot(plotspth[i])
#        first=0
#    else:
#        gp2.replot(plotspth[i])
                      
gp2("set term postscript color 18 lw 2 eps")
gp2.hardcopy("o7o6ratio.ps",color=True, fontsize=18)
                   
