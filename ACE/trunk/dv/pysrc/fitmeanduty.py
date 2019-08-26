from math import pi,cos,sin,atan,tan,acos,asin,sqrt
from Gnuplot import Gnuplot,GridData,Data
from scipy import zeros
from numpy import array
from libacepy.ancil import histogram,sig_histogram
from libacepy.newdutycycle import dutycycle
from libacepy.swicsiondata import swicsiondata
from libacepy.mag import magdata,sync_mag
from libacepy.attitude import attdata,sync_attitude
from libacepy.swepamdata import swepamdata,sync_h
from libacepy.multiplot import multiplot
from libacepy.swicsprotondata import swicsprotondata
from libacepy.dutyfunc import dutyfunc
from libacepy.lmfitmod import maxlifit

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

daylist=range(1,153)
timeframe=[[4.,9.],[17.4,25.25],[30.5,35.],[45.5,55.],[60.,63.],[65.5,70.],[73.25,80.5],[93.,97.5],[103.,107.],[119.,126.5],[129.,135.],[145.25,151.1]]
#timeframe=[[4.,9.]]
effpath="/data/ivar/ace/efficencies/aspeff/"
datapath="/data/wimmer/ace/12mdata/2007/"
datapath2="/data/zechine/ace/12mprotons/2007/"
swepampath="/data/ivar/ace/swepam/"
magpath="/data/ivar/ace/mag/"
#protondata=swicsprotondata("H1+",timeframe,datapath2)
#protondata.load()
ionlist=["He2+","C6+","C5+","N7+","N6+","O7+","O6+","Ne8+","Mg8+","Mg9+","Si8+","Si9+","S8+","S9+","Ca9+","Ca10+","Fe9+","Fe10+","Fe11+","Fe12+","Fe13+"]
ionlist=["He2+"]
swepam=swepamdata(720,2007,timeframe[0][0],timeframe[len(timeframe)-1][1]+1.,swepampath)
swepam.load()
mag=magdata(240,2007,float(daylist[0]),float(daylist[len(daylist)-1]),magpath)
mag.load()
att=attdata(mag.year,mag.path)
att.load()

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
first=1
magdirarr=[]
meanvalf=[]
meanv=[]
meanb=[]
meanbx=[]
meanbz=[]
meanax=[]
meanaz=[]
for ion in ionlist:
    iondata=swicsiondata(ion,timeframe,datapath)
    iondata.load()
    syncmag=sync_mag(mag,iondata)
    syncswepam=sync_h(swepam,iondata)
    syncatt=sync_attitude(att,iondata)


    # build all arrays for histograms!
    dvarr=[]
    dvarr2=[]
    vtharr=[]
    vtharr2=[]
    temparr=[]
    densarr=[]
    swepamvth=[]
    
    for i in range(len(iondata.time)):
        if (1):
            # calculate mag angle
            if (syncmag.phi[i][1]>=0. and syncmag.theta[i][1]!=0.):
                #tmpmag=acos(abs(cos(syncmag.phi[i][1]-syncatt.phi[i])*cos(syncmag.theta[i][1]-syncatt.theta[i])))
                tmpmag=acos(abs(cos(syncmag.phi[i][1])*cos(syncmag.theta[i][1])))
            else:
                tmpmag=0.
            # calculate alfvenspeed
            if (syncswepam.dens[i][1]>0.):
                valf=21.8*syncmag.magb[i][1]/sqrt(syncswepam.dens[i][1])
            else:
                valf=0.
            if (iondata.vel[i]>100. and iondata.vel[i]<1000. and syncswepam.vel[i][1]>600. and valf>0. and tmpmag>0. and tmpmag<1.6 and syncmag.phi[i][1]*syncmag.dpp[i][1]<pi/180.*11.5 and syncmag.theta[i][1]*syncmag.dtt[i][1]<pi/180.*11.5 and iondata.crvth[i]>10.):
                tmpasp=calc_newasp(syncmag.phi[i][1],syncmag.theta[i][1],syncatt.phi[i],syncatt.theta[i])
                dvarr.append([tmpmag,(iondata.crvel[i]-syncswepam.vel[i][1])/valf])
                dvarr2.append([tmpmag,(iondata.vel[i]-syncswepam.vel[i][1])/valf])
                #dvarr.append([tmpmag,(iondata.crvel[i]-protondata.crvel[i])/valf])
                #dvarr2.append([tmpmag,(iondata.vel[i]-protondata.crvel[i])/valf])
                vtharr.append([tmpmag,iondata.crvth[i]])
                vtharr2.append([tmpmag,iondata.vth[i]])
                temparr.append([tmpmag,iondata.temp[i][0]])
                densarr.append([tmpmag,iondata.dens[i][0]])
                meanvalf.append([tmpmag,valf])
                meanbx.append([tmpmag,syncmag.phi[i][1]])
                meanbz.append([tmpmag,syncmag.theta[i][1]])
                meanb.append([tmpmag,tmpmag])
                #meanax.append([tmpmag,syncatt.phi[i]])
                #meanaz.append([tmpmag,syncatt.theta[i]])
                meanax.append([tmpmag,tmpasp[0]])
                meanaz.append([tmpmag,tmpasp[1]])
                meanv.append([tmpmag,syncswepam.vel[i][1]])
                #meanv.append([tmpmag,protondata.crvel[i]])
                
    nrhist=4
    histstep=1.6/float(nrhist)
    # end building arrays
    valfhist=histogram(meanvalf,0.,histstep,nrhist,3)
    sigvalfhist=sig_histogram(meanvalf,valfhist,3)
    bxhist=histogram(meanbx,0.,histstep,nrhist,3)
    bzhist=histogram(meanbz,0.,histstep,nrhist,3)
    bhist=histogram(meanb,0.,histstep,nrhist,3)
    axhist=histogram(meanax,0.,histstep,nrhist,3)
    azhist=histogram(meanaz,0.,histstep,nrhist,3)
    vhist=histogram(meanv,0.,histstep,nrhist,3)
    dvhist=histogram(dvarr,0.,histstep,nrhist,4)
    #dvhist.append([1.6,0.,0])
    sigdvhist=sig_histogram(dvarr,dvhist,4)
    dverr=[]
    for i in range(len(dvhist)):
        dverr.append([dvhist[i][0],dvhist[i][1],sigdvhist[i][1]/sqrt(sigdvhist[i][2]+1.)])
    pdvhist.append(Data(dverr))
    pdvhist[len(pdvhist)-1].set_option_colonsep("title","'Observations'")
    pdvhist[len(pdvhist)-1].set_option_colonsep("with","yerrorbars lt 1 lw 2")
    pdvhist[len(pdvhist)-1].set_option_colonsep("using","1:2:3")
    dvhist2=histogram(dvarr2,0.,histstep,nrhist,3)
    dvhist2.append([1.6,0.,0])
    pdvhist2.append(Data(dvhist2))
    pdvhist2[len(pdvhist2)-1].set_option_colonsep("title","'Observations'")
    pdvhist2[len(pdvhist2)-1].set_option_colonsep("with","steps lt 1 lw 2")
    pdvhist2[len(pdvhist2)-1].set_option_colonsep("using","1:2")
    vthhist=histogram(vtharr,0.,histstep,nrhist,4)
    #vthhist.append([1.6,0.,0])
    sigvthhist=sig_histogram(vtharr,vthhist,4)
    vtherr=[]
    for i in range(len(dvhist)):
        vtherr.append([vthhist[i][0],vthhist[i][1],sigvthhist[i][1]/sqrt(sigvthhist[i][2]+1.)])
    pvthhist.append(Data(vtherr))
    pvthhist[len(pvthhist)-1].set_option_colonsep("title","'Observations'")
    pvthhist[len(pvthhist)-1].set_option_colonsep("with","yerrorbars lt 1 lw 2")
    pvthhist[len(pvthhist)-1].set_option_colonsep("using","1:2:3")
    vthhist2=histogram(vtharr2,0.,histstep,nrhist,3)
    vthhist2.append([1.6,0.,0])
    pvthhist2.append(Data(vthhist2))
    pvthhist2[len(pvthhist2)-1].set_option_colonsep("title","'Observations'")
    pvthhist2[len(pvthhist2)-1].set_option_colonsep("with","steps lt 1 lw 2")
    pvthhist2[len(pvthhist2)-1].set_option_colonsep("using","1:2")

###############################################################
print "Start fitting!"
###############################################################

# build array of x values for fitting 

xvals=[]
for i in range(len(vhist)):
    xvals.append([vhist[i][1],valfhist[i][1],bhist[i][1],0.,axhist[i][1],azhist[i][1],0.1,iondata.countspec[0],iondata.name,iondata.mass,iondata.charge,effpath])

# build array of y and sig values for fitting

yvals=[]
sigvals=[]
for i in range(len(vhist)):
    yvals.append([dverr[i][1],vtherr[i][1]])
    sigvals.append([dverr[i][2],vtherr[i][2]])
yvals=array(yvals)
sigvals=array(sigvals)

# starting values for fitting parameters
tratio=1.9
beampos=0.1
vthperp=vthhist[len(vthhist)-2][1]
vthpara=vthperp/sqrt(tratio)
pratio=0.8

print "Starting values of parameters for fitting :"
print iondata.name
print "BeamPos = ",beampos
print "P-Ratio = ",pratio
print "vthpara = ",vthpara
print "vthperp = ",vthperp
print "(T-Ratio = ",tratio,")"
    
para=[]
para.append(beampos)
para.append(pratio)
para.append(vthpara)
para.append(vthperp)
para=array(para)

ipara=zeros([len(para)],int)
ipara+=1
covar=zeros([4,4])
alpha=zeros([4,4])

chisq=maxlifit(xvals,yvals,sigvals,para,ipara,covar,alpha,dutyfunc)


"""
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

gp2("set autoscale")
gp2("set ylabel '{/Symbol D}v/v_{Alf}'")
gp2("set xlabel '{/Symbol b} [rad]'")
#gp2("set grid back")
gp2("set format y '%.2f'")
gp2("set yrange[0:0.8]")
gp2("set xrange[0:1.6]")
#gp2.plot(pdvhist2[len(pdvhist2)-1],pdvhisttheo,pdvhist[len(pdvhist)-1],pdvhisttheovs)
gp2.plot(pdvhist[len(pdvhist)-1],pdvhisttheovs)
gp2("set term postscript color 20 lw 2 eps")
gp2.hardcopy("dvvirtobs_%s.ps"%(iondata.name),color="true",fontsize=20)

gp4("set autoscale")
gp4("set ylabel 'vth [km^{1}s^{-1}]'")
gp4("set xlabel '{/Symbol b} [rad]'")
#gp4("set grid back")
gp4("set format y '%.1f'")
gp4("set xrange[0:1.6]")
#gp4.plot(pvthhist2[len(pvthhist2)-1],pvthhisttheo,pvthhist[len(pvthhist)-1],pvthhisttheovs)
gp4.plot(pvthhist[len(pvthhist)-1],pvthhisttheovs)
gp4("set term postscript color 20 lw 2 eps")
gp4.hardcopy("vthvirtobs_%s.ps"%(iondata.name),color="true",fontsize=20)
"""




