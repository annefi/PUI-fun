import sys
from libacepy.mag import magdata
from libacepy.mag import sync_mag
from libacepy.swepamdata import swepamdata,sync_h
from libacepy.swicsiondata import swicsiondata
from libacepy.swicselemdata import swicselemdata
from Gnuplot import Gnuplot,Data,GridData
from libacepy.multiplot import multiplot
from math import sqrt,atan,pi,acos,cos
from numpy import *
from mag_hist_fkt import *
from scipy import zeros



event = []
si = []
#ohne Si
event += [[6.5,7.7,9.7,11.5], [24.4,24.9,29.1,29.4], [33.7,35.1,36.5,38.9], [49.,52.9,54.6,57.], [52.4,56.4,58.2,58.8], [77.9,78.6,82.2,85.1], [95.,98.,99.,101.], [103.,107.,107.7,111.], [130.5,133.3,135.3,138.3], [148.7,152.4,153.6,154.7], [156.,158.5,159.2,160.7], [175.8,177.1,180.7,0], [252.,255.5,256.8,259.], [280.,284.2,284.8,288.], [306.,309.9,313.3,314.], [331.7,339.2,0,0], [349.,351.2,0,0]]
si += [1,0,1,0,0,0,0,1,1,0,1,1,1,1,1,1,0] #ist das kommende Si Noerdlich (1) oder Suedlich(0)?
#mit Si
event += [[0,12.0,15.2,0], [28.9,29.2,0,0], [39.5,41.0,43.5,44.0], [0,62.2,63.7,65.5], [67.4,71.,0,0], [87.7,90.5,90.9,91.2], [108.5,111.1,112.3,113.], [113.6,117.6,0,0], [123.3,125.7,127.4,127.7], [160.7,163.8,164.8,165.3], [170.1,171.8,172.3,172.4], [182.,183.5,184.7,0], [188.,190.1,191.9,0], [198.,199.1,201.4,0], [203.5,204.6,207.5,210.5], [215.7,216.9,218.5,218.9], [224.5,227.2,0,0], [242.3,244.3,0,0], [296.,297.6,298.3,298.5]]
si += [0,0,0,1,1,1,1,1,0,0,1,1,0,1,1,0,1,0,0] #ist das kommende Si Noerdlich (1) oder Suedlich(0)?

nodip = [[],[]]
dip = [[],[]]
for i  in range(len(event)):
	if (event[i][0] != 0 and event[i][1] != 0):
		nodip[si[i]].append([event[i][0],event[i][1]])
	if (event[i][1] != 0 and event[i][2] != 0):
		dip[si[i]].append([event[i][1],event[i][2]])
	if (event[i][2] != 0 and event[i][3] != 0):
		nodip[si[i]].append([event[i][2],event[i][3]])


marks = [dip[0]+dip[1],nodip[0]+nodip[1]]
marktitle = ["in","out"]

parkerwinkel = pi*0.2

mres = 240
pres = 720
sires = 3600
year = 2007
binsize = 50
bincount = 600/binsize
plotcount = 6

hist = array(zeros([plotcount,len(marks),bincount,4],float))	# hist[plot][in,out][bin][vel,value,error,count]
title = ["O7/O6","Fe/O","He2temp","O6temp","Q_{Fe}","n_{O6}"]
ranges = [[0.,0.6],[0.,0.4],[1.e4,5.e6],[1.e4,5.e7],[0.,20.],[3.e-5,1.e-2]]
log = [0,0,1,1,0,1]

data = []					#data [plot][in,out]
for i in range(plotcount+1):
	data.append([])
	for j in range(len(marks)):
		data[i].append([])
for w in range(len(marks)):
	mark = marks[w]
	
	# Anfang: Daten holen
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
		
		data[0][w] += pdata.vel
		data[1][w] += densratio(o7data,o6data)
		data[2][w] += densratio(fedata,odata)
		data[3][w] += he2data.temp
		data[4][w] += o6data.temp
		data[5][w] += fedata.meanch
		data[6][w] += o6data.dens
		
		del pdata
		del he2data
		del o6data
		del o7data
	# Ende: Daten holen
	
	# Anfang: Values bestimmen (Mittelwert)
	for i in range(len(data[0][w])):
		bin = int(data[0][w][i][1]/binsize)
		if (data[1][w][i][1] > 1e-20):
			hist[0,w,bin,1] += data[1][w][i][1]	#o7/o6
			hist[0,w,bin,3] += 1
		if (data[2][w][i][1] > 1e-20):
			hist[1,w,bin,1] += data[2][w][i][1]	#feo
			hist[1,w,bin,3] += 1
		if (data[3][w][i][0] > 1e-20):
			hist[2,w,bin,1] += data[3][w][i][0]	#he2temp
			hist[2,w,bin,3] += 1
		if (data[4][w][i][0] > 1e-20):
			hist[3,w,bin,1] += data[4][w][i][0]	#o6temp
			hist[3,w,bin,3] += 1
		if (data[5][w][i][1] > 1e-20):
			hist[4,w,bin,1] += data[5][w][i][1]	#fe meanch
			hist[4,w,bin,3] += 1
		if (data[6][w][i][0] > 1e-20):
			hist[5,w,bin,1] += data[6][w][i][0]	#o6dens
			hist[5,w,bin,3] += 1
	
	for i in range(len(hist)):
		for b in range(len(hist[i,w,:,1])):
			if hist[i,w,b,3] > 1e-20:
				hist[i,w,b,1] /= hist[i,w,b,3]
	# Ende: Values bestimmen (Mittelwert)
	
	# Anfang: Standartabweichung bestimmen
	sum = array(zeros([plotcount,bincount],float))
	for p in range(len(hist)):
		for i in range(len(data[0][w])):
			bin = int(data[0][w][i][1]/binsize)
			sum[p,bin] += (data[p+1][w][i][1]-hist[p,w,bin,1])**2
		for i in range(len(sum[p])):
			hist[p,w,i,2] = sqrt(sum[p,i] / ((hist[p,w,i,3])**2))
	# Ende: Standartabweichung bestimmen
	
	# Anfang: Geschwindigkeiten anfügen
	for p in range(len(hist)):
		hist[p,w,:,0] = linspace(0,(bincount-1)*binsize,bincount) + binsize/2
	# Ende: Geschwindigkeiten anfügen



mp = multiplot(plotcount+1,1)
mpi = 0
mp.setgv(1)
mp.setxlabel("Geschwindigkeitsbins")
mp.setxrange(200,bincount*binsize)

#Anfang: Panels plotten
for p in range(len(hist)):
	for w in range(len(marks)):
		plotdata = Data(hist[p,w,:,0:3])
		plotdata.set_option_colonsep("title","'"+title[p]+" "+marktitle[w]+"'")
		plotdata.set_option_colonsep("with","yerrorline")
		mp.panel[mpi].adddata(plotdata)
	mp.panel[mpi].setyrange(ranges[p][0],ranges[p][1])
	mp.panel[mpi].setlogscale(log[p])
	del plotdata
	mpi += 1
#Ende: Panels plotten

#Anfang: Counts plotten
plotdata = Data(zip(hist[0,0,:,0],hist[0,0,:,3]))
mp.panel[mpi].adddata(plotdata)
plotdata = Data(zip(hist[0,1,:,0],hist[0,1,:,3]))
mp.panel[mpi].adddata(plotdata)
mp.panel[mpi].setyrange(1,900)
mp.panel[mpi].setlogscale(1)
del plotdata
#Ende: Counts plotten

mp.plot()