from libacepy.swepamdata import swepamdata,sync_h
from libacepy.swicsiondata import swicsiondata
from libacepy.swicselemdata import swicselemdata
from numpy import array
import sys

class data:
	def __init__(self,name,timeframe,path,source = "swics",res = 0,year = 0):
		self.name = name
		self.timeframe = timeframe
		self.path = path
		self.source = source
		self.res = res
		self.year = year
		
		self.error = False
		self.datatype = ""
		
		self.check_source()
		self.check_res()
		self.check_year()
		self.check_name()
		self.check_timeframe()
		self.check_path()
		if self.error == False:
			self.load()
		else
			del self
	
	def get_dens (self):
		if (self.datatype == "element"):
			if (self.source == "swics"):
				return array(self.data.dens)
		elif (self.datatype == "ion"):
			if (self.source == "swepam"):
				return array(self.data.dens)
			if (self.source == "swics"):
				return array(zip(array(self.data.time),array(self.data.dens)[:,0]))
	
	def sync_with (self,other):
		if (self.datatype != "swepam" or type(other) != instance or other.__class__ != "data" or other.datatype != "swepam"):
			print "data.sync_with : this routine is only to sync swepam with swics data"
			return
		self.data = sync_h(self.data,other.data)
	
	def load (self):
		if (self.datatype == "element"):
			if (self.source == "swics"):
				self.data = swicselemdata (self.name,self.timeframe,self.path)
				self.data.load()
		elif (self.datatype == "ion"):
			if (self.source == "swics"):
				self.data = swicsiondata (self.name,self.timeframe,self.path)
				self.data.load()
			if (self.source == "swepam"):
				self.data = swepamdata (self.res,self.year,self.timeframe[0][0],self.timeframe[0][1],self.path)
				self.data.load()
	
	def check_name (self):
		i = 0
		if (len (self.name) == 0 or self.name[i].isalpha() == False):
			self.error = True
			print "Wrong ion/element name is given"
			return
		i += 1
		
		if (len(self.name) > 1 and self.name[i].isalpha() == True):
			i += 1
		
		if (len(self.name) == i):
			self.datatype = "element"
		else:
			if (self.name[i].isdigit() == False or len(self.name)<=(i+1) or self.name[i+1] != "+"):
				self.error = True
				print "Wrong ion/element name is given"
				return
			i += 2
			if (len(self.name) == i):
				self.datatype = "ion"
	
	def check_timeframe (self):
		if type(self.timeframe) != list or len(self.timeframe) < 1:
			self.error = True
			print "illegal timeframe is given"
			return
		for i in range(len(self.timeframe)):
			if type(self.timeframe[i]) != list or len(self.timeframe[i]) != 2 or type(self.timeframe[i][0]) != float or type(self.timeframe[i][1]) != float:
				self.error = True
				print "illegal timeframe is given"
				return
	
	def check_path (self):
			#hier sollte noch was hin
		return
	
	def check_res (self):
			#hier sollte noch was hin
		return
	
	def check_year (self):
			#hier sollte noch was hin
		return
	
	def check_source (self):
		if (self.source != "swics" and self.source != "swepam"):
			print "source type is not supported"
			self.error = True
			return
		return

#if (len(sys.argv)>1):
#	string = sys.argv[1]
arr = [[1.,23.]]
bla = data("H",arr,"")