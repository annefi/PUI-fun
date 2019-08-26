#!/usr/bin/python
from scipy import zeros, sqrt,mean
from Gnuplot import Gnuplot, GridData, GnuplotOpts,Data
from numpy import float

GnuplotOpts.prefer_fifo_data=0
GnuplotOpts.prefer_inline_data=0

ergpath="/data/ivar/berger/work/america/runs/2005307-310_speed640/"
#ergname=ergpath+"erg_axlv2_2007002_004_1h.dat"

dim=58
xdim=512
ydim=128

epq_arr=zeros([dim],float)
epq_arr=[86.6359,75.0485,65.0109,56.3158,48.7837,42.2589,36.6069,31.7108,27.4695,23.7955,20.6129,17.856,16.619,15.4678,14.3962,13.399,12.4708,11.6069,10.8028,10.0545,9.35797,8.70971,8.10635,7.5448,7.02214,6.5357,6.08294,5.66156,5.26936,4.90433,4.56459,4.24839,3.95409,3.68017,3.42523,3.18796,2.96711,2.76157,2.57027,2.39222,2.2265,2.07226,1.92871,1.7951,1.67075,1.55501,1.44729,1.34703,1.25372,1.16687,1.08603,1.0108,0.940778,0.875607,0.81495,0.758496,0.705952,0.657048,0.611532,0.55]

ion_list=["He2+","O6+","Fe9+","Fe10+","Fe11+","C4+","C5+","C6+","H1+"]
#ion_list=["C4+","C5+","C6+"]
#ion_list=["O6+","O7+","O8+"]
#ion_list=["N5+","N6+","N7+"]
numberions=len(ion_list)

ergl=open("erglist.dat")
s=ergl.readline()
k=s.split()
numberfiles=int(k[0])

fitvel=[]
fittemp=[]
for i in range(numberions):
    fitvel.append([])
    fittemp.append([])


mass=[]
charge=[]
for ion in range(numberions):
    f=open("ions.dat")
    print "loading ion_para.dat"
    s=f.readline()
    s=f.readline()
    k=s.split()
    numberionslist=int(k[0])
    s=f.readline()
    s=f.readline()
    epn_arr=zeros([numberions,dim],float)
    vel_arr=zeros([numberions,dim],float)
    for l in range(numberionslist):
        s=f.readline()
        k=s.split()
        if (k[0]==ion_list[ion]):
            mass.append(float(k[1]))
            charge.append(float(k[2]))
    f.close()

for ion in range(numberions):
    for i in range(dim):
        epn_arr[ion][i]=epq_arr[i]*(charge[ion]/mass[ion])

allfiles=[]
for files in range(numberfiles):
    allcounts=[]
    s=ergl.readline()
    k=s.split()
    ergname=ergpath+k[0]
    for ion in range(numberions):
        counts=[]
        f=open(ergname)
        for step in range(dim):
            s=f.readline()
            k=s.split()
            print k
            tmpnumion=int(k[5])
            s=f.readline()
            for k in range(tmpnumion):
                s=f.readline()
                k=s.split()
                if (k[0]==ion_list[ion]):
                    tmp=[]
                    tmp.append(float(k[7])*1000.)
                    if (1):
#                    if (float(k[13])>1.e-10):
                        tmp.append(float(k[12]))
                    else:
                        tmp.append(0.)
                    if (1):
#                    if (float(k[13])>1.e-10):
                        tmp.append(float(k[13]))
                    else:
                        tmp.append(0.)

                    counts.append(tmp)
        allcounts.append(counts)
        f.close()
    allfiles.append(allcounts)

alldata=[]
for ion in range(numberions):
    tmpiondata=[]
    for i in range(numberfiles):
        tmpiondata.append(allfiles[i][ion])
    alldata.append(tmpiondata)


gpalldata=[]
for ion in range(numberions):
    tmpion=[]
    for i in range (len(alldata[ion])):
        tmpgpcounts=Data(alldata[ion][i])
        tmpgpcounts.set_option_colonsep("using", "1:2")
        tmpgpcounts.set_option_colonsep("title",  "'%s'" %(ion_list[ion]))
        tmpion.append(tmpgpcounts)
    gpalldata.append(tmpion)

tmpsum=[]
for ion in range(numberions):
    summe=0.
    for i in range(len(alldata[ion])):
        for step in range(len(alldata[ion][i])):
            summe+=alldata[ion][i][step][1]
    tmpsum.append(summe)

print tmpsum

gp=Gnuplot()
gp("set log y")
first=1
for ion in range(numberions):
    for i in range(len(alldata[ion])):
        if (first):
            gp.plot(gpalldata[ion][i])
            first=0
        else:
            gp.replot(gpalldata[ion][i])
                      
                      
maxvel=zeros([numberfiles,numberions],float)
maxflux=zeros([numberfiles,numberions],float)
maxdens=zeros([numberfiles,numberions],float)
for time in range(numberfiles):
    for ion in range(numberions):
        for i in range(len(alldata[ion][time])):
            if (alldata[ion][time][i][1]>maxflux[time][ion]):
                maxflux[time][ion]=alldata[ion][time][i][1]
                maxvel[time][ion]=alldata[ion][time][i][0]
            if (alldata[ion][time][i][1]>maxdens[time][ion]):
                maxdens[time][ion]=alldata[ion][time][i][0]

            
    
vdfval=[]
plot_ion=zeros([numberions])
#for ion in range(numberions):
for time in range(numberfiles):
    for ion in range(numberions):
        gp("pi = 3.14159265")
        gp("kb = 1.38065*10.**(-23)")
        gp("u = 1.660538*10.**(-27)")
        gp("m = u*%f" %(mass[ion]))
        gp("T=2000000.")
        gp("x0=%f"%(maxvel[time][ion]))
        gp("ph = %f/sqrt(m/(2.*pi*kb*T))"%(maxflux[time][ion]))
        gp("f(x)=ph*sqrt(m/(2.*pi*kb*T))*exp(-(m*(x-x0)**2.)/(2.*kb*T))")
        if (1):
            gp("fit f(x) '"+gpalldata[ion][0].filename+"' using 1:2 via x0" )
            gp("fit f(x) '"+gpalldata[ion][0].filename+"' using 1:2 via T" )
            gp("fit f(x) '"+gpalldata[ion][0].filename+"' using 1:2 via ph" )
            gp("fit f(x) '"+gpalldata[ion][0].filename+"' using 1:2 via x0" )
            gp("fit f(x) '"+gpalldata[ion][0].filename+"' using 1:2 via T" )
            gp("fit f(x) '"+gpalldata[ion][0].filename+"' using 1:2 via ph" )
            gp("fit f(x) '"+gpalldata[ion][0].filename+"' using 1:2 via x0" )
            gp("fit f(x) '"+gpalldata[ion][0].filename+"' using 1:2 via T" )
            gp("fit f(x) '"+gpalldata[ion][0].filename+"' using 1:2 via ph" )
            gp("fit f(x) '"+gpalldata[ion][0].filename+"' using 1:2 via T,ph,x0" )
        tempT=gp.eval("T")
        tempFlux=gp.eval("ph")
        tempVs=gp.eval("x0")
        tempVs=tempVs/1000.
        gp("ph = %f/sqrt(m/(2.*pi*kb*T))"%(maxdens[time][ion]))
        if (1):
            gp("fit f(x) '"+gpalldata[ion][0].filename+"' using 1:3 via x0" )
            gp("fit f(x) '"+gpalldata[ion][0].filename+"' using 1:3 via T" )
            gp("fit f(x) '"+gpalldata[ion][0].filename+"' using 1:3 via ph" )
            gp("fit f(x) '"+gpalldata[ion][0].filename+"' using 1:3 via x0" )
            gp("fit f(x) '"+gpalldata[ion][0].filename+"' using 1:3 via T" )
            gp("fit f(x) '"+gpalldata[ion][0].filename+"' using 1:3 via ph" )
            gp("fit f(x) '"+gpalldata[ion][0].filename+"' using 1:3 via x0" )
            gp("fit f(x) '"+gpalldata[ion][0].filename+"' using 1:3 via T" )
            gp("fit f(x) '"+gpalldata[ion][0].filename+"' using 1:3 via ph" )
            gp("fit f(x) '"+gpalldata[ion][0].filename+"' using 1:3 via T,ph,x0" )
        tempDens=gp.eval("ph")
    
        vdfval.append([ion_list[ion],tempVs,tempFlux,tempT,tempDens])
        gp("set yrange[1.e-15:1.e-4]")
#        gp.replot("f(x)")
    
#print "maxvel = ",maxvel
#print "maxflux = ",maxflux
#print "vdfval = ",vdfval
#print "mass = ",mass[0]

#    fitvel[ion].append([(14.6+(0.2*files)),tempVs])
#    fittemp[ion].append([(14.6+(0.2*files)),tempT])
#    gp("set xlabel 'V/Vs'")
#    gp("set ylabel 'Counts' ")
#    gp("set border 15 lw 2")
#    gp("set title '%s'"%(ion_names[ion]))
#    gp("set yrange[0.8:100000]")

#tmpvel=fitvel[1][len(fitvel[ion])-1][1]
#tmptemp=fittemp[1][len(fittemp[1])-1][1]

#    for ion in range(numberions):
#        fitvel[ion][len(fitvel[ion])-1][1]=fitvel[ion][len(fitvel[ion])-1][1]/tmpvel
#        fittemp[ion][len(fittemp[ion])-1][1]=fittemp[ion][len(fittemp[ion])-1][1]/tmptemp

    #gp.plot(gpallcounts[0],gpallcounts[1],gpallcounts[2],gpallcounts[3],gpallcounts[4],gpallcountsamerica[0],gpallcountsamerica[1],gpallcountsamerica[2],gpallcountsamerica[3],gpallcountsamerica[4])
#        gp.plot(gpallcounts[ion],gpallcountsamerica[ion],"f(x)")
    #gp.plot("f(x)")
    #gp.plot(gpallcounts[0],gpallcounts[1],gpallcounts[2],gpallcounts[3],gpallcounts[4],gpallcounts[5],gpallcounts[6],gpallcounts[7],gpallcounts[8],gpallcounts[9])
                      #gp("set term postscript color 18")
   #gp.hardcopy("comparemethods.ps", color=True, fontsize=18)
    #print sumcounts
    #gp("set term postscript color")
    #gp("set outp 'longtimepostions.ps'")
    #gp("splot 'tmpetmat.dat' with pm3d t'','tmppointsmat.dat' w p lt 3 pt 2 ps 3 t'', 'tmppointssrimmat.dat' w p lt 5 pt 1 ps 3 t ''")
#gp("set ylabel 'Velocity' ")
#gp("set xlabel 'Time'")
#gp("unset logscale x")
#gp("unset logscale y")
#gp("set autoscale")
#gp("set yrange[1:18000000]")
#gpvel=[]
#for ion in range(numberions):
#    gptmpvel=Data(fitvel[ion])
#    gptmpvel.set_option_colonsep("title",  "'%s'"%(ion_names[ion]))
#    gpvel.append(gptmpvel)
#gp("set title 'velocity'")
#gp.plot(gpvel[2])
#for ion in range(numberions-3):
#    if (plot_ion[ion+3]):
#        gp.replot(gpvel[ion+3])
#gp.hardcopy("velocity.ps", color=True, fontsize=18)
#gptemp=[]
#for ion in range(numberions):
#    gptmptemp=Data(fittemp[ion])
#    gptmptemp.set_option_colonsep("title",  "'%s'"%(ion_names[ion]))
#    gptemp.append(gptmptemp)
#gp("set title 'temperature'")
#gp.plot(gptemp[0])
#for ion in range(numberions-1):
#    if (plot_ion[ion]):
#        gp.replot(gptemp[ion+1])
#gp.hardcopy("temperature.ps", color=True, fontsize=18)
