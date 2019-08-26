#!/usr/bin/python
from numpy import float
from math import sqrt,atan,pi
from Gnuplot import Gnuplot,Data,GnuplotOpts
from scipy import fft

daystart=15
daystop=22
hourstart=0
minutestart=0
secondstart=0
timeres=1.
N=256*4
timeint=(float(N)*timeres)/(24.*60.*60.)
timesteps=84
binning=1
swsp=[]


def int2str(i):
    if (i<10):
        return "00%i"%(i)
    elif (i<100):
        return "0%i"%(i)
    else:
        return "%i"%(i)
    
# get solar wind speed for nominal parker angle
def get_parker_angle(daystart,daystop):
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
            magbz.append([float(k[1]),float(k[4])])
        if ((float(k[2])<-999. or float(k[3])<-999. or float(k[4])<-999.)):
            magbx.append([0.,0.])
            magby.append([0.,0.])
            magbz.append([0.,0.])
            datagap+=1
    magdatain.close()
    return datagap
    print "magdata read!"
    
for time in range(timesteps):
    psdngessum=[]
    gap=0
    doy=float(daystart)+float(hourstart)/24.+float(minutestart)/1440.+float(secondstart)/86400.+float(time)*float(binning)*timeint+float(binning)*0.5*timeint
    print doy
    for bin in range(binning):
        magbx=[]
        magby=[]
        magbz=[]
        magB=[]
        alpha=[]
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
                alpha.append([magbx[i][0],pi/2.])
        
                tmpmagB=sqrt(magbx[i][1]**2+magby[i][1]**2)
                magB.append([magbx[i][0],tmpmagB])
        if (len(alpha)<N):
            for i in range(N-len(alpha)):
                alpha.append([magbx[len(alpha)-1][0]+magbx[1][0]-magbx[0][0],pi/2.])

        alphan=[]
        norm=0.
        for j in range(N):
            norm+=abs(alpha[j][1])
        norm=norm/float(N)
        for i in range(N):
            alphan.append([alpha[i][0],(alpha[i][1]-norm)])

        alphanfft=[]
        for i in range(N):
            alphanfft.append(alphan[i][1])
        psdnraw=fft(alphanfft)
        psdnges=[]
        for i in range(len(psdnraw)/2+1):
            psdnges.append([(float(i)/(float(N)*timeres)),2.*abs(psdnraw[i].imag)/N+2.*abs(psdnraw[i].real)/N])

        if (bin==0):
            psdngessum=psdnges
        if (bin!=0):
            for i in range(len(psdngessum)):
                psdngessum[i][1]+=psdnges[i][1]
    plotpsdngessum=Data(psdngessum)
    plotpsdngessum.set_option_colonsep("with", "lines")
    gp=Gnuplot()
    gp("set title '%f , gap = %i'"%(doy,gap))
    gp("set logscale x")
    gp("set logscale y")
    gp("set yrange[1e-5:0.1]")
    gp("set xrange[0.001:1.]")
    gp.plot(plotpsdngessum)
    gp.hardcopy("%f_%is_%i_%i.ps"%(doy,int(timeres),N,binning), color=True, fontsize=18)
    del gp
