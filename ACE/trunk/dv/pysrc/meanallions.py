from math import pi,cos,sin,atan,tan,acos,asin,sqrt,log10
from Gnuplot import Gnuplot,GridData,Data
from scipy import zeros,median,mean,sort
from numpy import array
from scipy import histogram as histogram2
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
            #print beta*180./pi,vd1,vd2
            if (beta<pi/2. and vd1>0.):
                return vd1
            elif (beta>=pi/2. and vd2>0.):
                return vd2
            else:
                return 0.
            """
            if (vd1<100. and vd2<100. and vd1>0. and vd2>0.):
                return (abs(vd1)+abs(vd2))/2.
            elif (vd1<100. and vd1>0.):
                return vd1
            elif (vd2<100.):
                return vd2
            else:
                return 0.
            """
        else:
            return 0.
    elif (polarity==-1.):
        if vp**2*cos(beta)**2+vi**2-vp**2>=0.:
            vd1=vp*cos(beta)+sqrt(vp**2*cos(beta)**2+vi**2-vp**2)
            vd2=vp*cos(beta)-sqrt(vp**2*cos(beta)**2+vi**2-vp**2)
            #print beta*180./pi,vd1,vd2
            if (beta>pi/2. and vd1>0.):
                return vd1
            elif (beta<=pi/2. and vd2>0.):
                return vd2
            else:
                return 0.
            """
            if (vd1<100. and vd2<100. and vd1>0. and vd2>0.):
                return (abs(vd1)+abs(vd2))/2.
            elif (vd1<100. and vd1>0.):
                return vd1
            elif (vd2<100. and vd2>0.):
                return vd2
            else:
                return 0.
            """
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
resmag=1.
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

timeframe=[[6.,12.],[14.,20.]]
#timeframe=[[6.,12.]]#,[14.,20.]]
#timeframe=[[6.,6.5]]

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
ionlist=[["Fe18+"],["Fe17+"],["Fe16+"],["Fe15+"],["Fe14+"],["Fe13+"],["Fe12+"],["Fe11+"],["Fe10+"],["Fe9+"],["Fe8+"],["Fe7+"],["Ca12+"],["Ca11+"],["Ca10+"],["Ca9+"],["Ca8+"],["Ca7+"],["S12+"],["S11+"],["S10+"],["S9+"],["S8+"],["S7+"],["Si11+"],["Si10+"],["Si9+"],["Si8+"],["Si7+"],["Mg10+"],["Mg9+"],["Mg8+"],["Mg7+"],["Ne8+"],["O8+"],["O7+"],["O6+"],["N7+"],["N6+"],["N5+"],["C6+"],["C5+"],["C4+"],["He2+"]]
#ionlist=[["O6+"],["He2+"]]
elemlist=["He","C","N","O","Ne","Mg","Si","S","Ca","Fe"]
# get wave-power timeseries





polarity=zeros([len(timeframe)])
polarity2007=[1,1,1,1,1,-1,1,-1,-1,1,1,-1,1,-1,-1,1,1,-1,-1,1,-1,1,1,-1,1,1,-1,1,1,-1,1,1,1,-1,1]
polarity2008=[-1,1,1,-1,1,1,-1,1,-1,1,-1,1,-1,1,-1,-1,1,-1,-1,1,-1,1,-1,1,-1,1,-1,1,-1]
#polarity=[1,1,1,1,1,-1,1,-1,-1,1,1,-1,1,-1,-1,1,1,-1,-1,1,-1,1,1,-1,1,1,-1,1,1,-1,1,1,1,-1,1]
polarity=[-1,1,1,-1,1,1,-1,1,-1,1,-1,1,-1,1,-1,-1,1,-1,-1,1,-1,1,-1,1,-1,1,-1,1,-1]
polarity=[-1,1]
#polarity=[1]
mass=[]
charge=[]
meandvvsvparr=[]
dvvsvparr=[]
ratioarr=[]
for i in range(len(ionlist)):
    meandvvsvparr.append([0.,0.,0.,0.])  
    dvvsvparr.append([])
    ratioarr.append([])
p=-1
magarr=[]
alfarr=[]
masscharge=[]
for tf in timeframe:
    p+=1
    hedata=swicsiondata("He2+",resswics,year,[tf],datapath)
    swepam=swepamdata(resswepam,year,[tf],swepampath)
    swepam.sync_h(hedata)
    mag=magdata(resmag,year,[tf],magpath)
    mag.sync_mag(hedata)
    ionnr=-1
    for ion in ionlist:
        ionnr+=1

        iondata=swicsiondata(ion[0],resswics,year,[tf],datapath)
        meandvvsvparr[ionnr][0]=iondata.mass/iondata.charge
        meandvvsvparr[ionnr][3]=iondata.mass/iondata.charge**2
        if p==0:
            masscharge.append([iondata.mass,iondata.charge,0,0])
        for i in range(len(iondata.time)):
            if (swepam.dens[i]>0.):
                valf=21.8*mag.magb[i]/sqrt(swepam.dens[i])
            else:
                valf=0.
            if (valf>0.):# and colage>0.):
                if (mag.phi[i]!=0. and mag.theta[i]!=0. and swepam.vel[i]>0.):
                    tmpmag=acos((swepam.velx[i]*mag.magbx[i]+(swepam.vely[i])*mag.magby[i]+swepam.velz[i]*mag.magbz[i])/(swepam.vel[i]*sqrt(mag.magbx[i]**2+mag.magby[i]**2+mag.magbz[i]**2)))
                    #tmpmag=acos(cos(mag.phi[i])*cos(mag.theta[i]))
                else:
                    tmpmag=0.
                if iondata.vel[i]>300. and iondata.vel[i]<850. and (tmpmag<pi/180.*70. or tmpmag>pi/180.*110):
                    vd=getvd(swepam.vel[i],iondata.vel[i],tmpmag,polarity[p])
                    vdhe=getvd(swepam.vel[i],hedata.vel[i],tmpmag,polarity[p])
                    if 1:
                    #if vd>0.:
                        meandvvsvparr[ionnr][1]+=vd/valf
                        meandvvsvparr[ionnr][2]+=1.
                        dvvsvparr[ionnr].append(vd/valf)
                        if vdhe>0.:
                            ratioarr[ionnr].append(vd/vdhe)
                        if (ion[0]=="He2+"):
                            magarr.append(tmpmag)
                            alfarr.append(valf)
                        #if vd==0.:
                        #    meandvvsvparr[ionnr][3]+=1.
                    #else:
                    #    meandvvsvparr[ionnr][3]+=1.
                        
i=-1
for val in dvvsvparr:
    i+=1
    tmpval=sort(val)
    j=-1
    j0=0
    for val2 in tmpval:
        j+=1
        if val2==0.:
            j0=j
    meandvvsvparr[i][1]=mean(tmpval[j0:-j0-1])
    masscharge[i][2]=len(tmpval[j0:-j0-1])
    if len(tmpval)>0:
        masscharge[i][3]=2*j0

histmeandvarr=[]
for val in meandvvsvparr:
    histmeandvarr.append(val[1])
histmeandv=histogram2(histmeandvarr,20,[0.,1.])

numpion=[]
numpion2=[]
for i in range(len(elemlist)):
    numpion.append([])
    numpion2.append([])
mass=masscharge[-1][0]
elem=0
for i in range(len(masscharge)):
    if masscharge[-i-1][0]==mass:
        numpion[elem].append([elem+i+1,masscharge[-i-1][2],masscharge[-i-1][1]])
        numpion2[elem].append([elem+i+1,masscharge[-i-1][3],masscharge[-i-1][1]])
    else:
        mass=masscharge[-i-1][0]
        elem+=1
        numpion[elem].append([elem+i+1,masscharge[-i-1][2],masscharge[-i-1][1]])
        numpion2[elem].append([elem+i+1,masscharge[-i-1][3],masscharge[-i-1][1]])

#gp("set xtics ('0' '0','' '25' 1,'50' '50','' '75' 1,'100' '100','' '125' 1,'150' '150', '' '175' 1,'200' '200', '' '225' 1,'250' '250', '' '275' 1,'300' '300', '' '325' 1,'350' '350', '' '375' 1,'400' '400')") 
        
xtics="set xtics ("
for elem in range(len(numpion)):
    for ion in range(len(numpion[elem])):
        xtics+="'%i' '%i'"%(numpion[elem][ion][2],numpion[elem][ion][0])
        if elem==len(numpion)-1:
            if ion==len(numpion[elem])-1:
                continue
            else:
                xtics+=","
        else:
            xtics+=","
            
xtics+=") font 'Times-Roman,12'"
                        
pnumpion=[]
pnumpion2=[]
for i in range(len(numpion)):
    pnumpion.append(Data(numpion[i]))
    pnumpion[-1].set_option_colonsep("using","1:2")
    pnumpion[-1].set_option_colonsep("with","boxes fs solid .5 lt %i"%(len(numpion)-i))
    pnumpion2.append(Data(numpion2[i]))
    pnumpion2[-1].set_option_colonsep("using","1:2")
    pnumpion2[-1].set_option_colonsep("with","boxes fs solid .5 lt 0")

                    
"""
i=-1
for val in meandvvsvparr:
    i+=1
    if val[2]>0.:
        #val[1]/=val[2]
        #val[1]=median(dvvsvparr[i])
        val[1]=median(ratioarr[i])
"""

"""
for i in range(len(ionlist)):
    tmpsig=0.
    for val in dvvsvparr[i]:
        tmpsig+=(val-meandvvsvparr[i][1])**2
    if len(dvvsvparr[i])>0.:
        #tmpsig/=float(len(dvvsvparr[i]))
        tmpsig=sqrt(tmpsig)
        tmpsig/=float(len(dvvsvparr[i]))
    meandvvsvparr[i][2]=tmpsig
"""

histarr2=[]
meandv2=[]
for i in range(len(ionlist)):
    tmpsig=0.
    tmpval=sort(dvvsvparr[i])
    j=-1
    j0=0
    for val2 in tmpval:
        j+=1
        if val2==0.:
            j0=j
    for val in tmpval[j0:-j0-1]:
        tmpsig+=(val-meandvvsvparr[i][1])**2
    if len(tmpval[j0:-j0-1])>0.:
        tmpsig=sqrt(tmpsig/float(len(tmpval[j0:-j0-1]))**2)
    meandv2.append(mean(tmpval[j0:-j0-1]))
    tmphist=histogram2(tmpval[j0:-j0-1],60,[0.,3.])
    tmphist2=[]
    for k in range(60):
        tmphist2.append([tmphist[1][k],tmphist[0][k]])
    #tmphist2.append([mean(val),100.])
    histarr2.append(tmphist2)
    meandvvsvparr[i][2]=tmpsig
    meandvvsvparr[i][3]=(len(tmpval[j0:-j0-1]))

dvrmean=[]
for ion in dvvsvparr:
    dvrmean.append([])
    for i in range(len(ion)-20):
        dvrmean[-1].append(mean(ion[i:i+20]))
magrmean=[]
for i in range(len(magarr)-20):
    magrmean.append(mean(magarr[i:i+20]))

meanhevse=meandvvsvparr
pmeandvvsvparr=Data(meandvvsvparr)
pmeandvvsvparr.set_option_colonsep("using","1:4:2")

"""
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
"""

histarr=[]
meandv=[]
for val in dvvsvparr:
    meandv.append(mean(val))
    tmphist=histogram2(val,60,[0.,3.])
    tmphist2=[]
    for i in range(60):
        tmphist2.append([tmphist[1][i],tmphist[0][i]])
    #tmphist2.append([mean(val),100.])
    histarr.append(tmphist2)

phistarr=[]
phistarr2=[]
pmeandv=[]
pmeandv2=[]
for i in range(len(histarr)):
    phistarr.append(Data(histarr[i]))
    phistarr2.append(Data(histarr2[i]))
    pmeandv.append(Data([[meandv[i],0.],[meandv[i],180.]]))
    pmeandv2.append(Data([[meandv2[i],0.],[meandv2[i],180.]]))
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
meanelem[-4].append(meanhevse[-10])
meanelem[-4].append(meanhevse[-9])
meanelem[-4].append(meanhevse[-8])
meanelem[-5].append(meanhevse[-11])
meanelem[-6].append(meanhevse[-15])
meanelem[-6].append(meanhevse[-14])
meanelem[-6].append(meanhevse[-13])
meanelem[-6].append(meanhevse[-12])
meanelem[-7].append(meanhevse[-20])
meanelem[-7].append(meanhevse[-19])
meanelem[-7].append(meanhevse[-18])
meanelem[-7].append(meanhevse[-17])
meanelem[-7].append(meanhevse[-16])
meanelem[-8].append(meanhevse[-26])
meanelem[-8].append(meanhevse[-25])
meanelem[-8].append(meanhevse[-24])
meanelem[-8].append(meanhevse[-23])
meanelem[-8].append(meanhevse[-22])
meanelem[-8].append(meanhevse[-21])
meanelem[-9].append(meanhevse[-32])
meanelem[-9].append(meanhevse[-31])
meanelem[-9].append(meanhevse[-30])
meanelem[-9].append(meanhevse[-29])
meanelem[-9].append(meanhevse[-28])
meanelem[-9].append(meanhevse[-27])
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
    pmeanelem[-1].set_option_colonsep("with","yerrorbars ps 2 lw 2")
    pmeanelem[-1].set_option_colonsep("axes","x2y1")


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


gp=Gnuplot()
gp("set term postscript solid enhanced color 18 lw 2 ")
gp("set output 'papermeanfinal.ps'")
gp("set multiplot")
gp("set autoscale")
#gp("set origin 0.0235,0.")
#gp("set size .9765,0.35")
gp("set origin 0.,0.")
gp("set size 1.,0.35")
gp("set boxwidth 1.")
gp("%s"%(xtics))
gp("set xrange[0:%i]"%(numpion[-1][-1][0]+1))
gp("set yrange[10.:2000.]")
gp("set xlabel '{/Times-Roman=20 q [e]}'")# offset 1.5")
gp("set ylabel '{/Times-Roman=20 # data points}' offset -.32")
gp("set format y '10^%T'")
gp("set log y")

for i in range(len(elemlist)):
    tmp=array(numpion[i])
    print elemlist[i],mean(tmp[:,0]),10.
    gp("set label '%s' at %f,%f center front"%(elemlist[i],mean(tmp[:,0]),100.))
#pnumpion=array(pnumpion)
gp.plot(pnumpion[0],pnumpion[1],pnumpion[2],pnumpion[3],pnumpion[4],pnumpion[5],pnumpion[6],pnumpion[7],pnumpion[8],pnumpion[9])#,pnumpion2[0],pnumpion2[1],pnumpion2[2],pnumpion2[3],pnumpion2[4],pnumpion2[5],pnumpion2[6],pnumpion2[7],pnumpion2[8],pnumpion2[9])
#for i in range(len(pnumpion)-1):
#    gp.replot(pnumpion[i+1])

gp("set origin 0.,.288")
gp("set size 1.,0.65")
gp("set autoscale")
gp("unset xlabel")
gp("unset label")
gp("unset log y")
gp("unset format")
gp("set yrange[-1.:1.]")
gp("set grid front")
gp("unset grid")
#gp("set x2range[0:10]") 
gp("set yrange[0.:1.]") 
gp("set ytics 0.1,0.1")
gp("set x2range [1:9]")
gp("unset xtics")
gp("set x2tics auto mirror")
gp("set mx2tics 10")
gp("set x2label '{/Times-Roman=20 m/q [amu/e]}'")
gp("set ylabel '{/Times-Roman=20 Mean |v_{ip}|/C_{A}}' offset 2.")
gp("f1(x)=0.4")
gp("f2(x)=0.7")
gp.plot(pmeanelem[0],pmeanelem[1],pmeanelem[2],pmeanelem[3],pmeanelem[4],pmeanelem[5],pmeanelem[6],pmeanelem[7],pmeanelem[8],pmeanelem[9],"f1(x) with l lt 0 lw 2 title ''","f2(x) with l lt 0 lw 2 title ''")


phistarr[-1].set_option_colonsep("title","'He^{2+}'")
phistarr[-1].set_option_colonsep("with","steps lt 1 lw 2")
phistarr[36].set_option_colonsep("title","'O^{6+}'")
phistarr[36].set_option_colonsep("with","steps lt 3 lw 2")
phistarr[9].set_option_colonsep("title","'Fe^{9+}'")
phistarr[9].set_option_colonsep("with","steps lt 4 lw 2")
phistarr[26].set_option_colonsep("title","'Si^{9+}'")
phistarr[26].set_option_colonsep("with","steps lt 5 lw 2")
phistarr2[-1].set_option_colonsep("with","steps lt 1 lw 2")
phistarr2[36].set_option_colonsep("with","steps lt 3 lw 2")
phistarr2[9].set_option_colonsep("with","steps lt 4 lw 2")
phistarr2[26].set_option_colonsep("with","steps lt 5 lw 2")
pmeandv[-1].set_option_colonsep("with","l lt 1 lw 2")
pmeandv[36].set_option_colonsep("with","l lt 3 lw 2")
pmeandv[9].set_option_colonsep("with","l lt 4 lw 2")
pmeandv[26].set_option_colonsep("with","l lt 5 lw 2")
pmeandv2[-1].set_option_colonsep("with","l lt 1 lw 2")
pmeandv2[36].set_option_colonsep("with","l lt 3 lw 2")
pmeandv2[9].set_option_colonsep("with","l lt 4 lw 2")
pmeandv2[26].set_option_colonsep("with","l lt 5 lw 2")


mp=multiplot(2,1)
mp.setname("paperdvhistfinal")
mp.setxlabel("|v_{ip}|/C_{A}")
mp.setxrange(0,2)
mp.panel[1].setylabel("# occurences")
mp.panel[1].setyrange(0,180)
mp.panel[1].key="set key"
mp.panel[1].adddata(phistarr[-1])
mp.panel[1].adddata(phistarr[36])
mp.panel[1].adddata(phistarr[26])
mp.panel[1].adddata(phistarr[9])
mp.panel[1].adddata(pmeandv[-1])
mp.panel[1].adddata(pmeandv[36])
mp.panel[1].adddata(pmeandv[26])
mp.panel[1].adddata(pmeandv[9])
mp.panel[0].setylabel("# occurences")
mp.panel[0].setyrange(0,180)
mp.panel[0].adddata(phistarr2[-1])
mp.panel[0].adddata(phistarr2[36])
mp.panel[0].adddata(phistarr2[26])
mp.panel[0].adddata(phistarr2[9])
mp.panel[0].adddata(pmeandv2[-1])
mp.panel[0].adddata(pmeandv2[36])
mp.panel[0].adddata(pmeandv2[26])
mp.panel[0].adddata(pmeandv2[9])
mp.plot()
gp2=Gnuplot()
gp2("set xlabel '|v_{ip}|/C_{A}'")
gp2("set ylabel '# occurences'")
gp2("set xrange[0:2]")
gp2("set mxtics 10")
gp2("set mytics 4")
gp2.plot(phistarr2[-1],phistarr2[36],phistarr2[26],phistarr2[9])
gp2.hardcopy("paperdvhist.ps",color="True")

"""
gp("set boxwidth 1.")
gp("%s"%(xtics))
gp("set xrange[0:%i]"%(numpion[-1][-1][0]+1))
for i in range(len(elemlist)):
    tmp=array(numpion[i])
    print elemlist[i],mean(tmp[:,0]),10.
    gp("set label '%s' at %f,%f center front"%(elemlist[i],mean(tmp[:,0]),10.))

gp.plot(pnumpion[0])
for i in range(len(pnumpion)-1):
    gp.replot(pnumpion[i+1])
gp3=Gnuplot()
gp3("set xrange[0:10]") 
gp3("set yrange[0.:1.]") 
gp3("set ytics 0.1")
gp3("set xrange [1:9]")
gp3("set xlabel 'm/q [amu/e]'")
gp3("set ylabel 'Mean |v_{ip}|/C_{A}'")
gp3.plot(pmeanelem[0])
for i in range(1,10):
    gp3.replot(pmeanelem[i])
gp3.hardcopy("meandvallionserrorsIII.ps",color="True")    
"""

