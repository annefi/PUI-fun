from ace_utils import calc_day00
from pylib import dbData
from numpy import *
import os

class ace_sweswi(dbData):
    def load_data(self,*args,**kwargs):
        if kwargs.has_key("year"):
            if isinstance(kwargs["year"],list):
                self.year=kwargs["year"]
            elif isinstance(kwargs["year"],int) or isinstance(kwargs["year"],float):
                self.year=[kwargs["year"]]
        else:
            self.year=[2007]
        if kwargs.has_key("tf"):
            if isinstance(kwargs["tf"],list) or isinstance(kwargs["tf"],ndarray):
                self.timeframe=kwargs["tf"]
            elif kwargs["tf"]=="all":
                self.timeframe=[[1.,367]]
            else:
                print "periods need to be specified via key tf ([[start,stop],...,[start,stop]] or 'all'), no data loaded"
                self.timeframe=[]
        else:
            print "periods need to be specified via key tf ([[start,stop],...,[start,stop]] or 'all'), no data loaded"
            self.timeframe=[]
        if kwargs.has_key("fmt"):
            self.fmt=kwargs["fmt"]
        else:
            self.fmt="new"
        if kwargs.has_key("path"):
            self.path=kwargs["path"]
        else:
            if self.fmt=="new":
                self.path="/data/ivar/ace/sweswi/12mindata/"
            else:
                self.path="/data/etph/ace/swepam/"
        if self.fmt=="old":
            time=array([])
            years=array([])
            vsw=array([])
            dens=array([])
            temp=array([])
            heh=array([])
            for year in self.year:
                fin=open(self.path+"720s"+str(year)+".dat","r")
                k=fin.readline().split()
                while not (len(k)==2 and k[0]=="BEGIN" and k[1]=="DATA"):
                    k=fin.readline().split()
                dat=loadtxt(fin)
                years=append(years,ones(dat.shape[0])*year)
                time=append(time,dat[:,1])
                vsw=append(vsw,dat[:,5])
                dens=append(dens,dat[:,2])
                temp=append(temp,dat[:,3])
                heh=append(heh,dat[:,4])
            self.data["year"]=array(years)
            self.data["time"]=array(time)
            self.data["vsw"]=array(vsw)
            self.data["dsw"]=array(dens)
            self.data["tsw"]=array(temp)
            self.data["heh"]=array(heh)
            self.data["d00"]=calc_day00(self.data["year"],self.data["time"])
        elif self.fmt=="new":
            self.data["year"]=[]
            self.data["time"]=[]
            self.data["d00"]=[]
            self.data["vsw"]=[]
            self.data["dsw"]=[]
            self.data["tsw"]=[]
            self.data["heh"]=[]
            self.data["svsw"]=[]
            self.data["sdsw"]=[]
            self.data["stsw"]=[]
            self.data["sheh"]=[]
            for year in self.year:
                flist=os.listdir(self.path+str(year)+"/")
                for tf in self.timeframe:
                    for doy in arange(tf[0],tf[1]+0.1,1.):
                        print doy
                        tmpname="%.3i"%(doy)
                        for f in flist:
                            if tmpname in f:
                                fin=open(self.path+str(year)+"/"+f,"r")
                                fin.readline() # skip header
                                for l in fin:
                                    k=l.split()
                                    self.data["year"].append(year)
                                    self.data["time"].append(float(k[0]))
                                    self.data["d00"].append(float(k[1]))
                                    self.data["vsw"].append(float(k[2]))
                                    self.data["dsw"].append(float(k[3]))
                                    self.data["tsw"].append(float(k[4]))
                                    self.data["svsw"].append(float(k[5]))
                                    self.data["sdsw"].append(float(k[6]))
                                    self.data["stsw"].append(float(k[7]))
                                    self.data["heh"].append(float(k[8]))
                                    self.data["sheh"].append(float(k[9]))
            for key in self.data.keys():
                self.data[key]=array(self.data[key])
            
        else:
            print "load_data: unrecognized format!"
            print "fmt='new' -> 12min data (syncronized with ace swics data)"
            print "fmt='old' -> 1s data"

    def bin_data(self,t1,t2,prod1="d00",prod2="time"):
        """
        binning is performed on prod! default is day since 1.1.2000 (d00). Other prods like doy might not work properly if more than one year is present
        """
        self.reset_mask("Master")
        self.set_mask("Master",prod1,t1[0],t1[-1])
        self.set_mask("Master","vsw",0.,op="gt",reset=True)
        pT=self.get_data("Master",prod1)+1./24./60.
        indT=searchsorted(t1,pT)-1
        indT=indT[(indT>=0)*(indT<t1.shape[0]-1)]
        nrT,x=histogram(pT,t1)
        mask=nrT[indT]>0
        mvsw,x=histogram(pT[mask],t1,weights=self.get_data("Master","vsw")[mask])
        nrT[nrT==0.]=1.
        mvsw/=nrT
        svsw,x=histogram(pT[mask],t1,weights=(self.get_data("Master","vsw")[mask]-mvsw[indT][mask])**2)
        svsw=sqrt(svsw/nrT)
        self.remove_submask("Master","vsw")
        self.set_mask("Master","dsw",0.,op="gt",reset=True)
        pT=self.get_data("Master",prod1)+1./24./60.
        indT=searchsorted(t1,pT)-1
        indT=indT[(indT>=0)*(indT<t1.shape[0]-1)]
        nrT,x=histogram(pT,t1)
        mask=nrT[indT]>0
        mdsw,x=histogram(pT[mask],t1,weights=self.get_data("Master","dsw")[mask])
        nrT[nrT==0.]=1.
        mdsw/=nrT
        sdsw,x=histogram(pT[mask],t1,weights=(self.get_data("Master","dsw")[mask]-mdsw[indT][mask])**2)
        sdsw=sqrt(sdsw/nrT)
        self.remove_submask("Master","dsw")
        self.set_mask("Master","tsw",0.,op="gt",reset=True)
        pT=self.get_data("Master",prod1)+1./24./60.
        indT=searchsorted(t1,pT)-1
        indT=indT[(indT>=0)*(indT<t1.shape[0]-1)]
        nrT,x=histogram(pT,t1)
        mask=nrT[indT]>0
        mtsw,x=histogram(pT[mask],t1,weights=self.get_data("Master","tsw")[mask])
        nrT[nrT==0.]=1.
        mtsw/=nrT
        stsw,x=histogram(pT[mask],t1,weights=(self.get_data("Master","tsw")[mask]-mtsw[indT][mask])**2)
        stsw=sqrt(stsw/nrT)
        self.remove_submask("Master","tsw")
        self.set_mask("Master","heh",0.,op="gt",reset=True)
        pT=self.get_data("Master",prod1)+1./24./60.
        indT=searchsorted(t1,pT)-1
        indT=indT[(indT>=0)*(indT<t1.shape[0]-1)]
        nrT,x=histogram(pT,t1)
        mask=nrT[indT]>0
        mheh,x=histogram(pT[mask],t1,weights=self.get_data("Master","heh")[mask])
        nrT[nrT==0.]=1.
        mheh/=nrT
        sheh,x=histogram(pT[mask],t1,weights=(self.get_data("Master","heh")[mask]-mheh[indT][mask])**2)
        sheh=sqrt(sheh/nrT)
        self.remove_submask("Master","heh")
        nrT,x=histogram(self.get_data("Master",prod1),t1)
        myear,x=histogram(self.get_data("Master",prod1),t1,weights=self.get_data("Master","year"))
        nrT[nrT==0.]=1.
        myear/=nrT
        myear=ones(t2.shape[0])*self.year[0]
        
        self.data[prod1]=t1[:-1]
        self.data[prod2]=t2
        self.data["vsw"]=mvsw
        self.data["dsw"]=mdsw
        self.data["tsw"]=mtsw
        self.data["heh"]=mheh
        self.data["svsw"]=svsw
        self.data["sdsw"]=sdsw
        self.data["stsw"]=stsw
        self.data["sheh"]=sheh
        self.data["year"]=myear
        self.reset_mask("all")

    def save_bin(self,path="/data/ivar/ace/sweswi/12mindata/"):
        for year in self.year:
            self.reset_mask("Master")
            self.set_mask("Master","year",year,op="eq",reset=True)
            doys=self.get_data("Master","time")
            if doys.shape[0]>0:
                for day in range(int(amin(doys)),int(amax(doys))+1):
                    self.set_mask("Master","time",day,day+0.999999,reset=True)
                    fout=open(path+str(year)+"/%.3i"%(day),"w")
                    fout.write("DoY\t\td00\t\tvsw\tdsw\ttsw\tsvsw\tsdsw\tstsw\theh\tsheh\n")
                    nrvals=self.get_data("Master","time").shape[0]
                    dat=zeros((nrvals,10))
                    dat[:,0]=self.get_data("Master","time")
                    dat[:,1]=self.get_data("Master","d00")
                    dat[:,2]=self.get_data("Master","vsw")
                    dat[:,3]=self.get_data("Master","dsw")
                    dat[:,4]=self.get_data("Master","tsw")
                    dat[:,5]=self.get_data("Master","svsw")
                    dat[:,6]=self.get_data("Master","sdsw")
                    dat[:,7]=self.get_data("Master","stsw")
                    dat[:,8]=self.get_data("Master","heh")
                    dat[:,9]=self.get_data("Master","sheh")
                    savetxt(fout,dat,fmt=["%.8f","%.8f","%.3f","%.3f","%.3f","%.3f","%.3f","%.3f","%.3f","%.3f"],delimiter="\t")
        self.reset_mask("all")
        
