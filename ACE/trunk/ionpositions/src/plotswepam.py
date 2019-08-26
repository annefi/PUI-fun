#!/usr/bin/python
from numpy import float
from Gnuplot import Gnuplot,Data,GnuplotOpts

swepamdata=[]
swepampdata=[]
swepamspeed=[]
swepamdatain=open("/data/wimmer/ace/swepam/data/ASCEAAm8aGLn")
s=swepamdatain.readline()
k=s.split()
while (k[0]!="BEGIN" or k[1]!="DATA"):
    s=swepamdatain.readline()
    k=s.split()
    if (len(k)<2):
        k=["*","*"]

for s in swepamdatain:
    k=s.split()
    doy=float(k[1])+float(k[2])/24.+float(k[3])/1440.+float(k[4])/86400.
    if (float(k[0])==2007. and float(k[8])>0. and float(k[10])>0.):
        swepamdata.append([doy,float(k[8])*float(k[10])])
        swepampdata.append([doy,float(k[8])])
        swepamspeed.append([doy,float(k[11])])
swepamdatain.close()

swicsdata=[]
swicsspeed=[]
swicspspeed=[]
aspang=[]
for i in range(160):
    if (i<9):
        doy="00%i"%(i+1)
    if (i>=9 and i<99):
        doy="0%i"%(i+1)
    if (i>=99):
        doy="%i"%(i+1)
    print "doy = ",doy
    tmplistin=open("/data/wimmer/ace/1hdata/2007/"+doy+"/list.in")
    tmplistin.readline()
    for s in tmplistin:
        k=s.split()
        swicsdatain=open("/data/wimmer/ace/1hdata/2007/"+doy+"/res_"+k[0])
#        time=float(k[0][16:20])+float(k[0][21:24])/1000.+float(k[0][25:27])/24./1000.+float(k[0][28:30])/24./1000./60.+float(k[0][31:33])/24./1000./60./60.
        time=float(k[0][21:24])+float(k[0][25:27])/24.+float(k[0][28:30])/24./60.+float(k[0][31:33])/24./60./60.
        for s2 in swicsdatain:
            k2=s2.split()
            if (k2[0]=="He2+"):
                swicsdata.append([time,float(k2[10]),float(k2[11])+float(k2[12])])
                swicsspeed.append([time,float(k2[1])])
        swicsdatain.close()

        swicsdatain=open("/data/wimmer/ace/1hdata/2007/"+doy+"/erg_"+k[0])
        swicsdatain.readline()
        swicsdatain.readline()
        s2=swicsdatain.readline()
        k2=s2.split()
        aspang.append([time,float(k2[2])])
        s2=swicsdatain.readline()
        k2=s2.split()
        swicspspeed.append([time,float(k2[2])])
        swicsdatain.close()

plotaspang=Data(aspang)
plotswepamdata=Data(swepamdata)
plotswepampdata=Data(swepampdata)
plotswicsdata=Data(swicsdata)
plotswepamspeed=Data(swepamspeed)
plotswicsspeed=Data(swicsspeed)
plotswicspspeed=Data(swicspspeed)

plotswepamdata.set_option_colonsep("title", "'SWEPAM'")
plotswepamspeed.set_option_colonsep("with", "lines")
plotswicsdata.set_option_colonsep("with", "points ls 3")
plotswicsdata.set_option_colonsep("title", "'SWICS'")
plotswicsspeed.set_option_colonsep("with", "lines")
plotswicspspeed.set_option_colonsep("with", "lines")
plotaspang.set_option_colonsep("with", "lines")

gp=Gnuplot()
gp("set xrange[0:60]")
gp("set format y '10^{%T}'")
gp("set xlabel 'DoY 2007'")
gp("set ylabel 'He^{2+} Density [1cm^{-3}]'")
#gp("set yrange[0.01:1.]")
gp("set log y")
gp.plot(plotswepamdata,plotswicsdata,plotaspang)
gp("set term postscript color 18 lw 2 eps")
gp.hardcopy("absHedensswepamswics.ps",color=True, fontsize=18)
#gp2=Gnuplot()
#gp2("set xrange[0:60]")
#gp("set yrange[0.01:1.]")
#gp2("set logscale y")
#gp2.plot(plotswepamspeed,plotswicsspeed,plotswicspspeed)
#gp3=Gnuplot()
#gp3("set xrange[0:60]")
#gp("set yrange[0.01:1.]")
#gp2("set logscale y")
#gp3.plot(plotswepampdata)
#gp("set outp 'etslicefastswnew.ps'")
