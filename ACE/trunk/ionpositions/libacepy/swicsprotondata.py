from libacepy.ancil import int2str
from Gnuplot import Gnuplot,Data
from math import sqrt

class swicsprotondata:
    def __init__(self,ionname,timeframe,path): 
        self.name=ionname                          #  str -> name of ion  
        self.res=0.                                #  timeresolution of data in s
        self.time=[]                               #  vector [time]
        self.vel=[]                                #  vector [vel]
        self.velerr=[]                             #  vector [velerr]
        self.flux=[]                               #  vector [flux,cr-error,eff-error]
        self.dens=[]                               #  vector [dens,cr-error,eff-error]
        self.temp=[]                               #  vector [temp,cr-error,eff-error]
        self.vth=[]                                #  vector [thermalvel]
        self.densspec=[]                           #  vector of [[step][vel,diffdens,cr-error,+eff-error,-eff-error]]
        self.fluxspec=[]                           #  vector of [[step][vel,diffflux,cr-error,eff-error,-eff-error]]
        self.countspec=[]                          #  vector of [[step][vel,counts,cr-error,]]
        self.path=path                             #  str -> path of data
        self.mass=0.                               #  float -> ion mass
        self.charge=0.                             #  float -> ion charge
        self.timeframe=timeframe                   #  vector -> [[start,stop]]
        self.tailbulk=[]                           #  vector -> [tailbulk,cr-error]
        self.vel2=[]
        self.vth2=[]
        self.vth3=[]
        self.temp2=[]
        self.dens2=[]
        self.crvel=[]
        self.crvth=[]
        self.crtemp=[]
        self.crdens=[]
        self.bulkdens=[]
        self.skewness=[]
        self.kortosis=[]

    def load(self):
        Nres=0.
        for tf in self.timeframe:
            for day in range(int(tf[0]),int(tf[1])+1):
                doystr=int2str(day)
                ergdaypath=self.path+doystr+"/"
                listin=open(ergdaypath+"list.in")
                s=listin.readline()
                for s in listin:
                    k=s.split()
#                        time=(float(k[0][21:24])+float(k[0][25:27])/24.+float(k[0][28:30])/(24.*60.)+float(k[0][31:33])/(24.*60.*60.)+(float(k[0][39:42])+float(k[0][43:45])/24.+float(k[0][46:48])/(24.*60.))+float(k[0][49:51])/(24.*60.*60.))/2.
                    time=(float(k[0][21:24])+float(k[0][25:27])/24.+float(k[0][28:30])/(24.*60.)+float(k[0][31:33])/(24.*60.*60.))
                    if (time>=tf[0] and time<=tf[1]):
                        fluxname=ergdaypath+"flux_"+k[0]
                        resname=ergdaypath+"res_"+k[0]
                        self.res+=12.
                        Nres+=1.
                        self.time.append(time)
                        #print fluxname
                        resin=open(resname)
                        s=resin.readline()
                        k=s.split()
                        while (k[0]!=self.name):
                            s=resin.readline()
                            k=s.split()
                        for l in range(1,13):
                            try:
                                float(k[l])
                            except:
                                k[l]="0."
                        self.vel.append(float(k[1]))
                        self.velerr.append(float(k[2]))
                        self.dens.append([float(k[10]),float(k[11]),float(k[12])])
                        self.flux.append([float(k[7]),float(k[8]),float(k[9])])
                        self.temp.append([float(k[4]),float(k[5]),float(k[6])])
                        resin.close()
                        fluxin=open(fluxname)
                        k=["**"]
                        while (k[0]!=self.name):
                            s=fluxin.readline()
                            k=s.split()
                        s=fluxin.readline()
                        k=s.split()
                        if (self.mass==0.):
                            self.mass=float(k[2])
                        s=fluxin.readline()
                        k=s.split()
                        if (self.charge==0.):
                            self.charge=float(k[2])
                        densspec=[]
                        fluxspec=[]
                        countspec=[]
                        s=fluxin.readline()
                        for step in range(58):
                            s=fluxin.readline()
                            k=s.split()
                            for l in range(0,11):
                                try:
                                    float(k[l])
                                except:
                                    k[l]="0."
                            densspec.append([float(k[0]),float(k[7]),float(k[8]),float(k[9]),float(k[10])])                    
                            fluxspec.append([float(k[0]),float(k[3]),float(k[4]),float(k[5]),float(k[6])])                    
                            countspec.append([float(k[0]),float(k[1]),float(k[2])])                    
                        self.densspec.append(densspec)
                        self.fluxspec.append(fluxspec)
                        self.countspec.append(countspec)
                        resin.close()
                        fluxin.close()
        if (Nres>0.):
            self.res=float(int(self.res/Nres+0.5))*720.
        self.calc_vth()
        self.calc_higher_moments()
        self.recalc_moments()
        self.calc_crmoments()
        print self.name+" loaded"

    def calc_vth(self):
        if (1):
        #if (self.name=="He2+"):
            kb = 1.38065e-23
            u = 1.660538e-27
            for i in range(len(self.time)):
                self.vth.append(sqrt((self.temp[i][0]*kb)/(self.mass*u))/1000.)
        else:
            tmpdata=swicsiondata("He2+",self.timeframe,self.path)
            tmpdata.load()
            for i in tmpdata.vth:
                self.vth.append(i)
            self.vel=[]
            for v in tmpdata.vel:
                self.vel.append(v)
                
    def calc_suprathermal(self):
        self.suprath=[]
        self.suprath2=[]
        for i in range(len(self.dens)):
            spdens=0.
            sperr=0.
            spdens2=0.
            sperr2=0.
            #if (self.vel[i]>0.):
            #    print "low boundary = ",(self.vel[i]+3*self.vth[i])/self.vel[i]
            for step in range(len(self.densspec[i])):
                if (step>0 and step<len(self.densspec[i])-1):
                    lrange=(self.densspec[i][step][0]-self.densspec[i][step+1][0])/2.
                    rrange=(self.densspec[i][step-1][0]-self.densspec[i][step][0])/2.
                elif (step==0):
                    lrange=(self.densspec[i][step][0]-self.densspec[i][step+1][0])/2.
                    rrange=lrange
                elif (step==len(self.densspec[i])-1):
                    lrange=(self.densspec[i][step-1][0]-self.densspec[i][step][0])/2.
                    rrange=lrange
                else:
                    lrange=0.
                    rrange=0.
                if (self.densspec[i][step][0]+rrange>(self.vel[i]+3*self.vth[i]) and self.densspec[i][step][0]-lrange<self.vel[i]*2.3):
                    # right side integration
                    if (self.densspec[i][step][0]+rrange>self.vel[i]*2.3):
                        rv=self.vel[i]*2.3
                    elif (self.densspec[i][step][0]+rrange>(self.vel[i]+3*self.vth[i])):
                        rv=self.densspec[i][step][0]+rrange
                    else:
                        rv=(self.vel[i]+3*self.vth[i])
                    if (self.densspec[i][step][0]-lrange<(self.vel[i]+3*self.vth[i])):
                        lv=(self.vel[i]+3*self.vth[i])
                    elif (self.densspec[i][step][0]-lrange<(self.vel[i]*2.3)):
                        lv=self.densspec[i][step][0]-lrange
                    else:
                        lv=(self.vel[i]*2.3)
                    dv=rv-lv
                    spdens+=dv*1000.*self.densspec[i][step][1]
                    sperr+=(dv*1000.*self.densspec[i][step][2])**2
                #    print "integrating from ",lv/self.vel[i]," to ",rv/self.vel[i]
                if (self.densspec[i][step][0]>=2.3*self.vel[i]):
                    if (step==0):
                        spdens2+=(self.densspec[i][step][0]-self.densspec[i][step+1][0])*1000.*self.densspec[i][step][1]
                        sperr2+=((self.densspec[i][step][0]-self.densspec[i][step+1][0])*1000.*self.densspec[i][step][2])**2
                    elif (step==len(self.densspec[i])-1):
                        spdens2+=(self.densspec[i][step-1][0]-self.densspec[i][step][0])*1000.*self.densspec[i][step][1]
                        sperr2+=((self.densspec[i][step-1][0]-self.densspec[i][step][0])*1000.*self.densspec[i][step][2])**2
                    else:
                        spdens2+=(self.densspec[i][step-1][0]-self.densspec[i][step+1][0])*500.*self.densspec[i][step][1]
                        sperr2+=((self.densspec[i][step-1][0]-self.densspec[i][step+1][0])*500.*self.densspec[i][step][2])**2
            if (self.dens[i][0]!=0.):
                self.suprath.append([spdens/self.dens[i][0],(1/self.dens[i][0])*sqrt(sperr)+(spdens/self.dens[i][0]**2)*self.dens[i][1]])
                self.suprath2.append([spdens2/self.dens[i][0],(1/self.dens[i][0])*sqrt(sperr2)+(spdens2/self.dens[i][0]**2)*self.dens[i][1]])
            else:
                self.suprath.append([0.,0.])
                self.suprath2.append([0.,0.])

    def calc_densvelocity(self,velocity):
        self.densvelocity=[]
        for i in range(len(self.dens)):
            veldens=0.
            velerr=0.
            for step in range(len(self.densspec[i])):
                if (self.densspec[i][step][0]>=velocity):
                    if (step==0):
                        veldens+=(self.densspec[i][step][0]-self.densspec[i][step+1][0])*1000.*self.densspec[i][step][1]
                        velerr+=((self.densspec[i][step][0]-self.densspec[i][step+1][0])*1000.*self.densspec[i][step][2])**2
                    elif (step==len(self.densspec[i])-1):
                        veldens+=(self.densspec[i][step-1][0]-self.densspec[i][step][0])*1000.*self.densspec[i][step][1]
                        velerr+=((self.densspec[i][step-1][0]-self.densspec[i][step][0])*1000.*self.densspec[i][step][2])**2
                    else:
                        veldens+=(self.densspec[i][step-1][0]-self.densspec[i][step+1][0])*500.*self.densspec[i][step][1]
                        velerr+=((self.densspec[i][step-1][0]-self.densspec[i][step+1][0])*500.*self.densspec[i][step][2])**2
            if (self.dens[i][0]!=0.):
                self.densvelocity.append([veldens/self.dens[i][0],(1/self.dens[i][0])*sqrt(velerr)+(veldens/self.dens[i][0]**2)*self.dens[i][1]])
            else:
                self.densvelocity.append([0.,0.])
    
    def plot(self,gp):
        d=[]
        for i in range(len(self.dens)):
            d.append([self.time[i],self.suprath[i][0]])
        gp("set logscale y")
        gp.plot(d)

    def recalc_moments(self):
        kb = 1.38065e-23
        u = 1.660538e-27
        for i in range(len(self.time)):
            tmpmoments=getmoments(self.densspec[i],self.vel[i],self.vth[i])
            self.bulkdens.append(tmpmoments[0])
            self.vel2.append(tmpmoments[1]/1000.)
            self.temp2.append(tmpmoments[2]*u*self.mass/kb)
            self.vth2.append(sqrt(tmpmoments[2])/1000.)
            self.vth3.append(sqrt(tmpmoments[3])/1000.)
            self.dens2.append(tmpmoments[0]/100.)
                              
    def calc_crmoments(self):
        kb = 1.38065e-23
        u = 1.660538e-27
        for i in range(len(self.time)):
            tmpmoments=getcrmoments(self.countspec[i])
            self.crvel.append(tmpmoments[1])
            self.crtemp.append(tmpmoments[2]*1000.**2*u*self.mass/kb)
            self.crvth.append(sqrt(tmpmoments[2]))
            self.crdens.append(tmpmoments[0])

    def calc_higher_moments(self):
        for i in range(len(self.densspec)):
            skewness=0.
            kortosis=0.
            dens=0.
            if (self.vth[i]>1. and self.vel[i]>100. and self.vel[i]<1500.):
                for j in range(len(self.densspec[i])):
                    deltavel=0.
                    if (j==0):
                        deltavel=(self.densspec[i][j][0]-self.densspec[i][j+1][0])*1000.
                    elif (j==len(self.densspec[i])-1):
                        deltavel=(self.densspec[i][j-1][0]-self.densspec[i][j][0])*1000.
                    else:
                        deltavel=((self.densspec[i][j-1][0]-self.densspec[i][j+1][0])*0.5)*1000.
                    skewness+=self.densspec[i][j][1]*deltavel*(((self.densspec[i][j][0]-self.vel[i]))/self.vth[i])**3
                    kortosis+=self.densspec[i][j][1]*deltavel*(((self.densspec[i][j][0]-self.vel[i]))/self.vth[i])**4
                    dens+=self.densspec[i][j][1]*deltavel
            if (dens>0.):
                skewness=skewness/dens
                kortosis=kortosis/dens
            self.skewness.append(skewness)
            self.kortosis.append(kortosis)


def getmoments(data,vb,vth):
    A=0.     #-->  integral
    A1=0.
    A2=0.
    v0=0.    #-->  center of mass
    sigsq=0. #-->  sigma^2
    sigsq1=0.
    dvel=[]
    maxval=0.
    for i in range(len(data)):
        if (data[i][1]>maxval):
            maxval=data[i][1]
            #vb=data[i][0]
    for i in range(len(data)):
        deltavel=0.
        if (i==0):
            deltavel=(data[0][0]-data[1][0])*1000.
        elif (i==len(data)-1):
            deltavel=(data[len(data)-2][0]-data[len(data)-1][0])*1000.
        else:
            deltavel=((data[i-1][0]-data[i+1][0])*0.5)*1000.
        if (data[i][0]>=vb-8.*vth and data[i][0]<=vb+.0*vth):
            A=A+deltavel*data[i][1]
        if (data[i][0]>=vb and data[i][0]<=vb+8.*vth):
            A1=A1+deltavel*data[i][1]
        if (data[i][0]>=vb-8.*vth and data[i][0]<=vb+8.*vth):
            A2=A2+deltavel*data[i][1]
        dvel.append(deltavel)
    if (A2>0.):
        for i in range(len(data)):
            if (data[i][0]>=vb-8.*vth and data[i][0]<=vb+8.*vth):
                v0=v0+data[i][0]*data[i][1]*dvel[i]*1000.
        v0=v0/(A2)
        A=0.
        A1=0.
        for i in range(len(data)):
            #if (data[i][0]>=v0-6.*vth and data[i][0]<v0+.0*vth):
            if (data[i][0]<vb):
                #sigsq=sigsq+data[i][1]*dvel[i]*(data[i][0]*1000.-vb*1000.)**2
                sigsq=sigsq+data[i][1]*dvel[i]*(data[i][0]*1000.-vb)**2
                A+=data[i][1]*dvel[i]
            #if (data[i][0]>vb and data[i][0]<=vb+6.*vth):
            if (data[i][0]>vb):
                #sigsq1=sigsq1+data[i][1]*dvel[i]*(data[i][0]*1000.-vb*1000.)**2
                sigsq1=sigsq1+data[i][1]*dvel[i]*(data[i][0]*1000.-vb)**2
                A1+=data[i][1]*dvel[i]
        if (A>0.):
            sigsq=sigsq/(A)
        if (A1>0.):
            sigsq1=sigsq1/(A1)
    return [A2,v0,sigsq,sigsq1]

def getcrmoments(data):
    A=0.     #-->  integral
    v0=0.    #-->  center of mass
    sigsq=0. #-->  sigma^2
    for i in range(len(data)):
        A=A+data[i][1]
    if (A>0.):
        for i in range(len(data)):
            v0=v0+data[i][0]*data[i][1]
        v0=v0/A
        for i in range(len(data)):
            sigsq=sigsq+data[i][1]*(data[i][0]-v0)**2
        sigsq=sigsq/A
    return [A,v0,sigsq]

def ionratio(ion1, ion2):
    erg=[]
    for j in range(len(ion1.dens)):
        if (ion2.dens[j][0]!=0.):
            ratio=ion1.dens[j][0]/ion2.dens[j][0]
            err=(ion1.dens[j][1]/ion2.dens[j][0])**2+(ion1.dens[j][0]*ion2.dens[j][1]/ion2.dens[j][0]**2)**2
            err2=(ion1.dens[j][2]/ion2.dens[j][0])**2+(ion1.dens[j][0]*ion2.dens[j][2]/ion2.dens[j][0]**2)**2
        else:
            ratio=0.
            err=0.
            err2=0.
        erg.append([ratio,sqrt(err),sqrt(err2)])
    return erg
