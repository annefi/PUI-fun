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

year=2008
resswics=720.
resswepam=64.
resmag=240.
timeframe=[[4.,9.],[17.4,25.25],[30.5,35.],[45.5,55.],[60.,63.],[65.5,70.],[73.25,80.5],[93.,97.5],[103.,107.],[119.,126.5],[129.,135.],[145.25,151.1]]
#timeframe=[[70.,75.]]
#timeframe=[[73.25,80.5]]
#timeframe=[[30.5,35.]]

timeframe=[[3.5,9.],[17.5,29.],[30.,36.],[45.5,56.5],[59.5,63.5],[66.5,70.],[73.5,82.],[92.5,98.5],[106.,107.],[110.,112.],[118.5,126.5],[128.5,137.5],[139.5,141.5],[145.,151.5],[156.,158.5],[161.5,164.],[166.,172.],[174.5,179.5],[181.5,184.],[186.,191.5],[192.5,194.5],[196.5,201.],[203.,207.],[208.5,209.5],[211.,212.5],[214.,217.],[219.5,222.],[223.,226.5],[232.,237.],[239.5,243.],[246.,249.],[258.5,262.5],[265.5,270.5],[272.5,275.5],[277.,282.],[292.5,298.],[299.,302.],[303.5,312.5],[315.,316.],[318.,323.5],[325.,326.5],[327.,328.5],[329.,338.5],[339.5,344.],[346.,351.],[352.,354.],[355.,359.5],[362.,365.]]

timeframe2008=[[1.,4.5],[6.5,12.],[15.,24.5],[25.5,31.],[33.,38.5],[42.5,49.],[50.,58.5],[61.5,65.],[66.,68.],[70.,77.],[88.5,95.],[97.5,106.],[109.,113.5],[115.5,121.],[125.,131.5],[143.,148.5],[152.,158.],[160.,166.5],[168.,171.5],[172.5,176.5],[179.,187.],[188.5,193.5],[194.5,204.],[223.5,227.],[232.,247.],[248.5,250.],[251.,258.5],[259.5,261.],[262.5,269.5],[277.,285.],[286.,293.],[297.5,300.],[303.5,312.],[313.5,319.5],[321.5,329.5],[331.,337.5],[341.5,345.],[358.5,365.]]

timeframe2007=[[3.5,9.],[17.5,29.],[30.,36.],[45.5,56.5],[59.5,63.5],[66.5,70.],[73.5,82.],[92.5,98.5],[106.,107.],[110.,112.],[118.5,126.5],[128.5,137.5],[139.5,141.5],[145.,151.5],[156.,158.5],[161.5,164.],[166.,172.],[174.5,179.5],[181.5,184.],[186.,191.5],[192.5,194.5],[196.5,201.],[203.,207.],[208.5,209.5],[211.,212.5],[214.,217.],[219.5,222.],[223.,226.5],[232.,237.],[239.5,243.],[246.,249.],[258.5,262.5],[265.5,270.5],[272.5,275.5],[277.,282.],[299.,302.],[303.5,312.5],[315.,316.],[318.,323.5],[325.,326.5],[327.,328.5],[329.,338.5],[339.5,344.],[346.,351.],[352.,354.],[355.,359.5],[362.,365.]]


timeframe=[[3.5,9.],[17.5,29.],[30.,36.],[45.5,56.5],[59.5,63.5],[66.5,70.],[73.5,82.],[92.5,98.5],[106.,107.],[110.,112.],[118.5,126.5],[128.5,137.5],[139.5,141.5],[145.,151.5],[156.,158.5],[161.5,164.],[166.,172.],[174.5,179.5],[181.5,184.],[186.,191.5],[192.5,194.5],[196.5,201.],[203.,207.],[208.5,209.5],[211.,212.5],[214.,217.],[219.5,222.],[223.,226.5],[232.,237.],[239.5,243.],[246.,249.],[258.5,262.5],[265.5,270.5],[272.5,275.5],[277.,282.],[299.,302.],[303.5,312.5],[315.,316.],[318.,323.5],[325.,326.5],[327.,328.5],[329.,338.5],[339.5,344.],[346.,351.],[352.,354.],[355.,359.5],[362.,365.]]

timeframe2008new=[[6.25,12.2],[15.,22.5],[25.25,26.5],[33.,37.8],[42.5,49.],[50.,53.5],[61.,64.],[69.5,77.5],[88.5,91.5],[97.75,105.75],[115.5,118.5],[126.,130.],[143.,147.5],[151.,155.],[168.,171.],[172.5,175.5],[179.,181.5],[194.5,200.5],[223.25,226.75],[232.,234.75],[248.5,253.5],[259.5,261.],[276.5,281.5],[286.,288.5],[303.5,308.75],[313.25,314.25],[331.,335.],[341.5,344.],[359.,361.5]]

timeframe2007new=[[3.5,7.5],[17.,23.5],[30.,34.5],[45.5,50.],[59.5,61.5],[66.5,68.],[73.5,78.5],[92.5,97.],[118.5,122.5],[129.,130.5],[139.5,141.5],[145.,150.],[166.,172.],[174.5,177.],[186.,189.],[192.5,194.5],[196.5,199.],[211.,213.],[214.,216.5],[219.5,221.],[239.,243.],[246.,249.],[250.5,252.],[265.5,270.],[272.5,275.5],[277.,279.5],[293.,295.5],[299.,302.5],[303.5,305.],[318.,322.],[325.,326.],[327.,328.],[329.,333.5],[346.,350.],[355.,359.5]]

timeframe=[[6.25,12.2],[15.,22.5],[25.25,26.5],[33.,37.8],[42.5,49.],[50.,53.5],[61.,64.],[69.5,77.5],[88.5,91.5],[97.75,105.75],[115.5,118.5],[126.,130.],[143.,147.5],[151.,155.],[168.,171.],[172.5,175.5],[179.,181.5],[194.5,200.5],[223.25,226.75],[232.,234.75],[248.5,253.5],[259.5,261.],[276.5,281.5],[286.,288.5],[303.5,308.75],[313.25,314.25],[331.,335.],[341.5,344.],[359.,361.5]]


#timeframe=[[15.,22.5]]
#timeframe=[[6.25,12.2]]
#timeframe=[[6.25,12.2],[15.,22.5],[25.25,26.5],[33.,37.8]]#timeframe=[[166.,172.]]
#timeframe=[[3.5,9.],[17.5,29.],[30.,36.],[45.5,56.5],[59.5,63.5],[66.5,70.],[73.5,82.]]#timeframe=[[346.,351.]]
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

# get wave-power timeseries

"""
wp1=[]
wp2=[]
wp3=[]

wpout=open("wp_2008.dat","w")
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

vxbinwidth=.1
vxbinwidth=.1
nrxbins=40.
vybinwidth=0.05
nrybins=40.
vyoffset=0.

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
dvzeros=zeros([nrxbins,3])
polarity=zeros([len(timeframe)])
polarity2007=[1,1,1,1,1,-1,1,-1,-1,1,1,-1,1,-1,-1,1,1,-1,-1,1,-1,1,1,-1,1,1,-1,1,1,-1,1,1,1,-1,1]
polarity2008=[-1,1,1,-1,1,1,-1,1,-1,1,-1,1,-1,1,-1,-1,1,-1,-1,1,-1,1,-1,1,-1,1,-1,1,-1]
#polarity=[1,1,1,1,1,-1,1,-1,-1,1,1,-1,1,-1,-1,1,1,-1,-1,1,-1,1,1,-1,1,1,-1,1,1,-1,1,1,1,-1,1]
polarity=[-1,1,1,-1,1,1,-1,1,-1,1,-1,1,-1,1,-1,-1,1,-1,-1,1,-1,1,-1,1,-1,1,-1,1,-1]
#polarity=[-1]
#if len(polarity)!=(len(timeframe)):
#    raise Exception
for i in range(int(nrxbins)):
    dvzeros[i][0]=float(i*vxbinwidth)
    dvzeros[i][2]=1.

dvvsvparr=[]
dvvsvparr2=[]
meandvvsvparr=[]
for ion in range(len(ionlist)):
    meandvvsvparr.append([])
    for i in range(int(nrxbins)):
        #meandvvsvparr[-1].append([float(i*vxbinwidth),0.,0.])
        meandvvsvparr[-1].append([10**(-3+float(i*vxbinwidth)),0.,0.])
#meandvvsvparr=array(meandvvsvparr)
mass=[]
charge=[]


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
    swepam.sync_h(iondata[0])
    mag=magdata(resmag,year,timeframe,magpath)
    mag.sync_mag(iondata[0])
    dvvsvparr=[]
    for i in range(nrxbins):
        dvvsvparr.append([])
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
                vd=getvd(swepam.vel[i],tmpvel,tmpmag+tmpbetashift,polarity[p])
            else:
                vd=0.
            #if (((polarity[p]==-1 and tmpmag>pi/2+4*pi/16) or (polarity[p]==1 and tmpmag<pi/2-4*pi/16)) and o7o6[i][1]>0. and tmpvel>swepam.vel[i]-4*valf and tmpvel<swepam.vel[i]+4*valf):
            #if (((polarity[p]==-1 and tmpmag>pi/2+4.*pi/16) or (polarity[p]==1 and tmpmag<pi/2-4.*pi/16)) and wp1[i][1]>0. and tmpvel>swepam.vel[i]-4*valf and tmpvel<swepam.vel[i]+4*valf and vd>0. and sigphiarr[i][1]<pi/180.*12. and sigthetaarr[i][1]<pi/180.*12. and tmpmag!=0.):
            if (((polarity[p]==-1 and tmpmag>pi/2+4.*pi/16) or (polarity[p]==1 and tmpmag<pi/2-4.*pi/16)) and wp1[i][1]>0. and tmpvel>swepam.vel[i]-4*valf and tmpvel<swepam.vel[i]+4*valf and sigphiarr[i][1]<pi/180.*12. and sigthetaarr[i][1]<pi/180.*12. and tmpmag!=0.):
                #x=int((swepam.vel[i]+vxbinwidth/2)/vxbinwidth)
                #x=int((wp3[i][1]+vxbinwidth/2)/vxbinwidth)
                #x=int((log10(o7o6[i][1])+3.-vxbinwidth)/vxbinwidth)
                x=int((log10(wp3[i][1])+3.-vxbinwidth)/vxbinwidth)
                #x=int((mag.magb[i]+vxbinwidth/2)/vxbinwidth)
                
                y=int(((tmpvel-swepam.vel[i])/valf+vybinwidth/2-vyoffset)/vybinwidth)
                #y=int((vd/valf+vybinwidth/2)/vybinwidth)
            else:
                x=-1
                y=-1
            if (x>=0 and x<nrxbins and y>=0 and y<nrybins):# and vd>0.):
                dvvsvparr[x].append((tmpvel-swepam.vel[i])/valf)
                vivsvparr[x,y]+=1.
                #meandvvsvparr[ionnr][x][1]+=vd/valf
                meandvvsvparr[ionnr][x][1]+=(tmpvel-swepam.vel[i])/valf
                meandvvsvparr[ionnr][x][2]+=1.
            elif (x>=0 and x<nrxbins):# and y>0 and y<nrbins):
                dvzeros[x][1]+=1.
            if (sigphiarr[i][1]>pi/180.*12. and sigthetaarr[i][1]>pi/180.*12. and sigphiarr[i][1]>pi/180.*12. and sigthetaarr[i][1]>pi/180.*12.):# and vd>0.):
                dvvsvparr2.append([wp3[i][1],vd/valf])
    for val in meandvvsvparr[ionnr]:
        if val[2]>0.:
            val[1]/=val[2]
    for x in range(nrxbins):
        tmpsig=0.
        if meandvvsvparr[ionnr][x][1]>0.:
            for val in dvvsvparr[x]:
                tmpsig+=(meandvvsvparr[ionnr][x][1]-val)**2
            tmpsig=sqrt(tmpsig/len(dvvsvparr[x])**2)
        meandvvsvparr[ionnr][x][2]=tmpsig
                
#for ion in meandvvsvparr:
#    for val in ion:
#        if val[2]>0.:
#            val[1]/=val[2]

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
    tmpsum/=nrtmpsum
    deltasum=sqrt(deltasum)/nrtmpsum
    #tmpsum/=deltasum
    meanhevse.append([mass[i]/charge[i]**1.,tmpsum,deltasum])


    
for i in range(len(dvzeros)):
    if sum(vivsvparr[i])>0.:
        dvzeros[i][1]/=(sum(vivsvparr[i])+dvzeros[i][1])

xvals=[]
yvals=[]
for i in range(nrxbins):
    #xvals.append(float(i*vxbinwidth))
    xvals.append(10**(-3+float(i*vxbinwidth)))
for i in range(nrybins):
    yvals.append(float(i*vybinwidth)+vyoffset)

pvivsvparr=GridData(vivsvparr,xvals,yvals,binary=0)
pdvzeros=Data(dvzeros)
pdvzeros.set_option_colonsep("with","l lt -1")
xrange=[0.,3.]
#xrange=[300.,800.]
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
#gp("set logscale x")
gp("set palette model RGB functions gray<1.e-20 ? 1 : gray<0.5 ? gray*2 : 1 , gray<1.e-20 ? 1 : gray<0.5 ? gray*2 : 2-gray*2, gray <1.e-20 ? 1 : gray<0.5 ? 1-sqrt(gray*2) : 0")
gp("set logscale cb")
gp.splot(pvivsvparr,pdvzeros)#,pa)
gp.hardcopy("v%s_vs_vp.ps"%(ionlist[0]),color="true",fontsize=20)

pmeandv=[]
for ion in meandvvsvparr:
    pmeandv.append(Data(ion))
    pmeandv[-1].set_option_colonsep("using","1:2:3")
    pmeandv[-1].set_option_colonsep("with","yerrorbars")

gp2=Gnuplot()
gp2.plot(pmeandv[0])
for i in range(1,len(pmeandv)):
    gp2.replot(pmeandv[i])

pmeanhevse=Data(meanhevse)
pmeanhevse.set_option_colonsep("using","1:2:3")
pmeanhevse.set_option_colonsep("with","yerrorbars")

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
    
