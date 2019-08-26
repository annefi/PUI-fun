from libacepy.mag import magdata
from numpy import arccos,cos,mean,std,isnan,isinf,pi,histogram,arctan2,sqrt,searchsorted,loadtxt,array,append
from pylib import dbData

# Dieses Skript sucht in den ACE/MAG Daten nach perioden in denen das Magnetfeld konstante Richtung zur Sun-Earth Line zeigt


years=[2007]
startdoy=1
enddoy=365

class dbmag(dbData): 
    def load_data(self,*args,**kwargs):
        if not(("res") and ("year" in kwargs.keys()) and ("tf" in kwargs.keys())) and not("data" in kwargs.keys()):
            print "need year and tf or data"
            return
        if ("data" in kwargs.keys()):
            print "generate dbmag with direct data input"
            dat=kwargs["data"]
            self.data["B"]=dat[0]
            self.data["Bx"]=dat[1]
            self.data["By"]=dat[2]
            self.data["Bz"]=dat[3]
            self.data["phi"]=dat[4]
            self.data["theta"]=dat[5]
            self.data["time"]=dat[6]
            self.data["alpha"]=dat[7]
            self.data["dB"]=dat[8]
            self.data["dBx"]=dat[9]
            self.data["dBy"]=dat[10]
            self.data["dBz"]=dat[11]
            self.data["dphi"]=dat[12]
            self.data["dtheta"]=dat[13]
            self.data["dalpha"]=dat[14]
            return

        if not("path" in kwargs.keys()):
            path="/data/etph/ace/mag/"
        else:
            path=kwargs["path"]
        time=array([])
        B=array([])
        Bx=array([])
        By=array([])
        Bz=array([])

        print "Reading Mag data from : ",path," ; Year : ",kwargs["year"]," ; Resolution 1s ; timeframe : ",kwargs["tf"]
        for tf in kwargs["tf"]:
            for DoY in range(int(tf[0]),int(tf[1])+1):
                inname=path+"/1sdata/"+str(kwargs["year"])+"/%.3i"%(DoY)
                data = loadtxt(inname,skiprows=2)
                # data is fit into timeframe
                timemask=(data[:,0]>=tf[0])*(data[:,0]<=tf[1])
                data=data[timemask]

                # append data
                time=append(time,data[:,0])
                B=append(B,data[:,1])
                Bx=append(Bx,data[:,2]*(-1.))
                By=append(By,data[:,3])
                Bz=append(Bz,data[:,4])
        print "MAG-data loaded"
        # cut away bad values (indicated by -999.)
        mask=(B>0.)
        time=time[mask]
        B=B[mask]
        Bx=Bx[mask]
        By=By[mask]
        Bz=Bz[mask]
        phi=arctan2(By,Bx)
        theta=arctan2(Bz,sqrt(Bx**2+By**2))
        alpha=arccos(cos(phi)*cos(theta))
        # if tbins is not given -> no binning is applied, if tbins is given data is binned and standard deviations are calculated
        if not("tbins" in kwargs.keys()):
            self.data["B"]=B
            self.data["Bx"]=Bx
            self.data["By"]=By
            self.data["Bz"]=Bz
            self.data["phi"]=phi
            self.data["theta"]=theta
            self.data["time"]=time
            self.data["alpha"]=alpha
        else:
            tbins=kwargs["tbins"]
            mask=(phi!=0.)*(theta!=0.)
            time=time[mask]
            B=B[mask]
            Bx=Bx[mask]
            By=By[mask]
            Bz=Bz[mask]
            phi=phi[mask]
            theta=theta[mask]
            btime,x=histogram(time,tbins)
            bBx,x=histogram(time,tbins,weights=Bx)
            bBy,x=histogram(time,tbins,weights=By)
            bBz,x=histogram(time,tbins,weights=Bz)
            bBx/=btime
            bBy/=btime
            bBz/=btime
            bB=sqrt(bBx**2+bBy**2+bBz**2)
            bphi=arctan2(bBy,bBx)
            btheta=arctan2(bBz,sqrt(bBx**2+bBy**2))
            balpha=arccos(cos(bphi)*cos(btheta))
            ind=searchsorted(tbins,time)-1
            dB=(B-bB[ind])**2
            dBx=(Bx-bBx[ind])**2
            dBy=(By-bBy[ind])**2
            dBz=(Bz-bBz[ind])**2
            dphi=(phi-bphi[ind])**2
            dtheta=(theta-btheta[ind])**2
            dalpha=(alpha[mask]-balpha[ind])**2
            dB,x=histogram(time,tbins,weights=dB)
            dB=sqrt(dB/btime)
            dBx,x=histogram(time,tbins,weights=dBx)
            dBx=sqrt(dBx/btime)
            dBy,x=histogram(time,tbins,weights=dBy)
            dBy=sqrt(dBy/btime)
            dBz,x=histogram(time,tbins,weights=dBz)
            dBz=sqrt(dBz/btime)
            dphi,x=histogram(time,tbins,weights=dphi)
            dphi=sqrt(dphi/btime)
            dtheta,x=histogram(time,tbins,weights=dtheta)
            dtheta=sqrt(dtheta/btime)
            dalpha,x=histogram(time,tbins,weights=dalpha)
            dalpha=sqrt(dalpha/btime)
            
            self.data["B"]=bB
            self.data["Bx"]=bBx
            self.data["By"]=bBy
            self.data["Bz"]=bBz
            self.data["phi"]=bphi
            self.data["theta"]=btheta
            self.data["time"]=tbins
            self.data["alpha"]=balpha
            self.data["dB"]=dB
            self.data["dBx"]=dBx
            self.data["dBy"]=dBy
            self.data["dBz"]=dBz
            self.data["dphi"]=dphi
            self.data["dtheta"]=dtheta
            self.data["dalpha"]=dalpha


    def bin_mag(self,tbins):
        self.add_mask("valid")
        self.set_mask("valid","phi",0.,op="ne")
        self.set_mask("valid","theta",0.,op="ne")
        time=self.get_data("valid","time")
        B=self.get_data("valid","B")
        Bx=self.get_data("valid","Bx")
        By=self.get_data("valid","By")
        Bz=self.get_data("valid","Bz")
        phi=self.get_data("valid","phi")
        theta=self.get_data("valid","theta")
        alpha=self.get_data("valid","alpha")
        btime,x=histogram(time,tbins)
        bBx,x=histogram(time,tbins,weights=Bx)
        bBy,x=histogram(time,tbins,weights=By)
        bBz,x=histogram(time,tbins,weights=Bz)
        bBx/=btime
        bBy/=btime
        bBz/=btime
        bB=sqrt(bBx**2+bBy**2+bBz**2)
        bphi=arctan2(bBy,bBx)
        btheta=arctan2(bBz,sqrt(bBx**2+bBy**2))
        balpha=arccos(cos(bphi)*cos(btheta))
        ind=searchsorted(tbins,time)-1
        dB=(B-bB[ind])**2
        dBx=(Bx-bBx[ind])**2
        dBy=(By-bBy[ind])**2
        dBz=(Bz-bBz[ind])**2
        dphi=(phi-bphi[ind])**2
        dtheta=(theta-btheta[ind])**2
        dalpha=(alpha-balpha[ind])**2
        dB,x=histogram(time,tbins,weights=dB)
        dB=sqrt(dB/btime)
        dBx,x=histogram(time,tbins,weights=dBx)
        dBx=sqrt(dBx/btime)
        dBy,x=histogram(time,tbins,weights=dBy)
        dBy=sqrt(dBy/btime)
        dBz,x=histogram(time,tbins,weights=dBz)
        dBz=sqrt(dBz/btime)
        dphi,x=histogram(time,tbins,weights=dphi)
        dphi=sqrt(dphi/btime)
        dtheta,x=histogram(time,tbins,weights=dtheta)
        dtheta=sqrt(dtheta/btime)
        dalpha,x=histogram(time,tbins,weights=dalpha)
        dalpha=sqrt(dalpha/btime)
        return dbmag(data=(bB,bBx,bBy,bBz,bphi,btheta,tbins,balpha,dB,dBx,dBy,dBz,dphi,dtheta,dalpha))


"""
# Laenge des T-Fensters
nrmins=12.
twindow=(60.*nrmins)/(60.*60.*24)  # 24 minuten zeitfenster

# Schrittweite mit der das T-Fenster ueber die Daten geschoben wird
tstep=twindow/2. # 12 Minuten Schrittweite

nrsteps=int(1./tstep)-1

perout=open("magperiods_senkrecht_all.dat","w")
perout.write("year\tsdoy\t\tedoy\t\tmtheta\t\tsigtheta\n")

for year in years:
    for day in range(startdoy,enddoy+1):
        magdat=magdata(1.,year,[[float(day),float(day+1)]],"/data/etph/ace/mag/")
        theta=arccos(cos(magdat.phi)*cos(magdat.theta))
        for i in range(nrsteps):
            mask=(magdat.time>day+float(i)*tstep)*(magdat.time<day+float(i)*tstep+twindow)*(~isnan(theta))*(~isinf(theta))
            if len(theta[mask])>9.5/10.*nrmins*60.:  # wenn im intervall fuer mindestens 95% der Zeit 1s daten sind
                mtheta=mean(theta[mask])
                sigtheta=std(theta[mask])
                if (mtheta>pi/2.-0.25) and (mtheta<pi/2.+0.25):
                    if sigtheta<0.2:
                        perout.write("%i\t%f\t%f\t%f\t%f\n"%(year,day+float(i)*tstep,day+float(i)*tstep+twindow,mtheta,sigtheta))
        perout.flush()

perout.close()
"""
