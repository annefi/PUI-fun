from libacepy.swicsiondata import loadswicsiondata
from libacepy.mag import magdata
from libacepy.swepamdata import swepamdata 
from libacepy.swicsdcrtcr import swicsdcrtcr
from Gnuplot import Gnuplot,Data
from numpy import amax,sqrt,arccos,cos,pi,where,isinf,isnan,std,mean,sum,array,histogram,linspace,zeros,append,loadtxt
from scipy.stats import skew,kurtosis


class vspec:
    
    def __init__(self,year,timeframe):
        self.year=year
        self.timeframe=timeframe
        self.hedata=loadswicsiondata("He2+",720.,self.year,self.timeframe,"/data/etph/ace/")
        self.odata=loadswicsiondata("O6+",720.,self.year,self.timeframe,"/data/etph/ace/")
        self.hdata=swicsdcrtcr("H1+",self.year,self.timeframe,"/data/etph/ace/pui/12mdata/")
        self.swedata=swepamdata(64.,self.year,self.timeframe,"/data/etph/ace/swepam/")
        self.swedata.sync_h(self.hedata)
        self.mag=magdata(1.,self.year,self.timeframe,"/data/etph/ace/mag/")
        self.mag.sync_mag(self.hedata)
        self.theta=arccos(cos(self.mag.phi)*cos(self.mag.theta))
        self.valf=21.8/sqrt(self.swedata.dens)*(self.mag.magb)
        self.valf[isinf(self.valf)]=-1.
        self.valf[isnan(self.valf)]=-2.
        self.effh=zeros([58])
        self.effhe=zeros([58])
        self.effo=zeros([58])
        self.gp=Gnuplot()
        self.gp("set xr [-2:3]")
        self.gp("set yr [0:1]")
        self.gp("set xlabel '(v-v_{sw})/C_{A}'")
        self.stdhe=[]
        self.stdo=[]
        self.stdh=[]
        self.skewhe=[]
        self.skewo=[]
        self.skewh=[]
        self.kurthe=[]
        self.kurto=[]
        self.kurth=[]
        self.meanvhe=[]
        self.meanvo=[]
        self.meanvh=[]
        self.maxvhe=[]
        self.maxvo=[]
        self.maxvh=[]
        self.time=[]
        self.years=[]
        self.valfs=[]
        self.magb=[]
        self.thetas=[]
        self.sigtheta=[]
        self.vsw=[]
        self.dsw=[]
        self.tsw=[]
        self.load_eff()

    def load_eff(self):
        effh=loadtxt(open("/data/etph/ace/efficencies/H1+.eff","r"))
        effhe=loadtxt(open("/data/etph/ace/efficencies/He2+.eff","r"))
        effo=loadtxt(open("/data/etph/ace/efficencies/O6+.eff","r"))
        self.effh=effh[:,1]
        self.effhe=effhe[:,1]
        self.effo=effo[:,1]
        
    def moments(self,thetalist=[[0.,pi/18.],[pi-pi/18.,pi]]):
        thetamask=(self.theta>=thetalist[0][0])*(self.theta<=thetalist[0][1])
        if len(thetalist)>1:
            for val in thetalist[1:]:
                thetamask+=(self.theta>=val[0])*(self.theta<=val[1])
        for step in where(thetamask)[0]:
            if self.valf[step]>0.:
                self.years.append(self.hedata.year)
                self.time.append(self.hedata.time[step])
                self.valfs.append(self.valf[step])
                self.magb.append(self.mag.magb[step])
                self.thetas.append(self.mag.THETA[step])
                self.sigtheta.append(self.mag.sigTHETA[step])
                self.vsw.append(self.swedata.vel[step])
                self.dsw.append(self.swedata.dens[step])
                self.tsw.append(self.swedata.temp[step])
                # Protons
                il=where(self.hdata.time==self.hedata.time[step])[0]
                if il.shape[0]>0 and amax(self.hdata.tcrspec[il[0],:]+self.hdata.dcrspec[il[0],:])>0.:
                    tmpspec=zeros([self.hdata.velspec.shape[0],2])
                    tmpspec[:,0]=self.hdata.velspec
                    tmpspec[:,1]=1.*self.hdata.tcrspec[il[0]]+1.*self.hdata.dcrspec[il[0]]
                    tmpspec[:,1]=tmpspec[:,1]/(tmpspec[:,0]*0.03)/self.effh/tmpspec[:,0]
                    il2=where(tmpspec[:,1]==amax(tmpspec[:,1]))[0]
                    if (il2[0]>0 and il2[0]<tmpspec[:,1].shape[0]-1):
                        maxvh=sum(tmpspec[[il2[0]-1,il2[0],il2[0]+1],0]*tmpspec[[il2[0]-1,il2[0],il2[0]+1],1])/sum(tmpspec[[il2[0]-1,il2[0],il2[0]+1],1])
                    else:
                        maxvh=tmpspec[il2[0],0]
                    meanvh=sum(tmpspec[:,0]*tmpspec[:,1])/sum(tmpspec[:,1])
                    if maxvh>390.:
                        tmphvel=(tmpspec[:,0]-maxvh)/self.valf[step]
                        tmphcts=(tmpspec[:,1])/sum(tmpspec[:,1])
                        maskh=(tmphvel>=-3.)*(tmphvel<=3.)
                        stdh=sqrt(sum((tmphvel[maskh]**2)*tmphcts[maskh]))
                        skewh=(sum((tmphvel[maskh]**3)*tmphcts[maskh]))/stdh**3.
                        kurth=(sum((tmphvel[maskh]**4)*tmphcts[maskh]))/stdh**4.
                        self.stdh.append(stdh)
                        self.skewh.append(skewh)
                        self.kurth.append(kurth)
                        self.meanvh.append(meanvh)
                        self.maxvh.append(maxvh)
                    else:
                        self.stdh.append(-999.)
                        self.skewh.append(-999.)
                        self.kurth.append(-999.)
                        self.meanvh.append(-999.)
                        self.maxvh.append(-999.)
                else:
                    self.stdh.append(-999.)
                    self.skewh.append(-999.)
                    self.kurth.append(-999.)
                    self.meanvh.append(-999.)
                    self.maxvh.append(-999.)

                # Alphas
                if (where(self.hedata.countspec[step,:,1]>0.)[0].shape[0]>=3):
                    tmpspec=1.*self.hedata.countspec[step]
                    tmpspec[:,1]=tmpspec[:,1]/(tmpspec[:,0]*0.03)/self.effhe/tmpspec[:,0]
                    il2=where(tmpspec[:,1]==amax(tmpspec[:,1]))[0]
                    if (il2[0]>0 and il2[0]<tmpspec[:,1].shape[0]-1):
                        maxvhe=sum(tmpspec[[il2[0]-1,il2[0],il2[0]+1],0]*tmpspec[[il2[0]-1,il2[0],il2[0]+1],1])/sum(tmpspec[[il2[0]-1,il2[0],il2[0]+1],1])
                    else:
                        maxvhe=tmpspec[il2[0],0]
                    meanvhe=sum(tmpspec[:,0]*tmpspec[:,1])/sum(tmpspec[:,1])
                    tmphevel=(tmpspec[:,0]-maxvhe)/self.valf[step]
                    tmphects=(tmpspec[:,1])/sum(tmpspec[:,1])
                    maskhe=(tmphevel>=-3.)*(tmphevel<=3.)
                    stdhe=sqrt(sum((tmphevel[maskhe]**2)*tmphects[maskhe]))
                    skewhe=(sum((tmphevel[maskhe]**3)*tmphects[maskhe]))/stdhe**3.
                    kurthe=(sum((tmphevel[maskhe]**4)*tmphects[maskhe]))/stdhe**4.
                    self.stdhe.append(stdhe)
                    self.skewhe.append(skewhe)
                    self.kurthe.append(kurthe)
                    self.meanvhe.append(meanvhe)
                    self.maxvhe.append(maxvhe)
                else:
                    self.stdhe.append(-999.)
                    self.skewhe.append(-999.)
                    self.kurthe.append(-999.)
                    self.meanvhe.append(-999.)
                    self.maxvhe.append(-999.)

                # O6+
                if (where(self.odata.countspec[step,:,1]>0.)[0].shape[0]>=3):
                    tmpspec=1.*self.odata.countspec[step]
                    tmpspec[:,1]=tmpspec[:,1]/(tmpspec[:,0]*0.03)/self.effo/tmpspec[:,0]
                    il2=where(tmpspec[:,1]==amax(tmpspec[:,1]))[0]
                    if (il2[0]>0 and il2[0]<tmpspec[:,1].shape[0]-1):
                        maxvo=sum(tmpspec[[il2[0]-1,il2[0],il2[0]+1],0]*tmpspec[[il2[0]-1,il2[0],il2[0]+1],1])/sum(tmpspec[[il2[0]-1,il2[0],il2[0]+1],1])
                    else:
                        maxvo=tmpspec[il2[0],0]
                    meanvo=sum(tmpspec[:,0]*tmpspec[:,1])/sum(tmpspec[:,1])
                    tmpovel=(tmpspec[:,0]-maxvo)/self.valf[step]
                    tmpocts=(tmpspec[:,1])/sum(tmpspec[:,1])
                    masko=(tmpovel>=-3.)*(tmpovel<=3.)
                    stdo=sqrt(sum((tmpovel[masko]**2)*tmpocts[masko]))
                    skewo=(sum((tmpovel[masko]**3)*tmpocts[masko]))/stdo**3.
                    kurto=(sum((tmpovel[masko]**4)*tmpocts[masko]))/stdo**4.
                    self.stdo.append(stdo)
                    self.skewo.append(skewo)
                    self.kurto.append(kurto)
                    self.meanvo.append(meanvo)
                    self.maxvo.append(maxvo)
                else:
                    self.stdo.append(-999.)
                    self.skewo.append(-999.)
                    self.kurto.append(-999.)
                    self.meanvo.append(-999.)
                    self.maxvo.append(-999.)

            
        self.stdhe=array(self.stdhe)
        self.stdh=array(self.stdh)
        self.stdo=array(self.stdo)
        self.skewhe=array(self.skewhe)
        self.skewh=array(self.skewh)
        self.skewo=array(self.skewo)
        self.kurthe=array(self.kurthe)
        self.kurth=array(self.kurth)
        self.kurto=array(self.kurto)
        self.meanvhe=array(self.meanvhe)
        self.meanvh=array(self.meanvh)
        self.meanvo=array(self.meanvo)
        self.maxvhe=array(self.maxvhe)
        self.maxvh=array(self.maxvh)
        self.maxvo=array(self.maxvo)
        self.time=array(self.time)
        self.years=array(self.years)
        self.valfs=array(self.valfs)
        self.magb=array(self.magb)
        self.thetas=array(self.thetas)
        self.sigtheta=array(self.sigtheta)
        self.vsw=array(self.vsw)
        self.dsw=array(self.dsw)
        self.tsw=array(self.tsw)
        return


    def plot_vdist(self,thetalist=[[0.,pi/18.],[pi-pi/18.,pi]]):
        thetamask=(self.theta>=thetalist[0][0])*(self.theta<=thetalist[0][1])
        if len(thetalist)>1:
            for val in thetalist[1:]:
                thetamask+=(self.theta>=val[0])*(self.theta<=val[1])
        print where(thetamask)
        for i in where(thetamask)[0]:
            self.plot_step(i)

    def plot_step(self,step):
        if self.valf[step]>0.:
            self.gp("unset label")
            self.gp("set label 'v_{sw}=%f' at -1.5,0.95"%(self.swedata.vel[step])) 
            self.gp("set label 'C_{A}=%f' at -1.5,0.90"%(self.valf[step])) 
            self.gp("set label '{/Symbol= Q}=%f' at -1.5,0.85"%(self.theta[step]/pi*180.)) 
            self.gp("set label '{/Symbol= dQ}=%f' at -1.5,0.8"%(self.mag.sigTHETA[step]/pi*180.)) 
            self.gp("set title '%.4i DoY %f'"%(self.year,self.hedata.time[step]))
            if amax(self.hedata.countspec[step,:,1])>0.:
                self.gp.plot(Data((self.hedata.countspec[step,:,0]-self.swedata.vel[step])/self.valf[step],self.hedata.countspec[step,:,1]/amax(self.hedata.countspec[step,:,1]),with_="lp lt 3 lw 3",title="He^{2+}"))
            if amax(self.odata.countspec[step,:,1])>0.:
                self.gp.replot(Data((self.odata.countspec[step,:,0]-self.swedata.vel[step])/self.valf[step],self.odata.countspec[step,:,1]/amax(self.odata.countspec[step,:,1]),with_="lp lt 4 lw 3",title="O^{6+}"))
            il=where(self.hdata.time==self.hedata.time[step])[0]
            if il.shape[0]>0 and amax(self.hdata.tcrspec[il[0],:]+self.hdata.dcrspec[il[0],:])>0.:
                self.gp.replot(Data((self.hdata.velspec-self.swedata.vel[step])/self.valf[step],(self.hdata.tcrspec[il[0],:]+self.hdata.dcrspec[il[0],:])/amax(self.hdata.tcrspec[il[0],:]+self.hdata.dcrspec[il[0],:]),with_="lp lt 1 lw 3",title="H^{1+}"))

            self.gp.hardcopy("vdistperp_%.4i_%.3i.%.6i.ps"%(self.year,int(self.hedata.time[step]),int((self.hedata.time[step]%1)*1e6)),color=True)
            self.gp.sync()



def write_vs(outf,vs):
    for i in range(vs.time.shape[0]):
        outf.write("%.4i\t%f\t%.4f\t%.4f\t%.4f\t%.2f\t%.2f\t%.4e\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\n"%(vs.years[i],vs.time[i],vs.thetas[i],vs.sigtheta[i],vs.magb[i],vs.vsw[i],vs.dsw[i],vs.tsw[i],vs.valfs[i],vs.maxvh[i],vs.meanvh[i],vs.stdh[i],vs.skewh[i],vs.kurth[i],vs.maxvhe[i],vs.meanvhe[i],vs.stdhe[i],vs.skewhe[i],vs.kurthe[i],vs.maxvo[i],vs.meanvo[i],vs.stdo[i],vs.skewo[i],vs.kurto[i]))
        outf.flush()
#vs=vspec(2007,[[5.,6.]])
#print "para"
#vs.moments()
#print "perp"
#vs2=vspec(2007,[[5.,6.]])
#vs2.moments(thetalist=[[pi/2.-pi/18.,pi/2.+pi/18.]])
dim=60
skewhehist=zeros([2*dim])
skewhhist=zeros([2*dim])
skewohist=zeros([2*dim])
kurthehist=zeros([dim])
kurthhist=zeros([dim])
kurtohist=zeros([dim])
stdhehist=zeros([dim])
stdhhist=zeros([dim])
stdohist=zeros([dim])
skewhehist2=zeros([2*dim])
skewhhist2=zeros([2*dim])
skewohist2=zeros([2*dim])
kurthehist2=zeros([dim])
kurthhist2=zeros([dim])
kurtohist2=zeros([dim])
stdhehist2=zeros([dim])
stdhhist2=zeros([dim])
stdohist2=zeros([dim])
skewx=linspace(-6.,6.,121)
kurtx=linspace(0.,6.,61)
stdx=linspace(0.,6.,61)
gpskew=Gnuplot()
gpkurt=Gnuplot()
gpstd=Gnuplot()
gpskew2=Gnuplot()
gpkurt2=Gnuplot()
gpstd2=Gnuplot()
gpskew("set title 'skew para 3'")
gpkurt("set title 'kurt para 3'")
gpstd("set title 'std para 3'")
gpskew2("set title 'skew perp 3'")
gpkurt2("set title 'kurt perp 3'")
gpstd2("set title 'std perp 3'")
gpskew.plot(Data(skewx[:-1]+0.005,skewhhist,with_="histeps lt 1"),Data(skewx[:-1]+0.005,skewhehist,with_="histeps lt 3"),Data(skewx[:-1]+0.005,skewohist,with_="histeps lt 4"))
gpskew2.plot(Data(skewx[:-1]+0.005,skewhhist2,with_="histeps lt 1"),Data(skewx[:-1]+0.005,skewhehist2,with_="histeps lt 3"),Data(skewx[:-1]+0.005,skewohist2,with_="histeps lt 4"))
gpkurt.plot(Data(kurtx[:-1]+0.005,kurthhist,with_="histeps lt 1"),Data(kurtx[:-1]+0.005,kurthehist,with_="histeps lt 3"),Data(kurtx[:-1]+0.005,kurtohist,with_="histeps lt 4"))
gpkurt2.plot(Data(kurtx[:-1]+0.005,kurthhist2,with_="histeps lt 1"),Data(kurtx[:-1]+0.005,kurthehist2,with_="histeps lt 3"),Data(kurtx[:-1]+0.005,kurtohist2,with_="histeps lt 4"))
gpstd.plot(Data(stdx[:-1]+0.005,stdhhist,with_="histeps lt 1"),Data(stdx[:-1]+0.005,stdhehist,with_="histeps lt 3"),Data(stdx[:-1]+0.005,stdohist,with_="histeps lt 4"))
gpstd2.plot(Data(stdx[:-1]+0.005,stdhhist2,with_="histeps lt 1"),Data(stdx[:-1]+0.005,stdhehist2,with_="histeps lt 3"),Data(stdx[:-1]+0.005,stdohist2,with_="histeps lt 4"))
skewhe=zeros([0])
skewh=zeros([0])
skewo=zeros([0])
kurthe=zeros([0])
kurto=zeros([0])
kurth=zeros([0])
stdhe=zeros([0])
stdo=zeros([0])
stdh=zeros([0])
skewhe2=zeros([0])
skewh2=zeros([0])
skewo2=zeros([0])
kurthe2=zeros([0])
kurto2=zeros([0])
kurth2=zeros([0])
stdhe2=zeros([0])
stdo2=zeros([0])
stdh2=zeros([0])
meanvhe=zeros([0])
meanvh=zeros([0])
meanvo=zeros([0])
meanvhe2=zeros([0])
meanvh2=zeros([0])
meanvo2=zeros([0])
maxvhe=zeros([0])
maxvh=zeros([0])
maxvo=zeros([0])
maxvhe2=zeros([0])
maxvh2=zeros([0])
maxvo2=zeros([0])
valf=zeros([0])
valf2=zeros([0])
time=zeros([0])
time2=zeros([0])
years=zeros([0])
years2=zeros([0])
paraout=open("momentsparacoreff2.dat","w")
perpout=open("momentsperpcoreff2.dat","w")
paraout.write("year\tdoy\t\ttheta\tsigth\tB\tvsw\tdsw\ttsw\t\tvalf\tmaxvh\tmeanvh\tstdh\tskewh\tkurth\tmaxvhe\tmeanvhe\tstdhe\tskewhe\tkurthe\tmaxvo\tmeanvo\tstdo\tskewo\tkurto\n")
perpout.write("year\tdoy\t\ttheta\tsigth\tB\tvsw\tdsw\ttsw\t\tvalf\tmaxvh\tmeanvh\tstdh\tskewh\tkurth\tmaxvhe\tmeanvhe\tstdhe\tskewhe\tkurthe\tmaxvo\tmeanvo\tstdo\tskewo\tkurto\n")

for year in range(2001,2011):
    for doy in range(1,366):
        try:
            vs=vspec(year,[[doy,doy+1]])
            vs.moments()
            vs.gp.close()
            write_vs(paraout,vs)
            vs2=vspec(year,[[doy,doy+1]])
            vs2.moments(thetalist=[[pi/2.-pi/18.,pi/2.+pi/18.]])
            vs2.gp.close()
            write_vs(perpout,vs2)
            #print vs.mag.THETA-vs.theta
            #raw_input()
            y,x=histogram(vs.skewhe,skewx)
            skewhehist+=y
            y,x=histogram(vs.skewh,skewx)
            skewhhist+=y
            y,x=histogram(vs.skewo,skewx)
            skewohist+=y
            y,x=histogram(vs2.skewhe,skewx)
            skewhehist2+=y
            y,x=histogram(vs2.skewh,skewx)
            skewhhist2+=y
            y,x=histogram(vs2.skewo,skewx)
            skewohist2+=y
            y,x=histogram(vs.kurthe,kurtx)
            kurthehist+=y
            y,x=histogram(vs.kurth,kurtx)
            kurthhist+=y
            y,x=histogram(vs.kurto,kurtx)
            kurtohist+=y
            y,x=histogram(vs2.kurthe,kurtx)
            kurthehist2+=y
            y,x=histogram(vs2.kurth,kurtx)
            kurthhist2+=y
            y,x=histogram(vs2.kurto,kurtx)
            kurtohist2+=y
            y,x=histogram(vs.stdhe,stdx)
            stdhehist+=y
            y,x=histogram(vs.stdh,stdx)
            stdhhist+=y
            y,x=histogram(vs.stdo,stdx)
            stdohist+=y
            y,x=histogram(vs2.stdhe,stdx)
            stdhehist2+=y
            y,x=histogram(vs2.stdh,stdx)
            stdhhist2+=y
            y,x=histogram(vs2.stdo,stdx)
            stdohist2+=y
            stdhe=append(stdhe,vs.stdhe)
            stdhe2=append(stdhe2,vs2.stdhe)
            stdh=append(stdh,vs.stdh)
            stdh2=append(stdh2,vs2.stdh)
            stdo=append(stdo,vs.stdo)
            stdo2=append(stdo2,vs2.stdo)
            skewhe=append(skewhe,vs.skewhe)
            skewhe2=append(skewhe2,vs2.skewhe)
            skewh=append(skewh,vs.skewh)
            skewh2=append(skewh2,vs2.skewh)
            skewo=append(skewo,vs.skewo)
            skewo2=append(skewo2,vs2.skewo)
            kurthe=append(kurthe,vs.kurthe)
            kurthe2=append(kurthe2,vs2.kurthe)
            kurth=append(kurth,vs.kurth)
            kurth2=append(kurth2,vs2.kurth)
            kurto=append(kurto,vs.kurto)
            kurto2=append(kurto2,vs2.kurto)
            meanvhe=append(meanvhe,vs.meanvhe)
            meanvhe2=append(meanvhe2,vs2.meanvhe)
            meanvh=append(meanvh,vs.meanvh)
            meanvh2=append(meanvh2,vs2.meanvh)
            meanvo=append(meanvo,vs.meanvo)
            meanvo2=append(meanvo2,vs2.meanvo)
            maxvhe=append(maxvhe,vs.maxvhe)
            maxvhe2=append(maxvhe2,vs2.maxvhe)
            maxvh=append(maxvh,vs.maxvh)
            maxvh2=append(maxvh2,vs2.maxvh)
            maxvo=append(maxvo,vs.maxvo)
            maxvo2=append(maxvo2,vs2.maxvo)
            valf=append(valf,vs.valfs)
            valf2=append(valf2,vs2.valfs)
            time=append(time,vs.time)
            time2=append(time2,vs2.time)
            years=append(years,vs.years)
            years2=append(years2,vs2.years)

            if (1):
                gpskew.plot(Data(skewx[:-1]+0.005,skewhhist,with_="histeps lt 1"),Data(skewx[:-1]+0.005,skewhehist,with_="histeps lt 3"),Data(skewx[:-1]+0.005,skewohist,with_="histeps lt 4"))
                gpskew2.plot(Data(skewx[:-1]+0.005,skewhhist2,with_="histeps lt 1"),Data(skewx[:-1]+0.005,skewhehist2,with_="histeps lt 3"),Data(skewx[:-1]+0.005,skewohist2,with_="histeps lt 4"))
                gpkurt.plot(Data(kurtx[:-1]+0.005,kurthhist,with_="histeps lt 1"),Data(kurtx[:-1]+0.005,kurthehist,with_="histeps lt 3"),Data(kurtx[:-1]+0.005,kurtohist,with_="histeps lt 4"))
                gpkurt2.plot(Data(kurtx[:-1]+0.005,kurthhist2,with_="histeps lt 1"),Data(kurtx[:-1]+0.005,kurthehist2,with_="histeps lt 3"),Data(kurtx[:-1]+0.005,kurtohist2,with_="histeps lt 4"))
                gpstd.plot(Data(stdx[:-1]+0.005,stdhhist,with_="histeps lt 1"),Data(stdx[:-1]+0.005,stdhehist,with_="histeps lt 3"),Data(stdx[:-1]+0.005,stdohist,with_="histeps lt 4"))
                gpstd2.plot(Data(stdx[:-1]+0.005,stdhhist2,with_="histeps lt 1"),Data(stdx[:-1]+0.005,stdhehist2,with_="histeps lt 3"),Data(stdx[:-1]+0.005,stdohist2,with_="histeps lt 4"))
        except:
            print year,doy," broken!"
            continue
