from pylib import dbData
import numpy
import os
from pylib.etMisc import loading_bar 
import math
import time
import pylab




class umag_loader():
	def __init__(self):
		self.data = {}

	def load_data(self, start_date=(1991,1), end_date=(1992,1), path="data/et068/data_umag/umag_1sec/", data_keys=['dom_mag', 'Br', 'Bt', 'Bn', 'Babs']):
		days = (((end_date[0]-start_date[0])-1)*365)+end_date[1]+365-start_date[1]
		I = 0
		for keys in data_keys:
			self.data[keys]=[]
		for y in range (start_date[0], end_date[0]+1):
			start_day=1
			end_day=367
			if y == start_date[0]:
				start_day = start_date[1]
			if y == end_date[0]:
				end_day=end_date[1]
			for d in range(start_day,end_day+1):
				file_name="%s%d/%03d.dat"%(path,y,d)
				loading_bar(days, I, "#")
				I+=1
				if os.path.isfile(file_name):
					raw_data = numpy.loadtxt(file_name,unpack=True, skiprows = 1)
					if isinstance(raw_data[0],numpy.ndarray):
						for i,key in enumerate(data_keys):
							self.data[key]+=list(raw_data[i])
					else:
						for i,key in enumerate(data_keys):
							self.data[key].append(raw_data[i])
		return self.data
		
class umag_loader_direct_use(dbData):
	def load_data(self, start_date=(1991,1), end_date=(1992,1), path="/data/et068/data_umag/umag_1sec/", data_keys=['dom_mag', 'Br', 'Bt', 'Bn', 'Babs']):
		print 'k'
		days = (((end_date[0]-start_date[0])-1)*365)+end_date[1]+365-start_date[1]
		I = 0
		data = {}
		for keys in data_keys:
			data[keys] = []
		for y in range (start_date[0], end_date[0]+1):
			start_day = 1
			end_day = 367
			if y == start_date[0]:
				start_day = start_date[1]
			if y == end_date[0]:
				end_day=end_date[1]
			for d in range(start_day,end_day+1):
				file_name="%s%d/%03d.dat"%(path,y,d)
				loading_bar(days, I, "#")
				I+=1
				if os.path.isfile(file_name):
					raw_data = numpy.loadtxt(file_name,unpack=True, skiprows = 1)
					if isinstance(raw_data[0],numpy.ndarray):
						for i,key in enumerate(data_keys):
							data[key].append(raw_data[i])
		for key in data:
			self.data[key] = numpy.concatenate(data[key])
			data[key][:] = []
