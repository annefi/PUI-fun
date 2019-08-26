from numpy import loadtxt,savetxt,zeros,append,unique,amin,isnan,array,round,ones,arange,histogram2d,clip,amax,searchsorted,max,abs
from libsoho.libctof import tof_to_mq2,tof_to_mq,getionvel,convsecs70toDoY
from time import clock
from libsoho import pmdata

def dhms_in_days(str):
	
	a = str.split(":")
	                    
	days = float(a[0])
	hours = float(a[1])
	minutes = float(a[2])
	seconds = float(a[3])

	Days = days + (hours*3600.0 + minutes*60.0 + seconds *1.0)/(24.0*3600.0)
	return Days


def days_in_dhms(days):

	fulldays = int(days)	

	hours = (days-float(fulldays))*24.
	#print hours	
	fullhours = int(hours)
	
	minutes = (hours - float(fullhours))*60.	
	#print minutes	
	fullminutes = int(minutes)
		
	seconds = (minutes - float(fullminutes))*60.
	#print seconds	
	fullseconds = int(seconds)

	DHMS = "%i:%i:%i:%i" %(fulldays, fullhours, fullminutes, fullseconds)
	return DHMS  
	#print "The accuracy of the timevalue is +-1 second!"





class ctoflv1(object):
    def __init__(self,timeframe,year=1996,path="/data/ivar/berger/ctof/lv1/",loadlv="lv1",foillelem="Helium",foillcharge=1):
        """
        This class is ment to deal with CTOF PHA data. 
        year -> year of data (mind that CTOF only functioned properly from DoY 80 to 230 in 1996) 
        timeframe -> list of periods [[t1,t2],...,[tn-1,tn]]
        path -> should give the path to the pha data

        times,secs,tof,energy,range,step -> contains the information for each individual PHA word.
        time -> contains a list of the starting times of the instrumental cycles.Each cycle (a complete ESA sweep) is about 300s. 
        """
	start = clock()      

  	self.year=year
        self.timeframe=timeframe
        self.path=path
	self.foillelem=foillelem
	self.foillcharge=foillcharge

        self.times=zeros((0))
        self.secs=zeros((0))
        self.range=zeros((0))
        self.energy=zeros((0))
        self.tof=zeros((0))
        self.step=zeros((0))
        self.vel=zeros((0))
        self.vsw=zeros((0))
        self.dsw=zeros((0))
        self.tsw=zeros((0))
        self.mpq=zeros((0))
        self.w=zeros((0))
	self.vsw=zeros((0))
	self.vth=zeros((0))	
	self.vsw_safe = zeros((0))	
	self.vsw_sorted = zeros((0))
	self.vth_sorted = zeros((0))        
	self.dsw=zeros((0))
	self.dsw_sorted = zeros((0))        
	self.w=zeros((0))
        self.br=zeros((0))
        self.ratestep=zeros((0))
        self.ratetcr=zeros((0))
        self.ratedcr=zeros((0))
        self.ratessr=zeros((0))
        self.ratefsr=zeros((0))
        self.rateher=zeros((0))
        self.ratehpr=zeros((0))
        self.ratesecs=zeros((0))
	self.time_indices = zeros((0))
	self.time_indices_shifted = zeros((0))	
	self.time_dhms = zeros((0))	
	self.time_dhmsu = zeros((0))	
	self.pmtime =  zeros((0))
	self.pmtime_dhms = zeros((0))
	self.pmtime_shifted = zeros((0))
	self.pmtime_shifted_dhms = zeros((0))

        if loadlv=="lv1":
            self.loadlv1()
            self.calc_mpq()
            self.calc_ionvel()
            self.get_vsw()
            #self.calc_baserates()
        elif loadlv=="lv1br":
            self.loadlv1br()
            self.calc_ionvel()
	end = clock()	
        #self.load_rates()

    def loadlv1br(self):
        for tf in self.timeframe:
            for day in range(int(tf[0]),int(tf[1]+1.)):
                tmpdat=loadtxt(self.path+"cphbr"+str(self.year%100)+"%.3i.dat"%(day),skiprows=3)
                self.times=append(self.times,tmpdat[(tmpdat[:,0]>tf[0])*(tmpdat[:,0]<tf[1])][:,0])
                self.secs=append(self.secs,tmpdat[(tmpdat[:,0]>tf[0])*(tmpdat[:,0]<tf[1])][:,1])
                self.range=append(self.range,tmpdat[(tmpdat[:,0]>tf[0])*(tmpdat[:,0]<tf[1])][:,2])
                self.energy=append(self.energy,tmpdat[(tmpdat[:,0]>tf[0])*(tmpdat[:,0]<tf[1])][:,3])
                self.tof=append(self.tof,tmpdat[(tmpdat[:,0]>tf[0])*(tmpdat[:,0]<tf[1])][:,4])
                self.step=append(self.step,tmpdat[(tmpdat[:,0]>tf[0])*(tmpdat[:,0]<tf[1])][:,5])
                self.vsw=append(self.vsw,tmpdat[(tmpdat[:,0]>tf[0])*(tmpdat[:,0]<tf[1])][:,6])
                self.dsw=append(self.dsw,tmpdat[(tmpdat[:,0]>tf[0])*(tmpdat[:,0]<tf[1])][:,7])
                self.tsw=append(self.tsw,tmpdat[(tmpdat[:,0]>tf[0])*(tmpdat[:,0]<tf[1])][:,8])
                self.mpq=append(self.mpq,tmpdat[(tmpdat[:,0]>tf[0])*(tmpdat[:,0]<tf[1])][:,9])
                self.w=append(self.w,tmpdat[(tmpdat[:,0]>tf[0])*(tmpdat[:,0]<tf[1])][:,10])
                self.br=append(self.br,tmpdat[(tmpdat[:,0]>tf[0])*(tmpdat[:,0]<tf[1])][:,11])
        self.time=unique(self.times)
        print("phabr data loaded")
        return True


	#start_old = clock()        
	#self.get_vsw()
	#end_old = clock()	
	
	#start_safe = clock()
	#self.get_vsw_safe()
	#end_safe = clock()

	start_quick = clock()		
	self.get_vsw_quick()
	end_quick = clock()
	
	#start_new = clock()		
	#self.get_vsw_nj()
	#end_new = clock()	
	
	#start_conv = clock()	
	#self.conv_time()
	#end_conv = clock()
		
	print "Ctof Data loading time = %f seconds"%(end - start) 
	#print "get_vsw time = %f seconds"%(end_old - start_old) 	
	#print "get_vsw_safe time = %f seconds" %(end_safe - start_safe)	
	#print "get_vsw_nj time = %f seconds"%(end_new - start_new) 
	print "get_vsw_quick time = %f seconds" %(end_quick - start_quick)
	#print "Times-conversion time = %f seconds" %(end_conv - start_conv)


    def loadlv1(self):
        for tf in self.timeframe:
            for day in range(int(tf[0]),int(tf[1]+1.)):
                tmpdat=loadtxt(self.path+"cph"+str(self.year%100)+"%.3i.dat"%(day),skiprows=3)
                self.times=append(self.times,tmpdat[(tmpdat[:,0]>tf[0])*(tmpdat[:,0]<tf[1])][:,0])
                self.secs=append(self.secs,tmpdat[(tmpdat[:,0]>tf[0])*(tmpdat[:,0]<tf[1])][:,1])
                self.range=append(self.range,tmpdat[(tmpdat[:,0]>tf[0])*(tmpdat[:,0]<tf[1])][:,2])
                self.energy=append(self.energy,tmpdat[(tmpdat[:,0]>tf[0])*(tmpdat[:,0]<tf[1])][:,3])
                self.tof=append(self.tof,tmpdat[(tmpdat[:,0]>tf[0])*(tmpdat[:,0]<tf[1])][:,4])
                self.step=append(self.step,tmpdat[(tmpdat[:,0]>tf[0])*(tmpdat[:,0]<tf[1])][:,5])
        self.time=unique(self.times)
        print("pha data loaded")
        return True

    def calc_mpq(self):
        self.mpq=tof_to_mq2(self.tof,self.step,self.times,self.foillelem,self.foillcharge)
        return True

    def calc_ionvel(self):
        self.vel=getionvel(self.mpq,self.step)
        return True
    
    def get_vsw(self):
        pmdat=pmdata(self.timeframe,year=self.year)
        self.vsw=zeros(self.times.shape)
        self.dsw=zeros(self.times.shape)
        self.tsw=zeros(self.times.shape)
        for t in self.time:
            tmpptime=pmdat.time-t
            if amin(abs(tmpptime))<0.00348:
                mask=(abs(tmpptime)==amin(abs(tmpptime)))
                self.vsw[self.times==t]=pmdat.vel[mask][0]
                self.dsw[self.times==t]=pmdat.dens[mask][0]
                self.tsw[self.times==t]=pmdat.vth[mask][0]
        self.w=self.vel/self.vsw
        self.w[isnan(self.w)]=0.
        return True


    def get_vsw_safe(self,tol = 0.00360): #tolerance = 9 s => (302+9)s/(24*3600) < 0.00360d  

	pmdat = pmdata(self.timeframe)
	pmdat.time = pmdat.time - 0.00175	
	self.vsw_safe=ones((len(self.times)))
	print self.vsw_safe
	for i in arange(len(self.times)):			
		for j in arange(len(pmdat.time)):
			if (self.times[i] - pmdat.time[j]) >= 0. and abs(self.times[i] - pmdat.time[j]) < tol:
				self.vsw_safe[i] = pmdat.vel[j]
			else:  
				self.vsw_safe[i] = -999	
	return True




    def get_vsw_quick(self, tol = 0.00360):
	#Method get_vsw_quick is documentated in ctof/Verena.
		
	pmdat = pmdata(self.timeframe)
	pmdat.time_shifted = pmdat.time - 0.00175	
	pmdat.time_shifted = pmdat.time_shifted.tolist()
	pmdat.vel = pmdat.vel.tolist()		
	pmdat.vth = pmdat.vth.tolist()
	pmdat.dens = pmdat.dens.tolist()
	pmdat.time = pmdat.time.tolist()

	i = 1 
	while i < len(pmdat.time):
		if (pmdat.time_shifted[i] - pmdat.time_shifted[i-1]) > tol:
			pmdat.time_shifted.insert(i,pmdat.time_shifted[i-1]+0.00360) 
			pmdat.vel.insert(i,-999)
			pmdat.vth.insert(i,-999)		
			pmdat.dens.insert(i,-999)
			pmdat.time.insert(i,pmdat.time[i-1]+0.00360)	
		i = i+1
	
	pmdat.time_shifted = array(pmdat.time_shifted)
	pmdat.vel = array(pmdat.vel)
	pmdat.vth = array(pmdat.vth)
	pmdat.dens = array(pmdat.dens)
	pmdat.time = array(pmdat.time)
	
	self.time_indices = (searchsorted(pmdat.time_shifted,self.times, side = "right")-1)		
	
	self.vsw = pmdat.vel[self.time_indices]	
	self.vth = pmdat.vth[self.time_indices]	
	self.dsw = pmdat.dens[self.time_indices]		
	
	self.pmtime_shifted = pmdat.time_shifted[self.time_indices]
	self.pmtime = pmdat.time_shifted[self.time_indices] + 0.00175 #Creates the corresponding timestamp of pm(inaccuracy = 1 second). 


 


   



    #def get_cycle		
		

   
    def conv_time(self):
	self.times_dhms = []   	
	for t in self.times:
		T = days_in_dhms(t)
		self.times_dhms.append(T)	
	self.times_dhms = array(self.times_dhms)
	
	self.times_dhmsu = []
	for t in self.time:	
		T = days_in_dhms(t)
		self.times_dhmsu.append(T)	
	self.times_dhmsu = array(self.times_dhmsu)

   	self.pmtime_dhms = []   	
	for t in self.pmtime:
		T = days_in_dhms(t)
		self.pmtime_dhms.append(T)	
	self.pmtime_dhms = array(self.pmtime_dhms)		
	
       	self.pmtime_shifted_dhms = []   	
	for t in self.pmtime_shifted:
		T = days_in_dhms(t)
		self.pmtime_shifted_dhms.append(T)	
	self.pmtime_shifted_dhms = array(self.pmtime_shifted_dhms) #Ungenauigkeit 1s



    def load_rates(self):
        self.ratestep=zeros((0))
        self.ratetcr=zeros((0))
        self.ratedcr=zeros((0))
        self.ratessr=zeros((0))
        self.ratefsr=zeros((0))
        self.rateher=zeros((0))
        self.ratehpr=zeros((0))
        self.ratesecs=zeros((0))
        for tf in self.timeframe:
            for day in range(int(tf[0])-1,int(tf[1])+1):
                tmpdat=loadtxt(self.path+"c"+str(self.year%100)+"%.3i.cra"%(day),skiprows=13)
                mask=(tmpdat[:,3]<3)
                self.ratesecs=append(self.ratesecs,tmpdat[mask][:,0]+15)
                self.ratestep=append(self.ratestep,tmpdat[mask][:,1])
                self.ratefsr=append(self.ratefsr,tmpdat[mask][:,5])
                self.ratedcr=append(self.ratedcr,tmpdat[mask][:,6])
                self.ratetcr=append(self.ratetcr,tmpdat[mask][:,7])
                self.ratessr=append(self.ratessr,tmpdat[mask][:,8])
                self.ratehpr=append(self.ratehpr,tmpdat[mask][:,9])
                self.rateher=append(self.rateher,tmpdat[mask][:,10])
        self.ratesec=unique(self.ratesecs)
        self.sec=unique(self.secs)

        print("rate data loaded")
        return True


    def calc_baserates(self):
        """
        Load rate files (.cra) and calculate base rates for tcr and dcr.
        """
        self.load_rates()
        bint=(append(self.ratesec,self.ratesec[-1]+self.ratesec[-1]-self.ratesec[-2]),arange(120))  # one time step after last cycle is appended for histogram reasons
        ctstcr=array(histogram2d(self.secs[(self.energy>0.)],self.step[(self.energy>0.)],bins=bint))    # number of tcr pha counts are histogrammed (per step and time) 
        ctsdcr=array(histogram2d(self.secs[self.energy>=0.],self.step[self.energy>=0.],bins=bint))  # number of dcr pha counts are histogrammed (per step and time)
        rtcr=array(histogram2d(self.ratesecs,self.ratestep,bins=bint,weights=(self.ratetcr-self.ratehpr-0.9*self.rateher)))*2.5   # tcr rates are converted into counts (*2.5) and histogrammed
        #rdcr=array(histogram2d(self.ratesecs,self.ratestep,bins=bint,weights=(self.ratedcr-self.ratetcr)))*2.5 # tcr rates are converted into counts (*2.5) and histogrammed 
        rdcr=array(histogram2d(self.ratesecs,self.ratestep,bins=bint,weights=(self.ratedcr-self.ratehpr-self.rateher)))*2.5 # tcr rates are converted into counts (*2.5) and histogrammed 
        # zero rates and zero pha counts are set to 1. (Needed for base-rate calculation to avoid NAN and INF)
        ctstcr[0]=clip(ctstcr[0],1.,max(1.,amax(ctstcr[0])))
        ctsdcr[0]=clip(ctsdcr[0],1.,max(1.,amax(ctsdcr[0])))
        rtcr[0]=clip(rtcr[0],1.,max(1.,amax(rtcr[0])))
        rdcr[0]=clip(rdcr[0],1.,max(1.,amax(rdcr[0])))
        brbinx=ctstcr[2]
        brbiny=ctstcr[1]
        brwtcrar=rtcr[0]/ctstcr[0]
        brwdcrar=rdcr[0]/ctsdcr[0]
        time=searchsorted(brbiny,self.secs)
        steps=zeros(self.step.shape,int)
        steps[:]=self.step[:]
        brtcr=brwtcrar[time,steps]
        brdcr=brwdcrar[time,steps]
        self.br=zeros(self.times.shape)
        self.br[self.energy==0]=brdcr[self.energy==0]
        #self.br[self.energy>0]=brtcr[self.energy>0]
        self.br=brdcr
        
    def write_br_files(self):
        self.calc_baserates()
        for tf in self.timeframe:
            for day in range(int(tf[0]),int(tf[1])+1):
                outf=open(self.path+"cphbr396%.3i.dat"%(day),"w")
                outf.write("CTOF PHA data + solar wind properties from PM data + base rates from rate data (.cra) day %.3i year 1996\n"%(day))
                outf.write("*****\n")
                outf.write("DoY\t\tsecs1970\tRange\tEnergy\tToF\tEqstep\tvsw\tdsw\ttsw\tmpq\tw\tbr\n")
                mask=(self.times>=day)*(self.times<day+1)
                tmpdat=zeros((self.times[mask].shape[0],12))
                tmpdat[:,0]=self.times[mask]
                tmpdat[:,1]=self.secs[mask]
                tmpdat[:,2]=self.range[mask]
                tmpdat[:,3]=self.energy[mask]
                tmpdat[:,4]=self.tof[mask]
                tmpdat[:,5]=self.step[mask]
                tmpdat[:,6]=self.vsw[mask]
                tmpdat[:,7]=self.dsw[mask]
                tmpdat[:,8]=self.tsw[mask]
                tmpdat[:,9]=self.mpq[mask]
                tmpdat[:,10]=self.w[mask]
                tmpdat[:,11]=self.br[mask]
                savetxt(outf,tmpdat,fmt=["%f","%i","%.2i","%i","%i","%i","%.2f","%.2f","%.2f","%.2f","%.2f","%.2f"],delimiter="\t")
                #for i in range(self.times[mask].shape[0]):
                #    print i,float(i)/float(self.times[mask].shape[0])
                #    outf.write("%f\t%i\t%.2i\t%i\t%i\t%i\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\n"%(self.times[mask][i],self.secs[mask][i],self.range[mask][i],self.energy[mask][i],self.tof[mask][i],self.step[mask][i],self.vsw[mask][i],self.dsw[mask][i],self.tsw[mask][i],self.mpq[mask][i],self.w[mask][i],self.br[mask][i]))
                #    outf.flush()
                outf.close()
        
    def calc_baserates_old(self):
        self.load_rates()
        self.brtcr=[]
        self.brdcr=[]
        for j,sec in enumerate(self.ratesec):
            print float(j)/float(self.ratesec.shape[0])
            tmpratesteps=self.ratestep[self.ratesecs==sec]
            tmpratedcr=self.ratedcr[self.ratesecs==sec]
            tmpratetcr=self.ratetcr[self.ratesecs==sec]
            tmpratehpr=self.ratehpr[self.ratesecs==sec]
            for i,step in enumerate(tmpratesteps):
                masksecs=(self.secs==sec)
                maskdcr=(self.step[masksecs]==step)*(self.energy[masksecs]==0.)
                masktcr=(self.step[masksecs]==step)*(self.energy[masksecs]>0.)
                if sum(masktcr)>0.:
                    self.brtcr.append(((tmpratetcr[i]-tmpratehpr[i])*2.5)/sum(masktcr))
                else:
                    self.brtcr.append(1.)
                if sum(maskdcr)>0.:
                #if tmpratedcr[i]-tmpratetcr[i]>0. and sum(maskdcr)>0.:
                    self.brdcr.append(((tmpratedcr[i]-tmpratetcr[i])*2.5)/sum(maskdcr))
                else:
                    self.brdcr.append(1.)
        self.brtcr=array(self.brtcr)
        self.brdcr=array(self.brdcr)


    def get_rateepqstep(self):
        self.ratestepepq=[]
        for i in range(self.times.shape[0]):
            tmpval=self.rateepq[(self.ratetimes==self.times[i])*(self.ratestep==self.step[i])]
            if tmpval.shape[0]>0:
                self.ratestepepq.append(tmpval[0])
            else:
                self.ratestepepq.append(0)
            #print i,"/",self.times.shape[0]
        self.ratestepepq=array(self.ratestepepq)
        """
        for t in self.ratetime:
            print t
            tmpstep=self.step[self.times==t]
            tmpratestepepq=zeros(tmpstep.shape)
            tmpratestep=self.ratestep[self.ratetimes==t]
            tmprateepq=self.rateepq[self.ratetimes==t]
            print tmpstep.shape
            print tmpratestepepq.shape
            print tmpratestep.shape
            print tmprateepq.shape
            for i in range(tmpratestep.shape[0]):
                tmpratestepepq[tmpstep==tmpratestep[i]]=tmprateepq[i]
                self.ratestepepq=append(self.ratestepepq,tmpratestepepq)
        """

class ctofpui(ctoflv1):
    def __init__(self,timeframe,year=1996,path="/data/etph/soho/celias/ctof/"):
        """
        This class is ment to deal with CTOF PHA data. PUI data only mpq>10 (and 3.5<mpq<4.5) 
        year -> year of data (mind that CTOF only functioned properly from DoY 80 to 230 in 1996) 
        timeframe -> list of periods [[t1,t2],...,[tn-1,tn]]
        path -> should give the path to the pha data

        times,secs,tof,energy,range,step -> contains the information for each individual PHA word.
        time -> contains a list of the starting times of the instrumental cycles.Each cycle (a complete ESA sweep) is about 300s. 
        """
        self.year=year
        self.timeframe=timeframe
        self.path=path
        self.times=zeros((0))
        self.secs=zeros((0))
        self.tof=zeros((0))
        self.energy=zeros((0))
        self.range=zeros((0))
        self.step=zeros((0))
        self.mpq=zeros((0))
        self.vel=zeros((0))
        self.vsw=zeros((0))
        self.dsw=zeros((0))
        self.w=zeros((0))
        self.loadlv1()
        self.calc_ionvel()
        self.get_vsw()

    def loadlv1(self):
        for tf in self.timeframe:
            for day in range(int(tf[0]),int(tf[1]+1.)):
                tmpdat=loadtxt(self.path+"cph"+str(self.year%100)+"%.3i.dat"%(day),skiprows=3)
                self.times=append(self.times,tmpdat[(tmpdat[:,0]>tf[0])*(tmpdat[:,0]<tf[1])][:,0])
                self.secs=append(self.secs,tmpdat[(tmpdat[:,0]>tf[0])*(tmpdat[:,0]<tf[1])][:,1])
                self.range=append(self.range,tmpdat[(tmpdat[:,0]>tf[0])*(tmpdat[:,0]<tf[1])][:,2])
                self.energy=append(self.energy,tmpdat[(tmpdat[:,0]>tf[0])*(tmpdat[:,0]<tf[1])][:,3])
                self.tof=append(self.tof,tmpdat[(tmpdat[:,0]>tf[0])*(tmpdat[:,0]<tf[1])][:,4])
                self.step=append(self.step,tmpdat[(tmpdat[:,0]>tf[0])*(tmpdat[:,0]<tf[1])][:,5])
                self.calc_mpq()
                self.cut_mpq()
        self.time=unique(self.times)
        print("pha data loaded")
        return True

    def cut_mpq(self):
        mask=(self.mpq>10.)+((self.mpq>3.5)*(self.mpq<4.5))
        self.times=self.times[mask]
        self.secs=self.secs[mask]
        self.tof=self.tof[mask]
        self.energy=self.energy[mask]
        self.range=self.range[mask]
        self.step=self.step[mask]
        self.mpq=self.mpq[mask]
        


