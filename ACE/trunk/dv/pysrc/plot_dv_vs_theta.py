from Gnuplot import Gnuplot,GridData,Data
from libacepy.ancil import getdvarr
from libacepy.swicsiondata import loadswicsiondata
from libacepy.mag import loadmagdata
from libacepy.swepamdata import swepamdata
from libacepy.multiplot import multiplot
from libacepy.swicsprotondata import swicsprotondata
from numpy import pi,cos,arccos,sqrt,zeros,append,linspace,mean,std
from os.path import isfile

def getthvi(vp,dv,theta):
    """
    Calculate vi that would have been observed given proton velocity vp, absolute value of differential streaming dv and angle theta between vec(vp) and vec(vip)= vec(vi)-vec(vp).
    """
    from math import cos,sqrt
    vi=sqrt(dv**2-2*dv*vp*cos(theta)+vp**2)
    return vi

def getthdv(vp,dv,valf,polarity,steps=500):
    from math import pi
    from numpy import array
    thdvarr=[]
    for i in range(steps):
        if polarity==1:
            thdvarr.append([float(i)/float(steps)*pi,(getthvi(vp,dv*valf,pi-float(i)/float(steps)*pi)-vp)/valf])
        if polarity==-1:
            thdvarr.append([float(i)/float(steps)*pi,(getthvi(vp,dv*valf,float(i)/float(steps)*pi)-vp)/valf])
    return array(thdvarr)



resswics=720.
resswepam=64.
resmag=1.
ionlist=["He2+"]
years=[2006]

effpath="/data/ivar/ace/efficencies/aspeff/"
datapath="/data/wimmer/ace/"
datapath2="/data/zechine/ace/12mprotons/2008/"
swepampath="/data/wimmer/ace/swepam/"
magpath="/data/missions/ace/mag/lv2/"
magpath="/data/wimmer/ace/mag/"
outname="dv%s"%(ionlist[0].replace("+",""))
for year in years:
    outname+="_%i"%(year)
outname+=".ps"

timeframe2008new=[[6.25,12.2],[15.,22.5],[25.25,26.5],[33.,37.8],[42.5,49.],[50.,53.5],[61.,64.],[69.5,77.5],[88.5,91.5],[97.75,105.75],[115.5,118.5],[126.,130.],[143.,147.5],[151.,155.],[168.,171.],[172.5,175.5],[179.,181.5],[194.5,200.5],[223.25,226.75],[232.,234.75],[248.5,253.5],[259.5,261.],[276.5,281.5],[286.,288.5],[303.5,308.75],[313.25,314.25],[331.,335.],[341.5,344.],[359.,361.5]]

timeframe2007new=[[3.5,7.5],[17.,23.5],[30.,34.5],[45.5,50.],[59.5,61.5],[66.5,68.],[73.5,78.5],[92.5,97.],[118.5,122.5],[129.,130.5],[139.5,141.5],[145.,150.],[166.,172.],[174.5,177.],[186.,189.],[192.5,194.5],[196.5,199.],[211.,213.],[214.,216.5],[219.5,221.],[239.,243.],[246.,249.],[250.5,252.],[265.5,270.],[272.5,275.5],[277.,279.5],[293.,295.5],[299.,302.5],[303.5,305.],[318.,322.],[325.,326.],[327.,328.],[329.,333.5],[346.,350.],[355,359.5]]

timeframe2006new=[[24.5,25.],[26.5,29.],[35.,36.],[42.5,44.],[46.5,49.],[51.5,56.5],[60.,63.5],[68.,72.],[74.,76.],[77.5,84.5],[87.,88.5],[95.5,97.],[99.,103.],[104.,109.5],[110.5,116.],[126.5,129.5],[131.,135.],[138.5,144.],[152.,155.5],[157.5,163.],[166.,170.],[179.,184.],[185.5,189.5],[193.,195.],[209.,211.],[212.5,217.5],[219.5,225.],[239.5,242.5],[260.,263.5],[267.,271.],[274.,278.5],[281.,283.5],[286.,290.],[293.5,297.5],[302.,305.5],[314.,318.],[320.5,321.5],[327.5,333.],[340.,341.5],[344.,348.5],[353.,361.]]

timeframe=[]
timeframe.append(timeframe2006new)
#timeframe.append(timeframe2007new)
#timeframe.append(timeframe2008new)
#timeframe.append(timeframe2006new)


polarity2006=[-1,-1,1,1,1,-1,1,1,1,-1,1,1,1,-1,1,1,-1,1,1,-1,1,1,-1,1,1,-1,1,-1,1,-1,1,-1,1,-1,1,1,-1,1,1,-1,1]
polarity2007=[1,1,1,1,1,-1,1,-1,-1,1,1,-1,1,-1,-1,1,1,-1,-1,1,-1,1,1,-1,1,1,-1,1,1,-1,1,1,1,-1,1]
polarity2008=[-1,1,1,-1,1,1,-1,1,-1,1,-1,1,-1,1,-1,-1,1,-1,-1,1,-1,1,-1,1,-1,1,-1,1,-1]

polarity=[]
polarity.append(polarity2006)
#polarity.append(polarity2007)
#polarity.append(polarity2008)
#polarity=[[-1,1]]

ion=ionlist[0]
uppervel=800.
lowervel=350.
thetaarr1=zeros((0))
thetaarr2=zeros((0))
obsdvarr1=zeros((0))
obsdvarr2=zeros((0))
recdvarr1=zeros((0))
recdvarr2=zeros((0))

# get theoretical dv values
pthdv=Data(getthdv(600.,0.55,80.,1),with_="l lt -1 lw 3")
pthdv2=Data(getthdv(600.,0.55,80.,-1),with_="l lt -1 lw 3")

iyear=-1
for year in years:
    iyear+=1
    p=-1
    for tf in timeframe[iyear]:
        p+=1

        ion=ionlist[0]
        timeframe2=[tf]
        iondata=loadswicsiondata(ion,resswics,year,timeframe2,datapath,loadflux=0)
        plotelemname=iondata.name.replace("%s+"%(str(iondata.charge)),"")
        plotchargename=str(iondata.charge)+"+"
        swepam=swepamdata(resswepam,year,timeframe2,swepampath)
        mag=loadmagdata(resmag,year,timeframe2,magpath)
        #mag.sync_mag_hires(iondata)
        #swepam.sync_h_hires(iondata)
        mag.sync_mag(iondata)
        swepam.sync_h(iondata)

        # calculate angles between proton velocity and magnetic field vector
        theta=arccos((swepam.velx*mag.magbx+(swepam.vely)*mag.magby+swepam.velz*mag.magbz)/(swepam.vel*sqrt(mag.magbx**2+mag.magby**2+mag.magbz**2)))

        # calculate alfven speeds
        valf=21.8*mag.magb/sqrt(swepam.dens)

        # calculate collisional age
        colage=(6.4e8*swepam.dens)/(swepam.vel*(swepam.temp)**1.5)
        
        mask=(valf>0.)*(swepam.vel>0.)*(iondata.vel>0.)

        if polarity[iyear][p]==1:
            thetaarr1=append(thetaarr1,theta[mask])
            obsdvarr1=append(obsdvarr1,(iondata.vel[mask]-swepam.vel[mask])/valf[mask])
            recdvarr1=append(recdvarr1,getdvarr(swepam.vel[mask],iondata.vel[mask],theta[mask],polarity[iyear][p])/valf[mask])
        elif polarity[iyear][p]==-1:
            thetaarr2=append(thetaarr2,theta[mask])
            obsdvarr2=append(obsdvarr2,(iondata.vel[mask]-swepam.vel[mask])/valf[mask])
            recdvarr2=append(recdvarr2,getdvarr(swepam.vel[mask],iondata.vel[mask],theta[mask],polarity[iyear][p])/valf[mask])

    # end building arrays
nbins=18
thetabins=linspace(0.,pi,nbins+1)
meanobsdv1=zeros((nbins))
meanobsdv2=zeros((nbins))
meanrecdv1=zeros((nbins))
meanrecdv2=zeros((nbins))
stdobsdv1=zeros((nbins))
stdobsdv2=zeros((nbins))
stdrecdv1=zeros((nbins))
stdrecdv2=zeros((nbins))
for i in range(nbins):
    mask1=(thetaarr1>thetabins[i])*(thetaarr1<thetabins[i+1])
    mask2=(thetaarr2>thetabins[i])*(thetaarr2<thetabins[i+1])
    meanobsdv1[i]=mean(obsdvarr1[mask1])
    stdobsdv1[i]=std(obsdvarr1[mask1])
    meanobsdv2[i]=mean(obsdvarr2[mask2])
    stdobsdv2[i]=std(obsdvarr2[mask2])
    meanrecdv1[i]=mean(recdvarr1[mask1])
    stdrecdv1[i]=std(recdvarr1[mask1])
    meanrecdv2[i]=mean(recdvarr2[mask2])
    stdrecdv2[i]=std(recdvarr2[mask2])
thetabins=thetabins[:-1]+pi/float(nbins*2)
binwidths=zeros((nbins))+pi/float(nbins*2)

pmeanobsdv1=Data(thetabins,meanobsdv1,binwidths,stdobsdv1,with_="xyerrorbars lt 1 lw 3 pt 5",using="1:2:3:4")
pmeanobsdv2=Data(thetabins,meanobsdv2,binwidths,stdobsdv2,with_="xyerrorbars lt 3 lw 3 pt 7",using="1:2:3:4")
pmeanrecdv1=Data(thetabins,meanrecdv1,binwidths,stdrecdv1,with_="xyerrorbars lt 1 lw 3 pt 5",using="1:2:3:4")
pmeanrecdv2=Data(thetabins,meanrecdv2,binwidths,stdrecdv2,with_="xyerrorbars lt 3 lw 3 pt 7",using="1:2:3:4")


pdvscatter1=Data(thetaarr1,obsdvarr1,with_="d lt 1",using="1:2")
pdvscatter2=Data(thetaarr2,obsdvarr2,with_="d lt 3",using="1:2")

xaxis=[[0.,0.],[pi,0.]]
pxaxis=Data(xaxis)
pxaxis.set_option_colonsep("with","l lt -1")
yaxis=[[pi/2.,-1.,0.,2.]]
pyaxis=Data(yaxis)
pyaxis.set_option_colonsep("with","vector nohead lt 0")
box=[[0.,0.,-1.],[pi,0.,-1.]]
pbox=Data(box)
pbox.set_option_colonsep("using","1:2:3")
pbox.set_option_colonsep("with", "filledcurves lt 9")
gp=Gnuplot()
gp("set term postscript portrait solid enhanced color")
#gp("set term postscript color 20 lw 2 ps")
gp("set output '%s'"%(outname))
gp("set multiplot")
gp("set autoscale")
gp("set origin 0.,0.")
gp("set size 1.,0.35")
gp("set xrange[0:pi]")
gp("set xtics ('0' 0,'' %f 1,'' %f 1,'' %f 1,'{/Symbol p}/4' %f,'' %f 1,'' %f 1,'' %f 1,'{/Symbol p}/2' %f,'' %f 1,'' %f 1,'' %f 1,'{/Symbol p}3/4' %f,'' %f 1,'' %f 1,'' %f 1,'{/Symbol p}' %f)"%(pi/16.,pi/8.,pi*3/16.,pi/4.,pi*5./16.,pi*6/16.,pi*7/16.,pi/2.,pi*9./16.,pi*10./16.,pi*11./16.,pi*3./4.,pi*13./16.,pi*14./16.,pi*15./16.,pi))
gp("set ytics offset .5 ('-0.0' 0,'' .1,'0.2' .2,'' .3,'0.4' .4,'' .5,'0.6' .6,'' .7,'0.8' .8,'' .9,'' 1.)")
gp("set xlabel '{/Symbol Q} [rad]'")
gp("set ylabel '|{/Times-RomanBold= v}_{%s^{%s}p}|/C_{A}' offset 1.5"%(plotelemname,plotchargename))
gp("set yrange[0:1.]")
gp.plot(pmeanrecdv1,pmeanrecdv2)
gp("set origin 0.,.288")
gp("set size 1.,0.65")
gp("set ylabel '{/Symbol u}_{%s^{%s}p}/C_{A}' offset 1.5"%(plotelemname,plotchargename))
gp("unset xlabel")
gp("set yrange[-1.:1.]")
gp("set grid front")
gp("unset grid")
gp("set xrange[0:pi]")
gp("set mxtics 4")
gp("set label '{/Times-ROmanBold=22 I}' at %f,%f center front tc lt -1" % (pi/4.,0.85))
gp("set label '{/Times-ROmanBold=22 IV}' at %f,%f center front tc lt -1" % (pi/4.,-0.85))
gp("set label '{/Times-ROmanBold=22 III}' at %f,%f center front tc lt -1" % (3*pi/4.,-0.85))
gp("set label '{/Times-ROmanBold=22 II}' at %f,%f center front tc lt -1" % (3*pi/4.,0.85))
#gp("set label center'{/Helvetica B_{+}Earth-pointing}' at graph 0.25,0.95 tc lt 1")
#gp("set label center front '{/Helvetica B_{+} Sun-pointing}' at graph 0.75,0.05 tc lt 1")
#gp("set label center'{/Helvetica B_{-}Earth-pointing}' at graph 0.75,0.95 tc lt 3")
#gp("set label center front '{/Helvetica B_{-} Sun-pointing}' at graph 0.25,0.05 tc lt 3")
#gp("set label center front '|' at screen 0.04,0.6 tc lt -1")
#gp("set label center front '|' at screen 0.04,0.61 tc lt -1")
#gp("set label center front '|' at screen 0.04,0.62 tc lt -1")
#gp("set label center front '|' at screen 0.04,0.63 tc lt -1")

gp("set xtics ('' 0,'' %f 1,'' %f 1,'' %f 1,'' %f,'' %f 1,'' %f 1,'' %f 1,'' %f,'' %f 1,'' %f 1,'' %f 1,'' %f,'' %f 1,'' %f 1,'' %f 1,'' %f)"%(pi/16.,pi/8.,pi*3/16.,pi/4.,pi*5./16.,pi*6/16.,pi*7/16.,pi/2.,pi*9./16.,pi*10./16.,pi*11./16.,pi*3./4.,pi*13./16.,pi*14./16.,pi*15./16.,pi))
gp("set ytics offset .5 ('-1.0' -1,'' -.9,'-0.8' -.8,'' -.7,'-0.6' -.6,'' -.5,'-0.4' -.4,'' -.3,'-0.2' -.2,'' -.1,'-0.0' 0,'' .1,'0.2' .2,'' .3,'0.4' .4,'' .5,'0.6' .6,'' .7,'0.8' .8,'' .9,'1.0' 1.)")
gp.plot(pbox,pmeanobsdv1,pmeanobsdv2,pdvscatter1,pdvscatter2,pxaxis,pyaxis,pthdv,pthdv2)

