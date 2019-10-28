from pylib import dbData
import numpy
import os
from pylib.etMisc import loading_bar 
import math
import time
import pylab
#from Programme.Swoops.swoops_data import *
from Programme.functions import *

class mag_loader(dbData):
	def load_data(self, start_date=(1991,1), end_date=(1991,10), path="/data/et068/data_umag/umag_1sec/", data_keys=["dom_mag", "Br", "Bt", "Bn",'Babs']):
		data = {}
		days = (((end_date[0]-start_date[0])-1)*365)+end_date[1]+365-start_date[1]
		I = 0
		print "loading (loading bar by christian)"
		for keys in data_keys:
			data[keys]=[]
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
					raw_data = numpy.loadtxt(file_name,unpack=True, skiprows=1)
					for i,key in enumerate(data_keys):
						data[key].append(raw_data[i])
		for key in data:
			for i, element in enumerate(data[key]):
				if type(element) == numpy.float64:
					data[key].pop(i)
			self.data[key] = numpy.concatenate(data[key])
			data[key][:] = []


	
#def refine_umag_data():
	#load_path = "/data/et068/data_umag/umag_1sec_unsorted/"
	#save_path = "/data/et068/data_umag/umag_1sec/"
	#header = 'dom\tB_r\tB_t\tB_n\tB_abs'
	#folders = os.listdir('%s'%(load_path))
	#leap_years = numpy.array([1992, 1996, 2000, 2004, 2008])
	#for folder in folders:
		#if folder[2] == '9':
			#save_folder = '19%s'%(folder[2:4])
		#else:
			#save_folder = '20%s'%(folder[2:4])
		#print save_folder
		#files = os.listdir('%s%s/'%(load_path, folder))
		#year_offeset = (int(save_folder)-1990)*365+len(leap_years[leap_years<int(save_folder)])
		#for filename in files:
			#o = open('%s%s/%s'%(load_path, folder, filename), 'r')
			#save_file = '%s%s/%s'%(save_path, save_folder, filename)
			#if os.path.exists('%s%s/'%(save_path, save_folder)) == False:
				#os.mkdir('%s%s/'%(save_path, save_folder))
			#s = open('%s'%(save_file), 'w')
			#s.write(header+'\n')
			#for line in o:
				#l = line.split()
				#if len(l) != 0:
					#new_time = time.gmtime(int(l[0]))
					#if int(new_time[0])-20 == int(save_folder):
						#dom = new_time[7]+new_time[3]/24.+new_time[4]/(24.*60)+new_time[5]/(24.*60*60)+year_offeset
					#elif int(new_time[0])-20 < int(save_folder):
						#dom = new_time[7]+new_time[3]/24.+new_time[4]/(24.*60)+new_time[5]/(24.*60*60)+year_offeset+365
					#new_line = str(dom)+'\t'+l[1]+'\t'+l[2]+'\t'+l[3]+'\t'+l[4]
					#s.write(new_line+'\n')
				
			#o.close()
			#s.close()

def refine_umag_data():
	load_path = "/data/et068/data_umag/umag_1sec_unsorted/"
	save_path = "/data/et068/data_umag/umag_1sec/"
	header = 'dom\tB_r\tB_t\tB_n\tB_abs'
	folders = os.listdir('%s'%(load_path))
	folders = numpy.arange(1990, 2010, 1)
	folders_done = [2006, 1992, 2001, 1996, 2002]
	for folder in folders:
		if folder in folders_done:
			continue
		#if folder[2] == '9':
			#save_folder = '19%s'%(folder[2:4])
		#else:
			#save_folder = '20%s'%(folder[2:4])
		print folder
		files = os.listdir('%s%s/'%(load_path, folder))
		for filename in files:
			o = open('%s%s/%s'%(load_path, folder, filename), 'r')
			save_file = '%s%s/%s'%(save_path, folder, filename)
			if os.path.exists('%s%s/'%(save_path, folder)) == False:
				os.mkdir('%s%s/'%(save_path, folder))
			s = open('%s'%(save_file), 'w')
			s.write(header+'\n')
			for line in o:
				l = line.split()
				if len(l) == 0:
					continue
				dom = calc_dom_old(int(folder), int(l[1]))+float(l[2])/24.+float(l[3])/24./60.+float(l[4])/24./60./60.
				s.write('%6f\t%s\t%s\t%s\t%s\n'%(dom, l[5], l[6], l[7], l[8]))
			o.close()
			s.close()

			
def slim_umag_data():
	path = '/data/et068/data_umag/umag_1sec/'
	save_path = '/data/et068/data_umag/umag_2min/'
	#folders = numpy.arange(1990, 2010, 1)
	folders = numpy.append(numpy.arange(1991, 1995,1), numpy.arange(1996, 2010,1))
	header = 'dom\tB_r\tB_t\tB_n\tB_abs'
	for folder in folders:
		if os.path.exists('%s%s'%(save_path, folder)) == False:
			os.mkdir('%s%s/'%(save_path, folder))
		files = os.listdir('%s%s/'%(path, folder))
		for day in files:
			data = numpy.loadtxt('%s%s/%s'%(path, folder, day), skiprows = 1)
			if len(data) != 0: 
				slim_data = data[::120]
				o = open('%s%s/%s'%(save_path, folder, day), 'w')
				o.write('%s\n'%(header))
				numpy.savetxt(o, slim_data, fmt=['%6f', '%3f', '%3f', '%3f', '%3f'])
			o.close()



def average_umag_data():
	path_umag = "/data/et068/data_umag/umag/"
	path_save = '/data/et068/data_umag/umag_13min_averaged/'
	years = numpy.arange(1990, 2010,1)
	header = 'dom	Babs\tBabs_std\tBr\tBr_std\tBt\tBt_std\tBn\tBn_std\tBlon\tBazi'
	margin = 14
	for year in years:
		days = os.listdir('%s%s/'%(path_umag, year))
		if os.path.exists('%s%s'%(path_save, year)) == False:
			os.mkdir('%s%s/'%(path_save, year))
		for day in days:
			file_umag = '%s%s/%s'%(path_umag, year, day)
			file_save = '%s%s/%s'%(path_save, year, day)
			s = open(file_save, 'w')
			s.write(header+'\n')
			data_umag = numpy.loadtxt(file_umag, skiprows = 1)
			if len(data_umag) == 0:
				continue
			babs_av , t_abs = create_sliding_average(data_umag[:,4], margin)
			br_av, t_r = create_sliding_average(data_umag[:,1], margin)
			bt_av, t_t = create_sliding_average(data_umag[:,2], margin)
			bn_av, t_n = create_sliding_average(data_umag[:,3], margin)
			array_to_save = numpy.column_stack((data_umag[:,0], babs_av, br_av, bt_av, bn_av))
			angles = numpy.zeros(2)
			for row in array_to_save:
				blon, bazi = calc_magnetic_field_angle_(row[1], row[3], row[5], row[7])
				angles = numpy.row_stack((angles, [blon, bazi]))
			angles = numpy.delete(angles, 0,0)
			array_to_save = numpy.column_stack((array_to_save, angles))
			numpy.savetxt(s, array_to_save, fmt = ['%.9f', '%.3f', '%.4f', '%.3f', '%.4f', '%.3f', '%.4f', '%.3f', '%.4f', '%.1f', '%.1f'])
			t_total = t_abs+t_r+t_t+t_n
			s.close()
			print '%s of year %s done, it took me %f seconds'%(day[0:3], year, t_total)
			

def pick_swics_timestamps():
	header = 'dom	Babs	Babs_std	Br	Br_std	Bt	Bt_std	Bn	Bn_std'
	path_swics = '/data/et068/data_swics/'
	path_umag = '/data/et068/data_umag/umag_13min_averaged/'
	path_save = '/data/et068/data_umag/umag_13min_averaged_picked/'
	years = numpy.arange(1990, 2010, 1)
	for year in years:
		print year
		if os.path.exists('%s%s'%(path_save, year)) == False:
			os.mkdir('%s%s/'%(path_save, year))
		days = os.listdir('%s%s/'%(path_swics, year))
		for day in days:
			file_swics = '%s%s/%s'%(path_swics, year, day)
			file_umag = '%s%s/%s.dat'%(path_umag, year, day[0:3])
			file_save = '%s%s/%s.dat'%(path_save, year, day[0:3])
			if os.path.isfile(file_umag) == False:
				continue
			swics_timestamp = numpy.unique(numpy.loadtxt(file_swics, skiprows = 1, usecols = [1]))
			umag_data = numpy.loadtxt(file_umag, skiprows = 1)
			indices = numpy.searchsorted(umag_data[:,0], swics_timestamp)
			indices[indices == len(umag_data)] = -1
		 	umag_data_picked = umag_data[indices]
			s = open(file_save, 'w')
			s.write(header+'\n')
			numpy.savetxt(s, umag_data_picked, fmt = ['%.9f', '%.3f', '%.4f', '%.3f', '%.4f', '%.3f', '%.4f', '%.3f', '%.4f'])
			s.close()
			print file_save

#swoops_indices[swoops_indices == len(swoops_data['dom_swo'])] = -1
			
def create_sliding_average(data_U, margin_U):
	data_aver = numpy.copy(data_U)*0
	data_aver = numpy.column_stack((data_aver, numpy.zeros(len(data_aver))))
	runtime = 0
	for i, line in enumerate(data_U):
		time_s = time.time()
		start_index = i-margin_U
		stop_index = i+margin_U
		if start_index < 0:
			start_index = 0
		data_to_average = data_U[start_index:stop_index+1]
		d_mean = numpy.mean(data_to_average, 0)
		d_std = numpy.std(data_to_average, 0)
		data_aver[i, 0] = d_mean
		data_aver[i, 1] = d_std
		time_e = time.time()
		runtime=runtime+(time_e-time_s)
	return data_aver, runtime
	

def calc_magnetic_field_angle(babs, br, bt, bn):
	d = 180./math.pi
	longitude = d*deter_angle(-1.*br, bt)
	azimuth = d*deter_angle(bn, babs)
	return longitude, azimuth
	
def calc_magnetic_field_angle_(babs, br, bt, bn):
	'''
	calculates the magnetic field angle from 0 to 360 degree. 90 degree points towards the sun and 270 degree away from the sun. 180 degree point in the Bt direction 
	'''
	d = 180./math.pi
	def deter_angle_intern(br, bt):
		if br == 0 and bt == 0:
			angle = 0
		elif bt >= 0 and br >= 0:
			angle = numpy.arcsin(br/(numpy.sqrt(br**2+bt**2)))+numpy.pi
		elif bt < 0 and br >= 0:
			angle = numpy.arcsin(numpy.abs(bt)/(numpy.sqrt(br**2+bt**2)))+3*numpy.pi/2
		elif bt >= 0 and br < 0:
			angle = numpy.arcsin(numpy.abs(bt)/(numpy.sqrt(br**2+bt**2)))+numpy.pi/2
		elif bt < 0 and br < 0:
			angle = numpy.arccos(numpy.abs(bt)/(numpy.sqrt(br**2+bt**2)))
		return(angle)
	def deter_azi(babs, bn):
		if bn >= 0:
			azi = numpy.arccos(bn/babs)
		if bn < 0:
			azi = numpy.arcsin(numpy.abs(bn)/babs)+numpy.pi/2
		return(azi)
	longitude = d*deter_angle_intern(br, bt)
	azimuth = d*deter_azi(babs, bn)
	return longitude, azimuth
	

	
	
def plot_mag_field(data_U, time = 'dom_swo', mask_U = 'Master'):
	x = data_U.get_data(mask_U, time)
	y = numpy.zeros(len(x))
	br = data_U.get_data(mask_U, 'Br')
	bt = data_U.get_data(mask_U, 'Bt')
	pylab.figure()
	pylab.quiver(x, y, br, bt, scale = 50, units = 'y')


