from math import pi,cos,sin,atan,tan,acos,asin,sqrt,log10
from Gnuplot import Gnuplot,GridData,Data
from scipy import zeros
from libacepy.ancil import histogram,sig_histogram,numint
from libacepy.newdutycycle import dutycycle
from libacepy.swicsiondata import swicsiondata
from libacepy.mag import magdata,get_wpspec
from libacepy.attitude import attdata,sync_attitude
from libacepy.swepamdata import swepamdata
from libacepy.multiplot import multiplot
from libacepy.swicsprotondata import swicsprotondata

def getvd(vp0,vi,beta,polarity):
    vp=vp0
    if (polarity==1.):
        if vp**2*cos(pi-beta)**2+vi**2-vp**2>=0.:
            vd1=vp*cos(pi-beta)+sqrt(vp**2*cos(pi-beta)**2+vi**2-vp**2)
            vd2=vp*cos(pi-beta)-sqrt(vp**2*cos(pi-beta)**2+vi**2-vp**2)
            #if vd1<0.:
            #    vd1=0.
            #if vd2<0.:
            #    vd2=0.
            #if beta<pi/2.:
            #    print "dv,vd1,vd2 =",vi-vp,vd1,vd2
            #if (vd1<100. and vd2<100. and vd1>-100. and vd2>-100.):
            #    return (abs(vd1)+abs(vd2))/2.
            if (vd1<100. and vd2<100. and vd1>-100. and vd2>-100.):
                return (abs(vd1)+abs(vd2))/2.
            elif (abs(vd1)<100.):
                return abs(vd1)
            elif (abs(vd2)<100.):
                return abs(vd2)
            else:
                return 0.
        else:
            return 0.
    elif (polarity==-1.):
        if vp**2*cos(beta)**2+vi**2-vp**2>=0.:
            vd1=vp*cos(beta)+sqrt(vp**2*cos(beta)**2+vi**2-vp**2)
            vd2=vp*cos(beta)-sqrt(vp**2*cos(beta)**2+vi**2-vp**2)
            #if vd1<0.:
            #    vd1=0.
            #if vd2<0.:
            #    vd2=0.
            #print "dv,vd1,vd2 =",vi-vp,vd1,vd2
            if (vd1<100. and vd2<100. and vd1>-100. and vd2>-100.):
                return (abs(vd1)+abs(vd2))/2.
            elif (abs(vd1)<100.):
                return abs(vd1)
            elif (abs(vd2)<100.):
                return abs(vd2)
            else:
                return 0.
        else:
            return 0.
    else:
        return 0.


def get_korreff(arr):
    meanx=0.
    meany=0.
    for val in arr:
        meanx+=val[0]
        meany+=val[1]
    if len(arr)>0.:
        meanx/=float(len(arr))
        meany/=float(len(arr))
    sum1=0.
    sum2=0.
    sum3=0.
    for val in arr:
        sum1+=(val[0]-meanx)*(val[1]-meany)
        sum2+=(val[0]-meanx)**2
        sum3+=(val[1]-meany)**2
    sum2=sqrt(sum2*sum3)
    korreff=sum1/sum2
    return korreff

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
resmag=1.

timeframe2008new=[[6.25,12.2],[15.,22.5],[25.25,26.5],[33.,37.8],[42.5,49.],[50.,53.5],[61.,64.],[69.5,77.5],[88.5,91.5],[97.75,105.75],[115.5,118.5],[126.,130.],[143.,147.5],[151.,155.],[168.,171.],[172.5,175.5],[179.,181.5],[194.5,200.5],[223.25,226.75],[232.,234.75],[248.5,253.5],[259.5,261.],[276.5,281.5],[286.,288.5],[303.5,308.75],[313.25,314.25],[331.,335.],[341.5,344.],[359.,361.5]]

timeframe2007new=[[3.5,7.5],[17.,23.5],[30.,34.5],[45.5,50.],[59.5,61.5],[66.5,68.],[73.5,78.5],[92.5,97.],[118.5,122.5],[129.,130.5],[139.5,141.5],[145.,150.],[166.,172.],[174.5,177.],[186.,189.],[192.5,194.5],[196.5,199.],[211.,213.],[214.,216.5],[219.5,221.],[239.,243.],[246.,249.],[250.5,252.],[265.5,270.],[272.5,275.5],[277.,279.5],[293.,295.5],[299.,302.5],[303.5,305.],[318.,322.],[325.,326.],[327.,328.],[329.,333.5],[346.,350.],[355.,359.5]]

timeframe=[[3.5,7.5],[17.,23.5],[30.,34.5],[45.5,50.],[59.5,61.5],[66.5,68.],[73.5,78.5],[92.5,97.],[118.5,122.5],[129.,130.5],[139.5,141.5],[145.,150.],[166.,172.],[174.5,177.],[186.,189.],[192.5,194.5],[196.5,199.],[211.,213.],[214.,216.5],[219.5,221.],[239.,243.],[246.,249.],[250.5,252.],[265.5,270.],[272.5,275.5],[277.,279.5],[293.,295.5],[299.,302.5],[303.5,305.],[318.,322.],[325.,326.],[327.,328.],[329.,333.5],[346.,350.],[355.,359.5]]

#timeframe=[[6.,12.2],[12.2,20.]]


polarity=zeros([len(timeframe)])
polarity2007=[1,1,1,1,1,-1,1,-1,-1,1,1,-1,1,-1,-1,1,1,-1,-1,1,-1,1,1,-1,1,1,-1,1,1,-1,1,1,1,-1,1]
polarity2008=[-1,1,1,-1,1,1,-1,1,-1,1,-1,1,-1,1,-1,-1,1,-1,-1,1,-1,1,-1,1,-1,1,-1,1,-1]
polarity=[1,1,1,1,1,-1,1,-1,-1,1,1,-1,1,-1,-1,1,1,-1,-1,1,-1,1,1,-1,1,1,-1,1,1,-1,1,1,1,-1,1]
#polarity=[-1,1]
#polarity=[-1]

effpath="/data/ivar/ace/efficencies/aspeff/"
datapath="/data/wimmer/ace/"
datapath2="/data/zechine/ace/12mprotons/2008/"
swepampath="/data/wimmer/ace/swepam/"
magpath="/data/missions/ace/mag/lv2/"
magpath="/data/wimmer/ace/mag/"
#ionlist=["Fe8+"]#,"O6+"]#,"Fe9+"]
ionlist=["He2+","O6+","C5+","Si8+","S8+","Fe8+"]
#ionlist=[["He2+"],["C4+","C5+","C6+"],["O6+"],["N5+","N6+","N7+"],["Mg7+","Mg8+","Mg9+","Mg10+"],["Si8+","Si9+","Si10+"],["Fe8+","Fe9+","Fe10+","Fe11+","Fe12+"]]
#ionlist=[["He2+"]]
ionlist=[["He2+"],["C4+","C5+","C6+"],["O6+"],["N5+","N6+","N7+"],["Mg7+","Mg8+","Mg9+","Mg10+"],["Si8+","Si9+","Si10+"],["Fe8+","Fe9+","Fe10+","Fe11+","Fe12+"]]
ionlist=[["Fe14+","Fe13+","Fe12+","Fe11+","Fe10+","Fe9+","Fe8+","Fe7+"],["O8+","O7+","O6+","O5+"],["He2+"]]
#ionlist=[["Fe14+"],["Fe13+"],["Fe12+"],["Fe11+"],["Fe10+"],["Fe9+"],["Fe8+"],["Fe7+"],["S10+"],["S9+"],["S8+"],["Si10+"],["Si9+"],["Si8+"],["Mg10+"],["Mg9+"],["Mg8+"],["Mg7+"],["Ne8+"],["O8+"],["O7+"],["O6+"],["O5+"],["N7+"],["N6+"],["N5+"],["C6+"],["C5+"],["C4+"],["He2+"]]
ionlist=[["Fe18+"],["Fe17+"],["Fe16+"],["Fe15+"],["Fe14+"],["Fe13+"],["Fe12+"],["Fe11+"],["Fe10+"],["Fe9+"],["Fe8+"],["Fe7+"],["Ca12+"],["Ca11+"],["Ca10+"],["Ca9+"],["Ca8+"],["Ca7+"],["S12+"],["S11+"],["S10+"],["S9+"],["S8+"],["S7+"],["Si12+"],["Si11+"],["Si10+"],["Si9+"],["Si8+"],["Si7+"],["Mg12+"],["Mg11+"],["Mg10+"],["Mg9+"],["Mg8+"],["Mg7+"],["Ne8+"],["O8+"],["O7+"],["O6+"],["O5+"],["N7+"],["N6+"],["N5+"],["C6+"],["C5+"],["C4+"],["He2+"]]
#ionlist=[["O6+"],["He2+"]]
ionlist=[["O6+"]]
logs=0
# get wave-power timeseries


"""
wp1=[]
wp2=[]
wp3=[]

wpout=open("wp_dummy.dat","w")
sigphiarr=[]
sigthetaarr=[]
for tf in timeframe:
    hedata=swicsiondata("He2+",resswics,year,[tf],datapath)
    mag=magdata(1.,year,[tf],magpath)
    j=0
    for time in hedata.time:
        magx=[]
        magy=[]
        magz=[]
        phi=[]
        theta=[]
        while mag.time[j]<time and j<len(mag.time)-2:
            j+=1
        analyse=1
        while mag.time[j]<time+resswics/86400. and j<len(mag.time)-2:
            magx.append(mag.magbx[j])
            magy.append(mag.magby[j])
            magz.append(mag.magbz[j])
            phi.append(mag.phi[j])
            theta.append(mag.theta[j])
            if (mag.magbx[j]==mag.magby[j]==mag.magbz[j]==0.):
                #print mag.time[j]," : gap"
                analyse=-1 
            j+=1
        mphi=0.
        mtheta=0.
        for i in range(len(phi)):
            mphi+=phi[i]
            mtheta+=theta[i]
        mphi/=float(len(phi))
        mtheta/=float(len(theta))
        sigphi=0.
        sigtheta=0.
        for val in phi:
            sigphi+=(val-mphi)**2
        for val in theta:
            sigtheta+=(val-mtheta)**2
        sigphi/=len(phi)
        sigtheta/=len(theta)
        sigphi=sqrt(sigphi)
        sigtheta=sqrt(sigtheta)
        sigphiarr.append([time,sigphi])
        sigthetaarr.append([time,sigtheta])
        #if sigphi>pi/180.*12.:
        #    analyse=-1
        #if sigtheta>pi/180.*12.:
        #    analyse=-1
        if (analyse==1):
            psdx=get_wpspec(magx,1.)
            psdy=get_wpspec(magy,1.)
            psdz=get_wpspec(magz,1.)
            intx1=numint(psdx,0.01,0.1)
            intx2=numint(psdx,0.1,1.)
            intx3=numint(psdx,0.01,1.)
            inty1=numint(psdy,0.01,0.1)
            inty2=numint(psdy,0.1,1.)
            inty3=numint(psdy,0.01,1.)
            intz1=numint(psdz,0.01,0.1)
            intz2=numint(psdz,0.1,1.)
            intz3=numint(psdz,0.01,1.)
            wp1.append([time,intx1+inty1+intz1])
            wp2.append([time,intx2+inty2+intz2])
            wp3.append([time,intx3+inty3+intz3])
        else:
            #print time," : data gap"
            wp1.append([time,0.])
            wp2.append([time,0.])
            wp3.append([time,0.])

for i in range(len(wp1)):
    wpout.write("%.6f\t%.6f\t%.6f\t%.6f\t%.6f\t%.6f\n"%(wp1[i][0],wp1[i][1],wp2[i][1],wp3[i][1],sigphiarr[i][1],sigthetaarr[i][1]))
wpout.close()            


"""
wp1=[]
wp2=[]
wp3=[]
sigphiarr=[]
sigthetaarr=[]
wpin=open("wp_2008.dat")
for s in wpin:
    k=s.split()
    wp1.append([float(k[0]),float(k[1])])
    wp2.append([float(k[0]),float(k[2])])
    wp3.append([float(k[0]),float(k[3])])
    sigphiarr.append([float(k[0]),float(k[4])])
    sigthetaarr.append([float(k[0]),float(k[5])])
print "wp loaded"


# linear vel
vxbinwidth=10.
nrxbins=80.
vybinwidth=0.05
nrybins=40.
vyoffset=0.
# log wp
vxbinwidth2=.1
vxbinwidth2=.1
nrxbins2=50.
vybinwidth2=0.05
nrybins2=40.
vyoffset2=0.


"""
o7=swicsiondata("O7+",resswics,year,timeframe,datapath)
o6=swicsiondata("O6+",resswics,year,timeframe,datapath)
o7dens=o7.getvals(["time","dens"])
o6dens=o6.getvals(["time","dens"])
o7o6=[]
for i in range(len(o6dens)):
    if o6dens[i][1]>0.:
        o7o6.append([o6dens[i][0],o7dens[i][1]/o6dens[i][1]])
    else:
        o7o6.append([o6dens[i][0],0.])
po7o6=Data(o7o6)
po7o6.set_option_colonsep("with","l lt 1 lw 1")
"""

vivsvparr=zeros([nrxbins,nrybins])
vivsvparr2=zeros([nrxbins2,nrybins])
dvzeros=zeros([nrxbins,3])
#if len(polarity)!=(len(timeframe)):
#    raise Exception
for i in range(int(nrxbins)):
    dvzeros[i][0]=float(i*vxbinwidth)
    dvzeros[i][2]=1.

dvvsvparr=[]
dvvsvparr2=[]
meandvvsvparr=[]
meandvvsvparr2=[]
meandvvswparr=[]
meandvvswparr2=[]
for ion in range(len(ionlist)):
    meandvvsvparr.append([])
    meandvvsvparr2.append([])
    meandvvswparr.append([])
    meandvvswparr2.append([])
    for i in range(int(nrxbins2)):
        meandvvswparr[-1].append([10**(-3+float(i*vxbinwidth2)),0.,0.])
        meandvvswparr2[-1].append([10**(-3+float(i*vxbinwidth2)),0.,0.])
    for i in range(int(nrxbins)):
        meandvvsvparr[-1].append([float(i*vxbinwidth),0.,0.])
        meandvvsvparr2[-1].append([float(i*vxbinwidth),0.,0.])
#meandvvsvparr=array(meandvvsvparr)
mass=[]
charge=[]



korrarr1=[]
korrarr2=[]
korrarr3=[]
korrarr4=[]
ionnr=-1
for ion in ionlist:
    ionnr+=1
    iondata=[]
    
    for ion2 in ion:
        #iondata=swicsiondata(ion2,resswics,year,timeframe,datapath)
        iondata.append(swicsiondata(ion2,resswics,year,timeframe,datapath))
    mass.append(iondata[-1].mass)
    charge.append(iondata[-1].charge)
    swepam=swepamdata(resswepam,year,timeframe,swepampath)
    swepam.sync_h_hires(iondata[0])
    mag=magdata(resmag,year,timeframe,magpath)
    mag.sync_mag_hires(iondata[0])
    dvvsvparr=[]
    dvvsvparr2=[]
    dvvswparr=[]
    dvvswparr2=[]
    for i in range(nrxbins):
        dvvsvparr.append([])
        dvvsvparr2.append([])
    for i in range(nrxbins2):
        dvvswparr.append([])
        dvvswparr2.append([])
    # build all arrays for histograms!

    for i in range(len(iondata[0].time)):
        p=-1
        if (swepam.dens[i]>0.):
            valf=21.8*mag.magb[i]/sqrt(swepam.dens[i])
        else:
            valf=0.
        if (swepam.vel[i]>0. and swepam.temp[i]>0.):
            colage=(6.4e8*swepam.dens[i])/(swepam.vel[i]*(swepam.temp[i])**1.5)
        else:
            colage=0.
        if (swepam.vel[i]>0. and swepam.temp[i]>0.):
            pbeta=2.51327e-5*swepam.dens[i]*swepam.temp[i]/mag.magb[i]**2.
        else:
            pbeta=0.
        if (valf>0.):# and colage>0.):
            p=getperiod(iondata[0].time[i],iondata[0].timeframe)
            if (mag.phi[i]!=0. and mag.theta[i]!=0. and swepam.vel[i]>0.):
                tmpmag=acos(cos(mag.phi[i])*cos(mag.theta[i]))
            else:
                tmpmag=0.
            tmpbetashift=atan(sqrt(swepam.vely[i]**2+swepam.velz[i]**2)/swepam.velx[i])
            nrtmpvel=0.
            tmpvel=0.
            for ion2 in iondata:
                if (ion2.vel[i]>0. and ion2.dens[i][0]>0.):
                    tmpvel+=ion2.vel[i]*ion2.dens[i][0]
                    nrtmpvel+=ion2.dens[i][0]
            if nrtmpvel>0.:
                tmpvel/=nrtmpvel
            if tmpbetashift!=0.:
                vd=getvd(swepam.vel[i],tmpvel,tmpmag-tmpbetashift,polarity[p])
##                if polarity[p]==1 and tmpmag:
##                    vd=getvd(swepam.vel[i],tmpvel,tmpmag-tmpbetashift,polarity[p])
##                if polarity[p]==-1:
##                    vd=getvd(swepam.vel[i],tmpvel,tmpmag+tmpbetashift,polarity[p])
            else:
                vd=0.
            #if (((polarity[p]==-1 and tmpmag>pi/2+4*pi/16) or (polarity[p]==1 and tmpmag<pi/2-4*pi/16)) and o7o6[i][1]>0. and tmpvel>swepam.vel[i]-4*valf and tmpvel<swepam.vel[i]+4*valf):
            #if (mag.wp3[i]>0. and tmpmag!=0. and ((polarity[p]==1 and tmpmag<pi/2.-2.*pi/16.) or (polarity[p]==-1 and tmpmag>pi/2.+2.*pi/16.)) and swepam.dvel[i]<150. and swepam.ddens[i]<1. and colage>0. and pbeta>0.):# and mag.dang[i]/pi*180.<25. and swepam.dvel[i]<20. and swepam.ddens[i]<.2):
            if (mag.wp3[i]>0. and tmpmag!=0. and tmpmag!=0. and swepam.dvel[i]<150. and swepam.ddens[i]<1. and colage>0. and pbeta>0.):# and mag.dang[i]/pi*180.<25. and swepam.dvel[i]<20. and swepam.ddens[i]<.2):
                x2=int((log10(pbeta)+3.-vxbinwidth2)/vxbinwidth2)
                #x2=int((log10(colage)+3.-vxbinwidth2)/vxbinwidth2)
                #x2=int((log10(wp3[i][1]/colage)+3.-vxbinwidth2)/vxbinwidth2)
                #x2=int((log10(1./pbeta*wp3[i][1]/colage)+3.-vxbinwidth2)/vxbinwidth2)
                x1=int((swepam.vel[i]+vxbinwidth/2)/vxbinwidth)
                #x=int((wp3[i][1]+vxbinwidth/2)/vxbinwidth)
                #x=int((log10(o7o6[i][1])+3.-vxbinwidth)/vxbinwidth)
                #x=int((mag.magb[i]+vxbinwidth/2)/vxbinwidth)
                
                #y=int(((tmpvel-swepam.vel[i])/valf+vybinwidth/2-vyoffset)/vybinwidth)
                y=int((vd/valf+vybinwidth/2-vyoffset)/vybinwidth)
                #y=int((vd/valf+vybinwidth/2)/vybinwidth)
            
            else:
                x1=-1
                x2=-1
                y=-1
            if (x1>=0 and x1<nrxbins):# and vd>0.):
                #korrarr.append([log10(wp3[i][1]/mag.magb[i]/colage),(tmpvel-swepam.vel[i])/valf])
                #korrarr.append([log10(wp3[i][1]/mag.magb[i]/colage),vd/valf])
                if polarity[p]==-1:
                    korrarr3.append([swepam.vel[i],vd/valf])

                #if 1:
                    dvvsvparr[x1].append(vd/valf)
                    #dvvsvparr[x1].append((tmpvel-swepam.vel[i])/valf)
                if polarity[p]==1:
                    korrarr4.append([swepam.vel[i],vd/valf])
                    dvvsvparr2[x1].append(vd/valf)
                    #dvvsvparr2[x1].append((tmpvel-swepam.vel[i])/valf)
                    if (y>0 and y<nrybins):
                        vivsvparr[x1,y]+=1.
                #meandvvsvparr[ionnr][x][1]+=vd/valf
                if polarity[p]==-1:
                #if 1:
                    meandvvsvparr[ionnr][x1][1]+=vd/valf
                    #meandvvsvparr[ionnr][x1][1]+=(tmpvel-swepam.vel[i])/valf
                    meandvvsvparr[ionnr][x1][2]+=1.
                if polarity[p]==1:
                    meandvvsvparr2[ionnr][x1][1]+=vd/valf
                    #meandvvsvparr2[ionnr][x1][1]+=(tmpvel-swepam.vel[i])/valf
                    meandvvsvparr2[ionnr][x1][2]+=1.
            if (x2>=0 and x2<nrxbins2 and vd>0.):
                if polarity[p]==-1:
                #if 1:
                    #dvvswparr[x2].append((tmpvel-swepam.vel[i])/valf)
                    dvvswparr[x2].append(vd/valf)
                    #if log10(mag.wp3[i]/colage)>-1.:
                    korrarr1.append([log10(pbeta),vd/valf])

                if polarity[p]==1:
                    #dvvswparr2[x2].append((tmpvel-swepam.vel[i])/valf)
                    dvvswparr2[x2].append(vd/valf)
                    #if log10(wp3[i][1]/colage)>-1.:
                    korrarr2.append([log10(pbeta),vd/valf])
                    
                    if (y>0 and y<nrybins and vd>0.):
                        vivsvparr2[x2,y]+=1.
                if polarity[p]==-1:
                #if 1:
                    meandvvswparr[ionnr][x2][1]+=vd/valf
                    #meandvvswparr[ionnr][x2][1]+=(tmpvel-swepam.vel[i])/valf
                    meandvvswparr[ionnr][x2][2]+=1.
                if polarity[p]==1:
                    meandvvswparr2[ionnr][x2][1]+=vd/valf
                    #meandvvswparr2[ionnr][x2][1]+=(tmpvel-swepam.vel[i])/valf
                    meandvvswparr2[ionnr][x2][2]+=1.


    for val in meandvvsvparr[ionnr]:
        if val[2]>0.:
            val[1]/=val[2]
    for val in meandvvsvparr2[ionnr]:
        if val[2]>0.:
            val[1]/=val[2]
    for val in meandvvswparr[ionnr]:
        if val[2]>0.:
            val[1]/=val[2]
    for val in meandvvswparr2[ionnr]:
        if val[2]>0.:
            val[1]/=val[2]
    for x in range(nrxbins):
        tmpsig=0.
        if meandvvsvparr[ionnr][x][1]>0.:
            for val in dvvsvparr[x]:
                tmpsig+=(meandvvsvparr[ionnr][x][1]-val)**2
            tmpsig=sqrt(tmpsig/len(dvvsvparr[x])**2)
        meandvvsvparr[ionnr][x][2]=tmpsig
    for x in range(nrxbins):
        tmpsig=0.
        if meandvvsvparr2[ionnr][x][1]>0.:
            for val in dvvsvparr2[x]:
                tmpsig+=(meandvvsvparr2[ionnr][x][1]-val)**2
            tmpsig=sqrt(tmpsig/len(dvvsvparr2[x])**2)
        meandvvsvparr2[ionnr][x][2]=tmpsig
    for x in range(nrxbins2):
        tmpsig=0.
        if meandvvswparr[ionnr][x][1]>0.:
            for val in dvvswparr[x]:
                tmpsig+=(meandvvswparr[ionnr][x][1]-val)**2
            tmpsig=sqrt(tmpsig/len(dvvswparr[x])**2)
        meandvvswparr[ionnr][x][2]=tmpsig
        meandvvswparr[ionnr][x][0]=log10(meandvvswparr[ionnr][x][0])
    for x in range(nrxbins2):
        tmpsig=0.
        if meandvvswparr2[ionnr][x][1]>0.:
            for val in dvvswparr2[x]:
                tmpsig+=(meandvvswparr2[ionnr][x][1]-val)**2
            tmpsig=sqrt(tmpsig/len(dvvswparr2[x])**2)
        meandvvswparr2[ionnr][x][2]=tmpsig
        meandvvswparr2[ionnr][x][0]=log10(meandvvswparr2[ionnr][x][0])

"""
korrarr1=[]
korrarr2=[]
korrarr3=[]
korrarr4=[]

for val in meandvvswparr[0]:
    if val[1]!=0.:
        korrarr1.append(val)


for val in meandvvswparr2[0]:
    if val[1]!=0.:
        korrarr2.append(val)


for val in meandvvsvparr[0]:
    if val[1]!=0.:
        korrarr3.append(val)


for val in meandvvsvparr2[0]:
    if val[1]!=0.:
        korrarr4.append(val)


"""

kor1=get_korreff(korrarr1)
kor2=get_korreff(korrarr2)
kor3=get_korreff(korrarr3)
kor4=get_korreff(korrarr4)

meanhevse=[]
i=-1
for ion in meandvvsvparr:
    i+=1
    tmpsum=0.
    deltasum=0.
    nrtmpsum=0
    j=-1
    for val in ion:
        j+=1
        if (val[0]>0.01 and val[0]<0.4 and meandvvsvparr[-1][j][1]>0.):
            delta=val[2]/meandvvsvparr[-1][j][1]+val[1]/meandvvsvparr[-1][j][1]**2*meandvvsvparr[-1][j][2]
            tmpsum+=val[1]/meandvvsvparr[-1][j][1]
            deltasum+=delta**2
            nrtmpsum+=1.
    if nrtmpsum>0:
        tmpsum/=nrtmpsum
        deltasum=sqrt(deltasum)/nrtmpsum
    #tmpsum/=deltasum
    meanhevse.append([mass[i]/charge[i]**1.,tmpsum,deltasum])


for val in vivsvparr:
    if max(val)>0.:
        val/=max(val)
for val in vivsvparr2:
    if max(val)>0.:
        val/=max(val)
    

xvals=[]
xvals2=[]
yvals=[]
for i in range(nrxbins):
    #xvals.append(float(i*vxbinwidth))
    xvals.append(float(i*vxbinwidth))
for i in range(nrxbins2):
    xvals2.append(10**(-3+float(i*vxbinwidth2)))

for i in range(nrybins):
    yvals.append(float(i*vybinwidth)+vyoffset)

pvivsvparr=GridData(vivsvparr,xvals,yvals,binary=0)
pvivsvparr2=GridData(vivsvparr2,xvals2,yvals,binary=0)
#xrange=[0.,3.]
xrange=[300.,800.]
yrange=[0.,2.]
xrange2=[0.001,100.]
yrange=[0.,2.]
a=[[xrange[0],yrange[0],1.],[xrange[1],yrange[1],1.]]
pa=Data(a)
pa.set_option_colonsep("with","l lt -1")
gp=Gnuplot()
gp("set pm3d at bs map explicit corners2color c1")
#gp("set pm3d map")
gp("set size square")
gp("set xrange[%f:%f]"%(xrange[0],xrange[1])) 
gp("set yrange[%f:%f]"%(yrange[0],yrange[1]))
gp("set xlabel 'vsw")
gp("set title '%i'"%(year))
#gp("set logscale x")
gp("set palette model RGB functions gray<1.e-20 ? 1 : gray<0.5 ? gray*2 : 1 , gray<1.e-20 ? 1 : gray<0.5 ? gray*2 : 2-gray*2, gray <1.e-20 ? 1 : gray<0.5 ? 1-sqrt(gray*2) : 0")
#gp("set logscale cb")
gp.splot(pvivsvparr)#,pa)
gp.hardcopy("dv%s64s_vs_vp%s.ps"%(ionlist[0][0],year),color="true",fontsize=20)

gp4=Gnuplot()
gp4("set pm3d at bs map explicit corners2color c1")
#gp("set pm3d map")
gp4("set size square")
gp4("set xrange[%f:%f]"%(xrange2[0],xrange2[1])) 
gp4("set yrange[%f:%f]"%(yrange[0],yrange[1]))
gp4("set xlabel 'pbeta")
#gp("set logscale x")
gp4("set palette model RGB functions gray<1.e-20 ? 1 : gray<0.5 ? gray*2 : 1 , gray<1.e-20 ? 1 : gray<0.5 ? gray*2 : 2-gray*2, gray <1.e-20 ? 1 : gray<0.5 ? 1-sqrt(gray*2) : 0")
#gp4("set logscale cb")
gp4("set logscale x")
gp4.splot(pvivsvparr2)#,pa)
gp4.hardcopy("dv%s64s_vs_pbeta%i.ps"%(ionlist[0][0],year),color="true",fontsize=20)

pmeandv=[]
for ion in meandvvsvparr:
    pmeandv.append(Data(ion))
    pmeandv[-1].set_option_colonsep("using","1:2:3")
    pmeandv[-1].set_option_colonsep("with","yerrorbars lt 1")
    pmeandv[-1].set_option_colonsep("title","'polarity -'")
pmeandv2=[]
for ion in meandvvsvparr2:
    pmeandv2.append(Data(ion))
    pmeandv2[-1].set_option_colonsep("using","1:2:3")
    pmeandv2[-1].set_option_colonsep("with","yerrorbars lt 3")
    pmeandv2[-1].set_option_colonsep("title","'polarity +'")
pmeandvwp=[]
for ion in meandvvswparr:
    pmeandvwp.append(Data(ion))
    pmeandvwp[-1].set_option_colonsep("using","1:2:3")
    pmeandvwp[-1].set_option_colonsep("with","yerrorbars lt 1")
    pmeandvwp[-1].set_option_colonsep("title","'polarity -'")
pmeandvwp2=[]
for ion in meandvvswparr2:
    pmeandvwp2.append(Data(ion))
    pmeandvwp2[-1].set_option_colonsep("using","1:2:3")
    pmeandvwp2[-1].set_option_colonsep("with","yerrorbars lt 3")
    pmeandvwp2[-1].set_option_colonsep("title","'polarity +'")


gp2=Gnuplot()
gp2.plot(pmeandv[0])
for i in range(1,len(pmeandv)):
    gp2.replot(pmeandv[i])
for i in range(0,len(pmeandv2)):
    gp2.replot(pmeandv2[i]) 
gp2.hardcopy("dvmeanvsw%s%i.ps"%(ionlist[0][0],year),color="True")
gp3=Gnuplot()
gp3.plot(pmeandvwp[0])
for i in range(1,len(pmeandvwp)):
    gp3.replot(pmeandvwp[i])
for i in range(0,len(pmeandvwp2)):
    gp3.replot(pmeandvwp2[i])
gp3.hardcopy("dvmeanpbeta%s%i.ps"%(ionlist[0][0],year),color="True")

pmeanhevse=Data(meanhevse)
pmeanhevse.set_option_colonsep("using","1:2:3")
pmeanhevse.set_option_colonsep("with","yerrorbars")

print "wp1: ",kor1
print "wp2: ",kor2
print "vp1: ",kor3
print "vp2: ",kor4

"""
meanelem=[]
for i in range(10):
    meanelem.append([])


meanelem[-1].append(meanhevse[-1])
meanelem[-2].append(meanhevse[-4])
meanelem[-2].append(meanhevse[-3])
meanelem[-2].append(meanhevse[-2])
meanelem[-3].append(meanhevse[-7])
meanelem[-3].append(meanhevse[-6])
meanelem[-3].append(meanhevse[-5])
meanelem[-4].append(meanhevse[-11])
meanelem[-4].append(meanhevse[-10])
meanelem[-4].append(meanhevse[-9])
meanelem[-4].append(meanhevse[-8])
meanelem[-5].append(meanhevse[-12])
meanelem[-6].append(meanhevse[-18])
meanelem[-6].append(meanhevse[-17])
meanelem[-6].append(meanhevse[-16])
meanelem[-6].append(meanhevse[-15])
meanelem[-6].append(meanhevse[-14])
meanelem[-6].append(meanhevse[-13])
meanelem[-7].append(meanhevse[-24])
meanelem[-7].append(meanhevse[-23])
meanelem[-7].append(meanhevse[-22])
meanelem[-7].append(meanhevse[-21])
meanelem[-7].append(meanhevse[-20])
meanelem[-7].append(meanhevse[-19])
meanelem[-8].append(meanhevse[-30])
meanelem[-8].append(meanhevse[-29])
meanelem[-8].append(meanhevse[-28])
meanelem[-8].append(meanhevse[-27])
meanelem[-8].append(meanhevse[-26])
meanelem[-8].append(meanhevse[-25])
meanelem[-9].append(meanhevse[-36])
meanelem[-9].append(meanhevse[-35])
meanelem[-9].append(meanhevse[-34])
meanelem[-9].append(meanhevse[-33])
meanelem[-9].append(meanhevse[-32])
meanelem[-9].append(meanhevse[-31])
meanelem[0].append(meanhevse[0])
meanelem[0].append(meanhevse[1])
meanelem[0].append(meanhevse[2])
meanelem[0].append(meanhevse[3])
meanelem[0].append(meanhevse[4])
meanelem[0].append(meanhevse[5])
meanelem[0].append(meanhevse[6])
meanelem[0].append(meanhevse[7])
meanelem[0].append(meanhevse[8])
meanelem[0].append(meanhevse[9])
meanelem[0].append(meanhevse[10])
meanelem[0].append(meanhevse[11])

pmeanelem=[]
for val in meanelem:
    pmeanelem.append(Data(val))
    pmeanelem[-1].set_option_colonsep("using","1:2:3")
    pmeanelem[-1].set_option_colonsep("with","yerrorbars")


pmeanelem[9].set_option_colonsep("title","'He'")
pmeanelem[8].set_option_colonsep("title","'C'")
pmeanelem[7].set_option_colonsep("title","'N'")
pmeanelem[6].set_option_colonsep("title","'O'")
pmeanelem[5].set_option_colonsep("title","'Ne'")
pmeanelem[4].set_option_colonsep("title","'Mg'")
pmeanelem[3].set_option_colonsep("title","'Si'")
pmeanelem[2].set_option_colonsep("title","'S'")
pmeanelem[1].set_option_colonsep("title","'Ca'")
pmeanelem[0].set_option_colonsep("title","'Fe'")


gp3=Gnuplot()
gp3("set xrange[0:10]") 
gp3("set yrange[0.4:1.8]") 
gp3.plot(pmeanelem[0])
for i in range(1,10):
    gp3.replot(pmeanelem[i])
"""    
