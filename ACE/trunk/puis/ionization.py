from libsoho import ctofpui
from numpy import ones, histogram, linspace, zeros, isnan, unique, mean, array, loadtxt
from Gnuplot import Gnuplot, Data, GridData
import cPickle
import os, copy
import sys

class ctof_pui_ana:
	def __init__(self, dump=False,dump_path="",timeframe = [[150,230]]):
		"""
		todo
		"""
		### Mask Ranges
		self.masks = {}
		self.masks["vsw"] = 0,2000
		self.masks["dsw"] = 0,2000
		self.masks["times"] = 0,1000
		self.masks["w"] = 0, 100
		self.masks["vel"] = 0, 5000
		self.masks["mpq"] = 0, 1000
		self.masks["step"] = 0, 117
		self.masks["tof"] = 0, 1024
		self.masks["energy"] = 0, 1024
		### Standard attributes
		self.filtered_data={}
		self.timeframe = timeframe
		self.dump_path = dump_path
		self.dump_name = "ctof_pui_dump_%s_%s.dat"%(self.timeframe[0][0],self.timeframe[-1][1])  
		self.dump=dump
		self.debug = False
		if os.path.isfile(self.dump_path+self.dump_name) and not self.dump:
			sys.stdout.write("Loading pickled data ...")
			self.raw_data = cPickle.load(open(self.dump_path+self.dump_name,"r"))
			sys.stdout.write("Done\n")
		else:
			sys.stdout.write("Loading unpickled data ...")
			self.raw_data = ctofpui(self.timeframe)
			sys.stdout.write("Done\n")
			if self.debug == False:	
				sys.stdout.write("Dumping pickled data ...")
				cPickle.dump(self.raw_data,open(self.dump_path+self.dump_name,"w"))
				sys.stdout.write("Done\n")
			pass
		
	def set_mask(self,arg,val):
		"""	
		Applies a filter to the raw data. The data can be filtered by a value range (val) of a given data paramater arg
		"""
		self.masks[arg] = val

	def show_mask(self):
		print "### Current mask ###"
		for arg in self.masks:
			print arg,": ",self.masks[arg]

	def reset_mask(self):
		self.masks["vsw"] = 0,2000
		self.masks["dsw"] = 0,2000
		self.masks["times"] = 0,1000
		self.masks["w"] = 0, 100
		self.masks["vel"] = 0, 5000
		self.masks["mpq"] = 0, 1000
		self.masks["step"] = 0, 117
		self.masks["tof"] = 0, 1024
		self.masks["energy"] = 0, 1024
		#self.show_mask()

	def apply_mask(self):
		"""
		Apllies the filter to the mask
		"""
		mask = ones(self.raw_data.times.shape[0],bool)
		for arg in self.masks:
			mask*=(self.raw_data.__getattribute__(arg)<self.masks[arg][1])*(self.raw_data.__getattribute__(arg)>self.masks[arg][0])
		for arg in self.masks:
			self.filtered_data[arg] = 1.*self.raw_data.__getattribute__(arg)[mask]

	def get_histogram(self,arg,bin_array):
		"""
		Creates a histogram of the given data
		INPUT: arg: kind of data as a string
		       bin_array: bins as an array
		OUTPUT: histogram, histogram bins
		"""
		y,x=histogram(self.filtered_data[arg],bins=bin_array)
		return x[:-1],y

	def get_timeseries(self,arg,timeres=60.):
		"""
		Creates a histogram of the given data
		INPUT: arg: kind of data as a string
		OUTPUT: time_array, data_array, countrates
		"""
		nbins = (self.timeframe[-1][1]-self.timeframe[0][0])*24.*60./timeres
		time = linspace(self.timeframe[0][0],self.timeframe[-1][1],nbins+1)[:-1]
		bin_width = time[1]-time[0]
		
		data = zeros(nbins)
		datafreq = zeros(nbins)
		
		for tindex,t in enumerate(self.filtered_data["times"]):
			ti = int((t-self.timeframe[0][0])/bin_width)
			data[ti]+=self.filtered_data[arg][tindex]
			datafreq[ti]+=1.
		data = data/datafreq
		data[isnan(data)]=0
		return time, data, datafreq

	def get_mean_vswcounts(self,varr=linspace(280.,580.,31),w=(1.,2.),mpq=(11.,13.)):
		"""
		Derives mean countrate depending on the solar wind speed for a given mass per charge and w range.
		INPUT: varr -> array with vsw_binedges; w,mpq -> tuples (min,max)
		OUTPUT: varr (s. INPUT), mcounts -> array with mean countrates
		"""
		sys.stdout.write("Dumping pickled data ...")
		mcounts=zeros(varr.shape[0]-1)
		for i in range(varr.shape[0]-1):
			carr=[]
			self.reset_mask()
			self.set_mask("vsw",(varr[i],varr[i+1]))
			self.apply_mask()
			time=unique(self.filtered_data["times"])
			self.reset_mask()
			self.set_mask("mpq",(mpq[0],mpq[1]))
			self.set_mask("w",(w[0],w[1]))
			self.apply_mask()
			times=self.filtered_data["times"]
			for t in time:
				carr.append(times[times==t].shape[0])
			carr=array(carr)
			mcounts[i]=mean(carr)
		self.reset_mask()
		mcounts[isnan(mcounts)]=0.
		sys.stdout.write("Done\n")
		return varr,mcounts

	def get_expected_countrates(self,varr=linspace(280.,580.,31),w=(1.5,2.),mpq=(11.,13.),timeres=5.):
		v,mc=self.get_mean_vswcounts(varr,w,mpq)
		sys.stdout.write("Calculating expected counts ...")
		self.reset_mask()
		#self.set_mask("w",w)
		#self.set_mask("mpq",mpq)
		self.apply_mask()
		nbins = (self.timeframe[-1][1]-self.timeframe[0][0])*24.*60./timeres
		time = linspace(self.timeframe[0][0],self.timeframe[-1][1],nbins+1)[:-1]
		bin_width = time[1]-time[0]
		
		datafreq = zeros(nbins)

		tt=unique(self.filtered_data["times"])
		for t in tt:
			ti = int((t-self.timeframe[0][0])/bin_width)
			vi = int((self.filtered_data["vsw"][self.filtered_data["times"]==t][0]-v[0])/(v[1]-v[0]))
			if vi>=0:
				datafreq[ti]+=mc[vi]
		self.reset_mask()
		self.apply_mask()
		sys.stdout.write("Done\n")
		return time,datafreq

	def get_relative_rates(self,varr=linspace(280.,580.,31),w=(1.5,2.),mpq=(11.,13.),timeres=5.):
		t,ec=self.get_expected_countrates(varr,w,mpq,timeres)
		self.reset_mask()
		self.set_mask("mpq",mpq)
		self.set_mask("w",w)
		self.apply_mask()
		x,y,c=self.get_timeseries("w",timeres)
		self.reset_mask()
		return t,c/ec
			
if __name__=="__main__":
	test = ctof_pui_ana(dump_path="/data/etph/berger/",timeframe=[[150,230]])
	#test.set_mask("mpq",(11,13))
	#test.set_mask("w",(1.5,2.0))
	#test.apply_mask()
	t,rchel=test.get_relative_rates(w=(1.1,1.3),mpq=(3.5,4.5),timeres=24.*60.)
	t,rcheh=test.get_relative_rates(w=(2.,2.1),mpq=(3.5,4.5),timeres=24.*60.)
	t,rcol=test.get_relative_rates(w=(1.,1.3),mpq=(15.,17.),timeres=24.*60.)
	t,rcoh=test.get_relative_rates(w=(1.5,2.),mpq=(15.,17.),timeres=24.*60.)
	t,rccl=test.get_relative_rates(w=(1.,1.3),mpq=(11.,13.),timeres=24.*60.)
	t,rcch=test.get_relative_rates(w=(1.5,2.),mpq=(11.,13.),timeres=24.*60.)
	
	namesem="/data/etph/soho/celias/sem/sem_data_5m.dat"
	semin=open(namesem,"r")
	semtot=loadtxt(semin)
	semtime=1.*semtot[:,2]+1.*semtot[:,3]/(24.*60.*60)
	semfflux=1.*semtot[:,16]
	semsflux=1.*semtot[:,15]

	gp = Gnuplot()
	#gp.plot(Data(x,c,with_="lines"),Data(semtime,semfflux,with_="l lt 3"))
	gp("set xr[150,230]")
	gp("set y2tics")
	gp("set y2r[0:]")
	gp.plot(Data(t,rcol,with_="histeps"),Data(semtime,semfflux/mean(semfflux),with_="l lt 3 axis x1y2"))
