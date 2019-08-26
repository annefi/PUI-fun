#!/usr/bin/python
from numpy import float
from math import sqrt,atan,pi
from Gnuplot import Gnuplot,Data,GnuplotOpts
from scipy import fft

daystart=3
daystop=29
hourstart=0
minutestart=0
secondstart=0
timeres=1.
N=172800/2/2
timeint=(float(N)*timeres)/(24.*60.*60.)
timesteps=27*2
binning=1
swsp=[]
dofft=1
doautocorr=0
doplasmab=0
plasmab=[]

def int2str(i):
    if (i<10):
        return "00%i"%(i)
    elif (i<100):
        return "0%i"%(i)
    else:
        return "%i"%(i)

# get solar wind thermal pressure (from He2+ -> a factor of 20 is applied (*2 ions and electrons *10 He2+ -> ions))  
def get_thermal_pressure(daystart,daystop):
    data=[]
    for i in range(int(daystop)-int(daystart)+1):
        doy=int2str(daystart+i)
        swsplistin=open("/data/kleopatra/ace/1hdata/2007/"+doy+"/list.in")
        swsplistin.readline()
        for name in swsplistin:
            k=name.split()
            swspin=open("/data/kleopatra/ace/1hdata/2007/"+doy+"/erg_"+k[0])
            thpin=open("/data/kleopatra/ace/1hdata/2007/"+doy+"/res_"+k[0])
            s=swspin.readline()
            k=s.split()
            print k[4],k[6]
            time=(float(k[4][5:8])+float(k[4][9:11])/24.+float(k[4][12:14])/(24.*60.)+float(k[4][15:17])/(24.*60.*60.)+float(k[6][5:8])+float(k[6][9:11])/24.+float(k[6][12:14])/(24.*60.)+float(k[6][15:17])/(24.*60.*60.))/2.
            swspin.close()
            thpin.readline()
            s=thpin.readline()
            k=s.split()
            data.append([time,float(k[4]),float(k[10])])
            thpin.close
        swsplistin.close()
    thp=[]
    c=20.*1.38065e-23+1.e6 # 2* boltzmann constant * last term (density from 1/cm3 -> 1/m3)
    for i in range(len(data)):
        tmpthp=c*data[i][1]*data[i][2]
        thp.append([data[i][0],tmpthp])
    return thp
    print "thp read!"



# get solar wind speed for nominal parker angle
def get_parker_angle(daystart,daystop):
    swsp=[]
    for i in range(int(daystop)-int(daystart)+1):
        doy=int2str(daystart+i)
        swsplistin=open("/data/kleopatra/ace/1hdata/2007/"+doy+"/list.in")
        swsplistin.readline()
        for name in swsplistin:
            k=name.split()
            swspin=open("/data/kleopatra/ace/1hdata/2007/"+doy+"/erg_"+k[0])
            s=swspin.readline()
            k=s.split()
            print k[4],k[6]
            time=(float(k[4][5:8])+float(k[4][9:11])/24.+float(k[4][12:14])/(24.*60.)+float(k[4][15:17])/(24.*60.*60.)+float(k[6][5:8])+float(k[6][9:11])/24.+float(k[6][12:14])/(24.*60.)+float(k[6][15:17])/(24.*60.*60.))/2.
            swspin.readline()
            swspin.readline()
            s=swspin.readline()
            k=s.split()
            swsp.append([time,float(k[2])])
            swspin.close
        swsplistin.close()
    pang=[]
    for i in range(len(swsp)):
        tmppang=(2.7e-6*148.5e6)/swsp[i][1]
        pang.append([swsp[i][0],tmppang])
    return pang
    print "swsp read!"


def get_mag_data(start,steps,magbx,magby,magbz):
    # find magfile
    datagap=0
    found = 0
    br=0
    while (found!=1):
        if ((3+br*27<=int(start)) and (29+br*27>=int(start))):
            found = 1
        else:
            br+=1
    magdatain=open("/data/kleopatra/ace/mag/1s2007_%s_%s"%(int2str(3+br*27),int2str(29+br*27)))
    s=magdatain.readline()
    k=s.split()
    while (k[0]!="BEGIN" or k[1]!="DATA"):
        s=magdatain.readline()
        k=s.split()
        if (len(k)<2):
            k=["*","*"]
    s=magdatain.readline()
    k=s.split()
    while (float(k[1])<start):
        s=magdatain.readline()
        k=s.split()
    magbx.append([float(k[1]),float(k[2])])
    magby.append([float(k[1]),float(k[3])])
    magbz.append([float(k[1]),float(k[4])])
    for step in range(steps-1):
        s=magdatain.readline()
        k=s.split()
        if (float(k[2])>-999. and float(k[3])>-999. and float(k[4])>-999.):
            magbx.append([float(k[1]),float(k[2])])
            magby.append([float(k[1]),float(k[3])])
            magbz.append([float(k[1]),abs(float(k[4]))])
        if ((float(k[2])<-999. or float(k[3])<-999. or float(k[4])<-999.)):
            magbx.append([0.,0.])
            magby.append([0.,0.])
            magbz.append([0.,0.])
            datagap+=1
    magdatain.close()
    return datagap
    print "magdata read!"



def get_magnetic_pressure(magbx,magby,magbz):
    magp=[]
    for i in range(len(magbx)):
        magp.append([magbx[i][0],(magbx[i][1]**2+magby[i][1]**2+magbz[i][1]**2)/(2.*1.256637e-6)])
    return magp

def get_plasma_beta(daystart,daystop):
    thp=get_thermal_pressure(daystart,daystop)
    plasmab=[]
    deltat=thp[1][0]-thp[0][0]
    oneh=int(deltat*(86400))
    gap=0
    for time in range(len(thp)):
        time2=0
        mmagp=0.
        magbx,magby,magbz =[],[],[]
        start=thp[time][0]-deltat/2.
        gap+=get_mag_data(start,oneh,magbx,magby,magbz)
        magp=get_magnetic_pressure(magbx,magby,magbz)

        for time2 in range(len(magbx)):
            mmagp+=magp[time2][1]
        mmagp=mmagp/float(oneh)
        if (mmagp!=0.):
            plasmab.append([thp[time][0],thp[time][1]/mmagp])
    return plasmab

def prod(data,step):
    summ=0.
    for i in range(int(float(len(data))/2.)):
        if ((i+step)<len(data)):
            summ+=data[i]*data[i+step]
        if ((i+step)>=len(data)):
            summ+=data[i]*data[i+step-len(data)]
    return summ

def autocorr(data):
    corrdat=[]
    norm=prod(data,0)
    if (norm!=0.):
        for step in range(int(float(len(data))/2.)):
            corrdat.append([float(step),prod(data,step)/norm])
#        if (i!=0):
#            corrdat.append([1./float(i),prod(data,i)])
#        if (i==0):
#            corrdat.append([0.,prod(data,i)])
    return corrdat

def interp_pang(time,pang):
    i=0
    while (pang[i][0]<time):
        i+=1
    i-=1
    deltat=pang[i+1][0]-pang[i][0]
    deltapang=pang[i+1][1]-pang[i][1]
    ipang=(deltapang/deltat)*(time-pang[i][0])+pang[i][1]
    return ipang
    
if (doplasmab):
    plasmab=get_plasma_beta(daystart,daystop)

pang=get_parker_angle(daystart,daystop)

for time in range(timesteps):
    autoc=[]
    psdngessum=[]
    psdagessum=[]
    gap=0
    doy=float(daystart)+float(hourstart)/24.+float(minutestart)/1440.+float(secondstart)/86400.+float(time)*float(binning)*timeint+float(binning)*0.5*timeint
    print doy
    for bin in range(binning):
        magbx=[]
        magby=[]
        magbz=[]
        magB=[]
        alpha=[]
        beta=[]
        start=float(daystart)+float(hourstart)/24.+float(minutestart)/1440.+float(secondstart)/86400.+float(time)*float(binning)*timeint+float(bin)*timeint
        gap+=get_mag_data(start,N,magbx,magby,magbz)
        for i in range(len(magbx)):
            if (magby[i][1]!=0.):
                tmpalpha=0.
                if ((magbx[i][1]>=0. and magby[i][1]<0.)):
                    tmpalpha=atan(abs(magbx[i][1]/magby[i][1]))
                if ((magbx[i][1]<0. and magby[i][1]<0.)):
                    tmpalpha=pi-atan(abs(magbx[i][1]/magby[i][1]))
                if ((magbx[i][1]<0. and magby[i][1]>0.)):
                    tmpalpha=atan(abs(magbx[i][1]/magby[i][1]))
                if ((magbx[i][1]>=0. and magby[i][1]>0.)):
                    tmpalpha=pi-atan(abs(magbx[i][1]/magby[i][1]))
                alpha.append([magbx[i][0],tmpalpha])
            else:
                alpha.append([magbx[i][0],(pi/2.)])

            tmpmagB=sqrt(magbx[i][1]**2+magby[i][1]**2)
            magB.append([magbx[i][0],tmpmagB])
            tmpbeta=0.
            if (sqrt(magbx[i][1]**2+magby[i][1]**2)!=0.):
                tmpbeta=atan(magbz[i][1]/(sqrt(magbx[i][1]**2+magby[i][1]**2)))
            elif (magbz[i][1]<=0.):
                tmpbeta=pi/2.
            else:
                tmpbeta=-pi/2.
            beta.append([magbx[i][0],tmpbeta])

        if (len(alpha)<N):
            for i in range(N-len(alpha)):
                alpha.append([magbx[len(alpha)-1][0]+magbx[1][0]-magbx[0][0],pi/2.])

        alphan=[]
#        norm=0.
#        for j in range(N):
#            norm+=abs(alpha[j][1])
#        norm=norm/float(N)
        for i in range(N):
            tmppang=interp_pang(magbx[i][0],pang)
            alphan.append([alpha[i][0],(alpha[i][1]-tmppang)])
            
        alphanfft=[]
        magbzfft=[]
        betafft=[]
        for i in range(N):
            alphanfft.append(alphan[i][1])
            magbzfft.append(magbz[i][1])
            betafft.append(beta[i][1])
        if (dofft):
            psdnraw=fft(alphanfft)
            psdmagbzraw=fft(magbzfft)
            psdbetaraw=fft(betafft)
            psdnges=[]
            psdmagbzges=[]
            psdbetages=[]
            for i in range(len(psdnraw)/2+1):
                psdnges.append([(float(i)/(float(N)*timeres)),2.*abs(psdnraw[i].imag)/N+2.*abs(psdnraw[i].real)/N])
                psdmagbzges.append([(float(i)/(float(N)*timeres)),2.*abs(psdmagbzraw[i].imag)/N+2.*abs(psdmagbzraw[i].real)/N])
                psdbetages.append([(float(i)/(float(N)*timeres)),2.*abs(psdbetaraw[i].imag)/N+2.*abs(psdbetaraw[i].real)/N])

            if (bin==0):
                psdngessum=psdnges
            if (bin!=0):
                for i in range(len(psdngessum)):
                    psdngessum[i][1]+=psdnges[i][1]
        if (doautocorr):
            autoc=autocorr(alphanfft)
            autocfft=[]
            N2=len(autoc)
            for i in range(N2):
                autocfft.append(autoc[i][1])
            psdaraw=fft(autocfft)
            psdages=[]
            for i in range(len(psdaraw)/2+1):
                psdages.append([(float(i)/(float(N2)*timeres)),2.*abs(psdaraw[i].imag)/N2+2.*abs(psdaraw[i].real)/N2])

            if (bin==0):
                psdagessum=psdages
            if (bin!=0):
                for i in range(len(psdagessum)):
                    psdagessum[i][1]+=psdages[i][1]
    if (doautocorr):
        plotpsdagessum=Data(psdagessum)
        plotpsdagessum.set_option_colonsep("with", "lines")
        plotautoc=Data(autoc)
        plotautoc.set_option_colonsep("with", "lines")
    if (dofft):
        plotpsdngessum=Data(psdngessum)
        plotpsdngessum.set_option_colonsep("with", "lines")
        plotpsdmagbzges=Data(psdmagbzges)
        plotpsdmagbzges.set_option_colonsep("with", "lines")
        plotalphan=Data(alphan)
        plotalphan.set_option_colonsep("with", "lines")
        plotbeta=Data(beta)
        plotbeta.set_option_colonsep("with", "lines")
        plotpsdbetages=Data(psdbetages)
        plotpsdbetages.set_option_colonsep("with", "lines")

    if (dofft):
        gp=Gnuplot()
        gp("set title '%f , gap = %i'"%(doy,gap))
        gp("set logscale x")
        gp("set logscale y")
        gp("set yrange[1e-5:10.]")
        gp("set xrange[1e-6:1.]")
        gp.plot(plotpsdngessum)
        gp.hardcopy("%f_%is_%i_%i.ps"%(doy,int(timeres),N,binning), color=True, fontsize=18)
        gp2=Gnuplot()
        gp2("set title '%f , gap = %i'"%(doy,gap))
        gp2("set logscale x")
        gp2("set logscale y")
        gp2("set yrange[1e-5:1.]")
        gp2("set xrange[1e-5:1.]")
#        gp2("set autoscale")
        gp2.plot(plotpsdbetages)
        gp2.hardcopy("beta_%f_%is_%i_%i.ps"%(doy,int(timeres),N,binning), color=True, fontsize=18)
        del gp
        del gp2
    if (doautocorr):
        gp=Gnuplot()
        gp("set title '%f , gap = %i'"%(doy,gap))
#        gp("set logscale x")
#        gp("set logscale y")
        gp("set yrange[-1:1]")
#        gp("set xrange[0.001:1.]")
        gp.plot(plotautoc)
        gp.hardcopy("autocorr_%f_%is_%i_%i.ps"%(doy,int(timeres),N,binning), color=True, fontsize=18)
        gp("set logscale x")
        gp("set logscale y")
#        gp("set yrange[1e-3:1.]")
#        gp("set xrange[0.001:1.]")
        gp("set autoscale")
        gp.plot(plotpsdagessum)
        gp.hardcopy("autocorrfft_%f_%is_%i_%i.ps"%(doy,int(timeres),N,binning), color=True, fontsize=18)
        del gp

if (doplasmab):
    plotplasmab=Data(plasmab)
    plotplasmab.set_option_colonsep("with", "lines")
    gp=Gnuplot()
    gp("set title 'Plasma Beta'")
#    gp("set logscale x")
    gp("set logscale y")
#    gp("set yrange[1e-5:0.1]")
#    gp("set xrange[0.001:1.]")
    gp.plot(plotplasmab)
    gp.hardcopy("plasma_beta.ps", color=True, fontsize=18)
    del gp
