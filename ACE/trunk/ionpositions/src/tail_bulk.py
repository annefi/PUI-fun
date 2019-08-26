#!/usr/bin/python
from scipy import zeros, sqrt,mean
from Gnuplot import Gnuplot, GridData, GnuplotOpts,Data
from numpy import float
from math import atan
from libacepy.mag import magdata
from libacepy.swicsiondata import swicsiondata
from libacepy.ancil import int2str

GnuplotOpts.prefer_fifo_data=0
GnuplotOpts.prefer_inline_data=0

magpath="/data/kleopatra/ace/mag/"
datapath="/data/wimmer/ace/1hdata/2007/"
dim=58
ion_name=["He2+","C5+","C6+","N6+","N7+","O6+","O7+","O8+","Ne8+","Mg9+","Mg10+","Mg11+","Mg12+","Si8+","Si9+","Si10+","Si11+","Si12+","S8+","S10+","S11+","S12+","Ca9+","Ca10+","Ca11+","Ca12+","Fe8+","Fe9+","Fe10+","Fe11+","Fe12+","Fe13+","Fe14+"]
#"O6+","Ne8+","Mg9+","Si10+","Fe11+","C6+",,"O7+","O8+","N7+",]
#ion_name=["He2+","O6+","C5+","N6+"]
#ion_name=["S8+"]
mass=[]
charge=[]
sis=[[1.96,1.e-2],[15.45,1.e-2],[29.41,1.e-2],[43.45,1.e-2],[58.30,1.e-2],[70.87,1.e-2],[71.30,1.e-2],[71.53,1.e-2],[84.35,1.e-2],[91.10,1.e-2],[99.10,1.e-2],[117.60,1.e-2],[127.70,1.e-2],[127.90,1.e-2],[138.4,1.e-2],[144.00,1.e-2],[152.60,1.e-2],[164.4,1.e-2],[172.40,1.e-2],[184.90,1.e-2]]
A=[[1.96,1.e-2],[29.41,1.e-2],[58.30,1.e-2],[84.35,1.e-2],[111.30,1.e-2],[138.4,1.e-2],[164.4,1.e-2]]
B=[[8.00,1.e-2],[37.00,1.e-2],[62.10,1.e-2],[91.10,1.e-2],[117.60,1.e-2],[144.00,1.e-2],[172.4,1.e-2]]
C=[[15.45,1.e-2],[43.45,1.e-2],[71.30,1.e-2],[99.10,1.e-2],[127.90,1.e-2],[152.6,1.e-2],[180.0,1.e-2]]
D=[[105.90,1.e-2],[135.0,1.e-2],[159.00,1.e-2],[184.9,1.e-2]]
#daylist=[126,127,128,138,139,140]
#daylistst=[1,12,13,14,15,29,41,42,43,44,45,57,58,71,84,89,99,107,112,113,127,138,142,153,163,164,182,185]
#daylist=[1,12,13,14,15,29,41,42,43,44,45,57,58,71,84,89,99,107,112,113,127,138,142,153,163,164,182,185]
timeframest=[[1,2],[12,16],[29,30],[41,46],[57,59],[71,72],[84,85],[89,90],[99,100],[107,108],[112,114],[127,128],[138,139],[142,143],[153,154],[163,165],[182,183],[185,186]]
timeframequiet=[[2,12],[16,29],[30,41],[46,57],[59,71],[72,84],[90,99],[100,107],[108,112],[114,127],[128,138],[139,142],[143,153],[154,163],[165,182],[183,185],[186,190]]
timeframe=[[1,2],[12,16],[29,30],[41,46],[57,59],[71,72],[84,85],[89,90],[99,100],[107,108],[112,114],[127,128],[138,139],[142,143],[153,154],[163,165],[182,183],[185,186]]
timeframe=[[2,12],[16,29],[30,41],[46,57],[59,71],[72,84],[90,99],[100,107],[108,112],[114,127],[128,138],[139,142],[143,153],[154,163],[165,182],[183,185],[186,190]]
timeframest=[[1.,2.3],[9.1,9.6],[11.1,11.5],[12.0,17.1],[27.4,28.3],[28.9,29.9],[40.6,45.0],[56.3,58.7],[64.5,66.1],[70.6,72.1],[82.1,85.1],[88.9,85.1],[88.9,91.4],[97.8,101.1],[107.1,107.8],[111.4,115.3],[117.5,117.9],[125.7,128.6],[137.6,138.9],[141.6,144.6],[150.9,156.1],[160.2,161.5],[162.4,165.9],[172.2,173.2],[180.4,182.1],[183.4,185.9],[190.5,191.]]
timeframequiet=[[2.3,9.1],[9.6,11.1],[11.5,12.0],[17.1,27.4],[28.3,28.9],[29.9,40.6],[45.0,56.3],[58.7,64.5],[66.1,70.6],[72.1,82.1],[85.1,88.9],[85.1,88.9],[91.4,97.8],[101.1,107.1],[107.8,111.4],[115.3,117.5],[117.9,125.7],[128.6,137.6],[138.9,141.6],[144.6,150.9],[156.1,160.2],[161.5,162.4],[165.9,172.2],[173.2,180.4],[182.1,183.4],[185.9,190.0]]
timeframe=[[2.3,9.1],[9.6,11.1],[11.5,12.0],[17.1,27.4],[28.3,28.9],[29.9,40.6],[45.0,56.3],[58.7,64.5],[66.1,70.6],[72.1,82.1],[85.1,88.9],[85.1,88.9],[91.4,97.8],[101.1,107.1],[107.8,111.4],[115.3,117.5],[117.9,125.7],[128.6,137.6],[138.9,141.6],[144.6,150.9],[156.1,160.2],[161.5,162.4],[165.9,172.2],[173.2,180.4],[182.1,183.4],[185.9,190.0]]
#timeframe=[[1.,2.3],[9.1,9.6],[11.1,11.5],[12.0,17.1],[27.4,28.3],[28.9,29.9],[40.6,45.0],[56.3,58.7],[64.5,66.1],[70.6,72.1],[82.1,85.1],[88.9,85.1],[88.9,91.4],[97.8,101.1],[107.1,107.8],[111.4,115.3],[117.5,117.9],[125.7,128.6],[137.6,138.9],[141.6,144.6],[150.9,156.1],[160.2,161.5],[162.4,165.9],[172.2,173.2],[180.4,182.1],[183.4,185.9]]
#timeframe=[[1.,191.]]
daylist=range(81,100)
#timeframe=[[1.,191.]]
plottime=0
plotmq=0
plottemp=0
plotdens=0
plot_dbb=0
plotspth=1
doplotdenstime=0
#mag=magdata(16,2007,float(daylist[0]),float(daylist[len(daylist)-1]),magpath)
swicsdata=[]
spthmq=[]
plotspthmq=[]
    if (plotspth):
        N=0
        spth=0.
        sigspth=0.
        for i in range(len(iondata.suprath)):
            if (iondata.dens[i][0]!=0.):
                N+=1
                spth+=iondata.suprath[i][0]
                sigspth+=(iondata.suprath[i][1])**2
        if (N!=0):
            spth=spth/N
            sigspth=sqrt(sigspth)/N
            spthmq.append([iondata.mass/iondata.charge,spth,sigspth])
            tmpplotspthmq=Data(spthmq)
            #tmpplotspthmq.set_option_colonsep("title", "'%s'"%(iondata.name))
            tmpplotspthmq.set_option_colonsep("with", "errorbars")
            plotspthmq.append(tmpplotspthmq)
        del iondata

if (plotspth):
    #plotspthmq.set_option_colonsep("with", "lines")
    gp=Gnuplot()
    gp("set logscale y")
    #gp("set yrange[0.:0.015]")
    gp("set xrange[1.5:7.5]")
    gp("set xlabel 'm/q'")
    gp("set ylabel 'tail/bulk'")
    gp.plot(plotspthmq[0])
    for ion in range(len(plotspthmq)-1):
        gp.replot(plotspthmq[ion+1])
    gp("set term postscript color 18 lw 2 eps")
    gp.hardcopy("mq_tailbulk_quiet_errors_notitles.ps",color=True, fontsize=18)


if (doplotdenstime):
    dens=[]
    temp=[]
    vel=[]
    spth=[]
    spth2=[]
    for i in range(len(iondata.dens)):
        if (iondata.dens[i][0]!=0.):
            dens.append([iondata.time[i],iondata.dens[i][0]])
            temp.append([iondata.time[i],iondata.temp[i][0]])
            vel.append([iondata.time[i],iondata.vel[i]])
            spth.append([iondata.time[i],iondata.suprath[i][0]])
            spth2.append([iondata.time[i],iondata.suprath[i][0]*iondata.dens[i][0]])
    plotden2=Data(dens)
    #plotden2.set_option_colonsep("title", "'dens'")
    plotden2.set_option_colonsep("with", "lines")
    plottemp2=Data(temp)
    #plottemp2.set_option_colonsep("title", "'temp'")
    plottemp2.set_option_colonsep("with", "lines")
    plotvel=Data(vel)
    #plotvel.set_option_colonsep("title", "'vel'")
    plotvel.set_option_colonsep("with", "lines")
    plotspth2=Data(spth)
    #plotspth2.set_option_colonsep("title", "'spth/dens'")
    plotspth2.set_option_colonsep("with", "lines")
    plotspth3=Data(spth2)
    #plotspth3.set_option_colonsep("title", "'suprathermal dens'")
    plotspth3.set_option_colonsep("with", "lines lt 3")
    gp=Gnuplot()
    gp("set logscale y")
    gp("set xrange[%f:%f]"%(timeframe[0][0],timeframe[0][1]))
    gp("set ylabel 'Density [cm^{-3}]")
#    gp("set ylabel 'dens'")
    gp("set xlabel 'DoY 2007'")
    gp("set format y '10^{%T}'")
    gp.plot(plotden2,plotspth3)
    gp("set term postscript color 18 lw 2 eps")
    gp.hardcopy("%s_dens+spth.ps"%(iondata.name),color=True, fontsize=18)
    del gp
    gp=Gnuplot()
    gp("set logscale y")
    gp("set xrange[%f:%f]"%(timeframe[0][0],timeframe[0][1]))
    gp("set ylabel 'T [K]'")
    gp("set xlabel 'DoY'")
    gp("set format y '10^{%T}'")
    gp.plot(plottemp2)
    gp("set term postscript color 18 lw 2 eps")
    gp.hardcopy("%s_temp.ps"%(iondata.name),color=True, fontsize=18)
    del gp
    gp=Gnuplot()
    gp("set xrange[%f:%f]"%(timeframe[0][0],timeframe[0][1]))
    gp("set ylabel 'V [km^{1}s^{-1}]'")
    gp("set xlabel 'DoY'")
    #gp("set format y '10^{%T}'")
    gp.plot(plotvel)
    gp("set term postscript color 18 lw 2 eps")
    gp.hardcopy("%s_vel.ps"%(iondata.name),color=True, fontsize=18)
    del gp
    gp=Gnuplot()
    gp("set xrange[%f:%f]"%(timeframe[0][0],timeframe[0][1]))
    gp("set logscale y")
    #gp("set yrange[1.e-4:0.1]")
    gp("set ylabel 'SPTHDENS/DENS'")
    gp("set xlabel 'DoY 2007'")
    gp("set format y '10^{%T}'")
    gp.plot(plotspth2)
    gp.hardcopy("%s_tail_bulk.ps"%(iondata.name),color=True, fontsize=18)
    ratioout=open("He2+_tail_bulk.dat","w")
    densout=open("He2+_dens.dat","w")
    spthout=open("He2+_spth.dat","w")
    velout=open("He2+_vel.dat","w")
    tempout=open("He2+_temp.dat","w")
    for i in range(len(iondata.time)):
        ratioout.write("%f\t%f\n"%(iondata.time[i],iondata.suprath[i][0]))
        densout.write("%f\t%f\n"%(iondata.time[i],iondata.dens[i][0]))
        spthout.write("%f\t%f\n"%(iondata.time[i],iondata.suprath[i][0]*iondata.dens[i][0]))
        velout.write("%f\t%f\n"%(iondata.time[i],iondata.vel[i]))
        tempout.write("%f\t%f\n"%(iondata.time[i],iondata.temp[i][0]))
    ratioout.close()
    densout.close()
    spthout.close()
    velout.close()
    tempout.close()
    del iondata
    del plotspth2
    del plotvel
    del plottemp2
    del plotden2


    #,A,B,C,D)
#    gp("set term postscript color 18 lw 2 eps")
#    gp.hardcopy("%sspth2.ps"%(iondata.name),color=True, fontsize=18)
    #del gp

  
#mag.load()
#mag.plot()

#if (plotmq):
#    gp=Gnuplot()
#    gp("set log y")
#    gp("set format y '10^{%T}'")
#    gp("set xrange[1.5:7.5]")
    #gp("set yrange[0.:0.01]")
#    gp("set xlabel 'M/Q")
#    gp("set ylabel 'SPTH/DENS'")
#    gp.plot(plottbrmq[0])
#    for ion in range(len(plottbrmq)-1):
#        gp.replot(plottbrmq[ion+1])
#    gp("set term postscript color 18 lw 2 eps")
#    gp.hardcopy("tailbulk_mq_st.ps",color=True, fontsize=18)
    
if (plottime):
    gp=Gnuplot()
    #gp("set yrange[0.:0.1]")
    gp("set logscale y")
    gp("set xlabel 'DoY")
    gp("set ylabel 'SPTH/DENS'")
    gp.plot(plottbrtime[0])
#    for ion in range(len(plottbrtime)-1):
#        gp.replot(plottbrtime[ion+1])
    gp("set term postscript color 18 lw 2 eps")
    gp.hardcopy("tailbulk_time_st.ps",color=True, fontsize=18)


if (plottemp):
    gptemp=Gnuplot()
#    gptemp("set yrange[0.:0.01]")
    gptemp("set logscale y")
    gptemp("set xlabel 'DoY")
    gptemp("set ylabel 'T'")
    gptemp.plot(plottemptime[0])
#    for ion in range(len(plottemptime)-1):
#        gptemp.replot(plotttemp[ion+1])
    gptemp("set term postscript color 18 lw 2 eps")
    gptemp.hardcopy("temp_time_st.ps",color=True, fontsize=18)
    
if (plotdens):
    gpdens=Gnuplot()
#    gpdens("set yrange[0.:0.01]")
    gpdens("set logscale y")
    gpdens("set xlabel 'DoY")
    gpdens("set ylabel 'Dens'")
    gpdens.plot(plotdenstime[0])
#    for ion in range(len(plotdenstime)-1):
#        gpdens.replot(plottdens[ion+1])
    gpdens("set term postscript color 18 lw 2 eps")
    gpdens.hardcopy("dens_time_st.ps",color=True, fontsize=18)

if (plot_dbb):
    gpdbb=Gnuplot()
#    gpdbb("set yrange[0.:0.01]")
    gpdbb("set logscale y")
    gpdbb("set xlabel 'DoY")
    gpdbb("set ylabel 'dbb'")
    gpdbb.plot(plotdbb)
#    for ion in range(len(plotdbbtime)-1):
#        gpdbb.replot(plottdbb[ion+1])
    gpdbb("set term postscript color 18 lw 2 eps")
    gpdbb.hardcopy("dbb_time_st.ps",color=True, fontsize=18)
