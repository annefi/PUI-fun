from math import pi,cos,sin,atan,tan,acos,asin,sqrt
from Gnuplot import Gnuplot,GridData,Data
from scipy import zeros
from libacepy.ancil import histogram,sig_histogram
from libacepy.newdutycycle import dutycycle
from libacepy.swicsiondata import swicsiondata
from libacepy.mag import magdata
from libacepy.attitude import attdata,sync_attitude
from libacepy.swepamdata import swepamdata
from libacepy.multiplot import multiplot
from libacepy.swicsprotondata import swicsprotondata

def calc_newasp(bx,bz,ax,az):
    b=acos(cos(bx)*cos(bz))
    a=acos(cos(bx-ax)*cos(bz-az))
    an0=acos((cos(bz)*sin(ax)*sin(az)-sin(bx)*sin(bz)*cos(az))/sqrt(cos(bz)**2+(sin(bx)*sin(bz))**2))
    if (an0<=pi/2.):
        anz=pi/2.-an0
    else:
        anz=an0-pi/2.
    i=0
    j=0
    if (cos(a)/cos(anz)>1.):
        while (cos(a)/cos(anz)-float(i)>1.):
            i+=1
    if (cos(a)/cos(anz)<-1):
        while (cos(a)/cos(anz)+float(j)<-1.):
            j+=1
    if (cos(anz)!=0.):
        anx=b-acos(cos(a)/cos(anz)-float(i)+float(j))
    else:
        anx=b
    return [anx,anz]

def getperiod(time,timeframe):
    p=0
    for i in range(len(timeframe)):
        if (time>=timeframe[i][0] and time<=timeframe[i][1]):
            return i
    return -1

def getquadrant(phi):
    if (phi>0. and phi<=pi/2.):
        return 1
    elif (phi>pi/2. and phi<=pi):
        return 2
    elif (phi<0. and phi>=-pi/2.):
        return 4
    elif (phi<-pi/2. and phi>=-pi):
        return 3
    else:
        return 0

year=2007
resswics=720.
resswepam=64.
resmag=240.
timeframe=[[4.,9.],[17.4,25.25],[30.5,35.],[45.5,55.],[60.,63.],[65.5,70.],[73.25,80.5],[93.,97.5],[103.,107.],[119.,126.5],[129.,135.],[145.25,151.1]]
#timeframe=[[70.,75.]]
#timeframe=[[73.25,80.5]]
#timeframe=[[30.5,35.]]
timeframe=[[3.5,9.],[17.5,29.],[30.,36.],[45.5,56.5],[59.5,63.5],[66.5,70.],[73.5,82.],[92.5,98.5],[106.,107.],[110.,112.],[118.5,126.5],[128.5,137.5],[139.5,141.5],[145.,151.5],[156.,158.5],[161.5,164.],[166.,172.],[174.5,179.5],[181.5,184.],[186.,191.5],[192.5,194.5],[196.5,201.],[203.,207.],[208.5,209.5],[211.,212.5],[214.,217.],[219.5,222.],[223.,226.5],[232.,237.],[239.5,243.],[246.,249.],[258.5,262.5],[265.5,270.5],[272.5,275.5],[277.,282.],[292.5,298.],[299.,302.],[303.5,312.5],[315.,316.],[318.,323.5],[325.,326.5],[327.,328.5],[329.,338.5],[339.5,344.],[346.,351.],[352.,354.],[355.,359.5],[362.,365.]]
timeframe=[[3.5,9.],[17.5,29.],[30.,36.],[45.5,56.5],[59.5,63.5],[66.5,70.],[73.5,82.],[92.5,98.5],[106.,107.],[110.,112.],[118.5,126.5],[128.5,137.5],[139.5,141.5],[145.,151.5],[156.,158.5],[161.5,164.],[166.,172.],[174.5,179.5],[181.5,184.],[186.,191.5],[192.5,194.5],[196.5,201.],[203.,207.],[208.5,209.5],[211.,212.5],[214.,217.],[219.5,222.],[223.,226.5],[232.,237.],[239.5,243.],[246.,249.],[258.5,262.5],[265.5,270.5],[272.5,275.5],[277.,282.],[299.,302.],[303.5,312.5],[315.,316.],[318.,323.5],[325.,326.5],[327.,328.5],[329.,338.5],[339.5,344.],[346.,351.],[352.,354.],[355.,359.5],[362.,365.]]
timeframe=[[45.5,56.5]]
effpath="/data/ivar/ace/efficencies/aspeff/"
datapath="/data/wimmer/ace/"
datapath2="/data/zechine/ace/12mprotons/2008/"
swepampath="/data/ivar/ace/swepam/"
magpath="/data/missions/ace/mag/lv2/"
magpath="/data/wimmer/ace/mag/"
ionlist=["He2+"]# ,"O6+","Fe9+"]
#swepam=swepamdata(resswepam,year,timeframe,swepampath)
#mag=magdata(resmag,year,timeframe,magpath)
#att=attdata(mag.year,mag.path)
#att.load()

pnrdvhist=[]
pnrdvhist2=[]
pdvhist=[]
pdvhist2=[]
pdvmqhist=[]
ptemphist=[]
pdenshist=[]
pvthhist=[]
pvthhist2=[]
swepamvel=[]
swepamvthhist=[]
gp=Gnuplot()
gp2=Gnuplot()
gp3=Gnuplot()
gp4=Gnuplot()
gp5=Gnuplot()
irst=1
magdirarr=[]
meanvalf=[]
meanv=[]
meanb=[]
meanbx=[]
meanbz=[]
meanax=[]
meanaz=[]

#iondata=swicsiondata(ionlist[0],resswics,year,timeframe,datapath)
#mag.sync_mag(iondata)
#swepam.sync_h(iondata)
#syncatt=sync_attitude(att,iondata)


polarity=zeros([len(timeframe)])

uppervel=700.
lowervel=600.
linetype=0
for ion in ionlist:
    iondata=swicsiondata(ion,resswics,year,timeframe,datapath)
    #if (ion!="He2+"):
    #    hedata=swicsiondata("He2+",resswics,year,timeframe,datapath)
    #else:
    #    hedata=iondata
    #iondata.load()
    swepam=swepamdata(resswepam,year,timeframe,swepampath)
    mag=magdata(resmag,year,timeframe,magpath)
    att=attdata(mag.year,mag.path)
    att.load()
    mag.sync_mag(iondata)
    swepam.sync_h(iondata)
    syncatt=sync_attitude(att,iondata)

    dblistin=open("sigb_2007.dat")
    dblistin.readline()

    sigarr=[]
    barr=[]
    i=0
    for s in dblistin:
        k=s.split()
        if (float(k[0])>iondata.time[i]-0.001 and float(k[0])<iondata.time[i]+0.001 and i<len(iondata.time)-2):
                  i+=1
                  sigarr.append([float(k[0]),float(k[2])])
                  #if (float(k[1])>0.):
                  #    sigarr.append([float(k[0]),float(k[2])/float(k[1])])
                  #else:
                  #    sigarr.append([float(k[0]),0.])
                  barr.append([float(k[0]),float(k[1])])
    dblistin.close()

    p=-1
    for period in timeframe:
        p+=1
        meanphi=0.
        nrphi=0.
        for i in range(len(swepam.time)):
            if (swepam.time[i]>period[0] and swepam.time[i]<period[1] and swepam.vel[i]>600.):
                meanphi+=mag.phi[i]
                nrphi+=1.
        if (nrphi>0.):
            meanphi/=nrphi
        if (meanphi>0.):
        #if (meanphi>-pi/4. and meanphi<pi*3./4.):
            polarity[p]=1.
        elif (meanphi<0.):
            polarity[p]=-1.
        else:
            polarity[p]=0.

    

    # build all arrays for histograms!
    dvarr=[]
    dvarr2=[]
    vtharr=[]
    vtharr2=[]
    temparr=[]
    densarr=[]
    swepamvth=[]
    
    #j=0
    meansig=0.
    nrmeansig=0.
    meanplb=0.
    nrmeanplb=0.
    meancolage=0.
    nrmeancolage=0.
    for i in range(len(iondata.time)):
        if (1):
            p=-1
            # calculate mag angle
            if (mag.phi[i]!=0. and mag.theta[i]!=0. and swepam.vel[i]>0.):
            #if (((mag.phi[i]<0. and mag.phi[i]>-pi/2.) or (mag.phi[i]>pi/2. and mag.phi[i]<pi)) and mag.theta[i]!=0. and swepam.vel[i]>0.):
            #if (((mag.phi[i]>-pi/2. and mag.phi[i]<-pi)) and mag.theta[i]!=0. and swepam.vel[i]>0.):
            #if (((mag.phi[i]>0. and mag.phi[i]<pi/2.) or (mag.phi[i]<-pi/2. and mag.phi[i]>-pi)) and mag.theta[i]!=0. and swepam.vel[i]>0.):
            
                #tmpmag=acos(abs(cos(mag.phi[i][1]-syncatt.phi[i])*cos(mag.theta[i][1]-syncatt.theta[i])))
                #tmpmag=acos((cos(mag.phi[i]+atan(30./swepam.vel[i]))*cos(mag.theta[i])))
                tmpmag=acos(cos(mag.phi[i])*cos(mag.theta[i]))
            else:
                tmpmag=0.
            # calculate alfvenspeed
            if (swepam.dens[i]>0.):
                valf=21.8*mag.magb[i]/sqrt(swepam.dens[i])
            else:
                valf=0.
            if (swepam.dens[i]>0. and swepam.time[i]>0. and mag.magb[i]>0.):
                plbeta=3.47e-5*swepam.dens[i]*swepam.temp[i]/(mag.magb[i])**2.
                #plbeta=(1.3806504e-23*2.*1.2566)*(swepam.dens[i]*swepam.temp[i]*2.)/(mag.magb[i]*1e-9)**2.
                #print "time : ",iondata.time[i]," ; pbeta : ",plbeta
            else:
                plbeta=0.0
            if (swepam.vel[i]>0. and swepam.temp[i]>0.):
                colage=(6.4e8*swepam.dens[i])/(swepam.vel[i]*(swepam.temp[i])**1.5)
            else:
                colage=0.

            p=getperiod(iondata.time[i],iondata.timeframe)
            #if (iondata.vel[i]>600. and swepam.vel[i]>0. and valf>0. and tmpmag!=0. and mag.phi[i]*mag.dpp[i]<pi/180.*11.5 and mag.theta[i]*mag.dtt[i]<pi/180.*11.5 and iondata.crvth[i]>10.):
            #if (iondata.vel[i]>600. and iondata.vel[i]<700. and swepam.vel[i]>500. and valf>0. and tmpmag!=0. and p>=0.):# and plbeta>3. and plbeta<4.):# and mag.phi[i]*mag.dpp[i]<pi/180.*11.5 and mag.theta[i]*mag.dtt[i]<pi/180.*11.5 and iondata.crvth[i]>0.):
            #while (sigarr[j][0]-0.0001<iondata.time[i] and j<len(sigarr)-2):
            #    j+=1
            #j-=1
            if (swepam.vel[i]>lowervel and swepam.vel[i]<uppervel and iondata.vel[i]>lowervel-3.*valf and iondata.vel[i]<uppervel+3.*valf and valf>0. and tmpmag!=0. and p>=0. and sigarr[i][1]>.0 and sigarr[i][1]<12.):# and plbeta>3. and plbeta<4.):# and mag.phi[i]*mag.dpp[i]<pi/180.*11.5 and mag.theta[i]*mag.dtt[i]<pi/180.*11.5 and iondata.crvth[i]>0.):
                meansig+=sigarr[i][1]/barr[i][1]
                nrmeansig+=1
                meanplb+=plbeta
                nrmeanplb+=1
                if (colage>0.):
                    meancolage+=colage
                    nrmeancolage+=1
                #print sigarr[i][0],iondata.time[i]
                q=getquadrant(mag.phi[i])
                tmpasp=calc_newasp(mag.phi[i],mag.theta[i],syncatt.phi[i],syncatt.theta[i])
                if (polarity[p]==1. and (q==1 or q==4)):
                    dvarr.append([tmpmag,((iondata.vel[i]-swepam.vel[i])/valf)])#/abs(cos(tmpmag))])
                    vtharr.append([tmpmag,iondata.crvth[i]])
                if (polarity[p]==-1. and (q==2 or q==3)):
                    dvarr.append([tmpmag,((iondata.vel[i]-swepam.vel[i])/valf)])#/abs(cos(tmpmag))])
                    vtharr.append([tmpmag,iondata.crvth[i]])
                if (polarity[p]==1. and (q==2 or q==3)):
                    dvarr2.append([tmpmag,((iondata.vel[i]-swepam.vel[i])/valf)])#/abs(cos(tmpmag))])
                    vtharr2.append([tmpmag,iondata.vth[i]])
                if (polarity[p]==-1. and (q==1 or q==4)):
                    dvarr2.append([tmpmag,((iondata.vel[i]-swepam.vel[i])/valf)])#/abs(cos(tmpmag))])
                    vtharr2.append([tmpmag,iondata.vth[i]])
                temparr.append([tmpmag,iondata.temp[i][0]])
                densarr.append([tmpmag,iondata.dens[i][0]])
                meanvalf.append([tmpmag,valf])
                meanbx.append([tmpmag,mag.phi[i]])
                meanbz.append([tmpmag,mag.theta[i]])
                meanb.append([tmpmag,tmpmag])
                meanax.append([tmpmag,tmpasp[0]])
                meanaz.append([tmpmag,tmpasp[1]])
                meanv.append([tmpmag,swepam.vel[i]])
    if (nrmeansig>0):
        meansig/=nrmeansig
    print "Mean Bsig = ",meansig
    if (nrmeanplb>0):
        meanplb/=nrmeanplb
    print "Mean PlBeta = ",meanplb
    if (nrmeancolage>0):
        meancolage/=nrmeancolage
    print "Mean Colage = ",meancolage
                
    # end building arrays
    """
    valfhist=histogram(meanvalf,0.,0.2,8,3)
    sigvalfhist=sig_histogram(meanvalf,valfhist,3)
    bxhist=histogram(meanbx,0.,0.2,8,3)
    bzhist=histogram(meanbz,0.,0.2,8,3)
    bhist=histogram(meanb,0.,0.2,8,3)
    axhist=histogram(meanax,0.,0.2,8,3)
    azhist=histogram(meanaz,0.,0.2,8,3)
    vhist=histogram(meanv,0.,0.2,8,3)

    """
    binnr=17
    binw=pi/float(binnr-1)
    """

    dvhist=histogram(dvarr,0.,binw,binnr,4)
    #dvhist.append([1.6,0.,0])
    sigdvhist=sig_histogram(dvarr,dvhist,4)
    dverr=[]
    for i in range(len(dvhist)):
        dverr.append([dvhist[i][0],dvhist[i][1],sigdvhist[i][1]/sqrt(sigdvhist[i][2]+1.)])
    pdvhist.append(Data(dverr))
    pdvhist[-1].set_option_colonsep("title","'Observations'")
    pdvhist[-1].set_option_colonsep("with","yerrorbars lt 1 lw 2")
    pdvhist[-1].set_option_colonsep("using","1:2:3")
    """
    print len(dvarr),len(dvarr2),len(vtharr),len(vtharr2)
    if (len(dvarr)==0):
        dvarr.append([0.0,0.0])
    if (len(dvarr2)==0):
        dvarr2.append([0.0,0.0])
    if (len(vtharr)==0):
        vtharr.append([0.0,0.0])
    if (len(vtharr2)==0):
        vtharr2.append([0.0,0.0])
    if linetype!=1:
        linetype+=1
    else:
        linetype+=2
    dvhist=histogram(dvarr,0.,binw,binnr,3)
    pdvhist.append(Data(dvhist))
    pdvhist[-1].set_option_colonsep("title","'%s Earth-pointing'"%(ion))
    pdvhist[-1].set_option_colonsep("with","steps lt %i lw 2"%(linetype))
    pdvhist[-1].set_option_colonsep("using","1:2")
    nrdvhist=dvhist
    for val in nrdvhist:
        val[0]+=(nrdvhist[1][0]-nrdvhist[0][0])/2.
    pnrdvhist.append(Data(nrdvhist))
    pnrdvhist[-1].set_option_colonsep("title","''")
    pnrdvhist[-1].set_option_colonsep("axes","x1y2")
    pnrdvhist[-1].set_option_colonsep("with","p lt %i lw 2"%(linetype))
    pnrdvhist[-1].set_option_colonsep("using","1:3")

    if linetype!=1:
        linetype+=1
    else:
        linetype+=2
    dvhist2=histogram(dvarr2,0.,binw,binnr,3)
    pdvhist2.append(Data(dvhist2))
    pdvhist2[-1].set_option_colonsep("title","'%s Sun-pointing'"%(ion))
    pdvhist2[-1].set_option_colonsep("with","steps lt %i lw 2"%(linetype))
    pdvhist2[-1].set_option_colonsep("using","1:2")
    nrdvhist2=dvhist2
    for val in nrdvhist2:
        val[0]+=(nrdvhist2[1][0]-nrdvhist2[0][0])/2.
    pnrdvhist2.append(Data(nrdvhist2))
    pnrdvhist2[-1].set_option_colonsep("title","''")
    pnrdvhist2[-1].set_option_colonsep("axes","x1y2")
    pnrdvhist2[-1].set_option_colonsep("with","p lt %i lw 2"%(linetype))
    pnrdvhist2[-1].set_option_colonsep("using","1:3")
    """
    vthhist=histogram(vtharr,0.,binw,binnr,4)
    sigvthhist=sig_histogram(vtharr,vthhist,4)
    vtherr=[]
    for i in range(len(dvhist)):
        vtherr.append([vthhist[i][0],vthhist[i][1],sigvthhist[i][1]/sqrt(sigvthhist[i][2]+1.)])
    """
    vthhist=histogram(vtharr,0.,binw,binnr,3)
    pvthhist.append(Data(vthhist))
    pvthhist[-1].set_option_colonsep("title","'Earth-pointing'")
    pvthhist[-1].set_option_colonsep("with","steps lt 1 lw 2")
    pvthhist[-1].set_option_colonsep("using","1:2")
    vthhist2=histogram(vtharr2,0.,binw,binnr,3)
    pvthhist2.append(Data(vthhist2))
    pvthhist2[-1].set_option_colonsep("title","'Sun-pointing'")
    pvthhist2[-1].set_option_colonsep("with","steps lt 3 lw 2")
    pvthhist2[-1].set_option_colonsep("using","1:2")

"""
tratio=1.9
beampos=1.3
vthperp=vthhist[len(vthhist)-2][1]-0.5
vthpara=vthperp/sqrt(tratio)
ratio=[0.8]
deg=pi/180.
magang=[0.1,0.3,0.5,0.7,0.9,1.1,1.3,1.5]
dutyc=[]
dutycp=[]
dutycm=[]
dbeampos=0.0
dpratio=0.0
dtratio=0.01
dpvthpara=vthperp/sqrt(tratio+dtratio)
dmvthpara=vthperp/sqrt(tratio-dtratio)
shift=[]
for i in range(len(magang)):
    shift.append(0.05*valfhist[i][1]*cos(bhist[i][1]))
    #shift.append(0.)

print iondata.name
print "vthperp = ",vthperp
print "vthpara = ",vthpara
print "B-Ratio = ",ratio[0]/(1.+ratio[0]),ratio[0]
print "T-Ratio = ",tratio
print "BeamPos = ",beampos
i=0
for maga in magang:
    for pratio in ratio:
        dutyc.append(dutycycle(vhist[i][1]+shift[i],beampos*valfhist[i][1],bhist[i][1],0.,axhist[i][1],azhist[i][1],.1,pratio,vthpara,vthperp/vthpara,iondata.countspec[0],iondata.name,iondata.mass,iondata.charge,effpath))
        i+=1
"""
"""
        dutycp.append(dutycycle(vhist[i][1]+shift[i],(beampos+dbeampos)*valfhist[i][1],bhist[i][1],0.,axhist[i][1],azhist[i][1],.1,pratio+dpratio,vthpara,vthperp/dpvthpara,iondata.countspec[0],iondata.name,iondata.mass,iondata.charge,effpath))
        dutycm.append(dutycycle(vhist[i][1]+shift[i],(beampos-dbeampos)*valfhist[i][1],bhist[i][1],0.,axhist[i][1],azhist[i][1],.1,pratio-dpratio,vthpara,vthperp/dmvthpara,iondata.countspec[0],iondata.name,iondata.mass,iondata.charge,effpath))
"""
"""
for d in dutyc:
    print "calc duty mag : ",acos(cos(d.bxy)*cos(d.bz)),acos(cos(d.axy)*cos(d.az))," bx = ",d.bxy," bz = ",d.bz," ax = ",d.axy," az = ",d.az
    d.calc_duty_cycle()
"""
"""
for d in dutycp:
    print "calc dutyp mag : ",acos(cos(d.bxy)*cos(d.bz)),acos(cos(d.axy)*cos(d.az))," bx = ",d.bxy," bz = ",d.bz," ax = ",d.axy," az = ",d.az
    d.calc_duty_cycle()
for d in dutycm:
    print "calc dutym mag : ",acos(cos(d.bxy)*cos(d.bz)),acos(cos(d.axy)*cos(d.az))," bx = ",d.bxy," bz = ",d.bz," ax = ",d.axy," az = ",d.az
    d.calc_duty_cycle()
"""
"""    
comdiff=[]
sig=[]
i=0
for d in dutyc:
    comdiff.append([i*0.2,(d.vsvel-vhist[i][1])/valfhist[i][1]])
    sig.append([i*0.2,d.prvth])
    i+=1
comdiff.append([1.6,0.])
sig.append([1.6,0.])

"""
"""
dpcomdiffvs=[]
dpsig=[]
i=0
for d in dutyc:
    dpcomdiffvs.append([i*0.2,((dutycp[i].vsvel-d.vsvel)/dtratio)/valfhist[i][1]])
    dpsig.append([i*0.2,(dutycp[i].vsvth-d.vsvth)/dtratio])
    i+=1

dmcomdiffvs=[]
dmsig=[]
i=0
for d in dutyc:
    dmcomdiffvs.append([i*0.2,((d.vsvel-dutycm[i].vsvel)/dtratio)/valfhist[i][1]])
    dmsig.append([i*0.2,(d.vsvth-dutycm[i].vsvth)/dtratio])
    i+=1
"""
"""
comdiffvs=[]
sigvs=[]
i=0
for d in dutyc:
    comdiffvs.append([i*0.2,(d.prvel-vhist[i][1])/valfhist[i][1]])
    sigvs.append([i*0.2,d.vsvth])
    i+=1
comdiffvs.append([1.6,0.])
sigvs.append([1.6,0.])


print "model parameter : Tratio = ",tratio," Beampos = ",beampos," Iratio = ",ratio[0]


pdvhisttheo=Data(comdiff)
pdvhisttheo.set_option_colonsep("title","'Model'")
pdvhisttheo.set_option_colonsep("with","steps lt 3")
pdvhisttheo.set_option_colonsep("using","1:2")
pvthhisttheo=Data(sig)
pvthhisttheo.set_option_colonsep("title","'Model'")
pvthhisttheo.set_option_colonsep("with","steps lt 3")
pvthhisttheo.set_option_colonsep("using","1:2")
pdvhisttheovs=Data(comdiffvs)
pdvhisttheovs.set_option_colonsep("title","'Model'")
pdvhisttheovs.set_option_colonsep("with","steps lt 3 lw 2")
pdvhisttheovs.set_option_colonsep("using","1:2")
pvthhisttheovs=Data(sigvs)
pvthhisttheovs.set_option_colonsep("title","'Model'")
pvthhisttheovs.set_option_colonsep("with","steps lt 3 lw 2")
pvthhisttheovs.set_option_colonsep("using","1:2")
"""

a=mag.getvals(["time","phi"])
b=mag.getvals(["time","theta"])
c=mag.getvals(["time","phi"])
for i in range(len(c)):
    c[i,1]=acos(cos(a[i,1])*cos(b[i,1]))
#c[:,1]-=pi/2.
#c[:,1]=-c[:,1]
d=iondata.getvals(["time","vel"])
d[:,1]/=100
pa=Data(a)
pa.set_option_colonsep("with","l lt 1")
pb=Data(b)
pc=Data(c)
pc.set_option_colonsep("with","l lt 3")
pd=Data(d)
pd.set_option_colonsep("with","l lt 4")

denssw=iondata.getvals(["time","dens"])
dens=swepam.getvals(["time","dens"])
vel=iondata.getvals(["time","vel"])
vels=swepam.getvals(["time","vel"])
temp=iondata.getvals(["time","temp"])
temps=swepam.getvals(["time","temp"])
magb=mag.getvals(["time","magb"])
prdbb=mag.getvals(["time","prdbb"])
dbb=mag.getvals(["time","dbb"])
dbb[:,1]*=magb[:,1]
valf=zeros([len(dens)])
dv=zeros([len(dens),2])
colage=zeros([len(dens),2])
plbeta=zeros([len(dens),2])
agebeta=zeros([len(dens),2])
for i in range(len(dens)):
    if (vels[i,1]>0. and temp[i,1]>0. and temps[i,1]>0.):
        colage[i,1]=(6.4e8*dens[i,1])/(vels[i,1]*(temps[i,1]+temp[i,1]/4.)**1.5)
    if (dens[i,1]>0. and temp[i,1]>0.):
        #a1=(1.3806504e-23*2.*1.2566)
        #a2=(dens[i,1]*temps[i,1]+denssw[i,1]*temp[i,1]+(dens[i,1]+denssw[i,1]*2.)*temp[i,1])
        #a3=(magb[i,1]*1e-9)**2
        #plbeta[i,1]=(a1*a2)/a3
        #plbeta[i,1]=(1.3806504e-23*2.*1.2566)*(dens[i,1]*temps[i,1]+denssw[i,1]*temp[i,1]+(dens[i,1]+denssw[i,1]*2.)*temp[i,1])/(magb[i,1]*1e-9)**2.
        plbeta[i,1]=(1.3806504e-23*2.*1.2566)*(dens[i,1]*temps[i,1]*2.)/(magb[i,1]*1e-9)**2.
    if (dens[i,1]>0.):
        valf[i]=21.8*magb[i,1]/sqrt(dens[i,1])
    if (colage[i,1]>0.):
        agebeta[i,1]=1./colage[i,1]*plbeta[i,1]
for i in range(len(dens)):
    dv[i,0]=dens[i,0]
    colage[i,0]=dens[i,0]
    plbeta[i,0]=dens[i,0]
    agebeta[i,0]=dens[i,0]
    if (valf[i]>0.):
        dv[i,1]=((vel[i,1]-vels[i,1])/valf[i])
        #dv[i,1]=((vel[i,1]-vels[i,1])/valf[i])*2.
        #dv[i,1]=((vel[i,1]-vels[i,1]))
pprdbb=Data(prdbb)
pprdbb.set_option_colonsep("with","l lt 8")
pdbb=Data(dbb)
pdbb.set_option_colonsep("with","l lt 4")
pcolage=Data(colage)
pcolage.set_option_colonsep("with","l lt 6")
pagebeta=Data(agebeta)
pagebeta.set_option_colonsep("with","l lt 7")
pbeta=Data(plbeta)
pbeta.set_option_colonsep("with","l lt 7")
pdv=Data(dv)
pdv.set_option_colonsep("with","l lt 1")

gp=Gnuplot()
gp("f(x)=pi/2.")
gp("f2(x)=0.")
gp("f3(x)=-pi/2.")
gp("f4(x)=pi")
gp("f5(x)=-pi")
gp("f6(x)=6.")
#gp("set xrange[73.25:76]")
#gp.plot(pc,pd,pdv,pdbb,pprdbb,"f(x) with l lt 0 title ''","f2(x) with l lt 0 title ''","f3(x) with l lt 0 title ''","f4(x) with l lt 0 title ''","f5(x) with l lt 0 title ''")#,"f6(x) with l lt -1 title ''")
gp.plot(pc,pd,pdv,"f(x) with l lt 0 title ''","f2(x) with l lt 0 title ''","f3(x) with l lt 0 title ''","f4(x) with l lt 0 title ''","f5(x) with l lt 0 title ''")#,"f6(x) with l lt -1 title ''")
gp.hardcopy("mag.ps",color="true",fontsize=20)

gp2("set autoscale")
gp2("set ylabel '{/Symbol D}v/v_{Alf}'")
gp2("set xlabel '{/Symbol b} [rad]'")
#gp2("set grid back")
gp2("set format y '%.2f'")
gp2("set yrange[-.8:.8]")
gp2("set y2range[0.:1000.]")
gp2("set y2tics auto")
gp2("set autoscale y2")
gp2("set xrange[0:3.2]")
gp2("set xtics ('0' 0,'pi/4' %f,'pi/2' %f,'pi3/4' %f,'pi' %f)"%(pi/4.,pi/2.,pi*3./4.,pi))
#gp2("c(x)=0.5*cos(x)")
#gp2.plot(pdvhist2[len(pdvhist2)-1],pdvhisttheo,pdvhist[len(pdvhist)-1],pdvhisttheovs)
#gp2.plot(pdvhist[-1],pdvhisttheovs)
#gp2.plot(pdvhist[-1],pdvhist2[-1])#,"c(x)")
gp2.plot(pdvhist[0],pdvhist2[0],pnrdvhist[0],pnrdvhist2[0])#,pdvhist[1],pdvhist2[1],pnrdvhist[1],pnrdvhist2[1],pdvhist[2],pdvhist2[2],pnrdvhist[2],pnrdvhist2[2])#,"c(x)")
gp2("set term postscript color 20 lw 2 eps")
gp2.hardcopy("newdv_%s.ps"%(iondata.name),color="true",fontsize=20)
#gp2.hardcopy("dvvirtobs_%s.ps"%(iondata.name),color="true",fontsize=20)

gp4("set autoscale")
gp4("set ylabel 'vth [km^{1}s^{-1}]'")
gp4("set xlabel '{/Symbol b} [rad]'")
#gp4("set grid back")
gp4("set format y '%.1f'")
gp4("set xrange[0:3.2]")
gp4("set yrange[40:50]")
gp4("set xtics ('0' 0,'pi/4' %f,'pi/2' %f,'pi3/4' %f,'pi' %f)"%(pi/4.,pi/2.,pi*3./4.,pi))
#gp4.plot(pvthhist2[len(pvthhist2)-1],pvthhisttheo,pvthhist[len(pvthhist)-1],pvthhisttheovs)
#gp4.plot(pvthhist[-1],pvthhisttheovs)
gp4.plot(pvthhist[-1],pvthhist2[-1])
gp4("set term postscript color 20 lw 2 eps")
gp4.hardcopy("newvth_%s.ps"%(iondata.name),color="true",fontsize=20)


def getperiod(time,timeframe):
    p=0
    for i in range(len(timeframe)):
        if (time>=timeframe[i][0] and time<=timeframe[i][1]):
            return i
    return -1

def getquadrant(phi):
    if (phi>0. and phi<=pi/2.):
        return 1
    elif (phi>pi/2. and phi<=pi):
        return 2
    elif (phi<0. and phi>=-pi/2.):
        return 4
    elif (phi<-pi/2. and phi>=-pi):
        return 3
    else:
        return 0
