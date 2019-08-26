import sys
from libacepy.mag import magdata
from libacepy.mag import sync_mag
from libacepy.swepamdata import swepamdata,sync_h
from libacepy.swicsiondata import swicsiondata
from libacepy.swicselemdata import swicselemdata
from Gnuplot import Gnuplot,Data,GridData
from libacepy.multiplot import multiplot
from math import sqrt,atan,pi,acos,cos
from numpy import array
from mag_hist_fkt import *

nodip = []
nodip += [[6.5,7.7],[9.7,11.5],[23.,26.4],[33.7,35.1],[36.5,38.9],[82.2,84.2],[95.,98.],[98.9,99.3],[103.,107.],[107.7,113.],[149.,152.4],[153.6,155.7],[156.,158.5],[159.2,163.],[197.5,199.],[201.3,201.8],[252.,254.6],[256.8,259.],[285.2,288.]]
dip = []
dip += [[7.7,9.7],[35.1,36.5],[78.4,82.2],[152.4,153.6],[158.5,159.2],[199.,201.3]]

#mark = nodip
mark = dip

parkerwinkel = pi*0.2

mres = 240
pres = 720
sires = 3600
year = 2007
x_binsize = 0.001
y_binsize = 0.03

def get_hist_x_over_y (x,y,x_binsize = 0.001,y_binsize = 0.03):
	blub = []
	for i in range(len(x)):
		x_index = int(x[i]/x_binsize)
		y_index = int(y[i]/y_binsize)
		if (x_index < 0 or y_index < 0):
			continue
		while (len(blub) <= x_index):
			blub.append([])
		while (len(blub[x_index]) <= y_index):
			blub[x_index].append(0)
		blub[x_index][y_index] += 1
	return blub


hist = []
x_max = []
y_max= []
for m in range(len(mark)):
	print "Mark "+str(m+1)+" von "+str(len(mark))
	timeframe = [mark[m][0],mark[m][1]]
	he2data = swicsiondata("He2+",[timeframe],"/data/wimmer/ace/1hdata/"+str(year)+"/")
	he2data.load()
	o6data = swicsiondata("O6+",[timeframe],"/data/wimmer/ace/1hdata/"+str(year)+"/")
	o6data.load()
	o7data = swicsiondata("O7+",[timeframe],"/data/wimmer/ace/1hdata/"+str(year)+"/")
	o7data.load()
	pdata = swepamdata(pres,year,timeframe[0],timeframe[1],"/data/ivar/ace/swepam/")
	pdata.load()
	pdata = sync_h(pdata,he2data)
	odata = swicselemdata("O",[timeframe],"/data/wimmer/ace/1hdata/"+str(year)+"/")
	odata.load()
	fedata = swicselemdata("Fe",[timeframe],"/data/wimmer/ace/1hdata/"+str(year)+"/")
	fedata.load()
	
	he2_h = array(densratio(he2data,pdata))
	fe_o = array(densratio(fedata,odata))
	
	x_max.append(max(he2_h[:,1]))
	y_max.append(max(fe_o[:,1]))
	
	tmp = get_hist_x_over_y(he2_h[:,1],fe_o[:,1])
	while (len(hist) < len(tmp)):
		hist.append([])
	for i in range(len(tmp)):
		while (len(hist[i]) < len(tmp[i])):
			hist[i].append(0)
		for j in range(len(tmp[i])):
			hist[i][j] += tmp[i][j]
	
	del pdata
	del he2data
	del o6data
	del o7data

x_max = max(x_max)
y_max = max(y_max)

y_max_len = []
for i in range(len(hist)):
	y_max_len.append(len(hist[i]))
y_max_len = max(y_max_len)
for i in range(len(hist)):
	while (len(hist[i]) < y_max_len):
			hist[i].append(0)

x_label = []
akt = 0.
while (akt < x_max):
	x_label.append(akt)
	akt += x_binsize
y_label = []
akt = 0.
while (akt < y_max):
	y_label.append(akt)
	akt += y_binsize

gp = Gnuplot()
gpdata=GridData(hist,x_label,y_label,binary=0)
gp("set pm3d at bs map explicit corners2color c1")

gp("set palette model RGB functions gray<1.e-20 ? 1 : gray<0.5 ? gray*2 : 1 , gray<1.e-20 ? 1 : gray<0.5 ? gray*2 : 2-gray*2, gray <1.e-20 ? 1 : gray<0.5 ? 1-sqrt(gray*2) : 0")
gp.splot(gpdata)
