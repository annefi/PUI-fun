from libacepy.swicsiondata import loadswicsiondata
from libacepy.swepamdata import swepamdata
from libacepy.mag import loadmagdata
from numpy import *
from Gnuplot import Gnuplot,Data
from libacepy.multiplot import multiplot
from libacepy.attitude import attdata,sync_attitude
from libacepy.vdetector import vdetector
from libacepy.funcs import twobimaxmag


ion="He2+"
ion2="C5+"
res=720.
year=2008
path="/data/wimmer/ace/"
#timeframe=array([[60.,90.]])


#for i in range(19):
for i in range(1):
    timeframe=array([[float(i)*20.+1.,float(i+1)*20.+1]])
    timeframe=array([[10.25,10.75]])
    hedata=loadswicsiondata(ion,res,year,timeframe,path)
    odata=loadswicsiondata(ion2,res,year,timeframe,path)
    hdata=swepamdata(64.,year,timeframe,path+"swepam/")
    hdata.sync_h(hedata)
    magdata=loadmagdata(1.,year,timeframe,path+"mag/")
    magdata.sync_mag(hedata)
    att=attdata(year,"/data/ivar/ace/")
    att.load()
    syncatt=sync_attitude(att,hedata)

    thetaarr=arccos(cos(magdata.phi)*cos(magdata.theta))
    valf=21.8*magdata.magb/sqrt(hdata.dens)

    hphi=arctan(hdata.vely/hdata.velx)
    htheta=arctan(hdata.velz/sqrt(hdata.velx**2+hdata.velz**2))

    vy=tan(syncatt.phi)*hdata.vel-hdata.vely
    vz=tan(syncatt.theta)*hdata.vel-hdata.velz
    dvc=sqrt(vy**2+vz**2)
    tmpmagphi=array(magdata.phi)
    tmpmagphi[tmpmagphi<0]=2*pi+tmpmagphi[tmpmagphi<0]
    tmpmagphi=tmpmagphi-pi
    vyb=tan(syncatt.phi)*(hdata.vel+valf)-(hdata.vely+valf*tan(tmpmagphi))
    vzb=tan(syncatt.theta)*(hdata.vel+valf)-(hdata.velz+valf*tan(magdata.theta))
    dvb=sqrt(vyb**2+vzb**2)

    vyb2=tan(syncatt.phi)*(hdata.vel+valf*0.5)-(hdata.vely+valf*0.5*tan(tmpmagphi))
    vzb2=tan(syncatt.theta)*(hdata.vel+valf*0.5)-(hdata.velz+valf*0.5*tan(magdata.theta))
    dvb2=sqrt(vyb2**2+vzb2**2)

    counts=sum(hedata.countspec[:,:,1],axis=1)

    #vspec=[]
    #for i in range(len(hedata.time)):
    #    vd=vdetector(func=twobimaxmag,para=[hdata.vel[i]+0.2*valf[i],0.,0.,20.,30.,30.,0.03,0.8,0.8*valf[i],tmpmagphi[i],magdata.theta[i]],aspphi=-syncatt.phi[i],asptheta=syncatt.theta[i])
        #vd=vdetector(func=twobimaxmag,para=[hdata.velx[i],hdata.vely[i],hdata.velz[i],20.,30.,30.,0.02,0.5,valf[i],tmpmagphi[i],magdata.theta[i]],aspphi=-syncatt.phi[i],asptheta=syncatt.theta[i])
    #    vspec.append(array(vd.vspec))

    mp=multiplot(4)
    mp.setgv(0)
    mp.setname("sp_%3.i_%3.i"%(int(timeframe[0,0]),int(timeframe[-1,1])))
    mp.setxrange(timeframe[0,0],timeframe[-1,1])
    mp.panel[0].adddata(Data(magdata.time,thetaarr,with_="l lt 1"))
    mp.panel[0].adddata(Data(array([[timeframe[0,0],pi/2.],[timeframe[-1,1],pi/2.]]),with_="l lt 0"))
    mp.panel[0].setyrange(0,pi)
    mp.panel[0].setytics("('0' 0,'' %f 1,'' %f 1,'' %f 1,'{/Symbol p}/4' %f,'' %f 1,'' %f 1,'' %f 1,'{/Symbol p}/2' %f,'' %f 1,'' %f 1,'' %f 1,'{/Symbol p}3/4' %f,'' %f 1,'' %f 1,'' %f 1,'{/Symbol p}' %f)"%(pi/16.,pi/8.,pi*3/16.,pi/4.,pi*5./16.,pi*6/16.,pi*7/16.,pi/2.,pi*9./16.,pi*10./16.,pi*11./16.,pi*3./4.,pi*13./16.,pi*14./16.,pi*15./16.,pi))
    mp.panel[1].adddata(Data(magdata.time,magdata.phi,with_="l lt 1"))
    mp.panel[1].adddata(Data(magdata.time,magdata.theta,with_="l lt 3"))
    mp.panel[1].adddata(Data(array([[timeframe[0,0],pi/2.],[timeframe[-1,1],pi/2.]]),with_="l lt 0"))
    mp.panel[1].setyrange(-pi,pi)
    mp.panel[1].setytics("('0' 0,'' %f 1,'' %f 1,'' %f 1,'{/Symbol p}/4' %f,'' %f 1,'' %f 1,'' %f 1,'{/Symbol p}/2' %f,'' %f 1,'' %f 1,'' %f 1,'{/Symbol p}3/4' %f,'' %f 1,'' %f 1,'' %f 1,'{/Symbol p}' %f,'' %f 1,'' %f 1,'' %f 1,'-{/Symbol p}/4' %f,'' %f 1,'' %f 1,'' %f 1,'-{/Symbol p}/2' %f,'' %f 1,'' %f 1,'' %f 1,'-{/Symbol p}3/4' %f,'' %f 1,'' %f 1,'' %f 1,'-{/Symbol p}' %f)"%(pi/16.,pi/8.,pi*3/16.,pi/4.,pi*5./16.,pi*6/16.,pi*7/16.,pi/2.,pi*9./16.,pi*10./16.,pi*11./16.,pi*3./4.,pi*13./16.,pi*14./16.,pi*15./16.,pi,-pi/16.,-pi/8.,-pi*3/16.,-pi/4.,-pi*5./16.,-pi*6/16.,-pi*7/16.,-pi/2.,-pi*9./16.,-pi*10./16.,-pi*11./16.,-pi*3./4.,-pi*13./16.,-pi*14./16.,-pi*15./16.,-pi))
    mp.panel[2].adddata(Data(hedata.time,hedata.vel-hdata.vel,with_="l lt 3"))
    mp.panel[2].adddata(Data(hedata.time,valf,with_="l lt 4"))
    mp.panel[2].adddata(Data(array([[timeframe[0,0],0.],[timeframe[-1,1],0.]]),with_="l lt 0"))
    mp.panel[2].setyrange(-100.,100.)
    mp.panel[3].adddata(Data(hedata.time,hedata.vel,with_="l lt 4"))
    mp.panel[3].setyrange(250.,750.)
    mp.plot()




gp=Gnuplot()
gp("set style data lines")
gp("set xrange[400:700]")

gp2=Gnuplot()
#gp2.plot([syncatt.time,syncatt.phi],[syncatt.time,syncatt.theta],[hdata.time,hphi],[hdata.time,htheta])
gp2.plot(Data(hedata.time,syncatt.phi),Data(hedata.time,syncatt.theta),Data(hedata.time,hphi),Data(hedata.time,htheta))

gp3=Gnuplot()
gp3.plot(Data(hedata.time,counts))

gp4=Gnuplot()
gp4.plot(Data(hedata.time,dvc),Data(hedata.time,dvb),Data(hedata.time,dvb2))
