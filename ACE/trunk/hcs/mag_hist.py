"""
Dieses Script bildet eine Mittelung aus allen im Array 'mark' enthaltenen Ereignissen (+-4Tage)
Wenn ein Parameter übergeben wird, dann wird nur der einzelne übergebene Zeitpunkt geplottet
"""

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
from mag_hist_fkt import *

mark = []
#aufsteigenede swaps ohne si
mark += [8.0,26.4,35.1,53.,81.1,107.,133.5,159.,200.1,255.4,284.,310.,335.2]
#absteigenede swaps ohne si
mark += [82.4,99.,152.7]
#aufsteigenede swaps mit si drauf
#mark += [90.9,143.5,172.7,210.4]
#absteigenede swaps mit si drauf
#mark += [15.2,29.2,43.5,112.5,127.3,138.2,179.8,192.,207.5,324.2]
#aufsteigende swaps mit si daneben
#mark += [62.5,116.5,184.2,227.,297.8]
#absteigende swaps mit si daneben
#mark += [56.5,70.6,164.7,217.7,244.,270.5]



event = []
#ohne Si
event += [[6.5,7.7,9.7,11.5], [24.4,24.9,29.1,29.4], [33.7,35.1,36.5,38.9], [49.,52.9,54.6,57.], [52.4,56.4,58.2,58.8], [77.9,78.6,82.2,85.1], [95.,98.,99.,101.], [103.,107.,107.7,111.], [130.5,133.3,135.3,138.3], [148.7,152.4,153.6,154.7], [156.,158.5,159.2,160.7], [175.8,177.1,180.7,0], [252.,255.5,256.8,259.], [280.,284.2,284.8,288.], [306.,309.9,313.3,314.], [331.7,339.2,0,0], [349.,351.2,0,0]]
#mit Si
event += [[0,12.0,15.2,0], [28.9,29.2,0,0], [39.5,41.0,43.5,44.0], [0,62.2,63.7,65.5], [67.4,71.,0,0], [87.7,90.5,90.9,91.2], [108.5,111.1,112.3,113.], [113.6,117.6,0,0], [123.3,125.7,127.4,127.7], [160.7,163.8,164.8,165.3], [170.1,171.8,172.3,172.4], [182.,183.5,184.7,0], [188.,190.1,191.9,0], [198.,199.1,201.4,0], [203.5,204.6,207.5,210.5], [215.7,216.9,218.5,218.9], [224.5,227.2,0,0], [242.3,244.3,0,0], [296.,297.6,298.3,298.5]]

ionnames = ["He2+","O6+","O7+"]

parkerwinkel = pi*0.2

mres = 240
pres = 720
sires = 3600

bintime = 4*3600
year = 2007

#Multiplotklasse initialisieren
mp=multiplot(7,1)
mp.setgv(1)
mp.setxlabel("Tage relativ zum Ereignis")
mp.setxrange(-4,+4)
mpi = 0

# parameteuebergabe zum plotten eines einzelnen ereignisses
if (len(sys.argv)>1):
	del mark
	mark = [float(sys.argv[1])]
	mp.setgv(0)
	mp.settitle("Ereignis "+str(mark[0]))
	
	#dips einzeichnen
	for i in range(len(event)):
		mp.addplotmark("vline")
		mp.plotmarks[4*i].setvlinepos(event[i][0]-mark[0])
		mp.addplotmark("vline")
		mp.plotmarks[4*i+1].setvlinepos(event[i][1]-mark[0])
		mp.addplotmark("vline")
		mp.plotmarks[4*i+2].setvlinepos(event[i][2]-mark[0])
		mp.addplotmark("vline")
		mp.plotmarks[4*i+3].setvlinepos(event[i][3]-mark[0])


# daten[{plot}][{zeitindex}][zeit.wert]
daten = [[],[],[],[],[],[],[],[],[],[],[],[],[]]
title = ["{/Symbol F}_B","v_p","T_p","O7/O6","O6/He2","He2+/H+","O6+/H+","v_{He2+} - v_{H+}","v_{O6+} - v_{H+}","|B|","n_p","Fe/O","O/H"]
log = [0,0,0,1,0,0,1,0,0,0,0,0,0]
for i in range(24*8):
	for j in range(len(daten)):
		daten[j].append([-4.+i/24.,0])

daten = array(daten)

for m in range(len(mark)):
	print "Mark "+str(m+1)+" von "+str(len(mark))
	timeframe = [mark[m]-4,mark[m]+4]
	mdata = magdata(mres,year,timeframe[0],timeframe[1],"/data/ivar/ace/mag/")
	mdata.load()
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
	
	
	#Magnetfeldwinkel
	tmp = array(get_mag_angle(mdata,mark[m]))
	daten[0,:,1] += tmp[:]
	
	#Protonen v und T
	tmp = array(get_proton_velocity(pdata,mark[m]))
	daten[1,:,1] += tmp[:]
	tmp = array(get_proton_temperatur(pdata,mark[m]))
	daten[2,:,1] += tmp[:]
	
	
	# Verhaeltnis O7/O6, O6/He2, He2/H und O6/H
	tmp = array(get_densratio(o7data,o6data,mark[m]))
	daten[3,:,1] += tmp[:]
	tmp = array(get_densratio(o6data,he2data,mark[m]))
	daten[4,:,1] += tmp[:]
	tmp = array(get_densratio(he2data,pdata,mark[m]))
	daten[5,:,1] += tmp[:]
	tmp = array(get_densratio(o6data,pdata,mark[m]))
	daten[6,:,1] += tmp[:]
		
	#Differenz v_He2 - v_H und v_O6 - v_H
	tmp = array(get_veldiff(he2data,pdata,mark[m]))
	daten[7,:,1] += tmp[:]
	tmp = array(get_veldiff(o6data,pdata,mark[m]))
	daten[8,:,1] += tmp[:]
	
	#Magnetfeldstaerke
	tmp = array(get_magb(mdata,mark[m]))
	daten[9,:,1] += tmp[:]
	
	#Absolute Protonendichte
	tmp = array(get_dens(pdata,mark[m]))
	daten[10,:,1] += tmp[:]
	
	#Verhaeltnis Fe/O und O/H
	tmp = array(get_densratio(fedata,odata,mark[m]))
	daten[11,:,1] += tmp[:]
	tmp = array(get_densratio(odata,pdata,mark[m]))
	daten[12,:,1] += tmp[:]
	
	del mdata
	del pdata
	del he2data
	del o6data
	del o7data


if len(mark) > 0:
	daten[:,:,1] /= len(mark)

for i in [1,2,10,5,3,11,12]:
	plotdata = Data(daten[i])
	plotdata.set_option_colonsep("title","'"+title[i]+"'")
	if (log[i]):
		unten = 0.3*min(daten[i,:24*8-3,1])
		oben = 3.*max(daten[i,:24*8-3,1])
	else:
		unten = min(daten[i,:24*8-3,1]) - 0.3*abs(min(daten[i,:24*8-3,1]))
		oben = max(daten[i,:24*8-3,1]) + 0.3*abs(min(daten[i,:24*8-3,1]))
	
	if (title[i] == "v_p"):
		unten = 250
	
	mp.panel[mpi].setyrange(unten,oben)
	mp.panel[mpi].adddata(plotdata)
	mp.panel[mpi].setlogscale(log[i])
	mpi += 1
	del plotdata
"""
# Geschwindigkeitsdiffernzen
plotdata = Data(daten[7])
plotdata.set_option_colonsep("title","'"+title[7]+"'")
mp.panel[mpi].adddata(plotdata)
plotdata = Data(daten[8])
plotdata.set_option_colonsep("title","'"+title[8]+"'")
mp.panel[mpi].adddata(plotdata)
mp.panel[mpi].setyrange(-10,30)
mp.panel[mpi].setlogscale(0)
mpi += 1
del plotdata

# Magnetfeldstaerke & abs Protonendichte
plotdata = Data(daten[9])
plotdata.set_option_colonsep("title","'"+title[9]+"'")
mp.panel[mpi].adddata(plotdata)
plotdata = Data(daten[10])
plotdata.set_option_colonsep("title","'"+title[10]+"'")
mp.panel[mpi].adddata(plotdata)
mp.panel[mpi].setyrange(0,20)
mp.panel[mpi].setlogscale(0)
mpi += 1
del plotdata
"""
mp.plot()