import sys
from libacepy.mag import magdata
from libacepy.mag import sync_mag
from libacepy.swepamdata import swepamdata,sync_h
from libacepy.swicsiondata import swicsiondata
from libacepy.swicselemdata import swicselemdata
from Gnuplot import Gnuplot,Data
from libacepy.multiplot import multiplot
from math import sqrt,atan,pi,acos,cos
from numpy import array

def get_mag_angle(mdata,mark):
	test = []
	tmp = []
	for i in range(24*8):
		test.append(0)
		tmp.append(0)
	
	for i in range(len(mdata.magbx)):
		# Anfang: Winkel ausrechnen
		if (mdata.magbx[i][1] < 0):
			phi = atan(-mdata.magby[i][1]/mdata.magbx[i][1])
		elif (mdata.magbx[i][1] == 0):
			if (mdata.magby[i][1] > 0):
				phi = pi/2
			elif (mdata.magby[i][1] < 0):
				phi = -pi/2
			else:
				phi = 0
		else:
			phi = pi - atan(mdata.magby[i][1]/mdata.magbx[i][1])
		# Ende: Winkel ausrechnen
		
		time = int((mdata.time[i]-mark+4)*24)-1
		tmp[time] += phi
		test[time] += 1
		
	for i in range(24*8):
		if (test[i] > 0):
			tmp[i] /= test[i]
	
	return tmp

def get_proton_velocity(pdata,mark):
	test = []
	tmp = []
	for i in range(24*8):
		test.append(0)
		tmp.append(0)
		
	for i in range(len(pdata.vel)):
		time = int((pdata.time[i]-mark+4)*24)-1
		tmp[time] += pdata.vel[i][1]
		test[time] += 1
		
	for i in range(24*8):
		if (test[i] > 0):
			tmp[i] /= test[i]
	
	return tmp

def get_proton_temperatur(pdata,mark):
	test = []
	tmp = []
	for i in range(24*8):
		test.append(0)
		tmp.append(0)
		
	for i in range(len(pdata.temp)):
		time = int((pdata.time[i]-mark+4)*24)-1
		tmp[time] += pdata.temp[i][1]
		test[time] += 1
		
	for i in range(24*8):
		if (test[i] > 0):
			tmp[i] /= test[i]
	
	return tmp

def densratio (data1,data2):
	dens1 = []
	if data1.__class__ == swicsiondata:
		for i in range(len(data1.dens)):
			dens1.append(data1.dens[i][0])
	if data1.__class__ == swicselemdata:
		for i in range(len(data1.dens)):
			dens1.append(data1.dens[i][1])
	if data1.__class__ == swepamdata:
		for i in range(len(data1.dens)):
			dens1.append(data1.dens[i][1])
	dens2 = []
	if data2.__class__ == swicsiondata:
		for i in range(len(data2.dens)):
			dens2.append(data2.dens[i][0])
	if data2.__class__ == swicselemdata:
		for i in range(len(data2.dens)):
			dens2.append(data2.dens[i][1])
	if data2.__class__ == swepamdata:
		for i in range(len(data2.dens)):
			dens2.append(data2.dens[i][1])
	
	if (len(dens1) != len(dens2)):
		print "Error in densratio(): dens-lists have differend lenght"
		return []
	
	ratio = []
	for i in range(len(dens1)):
		if (dens2[i] != 0):
			ratio.append([data1.time[i],dens1[i]/dens2[i]])
		else:
			ratio.append([data1.time[i],0])
	return ratio

def get_densratio (data1,data2,mark):
	ratio = densratio (data1,data2)
	
	test = []
	tmp = []
	ret = []	
	for i in range(24*8):
		test.append(0)
		tmp.append(0)
		ret.append(0)
		
	for i in range(len(data1.time)):
		time = int((ratio[i][0]-mark+4)*24)-1
		tmp[time] += ratio[i][1]
		test[time] += 1
	
	for i in range(24*8):
		if (test[i] > 0):
			tmp[i] /= test[i]
	
	return tmp

def get_veldiff (data1,data2,mark):
	vel1 = []
	if data1.__class__ == swicsiondata:
		for i in range(len(data1.vel)):
			vel1.append(data1.vel[i])
	if data1.__class__ == swepamdata:
		for i in range(len(data1.vel)):
			vel1.append(data1.vel[i][1])
	vel2 = []
	if data2.__class__ == swicsiondata:
		for i in range(len(data2.vel)):
			vel2.append(data2.vel[i])
	if data2.__class__ == swepamdata:
		for i in range(len(data2.vel)):
			vel2.append(data2.vel[i][1])
	test = []
	tmp = []
	ret = []
	for i in range(24*8):
		test.append(0)
		tmp.append([0,0])
		ret.append(0)
	
	for i in range(len(data1.time)):
		time = int((data1.time[i]-mark+4)*24)-1
		tmp[time][0] += vel1[i]
		tmp[time][1] += vel2[i]
		test[time] += 1
	
	for i in range(24*8):
		if (test[i] > 0 and test[i] > 0):
			ret[i] += tmp[i][0]/test[i] - tmp[i][1]/test[i]
	return ret

def get_magb (mdata,mark):
	test = []
	tmp = []
	for i in range(24*8):
		test.append(0)
		tmp.append(0)
	
	for i in range(len(mdata.magb)):		
		time = int((mdata.time[i]-mark+4)*24)-1
		tmp[time] += mdata.magb[i][1]
		test[time] += 1
	
	for i in range(24*8):
		if (test[i] > 0):
			tmp[i] /= test[i]
	return tmp

def get_dens (data,mark):
	dens = []
	if data.__class__ == swicsiondata:
		for i in range(len(data.dens)):
			dens.append(data.dens[i][0])
	if data.__class__ == swepamdata:
		for i in range(len(data.dens)):
			dens.append(data.dens[i][1])
	
	test = []
	tmp = []
	for i in range(24*8):
		test.append(0)
		tmp.append(0)
	
	for i in range(len(data.time)):		
		time = int((data.time[i]-mark+4)*24)-1
		tmp[time] += dens[i]
		test[time] += 1
	
	for i in range(24*8):
		if (test[i] > 0):
			tmp[i] /= test[i]
	return tmp