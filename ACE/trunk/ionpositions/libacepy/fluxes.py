#!/usr/bin/python
from scipy import zeros,sqrt
from math import atan,pi
from numpy import float
from libacepy.ancil import getmaxpos,fgauss
from Gnuplot import Gnuplot, GridData, GnuplotOpts,Data
from random import Random

GnuplotOpts.prefer_fifo_data=0
GnuplotOpts.prefer_inline_data=0

"""
function : calculates dutycycle using aspect and machangle as input
"""
def dutycycle(aspang,thang):
    data=zeros([30,7],float)
    asparr = [0.0,0.2,0.4,0.6,0.8,1.0,1.2,1.4,1.6,1.8,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0,15.0,20.0,25.0,30.0,35.0,40.0,45.0,50.0,55.0,60.0,65.0]
    tharr = [0.0,0.5,1.0,2.0,3.0,5.0,10.0]
    darr = [0.5000,0.5000,0.4772,0.3413,0.2475,0.1555,0.0794,
            0.5000,0.4999,0.4762,0.3407,0.2473,0.1554,0.0794,
            0.5000,0.4998,0.4729,0.3389,0.2466,0.1552,0.0793,
            0.5000,0.4994,0.4673,0.3359,0.2454,0.1549,0.0793,
            0.5000,0.4984,0.4594,0.3318,0.2438,0.1545,0.0793,
            0.5000,0.4959,0.4490,0.3267,0.2417,0.1540,0.0792,
            0.5000,0.4904,0.4360,0.3205,0.2392,0.1534,0.0791,
            0.5000,0.4800,0.4206,0.3134,0.2363,0.1526,0.0790,
            0.5000,0.4627,0.4029,0.3056,0.2331,0.1518,0.0789,
            0.5000,0.4376,0.3833,0.2970,0.2294,0.1508,0.0788,
            0.5000,0.4053,0.3622,0.2879,0.2255,0.1498,0.0786,
            0.2324,0.2413,0.2532,0.2372,0.2019,0.1431,0.0777,
            0.1668,0.1689,0.1769,0.1872,0.1751,0.1344,0.0764,
            0.1312,0.1320,0.1351,0.1464,0.1485,0.1245,0.0748,
            0.1084,0.1089,0.1103,0.1178,0.1237,0.1139,0.0729,
            0.0925,0.0928,0.0936,0.0981,0.1040,0.1032,0.0707,
            0.0808,0.0809,0.0815,0.0841,0.0890,0.0930,0.0684,
            0.0717,0.0718,0.0722,0.0737,0.0774,0.0830,0.0659,
            0.0645,0.0646,0.0649,0.0660,0.0685,0.0739,0.0632,
            0.0432,0.0432,0.0433,0.0436,0.0442,0.0464,0.0496,
            0.0328,0.0328,0.0328,0.0329,0.0331,0.0339,0.0373,
            0.0266,0.0266,0.0266,0.0267,0.0268,0.0272,0.0293,
            0.0226,0.0226,0.0226,0.0226,0.0227,0.0229,0.0241,
            0.0198,0.0198,0.0198,0.0198,0.0199,0.0200,0.0205,
            0.0178,0.0178,0.0178,0.0178,0.0178,0.0179,0.0176,
            0.0163,0.0163,0.0163,0.0163,0.0163,0.0163,0.0149,
            0.0152,0.0152,0.0152,0.0152,0.0151,0.0140,0.0119,
            0.0144,0.0143,0.0136,0.0116,0.0104,0.0093,0.0085,
            0.0000,0.0000,0.0000,0.0008,0.0020,0.0036,0.0054,
            0.0000,0.0000,0.0000,0.0000,0.0000,0.0007,0.0028]
    j=0
    k=0
    for i in range(210):
        data[k,j]=darr[i]
        j+=1
        if ( j == 7 ):
            j=0
            k+=1
    j=0
    for i in range(7):
        if ((tharr[i] <= thang) and (j <= 5)):
            j+=1
    l=0
    for k in range(30):
        if ((asparr[k]) <= aspang and (l <= 28)):
            l+=1
    h1 = ( thang - tharr[j-1])  / ( tharr[j] - tharr[j-1] )
    h2 = ( aspang - asparr[l-1] ) / ( asparr[l] - asparr[l-1] )
    

    d = ( 1E0 - h1 ) * ( 1E0 - h2 ) * data[l-1,j-1] + h1 * ( 1E0 - h2 ) * data[l-1,j] + ( 1E0 - h1 ) * h2 * data[l,j-1] + h1 * h2 * data[l,j]
    return d


"""
subroutine : calculates velocities for each ion in ions
input
ions -> array class ion (s. ion.py)
"""
def calcvelocities(ions):
    for ion in ions:
        for step in range(len(ion.velocity)):
            ion.velocity[step]=getvelocity(ion.mass,ion.charge,step,1.0)

"""
function : calculates velocity at frac*E/q
"""
def getvelocity(mass,charge,step,frac):
    epq_arr = [86.6359,75.0485,65.0109,56.3158,48.7837,42.2589,36.6069,31.7108,27.4695,23.7955,20.6129,17.856,16.619,15.4678,14.3962,13.399,12.4708,11.6069,10.8028,10.0545,9.35797,8.70971,8.10635,7.5448,7.02214,6.5357,6.08294,5.66156,5.26936,4.90433,4.56459,4.24839,3.95409,3.68017,3.42523,3.18796,2.96711,2.76157,2.57027,2.39222,2.2265,2.07226,1.92871,1.7951,1.67075,1.55501,1.44729,1.34703,1.25372,1.16687,1.08603,1.0108,0.940778,0.875607,0.81495,0.758496,0.705952,0.657048]
    energy=(epq_arr[step]*charge*1.60217646e-19*1000.)*frac
    tmpmass=mass*1.66053886e-27
    velocity=sqrt(2.*energy)/sqrt(tmpmass)
    velocity=velocity/1000.
    return velocity

"""
function : returns delta v at a given E/q step
this is needed to calculate differential fluxes and densities
"""
def getdeltav(mass,charge,step):
    vp=0.
    vm=0.
    vp=getvelocity(mass,charge,step,1.03)
    vm=getvelocity(mass,charge,step,0.97)
    deltav=vp-vm
    return deltav

"""
function : returns machang guess from rawcounts 
iondata -> class ion (s. ion.py)
"""
def getmachangle(iondata):
    tmpmoments=getmoments(iondata.velocity,iondata.counts,0)
    machang=0.
    if (tmpmoments[1]>0.):
        machang=(180./pi)*atan(sqrt(tmpmoments[2])/tmpmoments[1])
    else:
        machang=0.
    return machang

"""
subroutine : calculates differential fluxes and densities. refion is used to filter instrumental pileup caused (eg. noise in Fe caused by He2+). refion should be He2+ but has to be provided by user (it is not checked in any way) 
input
iondata -> class ion (s. ion.py)
refion -> class ion 
"""
def calcflux(iondata,refion):
    geomfac=0.0225
    if (iondata.mass/iondata.charge>=3.):
    #if (1):
        tmpmoments=getmoments(refion.velocity,refion.counts,0)
        vref=tmpmoments[1]/1000.
        vthref=sqrt(tmpmoments[2])/1000.
    else:
        vref=0.
        vthref=0.
    print "vref= ",vref
    print "vthref= ",vthref
    
    vref=vref-4*vthref
    for step in range(len(iondata.velocity)):
        if (iondata.velocity[step]<vref):
            iondata.counts[step]=0.
            iondata.countserror[step]=0.

    """
    v0ref=vref*(sqrt(refion.charge/refion.mass)/sqrt(iondata.charge/iondata.mass))
    v0thref=vthref*(sqrt(refion.charge/refion.mass)/sqrt(iondata.charge/iondata.mass))
    if (v0ref+3*v0thref<vref-3*vthref):
        vref=v0ref+3*v0thref
    else:
        vref=vref*0.8
        cutstep=0
        while (refion.counts[cutstep]<refion.cycles*500. and (cutstep<len(refion.counts-2))):
            cutstep+=1
        for step in range(len(iondata.velocity)):
            if (step>cutstep):
                iondata.counts[step]=0.
    """
    machang=getmachangle(iondata)
    if (1):
   #if (machang<0.1 or machang>10.):
        machang=getmachangle(refion)
        
    if (iondata.name=="H1+" or iondata.name=="3He1+" or iondata.name=="He1+"):
        machang = 4.
    print "machangle %s : " %(iondata.name),machang  
    for step in range(len(iondata.counts)):
        fluxefferrlow=0.
        fluxefferrhigh=0.
        deltav=0.
        efff=open("/data/wimmer/ace/efficencies/"+iondata.name+".eff")
        for stepeff in range(step+1):
            s=efff.readline()
            k=s.split()
            eff=float(k[1])
            deltaeff=float(k[2])
        if (eff>0.):
            flux=0.
            flux=(iondata.counts[step]*(1./(float(iondata.cycles)*12.*dutycycle(iondata.aspang,machang))))/(geomfac*eff)
            fluxerror=iondata.countserror[step]*((1./(float(iondata.cycles)*12.*dutycycle(iondata.aspang,machang)))/(geomfac*eff))
            fluxefferrlow=iondata.counts[step]*((1./(float(iondata.cycles)*12.*dutycycle(iondata.aspang,machang)))/(geomfac*max(0,(eff-deltaeff))))
            fluxefferrhigh=iondata.counts[step]*((1./(float(iondata.cycles)*12.*dutycycle(iondata.aspang,machang)))/(geomfac*(eff+deltaeff)))
        else:
            flux=0.
            fluxerror=0.
            fluxefferrlow=0.
            fluxefferrhigh=0.
        if (iondata.velocity[step]*1000.>0.):
            dens=flux/(iondata.velocity[step]*1000.)
            denserror=fluxerror/(iondata.velocity[step]*1000.)
            densefferrlow=fluxefferrlow/(iondata.velocity[step]*1000.)
            densefferrhigh=fluxefferrhigh/(iondata.velocity[step]*1000.)
        else:
            dens=0.
            denserror=0.
            densefferrlow=0.
            densefferrhigh=0.
        deltav=getdeltav(iondata.mass,iondata.charge,step)
        flux=flux/(deltav*1000.)
        fluxefferrlow=fluxefferrlow/(deltav*1000.)
        fluxefferrhigh=fluxefferrhigh/(deltav*1000.)
        fluxerror=fluxerror/(deltav*1000.)
        dens=dens/(deltav*1000.)
        denserror=denserror/(deltav*1000.)
        densefferrlow=densefferrlow/(deltav*1000.)
        densefferrhigh=densefferrhigh/(deltav*1000.)
# next line converts dens from 1/cm^2*m to 1/cm^3
        dens=dens/(100.)
        denserror=denserror/(100.)
        densefferrlow=densefferrlow/(100.)
        densefferrhigh=densefferrhigh/(100.)
        iondata.flux[step]=flux
        iondata.dens[step]=dens
        iondata.fluxerror[step]=fluxerror
        iondata.fluxefferrlow[step]=fluxefferrlow
        iondata.fluxefferrhigh[step]=fluxefferrhigh
        iondata.denserror[step]=denserror
        iondata.densefferrlow[step]=densefferrlow
        iondata.densefferrhigh[step]=densefferrhigh
        efff.close()

"""
subroutine
initialises Gnuplot Object for fitting
"""
def gpinit(gp):
    gp("set yrange[-1.e20:1.e20]")
    gp("pi = 3.14159265")
    gp("kb = 1.38065*10.**(-23)")
    gp("u = 1.660538*10.**(-27)")

"""
subroutine
calculates moments and errors for ion quantites (totflux ...)
"""
def numint(iondata):
    pi = 3.14159265
    kb = 1.38065*10.**(-23)
    u = 1.660538*10.**(-27)
    mass = u * iondata.mass
    tmpmoments=[0.,0.,0.]
    tmpmoments2=[0.,0.,0.]
    rnd=Random()
    # calc total flux and corresponding quanteties
    tmpmoments=getmoments(iondata.velocity,iondata.flux,0)
    iondata.totfluxnumint=tmpmoments[0]
    iondata.bulkspeedfluxnumint=tmpmoments[1]/1000.
    iondata.iontempfluxnumint=tmpmoments[2]*mass/kb
    # errors for flux
    totfluxerr=0.
    v0err=0.
    iontemperr=0.
    for i in range(100):
        tmpdata=[]
        for i in range(len(iondata.flux)):
            if (iondata.fluxerror[i]!=0.):
                tmpdata.append(max(0.,rnd.gauss(iondata.flux[i],iondata.fluxerror[i])))
            else:
                tmpdata.append(0.)
        tmpmoments=getmoments(iondata.velocity,tmpdata,0)
        totfluxerr=totfluxerr+(tmpmoments[0]-iondata.totfluxnumint)**2
        v0err=v0err+(tmpmoments[1]/1000.-iondata.bulkspeedfluxnumint)**2
        iontemperr=iontemperr+((tmpmoments[2]*mass/kb)-iondata.iontempfluxnumint)**2
    totfluxerr=totfluxerr/100.
    v0err=v0err/100.
    iontemperr=iontemperr/100.
    iondata.totfluxnuminterror=sqrt(totfluxerr)
    iondata.bulkspeedfluxnuminterror=sqrt(v0err)
    iondata.iontempfluxnuminterror=sqrt(iontemperr)
    tmpmoments=getmoments(iondata.velocity,iondata.fluxefferrlow,0)
    tmpmoments2=getmoments(iondata.velocity,iondata.fluxefferrhigh,0)
    iondata.totfluxefferror=0.5*(sqrt((tmpmoments[0]-iondata.totfluxnumint)**2)+sqrt((tmpmoments2[0]-iondata.totfluxnumint)**2))
    iondata.bulkspeedfluxefferror=0.5*(sqrt((tmpmoments[1]/1000.-iondata.bulkspeedfluxnumint)**2)+sqrt((tmpmoments2[1]/1000.-iondata.bulkspeedfluxnumint)**2))
    iondata.iontempfluxefferror=0.5*(sqrt((tmpmoments[2]*mass/kb-iondata.iontempfluxnumint)**2)+sqrt((tmpmoments2[2]*mass/kb-iondata.iontempfluxnumint)**2))
    # calc total dens and corresponding quanteties
    tmpmoments=getmoments(iondata.velocity,iondata.dens,0)
    iondata.totdensnumint=tmpmoments[0]
    iondata.bulkspeeddensnumint=tmpmoments[1]/1000.
    iondata.iontempdensnumint=tmpmoments[2]*mass/kb
    # errors for dens
    totdenserr=0.
    v0err=0.
    iontemperr=0.
    for i in range(100):
        tmpdata=[]
        for i in range(len(iondata.dens)):
            if (iondata.denserror[i]!=0.):
                tmpdata.append(max(0.,rnd.gauss(iondata.dens[i],iondata.denserror[i])))
            else:
                tmpdata.append(0.)
        tmpmoments=getmoments(iondata.velocity,tmpdata,0)
        totdenserr=totdenserr+(tmpmoments[0]-iondata.totdensnumint)**2
        v0err=v0err+(tmpmoments[1]/1000.-iondata.bulkspeeddensnumint)**2
        iontemperr=iontemperr+(tmpmoments[2]-iondata.iontempdensnumint*kb/mass)**2
    totdenserr=totdenserr/100.
    v0err=v0err/100.
    iontemperr=iontemperr/100.
    iondata.totdensnuminterror=sqrt(totdenserr)
    iondata.bulkspeeddensnuminterror=sqrt(v0err)
    iondata.iontempdensnuminterror=sqrt(iontemperr)*mass/kb
    tmpmoments=getmoments(iondata.velocity,iondata.densefferrlow,0)
    tmpmoments2=getmoments(iondata.velocity,iondata.densefferrhigh,0)
    iondata.totdensefferror=0.5*(sqrt((tmpmoments[0]-iondata.totdensnumint)**2)+sqrt((tmpmoments2[0]-iondata.totdensnumint)**2))
    iondata.bulkspeeddensefferror=0.5*(sqrt((tmpmoments[1]/1000.-iondata.bulkspeeddensnumint)**2)+sqrt((tmpmoments2[1]/1000.-iondata.bulkspeeddensnumint)**2))
    iondata.iontempdensefferror=0.5*(sqrt((tmpmoments[2]*mass/kb-iondata.iontempdensnumint)**2)+sqrt((tmpmoments2[2]*mass/kb-iondata.iontempdensnumint)**2))
    

"""
function
data : array containing data for one quantity e.g. diff-fluxes
vel  : array containing velocities of ion (in km/s, therefore factor 1000. in function s.b.) 
mode : integer. 0 = normal mode moments are derived. 1 = error mode independent errors are squared summed an then the squareroot is taken 
returns moments of given distribution
"""
def getmoments(vel,data,mode):
    A=0.     #-->  integral
    v0=0.    #-->  central of mass
    sigsq=0. #-->  sigma^2
    dvel=[]
    for i in range(len(data)):
        deltavel=0.
        if (i==0):
            deltavel=(vel[0]-vel[1])*1000.
        elif (i==len(data)-1):
            deltavel=(vel[len(data)-2]-vel[len(data)-1])*1000.
        else:
            deltavel=((vel[i-1]-vel[i+1])*0.5)*1000.
        if (mode==1):
            A=A+(deltavel*data[i])**2
        else:
            A=A+deltavel*data[i]
        dvel.append(deltavel)
    if (A>0. and mode==1):
        A=sqrt(A)
    if (A!=0. and mode!=1):
        for i in range(len(data)):
            v0=v0+vel[i]*data[i]*dvel[i]*1000.
        v0=v0/A
        for i in range(len(data)):
            sigsq=sigsq+data[i]*dvel[i]*(vel[i]*1000.-v0)**2
        sigsq=sigsq/A
    return [A,v0,sigsq]


"""
subroutine : uses Gnuplot to fit a mawell-distribution to iondata and derives the moments of the distribution
input
iondata -> class ion (s. ion.py)
"""
def fitmaxwell(iondata):
    densfac=1.
    gp=Gnuplot()
    gpinit(gp)
    gp("m = u*%f" %(iondata.mass))
    tmpdata=[]
    maxflux=getmaxpos(iondata.flux)
    for i in range(len(iondata.flux)):
        if (iondata.countserror[i]>0.):
            tmpdata.append([iondata.velocity[i]*1000.,iondata.flux[i],iondata.fluxerror[i],iondata.dens[i]*densfac,iondata.denserror[i]*densfac,iondata.fluxefferrlow[i],iondata.fluxerror[i],iondata.fluxefferrhigh[i],iondata.fluxerror[i]])
    if (len(tmpdata)>3):
        gpdata=Data(tmpdata)
        for i in range(4):
            fluxefferrh=0.
            fluxefferrl=0.
            gp("set fit errorvariables")
            gp("FIT_MAXITER=100")
            if (i==0 or i==2 or i==3):
                gp("FIT_LIMIT = 1e-6")
            if (i==1):
                gp("FIT_LIMIT = 1e-14")
            if (i==0):
                guesspara=getfitpara(iondata.velocity,iondata.flux)
                gp("T=%f*m/kb"%(guesspara[2]))
                gp("x0=%f"%(guesspara[1]))
                gp("ph = %f"%(guesspara[0]))
            if (i==1):
                guesspara=getfitpara(iondata.velocity,iondata.dens)
                gp("T=%f*m/kb"%(guesspara[2]))
                gp("x0=%f"%(guesspara[1]))
                gp("ph = %f"%(guesspara[0]))
            if (i==2):
                guesspara=getfitpara(iondata.velocity,iondata.fluxefferrlow)
                gp("T=%f*m/kb"%(guesspara[2]))
                gp("x0=%f"%(guesspara[1]))
                gp("ph = %f"%(guesspara[0]))
            if (i==3):
                guesspara=getfitpara(iondata.velocity,iondata.fluxefferrhigh)
                gp("T=%f*m/kb"%(guesspara[2]))
                gp("x0=%f"%(guesspara[1]))
                gp("ph = %f"%(guesspara[0]))
            print "T = ",gp.eval("T")
            print "x0 = ",gp.eval("x0")
            print "ph = ",gp.eval("ph")
            print "fitparameters = ",guesspara
            gp("f(x)= ph*sqrt(m/(2.*pi*kb*T))*exp(-(m*(x-x0)**2.)/(2.*kb*T))")
#            if (1):
            if (guesspara[0]>0. and guesspara[1]>0. and guesspara[2]>0.):
                gp("fit f(x) '"+gpdata.filename+"' using 1:%i:%i via x0"%((i*2)+2,(i*2)+3))
                gp("fit f(x) '"+gpdata.filename+"' using 1:%i:%i via T"%((i*2)+2,(i*2)+3))
                gp("fit f(x) '"+gpdata.filename+"' using 1:%i:%i via ph"%((i*2)+2,(i*2)+3))
                gp("fit f(x) '"+gpdata.filename+"' using 1:%i:%i via x0"%((i*2)+2,(i*2)+3))
                gp("fit f(x) '"+gpdata.filename+"' using 1:%i:%i via T"%((i*2)+2,(i*2)+3))
                gp("fit f(x) '"+gpdata.filename+"' using 1:%i:%i via ph"%((i*2)+2,(i*2)+3))
                gp("fit f(x) '"+gpdata.filename+"' using 1:%i:%i via x0"%((i*2)+2,(i*2)+3))
                gp("fit f(x) '"+gpdata.filename+"' using 1:%i:%i via T"%((i*2)+2,(i*2)+3))
                gp("fit f(x) '"+gpdata.filename+"' using 1:%i:%i via ph"%((i*2)+2,(i*2)+3))
                gp("fit f(x) '"+gpdata.filename+"' using 1:%i:%i via ph,T,x0"%((i*2)+2,(i*2)+3))
            if (i==0):
                if (gp.eval("T")>=0.):
                    iondata.iontempfluxfit=gp.eval("T")
                else:
                    iondata.iontempfluxfit=-0.
                if (gp.eval("ph")>=0.):
                    iondata.totfluxfit=gp.eval("ph")
                else:
                    iondata.totfluxfit=-0.
                if ((gp.eval("x0")/1000.)>=0.):
                    iondata.bulkspeedfluxfit=(gp.eval("x0")/1000.)
                else:
                    iondata.bulkspeedfluxfit=-0.
                if (gp.eval("ph_err")>=0.):
                    iondata.totfluxfiterror=gp.eval("ph_err")
                else:
                    iondata.totfluxfiterror=-0.
            if (i==1):
                if (gp.eval("T")>=0.):
                    iondata.iontempdensfit=gp.eval("T")
                else:
                    iondata.iontempdensfit=-0.
                if (gp.eval("ph")>=0.):
                    iondata.totdensfit=gp.eval("ph")/densfac
                else:
                    iondata.totdensfit=-0.
                if ((gp.eval("x0")/1000.)>=0.):
                    iondata.bulkspeeddensfit=(gp.eval("x0")/1000.)
                else:
                    iondata.bulkspeeddensfit=-0.
                if (gp.eval("ph_err")>=0.):
                    iondata.totdensfiterror=(gp.eval("ph_err")/densfac)
                else:
                    iondata.totdensfiterror=-0.
                if (gp.eval("x0_err")>=0.):
                    iondata.bulkspeeddensfiterror=(gp.eval("x0_err")/1000.)
                else:
                    iondata.bulkspeeddensfiterror=-0.
                if (gp.eval("T_err")>=0.):
                    iondata.iontempdensfiterror=gp.eval("T_err")
                else:
                    iondata.iontempdensfiterror=-0.
            if (i==2):
                if (gp.eval("ph")>=0.):
                    fluxefferrl=gp.eval("ph")
                else:
                    fluxefferrl=0.
            if (i==3):
                if (gp.eval("ph")>=0.):
                    fluxefferrh=gp.eval("ph")
                else:
                    fluxefferrh=0.
                if (fluxefferrh>0. and fluxefferrl>0.):
                    iondata.totfluxfitefferr=(abs(iondata.totfluxfit-fluxefferrh)+abs(fluxefferrl-iondata.totfluxfit))/2.
                elif (fluxefferrh>0.):
                    iondata.totfluxfitefferr=(abs(iondata.totfluxfit-fluxefferrh))
                elif (fluxefferrl>0.):
                    iondata.totfluxfitefferr=(abs(fluxefferrl-iondata.totfluxfit))
                else:
                    iondata.totfluxfitefferr=0.

            """
            if (i==1 and iondata.name=="C4+"):
                plotdata=[]
                for i in range(len(iondata.dens)):
                    print "denserror[",i,"] = ",iondata.denserror[i]
                    if (iondata.denserror[i]!=0.):
                        plotdata.append([iondata.velocity[i]*1000.,iondata.dens[i],iondata.denserror[i]])
                    print "plotdata = ",plotdata
                gpplotdata=Data(plotdata)
                gpplotdata.set_option_colonsep("using", "1:2:3")
                gpplotdata.set_option_colonsep("with", "errorbars")
                gpplotdata.set_option_colonsep("title", "'%.4e+-%.4e'" %(iondata.totdensfit,iondata.totdensfiterror))
                gp("set autoscale")
                gp.plot(gpplotdata,"f(x)")    
                gp.hardcopy("%s.ps"%(iondata.name),color=True, fontsize=18)
                gp("set yrange[-1.e20:1.e20]")
            """
