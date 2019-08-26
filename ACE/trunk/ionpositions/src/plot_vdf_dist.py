#!/usr/bin/python
from scipy import zeros, sqrt,mean
from Gnuplot import Gnuplot, GridData, GnuplotOpts,Data
from numpy import float

GnuplotOpts.prefer_fifo_data=0
GnuplotOpts.prefer_inline_data=0

ergpath="/data/kleopatra/berger/binneddata/2007002_1h/"
ergamericapath="/data/ivar/berger/work/america/runs/heidelberg/2005001_12min/"
ergname=ergpath+"erg_axlv2_2007002_004_1h.dat"
ergamericaname=ergamericapath+"axlv2_pccomp_001_248.dat"

dim=58
xdim=512
ydim=128
ionname=''
mode=5

epq_arr=zeros([dim],float)
epq_arr=[86.6359,75.0485,65.0109,56.3158,48.7837,42.2589,36.6069,31.7108,27.4695,23.7955,20.6129,17.856,16.619,15.4678,14.3962,13.399,12.4708,11.6069,10.8028,10.0545,9.35797,8.70971,8.10635,7.5448,7.02214,6.5357,6.08294,5.66156,5.26936,4.90433,4.56459,4.24839,3.95409,3.68017,3.42523,3.18796,2.96711,2.76157,2.57027,2.39222,2.2265,2.07226,1.92871,1.7951,1.67075,1.55501,1.44729,1.34703,1.25372,1.16687,1.08603,1.0108,0.940778,0.875607,0.81495,0.758496,0.705952,0.657048,0.611532,0.55]


ergl=open("erglist.dat")
#ergamerical=open("ergamericalist.dat")
s=ergl.readline()
k=s.split()
numberfiles=int(k[0])
#s=ergamerical.readline()
#k=s.split()
#if (int(k[0])!=numberfiles):
#    return




for files in range(numberfiles):
    allcounts=[]
#    allcountsamerica=[]

    s=ergl.readline()
    k=s.split()
    ergname=ergpath+k[0]
#    s=ergamerical.readline()
#    k=s.split()
#    ergamericaname=ergamericapath+k[0]

    if (files==0):
        f=open(ergname)
        print "loading ion_para.dat"

        s=f.readline()
        k=s.split()
        s=f.readline()
        numberions=int(k[5])
        epn_arr=zeros([numberions,dim],float)
        vel_arr=zeros([numberions,dim],float)
        mass=[]
        for l in range(int(k[5])):
            s=f.readline()
            k=s.split()
            ionname+= ' '+k[0]
            mass.append(float(k[8]))
            charge=float(k[9])
            for i in range(dim):
                epn_arr[l][i]=epq_arr[i]*(charge/mass[l])

        ion_names=ionname.split()
        f.close()
        fitvel=[]
        fittemp=[]

        for i in range(numberions):
            fitvel.append([])
            fittemp.append([])

    for ion in range(numberions):
        counts=[]
        f=open(ergname)
        for step in range(dim):
            ionda=0
            s=f.readline()
            k=s.split()
            s=f.readline()
            for k in range(int(k[5])):
                s=f.readline()
                k=s.split()
            
                if (k[0]==ion_names[ion]):
                    tmp=[]
                    tmp.append(float(k[7])*1000)
                    tmp.append(float(k[10]))
                    counts.append(tmp)
                    ionda=1
        allcounts.append(counts)
    f.close()

    if (mode==0):
        f=open(ergamericaname)
        s=f.readline()
        s=f.readline()
        s=f.readline()
        s=f.readline()
        k=s.split()
        step=int(k[0])
        ions=0
        while (int(k[0])==step):
            ions+=1
            s=f.readline()
            k=s.split()
        f.close()

        for ion in range(numberions):
            counts=[]
            f=open(ergamericaname)
            s=f.readline()
            s=f.readline()
            s=f.readline()
            for step in range(dim):
                ionda=0
                for i in range(ions):
                    s=f.readline()
                    k=s.split()
                    if (ion_names[ion]==k[2]):
                        f2=open(ergname)
                        for step2 in range(step+1):
                            s=f2.readline()
                            k2=s.split()
                            s=f2.readline()
                            for ion2 in range(int(k2[5])):
                                s=f2.readline()
                                k2=s.split()
                                if ((step==step2)and(k2[0]==ion_names[ion])):
                                    tmp=[]
                                    tmp.append(float(k2[7])*1000)
                                    tmp.append(float(k[7]))
                                    ionda=1
                                    counts.append(tmp)
                        f2.close()
                        if (ionda==0):
                            counts.append([0.0,0.0])
            allcountsamerica.append(counts)
        f.close()



    if (mode==1):
        for ion in range(numberions):
            counts=[]
            f=open(ergname)
            for step in range(dim):
                ionda=0
                s=f.readline()
                k=s.split()
                s=f.readline()
                for k in range(int(k[5])):
                    s=f.readline()
                    k=s.split()
            
                    if (k[0]==ion_names[ion]):
                        tmp=[]
                        tmp.append(float(k[7]))
#                tmp.append(epn_arr[ion][step])
#                tmp.append(float(step+1))
                        tmp.append(float(k[10]))
                        counts.append(tmp)
                        ionda=1

            allcountsamerica.append(counts)
        f.close()

#    tmpsumcounts=zeros([numberions],float)
#    sumcounts=[]
#    for ion in range(numberions):
#        for step in range(len(allcounts[ion])):
#            tmpsumcounts[ion]+=allcounts[ion][step][1]

#    tmpsumcountsamerica=zeros([numberions],float)
#    sumcountsamerica=[]
#    for ion in range(numberions):
#        print len(allcounts[ion]),len(allcountsamerica[ion])
#        for step in range(len(allcountsamerica[ion])):
#            tmpsumcountsamerica[ion]+=allcountsamerica[ion][step][1]

#    for ion in range(numberions):
#        tmp=[]
#        tmp.append(ion_names[ion])
#        tmp.append(tmpsumcounts[ion])
#        tmp.append(tmpsumcountsamerica[ion])
#        sumcounts.append(tmp)


    gpallcounts=[]
    for ion in range(numberions):
        gpcounts=Data(allcounts[ion])
        gpcounts.set_option_colonsep("using", "1:2")
#    gpcounts.set_option_colonsep("title",  "'%s'" %(ion_names[ion]))
        gpcounts.set_option_colonsep("title",  "'maximum likelihood'")
        gpallcounts.append(gpcounts)


#    gpallcountsamerica=[]
#    for ion in range(numberions):
#        gpcountsamerica=Data(allcountsamerica[ion])
#        gpcountsamerica.set_option_colonsep("using", "1:2")
#    gpcountsamerica.set_option_colonsep("title",  "'%s'" %(ion_names[ion]))
#        gpcountsamerica.set_option_colonsep("title",  "'axlv2 from michigan'")
#        gpallcountsamerica.append(gpcountsamerica)

    ion=3

    maxvel=zeros([numberions],float)
    maxval=zeros([numberions],float)
    for ion in range(numberions):
        for i in range(len(allcounts[ion])):
            if (allcounts[ion][i][1]>maxval[ion]):
                maxval[ion]=allcounts[ion][i][1]
                maxvel[ion]=allcounts[ion][i][0]

            
    

    plot_ion=zeros([numberions])
    for ion in range(numberions):
        gp=Gnuplot()
        gp("pi = 3.14159265")
        gp("kb = 1.38065*10.**(-23)")
        gp("u = 1.660538*10.**(-27)")
        gp("m = u*%f" %(mass[ion]))
        gp("T=5000000.")
        gp("x0=%f"%(maxvel[ion]))
        gp("ph = %f/sqrt(m/(2.*pi*kb*T))"%(maxval[ion]))
        gp("f(x)=ph*sqrt(m/(2.*pi*kb*T))*exp(-(m*(x-x0)**2.)/(2.*kb*T))")
        if (maxval[ion]>5.):
            gp("fit f(x) '"+gpallcounts[ion].filename+"' using 1:2 via T,ph,x0" )
            gp("T=T*.8")
            gp("fit f(x) '"+gpallcounts[ion].filename+"' using 1:2 via T,ph" )
            plot_ion[ion]=1
        tempT=gp.eval("T")
        tempVs=gp.eval("x0")
        tempVs=tempVs/1000.
        fitvel[ion].append([(14.6+(0.2*files)),tempVs])
        fittemp[ion].append([(14.6+(0.2*files)),tempT])
        gp("set xlabel 'V/Vs'")
        gp("set ylabel 'Counts' ")
        gp("set border 15 lw 2")
        gp("set title '%s'"%(ion_names[ion]))
        gp("set yrange[0.8:100000]")

    tmpvel=fitvel[1][len(fitvel[ion])-1][1]
    tmptemp=fittemp[1][len(fittemp[1])-1][1]

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

gp("set ylabel 'Velocity' ")
gp("set xlabel 'Time'")
gp("unset logscale x")
gp("unset logscale y")

gp("set autoscale")
#gp("set yrange[1:18000000]")
gpvel=[]
for ion in range(numberions):
    gptmpvel=Data(fitvel[ion])
    gptmpvel.set_option_colonsep("title",  "'%s'"%(ion_names[ion]))
    gpvel.append(gptmpvel)

gp("set title 'velocity'")
gp.plot(gpvel[2])
for ion in range(numberions-3):
    if (plot_ion[ion+3]):
        gp.replot(gpvel[ion+3])
gp.hardcopy("velocity.ps", color=True, fontsize=18)

gptemp=[]
for ion in range(numberions):
    gptmptemp=Data(fittemp[ion])
    gptmptemp.set_option_colonsep("title",  "'%s'"%(ion_names[ion]))
    gptemp.append(gptmptemp)


#gp("set title 'temperature'")
#gp.plot(gptemp[0])
#for ion in range(numberions-1):
#    if (plot_ion[ion]):
#        gp.replot(gptemp[ion+1])
#gp.hardcopy("temperature.ps", color=True, fontsize=18)
