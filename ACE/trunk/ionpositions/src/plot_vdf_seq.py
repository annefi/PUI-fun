#!/usr/bin/python
from scipy import zeros, sqrt,mean
from Gnuplot import Gnuplot, GridData, GnuplotOpts,Data
from numpy import float

GnuplotOpts.prefer_fifo_data=0
GnuplotOpts.prefer_inline_data=0

def getdenstemp(data,maxvel,mass):
    print "gettemp : maxvel =",maxvel
    print "gettemp : mass =",mass
    print "gettemp : data =",data
    leftstep=0
    rightstep=0
    kb=1.38065*10.**(-23)
    
    u = 1.660538*10.**(-27)
    m=mass*u
    step=0
    temp=0.
    
    for tmpstep in range(len(data)):
        if ((maxvel>=data[tmpstep][0]-1.)and(maxvel<=data[tmpstep][0]+1.)):
            step = tmpstep
    print "gettemp : step =",step
    if (step==len(data)or(step==0)):
        return 0.
    first=1
    for tmpstep in range(len(data)-step-1):
        if ((first==1) and (data[tmpstep+step+1][1]<=(0.1*data[step][1]))and(data[tmpstep+step+1][1]>0.)):
            first=0
            rightstep=tmpstep+step+1
    first=1
    for tmpstep in range(step):
        if ((first==1) and (data[step-tmpstep-1][1]<=(0.1*data[step][1]))and(data[step-tmpstep-1][1]>0.)):
            first=0
            leftstep=step-tmpstep-1
    print "gettemp : leftstep =",leftstep
    print "gettemp : rightstep =",rightstep
    if ((leftstep==0)and(rightstep==0)):
        return 0.
    
    tempr=(data[step][0]-data[rightstep][0])**2.*m/(2.*kb)
    templ=(data[step][0]-data[leftstep][0])**2.*m/(2.*kb)
#    if (1):
    if ((tempr>=0.1*templ) and (tempr<=10*templ)):
        temp=(tempr+templ)/2.
    else:
        temp=0.
    return temp

#ergpath="/local/zechine-data/rodde/composition/test/"
ergpath="/data/ivar/berger/work/america/runs/flux280-284/"
#ergname=ergpath+"erg_axlv2_2007002_004_1h.dat"

dim=58
xdim=512
ydim=128

epq_arr=zeros([dim],float)
epq_arr=[86.6359,75.0485,65.0109,56.3158,48.7837,42.2589,36.6069,31.7108,27.4695,23.7955,20.6129,17.856,16.619,15.4678,14.3962,13.399,12.4708,11.6069,10.8028,10.0545,9.35797,8.70971,8.10635,7.5448,7.02214,6.5357,6.08294,5.66156,5.26936,4.90433,4.56459,4.24839,3.95409,3.68017,3.42523,3.18796,2.96711,2.76157,2.57027,2.39222,2.2265,2.07226,1.92871,1.7951,1.67075,1.55501,1.44729,1.34703,1.25372,1.16687,1.08603,1.0108,0.940778,0.875607,0.81495,0.758496,0.705952,0.657048,0.611532,0.55]

#ion_list=["He2+","O6+"]
ion_list=["He2+","He1+","C4+","C5+","C6+","13C6+","N5+","N6+","N7+","O5+","O6+","O7+","O8+","Ne8+","Ne7+","Mg6+","Mg7+","Mg8+","Mg9+","Mg10+","Mg11+","Mg12+","Si5+","Si6+","Si7+","Si8+","Si9+","Si10+","Si11+","Si12+","S5+","S6+","S7+","S8+","S9+","S10+","S11+","S12+","Ca6+","Ca7+","Ca8+","Ca9+","Ca10+","Ca11+","Ca12+","Ca13+","Ca14+","Fe5+","Fe6+","Fe7+","Fe8+","Fe9+","Fe10+","Fe11+","Fe12+","Fe13+","Fe14+","Fe15+","Fe16+","Fe17+"]
#ion_list=["Fe9+","Fe10+","Fe11+"]
#ion_list=["He2+","O6+","C5+","N5+","Fe9+"]
#ion_list=["C4+","C5+","C6+"]
#ion_list=["N5+","N6+","N7+"]
#ion_list=["He2+","He1+"]
#ion_list=["O5+","O6+","O7+","O8+"]
#ion_list=["Ne8+","Ne7+"]
#ion_list=["Mg6+","Mg7+","Mg8+","Mg9+","Mg10+"]
#ion_list=["Si6+","Si7+","Si8+","Si9+","Si10+"]
#ion_list=["S6+","S7+","S8+","S9+","S10+"]
#ion_list=["S6+","S7+","S8+","S9+","S10+","S11+","S12+"]
#ion_list=["Ca6+","Ca7+","Ca8+","Ca9+","Ca10+","Ca11+","Ca12+"]
#ion_list=["H1+","N5+","N6+","N7+"]
#ion_list=["He2+","O6+","Mg9+","Si8+","Fe9+"]
#ion_list=["He2+","H1+"]
#ion_list=["He2+"]
#ion_list=["Fe9+"]
#ion_list=["Fe11+"]
#ion_list=["O6+"]
#ion_list=["Mg11+"]
#ion_list=["He2+","H1+"]
#ion_list=["He2+","O6+","Mg9+","Si8+","Fe9+"]
#ion_list=["O6+"]
#ion_list=["Fe11+"]
#ion_list=["He2+","C6+","N6+","O6+","Si9+"]
#ion_list=["He2+"]
#ion_list=["He2+","C6+","O6+","Mg9+","S9+","Fe11+"]
#ion_list=["He2+","H1+"]
ion_list=["Ne8+","O5+","O6+","O7+","O8+"]

numberions=len(ion_list)
numberfiles=0

ergl=open("erglist.dat")
s=ergl.readline()
k=s.split()
ergpath=k[0]

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

#for ion in range(numberions):
#    for i in range(dim):
#        epn_arr[ion][i]=epq_arr[i]*(charge[ion]/mass[ion])

allfiles=[]
for ergfilename in ergl:
    numberfiles+=1
    allcounts=[]
    k=ergfilename.split()
    tmpname=k[0]
    tmp2name=tmpname[3:len(tmpname)]
    ergname=ergpath+"flux"+tmp2name
    print "opening ",ergname
    for ion in range(numberions):
        print "processing ",ion_list[ion]
        counts=[]
        f=open(ergname)
        for step in range(dim):
            s=f.readline()
            k=s.split()
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
#                    print ion_list[ion],tmp
        allcounts.append(counts)
        f.close()
    allfiles.append(allcounts)

ergl.close()

alldata=[]
for ion in range(numberions):
    tmpiondata=[]
    for i in range(numberfiles):
        tmpiondata.append(allfiles[i][ion])
    alldata.append(tmpiondata)


print "numberfiles = ",numberfiles," numberions = ",numberions,"lenalldata = "
for ion in range(numberions):
    print "lenalldata[",ion,"] = ",len(alldata[ion])
                                       
gpalldata=[]
for ion in range(numberions):
    print "ion = ",ion," ion name = ",ion_list[ion]
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
if (0):
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
            if (alldata[ion][time][i][2]>maxdens[time][ion]):
                maxdens[time][ion]=alldata[ion][time][i][2]

print "maxdens = ",maxdens

gp("set yrange[1.e-15:1.e20]")
#gp("set yrange[-0.:1.]")
vdfval=[]
for time in range(numberfiles):
    for ion in range(numberions):
        gp("pi = 3.14159265")
        gp("kb = 1.38065*10.**(-23)")
        gp("u = 1.660538*10.**(-27)")
        gp("m = u*%f" %(mass[ion]))
        guessT=getdenstemp(alldata[ion][time],maxvel[time][ion],mass[ion])
        print "guessT = ",guessT
        tempT=0.
        tempDens=0.
        tempFlux=0.
        tempVs=0.
        if (guessT>0.):
            gp("T=%f"%(guessT))
            if (ion==numberions-1):
                print "guess x0 = ",(maxvel[time][ion])
            gp("x0=%f"%(maxvel[time][ion]))
            gp("ph = %f/sqrt(m/(2.*pi*kb*T))"%(maxflux[time][ion]))
            gp("x02=%f"%(maxvel[time][ion]))
            gp("ph2 = %f/sqrt(m/(2.*pi*kb*T))"%(maxdens[time][ion]*10000.))
#            gp("a=0.001")
#            gp("k=3*10**(5)")
#            gp("b=0.")
#            gp("g(x)= a*x**-k +b"
            gp("f(x)= ph*sqrt(m/(2.*pi*kb*T))*exp(-(m*(x-x0)**2.)/(2.*kb*T))")
#            gp("f(x)= x<x0 ? ph*sqrt(m/(2.*pi*kb*T))*exp(-(m*(x-x0)**2.)/(2.*kb*T)) : x<1.6*x0 ? ph*sqrt(m/(2.*pi*kb*T))*exp(-(m*(x-x0)**2.)/(2.*kb*T))+a*exp(-(x/k)) +b : 0.")
            if (1):
                gp("fit f(x) '"+gpalldata[ion][time].filename+"' using 1:2 via x0" )
                gp("fit f(x) '"+gpalldata[ion][time].filename+"' using 1:2 via T" )
                gp("fit f(x) '"+gpalldata[ion][time].filename+"' using 1:2 via ph" )
                gp("fit f(x) '"+gpalldata[ion][time].filename+"' using 1:2 via x0" )
                gp("fit f(x) '"+gpalldata[ion][time].filename+"' using 1:2 via T" )
                gp("fit f(x) '"+gpalldata[ion][time].filename+"' using 1:2 via ph" )
                gp("fit f(x) '"+gpalldata[ion][time].filename+"' using 1:2 via x0" )
                gp("fit f(x) '"+gpalldata[ion][time].filename+"' using 1:2 via T" )
                gp("fit f(x) '"+gpalldata[ion][time].filename+"' using 1:2 via ph" )
                gp("fit f(x) '"+gpalldata[ion][time].filename+"' using 1:2 via ph,T,x0" )
#                gp("fit f(x) '"+gpalldata[ion][time].filename+"' using 1:2 via a,b,k" )
#                gp("fit f(x) '"+gpalldata[ion][time].filename+"' using 1:2 via a,b,k" )
            tempT=gp.eval("T")
            tempFlux=gp.eval("ph")
            tempVs=gp.eval("x0")
            tempVs=tempVs/1000.
            gp("T2=%f"%(guessT))
            gp("g(x)=ph2*sqrt(m/(2.*pi*kb*T2))*exp(-(m*(x-x02)**2.)/(2.*kb*T2))")
            if (1):
                gp("fit g(x) '"+gpalldata[ion][time].filename+"' using 1:($3)*10000. via x02" )
                gp("fit g(x) '"+gpalldata[ion][time].filename+"' using 1:($3)*10000 via T2" )
                gp("fit g(x) '"+gpalldata[ion][time].filename+"' using 1:($3)*10000. via ph2" )
                gp("fit g(x) '"+gpalldata[ion][time].filename+"' using 1:($3)*10000. via x02" )
                gp("fit g(x) '"+gpalldata[ion][time].filename+"' using 1:($3)*10000. via T2" )
                gp("fit g(x) '"+gpalldata[ion][time].filename+"' using 1:($3)*10000. via ph2" )
                gp("fit g(x) '"+gpalldata[ion][time].filename+"' using 1:($3)*10000. via x02" )
                gp("fit g(x) '"+gpalldata[ion][time].filename+"' using 1:($3)*10000. via T2" )
                gp("fit g(x) '"+gpalldata[ion][time].filename+"' using 1:($3)*10000. via ph2" )
                gp("fit g(x) '"+gpalldata[ion][time].filename+"' using 1:($3)*10000. via T2,ph2,x02" )
            tempDens=gp.eval("ph2")
            tempDens=tempDens/10000.
            print "tempDens = ",tempDens
            print "maxedens = ",maxdens[time][ion]
        print tempVs,tempFlux,tempT,tempDens
        vdfval.append([ion_list[ion],tempVs,tempFlux,tempT,tempDens])
#        gp("set autoscale")
#        gp("set yrange[1.e-15:1.e20]")
#        if (ion==0):
#               gp.replot("g(x)")
#            gp.replot("f(x)")
if (1):
    ergl=open("erglist.dat")
    s=ergl.readline()
    
    for time in range(numberfiles):
        s=ergl.readline()
        k=s.split()
        name=k[0]
        tmpname=k[0]
        tmp2name=tmpname[3:len(tmpname)]
        out=open(ergpath+"res_"+tmp2name,"w")
        out.write("Ion\t\tvelocity\tFlux\t\t\tTemp\t\t\tDens\n") 
        for ion in range(numberions):
            out.write("%s\t\t%.2f\t\t%.4e\t\t%.4e\t\t%.4e\n" %(ion_list[ion],vdfval[time*numberions+ion][1],vdfval[time*numberions+ion][2],vdfval[time*numberions+ion][3],vdfval[time*numberions+ion][4]))
    out.close()

if (0):
    tailbulkdist=[]
    first=1
    for ion in range(numberions):
        tailbulkdisttmp=[]
        for time in range(numberfiles):
            tmpsumme=0.
            for step in range(len(alldata[ion][time])):
                if ((alldata[ion][time][step][0]>=1.5*maxvel[time][ion]) and (alldata[ion][time][step][0]<=1.69*maxvel[time][ion])):
                    tmpsumme+=alldata[ion][time][step][1]
            tailbulk=tmpsumme/maxflux[time][ion]
            tailbulkdisttmp.append([305.+time*10.,tailbulk])
            print "ion : ",ion_list[ion],"tail/bulk = ",tailbulk
        tailbulkdist.append(tailbulkdisttmp)
    gptailbulkdist=[]
    for ion in range(numberions):
        tmpgptailbulk=Data(tailbulkdist[ion])
        tmpgptailbulk.set_option_colonsep("using", "1:2")
        tmpgptailbulk.set_option_colonsep("title",  "'%s'" %(ion_list[ion]))
        gptailbulkdist.append(tmpgptailbulk)

    gp("set autoscale")
    gp("set yrange[0.00001:0.1]")
    gp("set xlabel 'v_{sw} / km/s'")
    gp("set ylabel 'tail/bulk ratio / %' ")

    for ion in range(numberions):
        if (first):
            gp.plot(gptailbulkdist[ion])
            first=0
        else:
            gp.replot(gptailbulkdist[ion])

    gp("set term postscript color 18 lw 2 eps")
    gp.hardcopy("tailbulk.ps",color=True, fontsize=18)
    
    # DO Norm Bulk etc...
if (0):
# norm to bulk velocity

    for time in range(numberfiles):
        for ion in range(numberions):
            for step in range(len(alldata[ion][time])):
                if (ion==-11):
                    alldata[ion][time][step][0]=alldata[ion][time][step][0]/(vdfval[time*numberions][1]*1000.)
                else:
                    if (ion==numberions-1):
                        print (vdfval[time*numberions+ion][1]*1000.)
                    alldata[ion][time][step][0]=alldata[ion][time][step][0]/(vdfval[time*numberions+ion][1]*1000.)

            
    gpalldata2=[]
    for ion in range(numberions):
        tmpion=[]
        for i in range (len(alldata[ion])):
            tmpgpcounts=Data(alldata[ion][i])
            tmpgpcounts.set_option_colonsep("using", "1:2")
            tmpgpcounts.set_option_colonsep("title",  "'%s'" %(ion_list[ion]))
#            if (i==0 and ion==0):
#                tmpgpcounts.set_option_colonsep("title",  "'%s doy280-281' lt 1" %(ion_list[ion]))
#            if (i==1 and ion==0):
#                tmpgpcounts.set_option_colonsep("title",  "'%s doy282-284' lt 3" %(ion_list[ion]))
#            if (i==0 and ion==1):
#                tmpgpcounts.set_option_colonsep("title",  "'%s doy280-281' lt 4" %(ion_list[ion]))
#            if (i==1 and ion==1):
#                tmpgpcounts.set_option_colonsep("title",  "'%s doy282-284' lt 5" %(ion_list[ion]))
            tmpion.append(tmpgpcounts)
        gpalldata2.append(tmpion)
 
    gp("set autoscale")
    for ion in range(numberions):
        for time in range(numberfiles):
            if (time==0 and ion==0):
                gp.plot(gpalldata2[ion][time])
            else:
                gp.replot(gpalldata2[ion][time])
    gp("set yrange[0.001:1000.]")
    gp("T=0.001")
    gp("x0=1.")
    gp("ph =100.")
    gp("f(x)= ph*sqrt(1./(2.*pi*T))*exp(-((x-x0)**2.)/(2.*T))")
    gp("fit f(x) '"+gpalldata2[0][0].filename+"' using 1:2 via T" )
    gp("fit f(x) '"+gpalldata2[0][0].filename+"' using 1:2 via ph" )
    gp("fit f(x) '"+gpalldata2[0][0].filename+"' using 1:2 via T,ph" )
    gp("set yrange[0.000001:1000.]")
    gp.replot("f(x) title 'Maxwell-Boltzmann fit He2+'")

    gp("set xlabel 'v/v_{bulk}'")
    gp("set ylabel 'Flux / s^{-1}cm^{-2}s^{1}m^{-1}' ")
    gp("set term postscript color 18 lw 2")
    gp.hardcopy("Vdfs.ps", color=True, fontsize=18)


if (0):
# calc diff
    for ion in range(numberions):
        for step in range(len(alldata[ion][0])):
            alldata[ion][0][step][1]=alldata[ion][0][step][1]-alldata[ion][1][step][1]
            alldata[ion][0][step][2]=alldata[ion][0][step][2]-alldata[ion][1][step][2]

    gpdiffdata=[]
    for ion in range(numberions):
        tmpion=[]
        tmpgpcounts=Data(alldata[ion][0])
        tmpgpcounts.set_option_colonsep("using", "1:2")
        tmpgpcounts.set_option_colonsep("title",  "'%s'" %(ion_list[ion]))
        tmpion.append(tmpgpcounts)
        gpdiffdata.append(tmpion)
    


    gp("set autoscale")
    for ion in range(numberions):
        if (ion==0):
            gp.plot(gpdiffdata[ion][0])
        else:
            gp.replot(gpdiffdata[ion][0])


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
