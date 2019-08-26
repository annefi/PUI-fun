"""
Dieses Script ist zum Plotten des Magnetfeldes und anderen Daten über längere Zeiträume zur groben Suche nach Magnetfeldwechseln
"""

import sys
from libacepy.mag import magdata
from libacepy.swepamdata import swepamdata,sync_h
from libacepy.swicsiondata import swicsiondata
from Gnuplot import Gnuplot,Data
from libacepy.multiplot import multiplot
from math import sqrt,atan,pi,acos,cos

parkerwinkel = pi*0.2

mres = 240
pres = 720
sires = 3600

bintime = 6*3600
year = 2007
timeframe = [220,365]

#Multiplotklasse initialisieren
mp=multiplot(4,0)
mp.setgv(1)
mp.setxrange(timeframe[0],timeframe[1])
mpi = 0

# Anfang: Magdaten auswerten
mdata = magdata(mres,year,timeframe[0],timeframe[1],"/data/ivar/ace/mag/")
mdata.load()
binres = bintime/mres
mbin = []
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
	
	
	# Jedes binres-te Element neue bin anlegen und letzte normieren
	if (i % binres == 0):
		if (i>0):
			mbin[len(mbin)-1][1] /= binres
		mbin.append([mdata.time[i],phi])
	else:
		mbin[len(mbin)-1][1] += phi
if (i % binres != 0):
	mbin[len(mbin)-1][1] /= (i % binres)

plotdata = Data(mbin)
plotdata.set_option_colonsep("title","'{/Symbol F}_B'")
mp.panel[mpi].adddata(plotdata)
mp.panel[mpi].adddata(Data([[timeframe[0],pi/2+parkerwinkel],[timeframe[1],pi/2+parkerwinkel]]))
mp.panel[mpi].adddata(Data([[timeframe[0],parkerwinkel],[timeframe[1],parkerwinkel]]))
mp.panel[mpi].adddata(Data([[timeframe[0],pi+parkerwinkel],[timeframe[1],pi+parkerwinkel]]))
mp.panel[mpi].setyrange(-2,6)
mp.panel[mpi].setlogscale(0)
mp.panel[mpi].setylabel("B-Winkel")
mpi += 1
del plotdata
del mdata
del mbin
# Ende: Magdaten auswerten


# Anfang: Swepam auswerten
he2data = swicsiondata("He2+",[timeframe],"/data/wimmer/ace/1hdata/"+str(year)+"/")
he2data.load()
pdata = swepamdata(pres,year,timeframe[0],timeframe[1],"/data/ivar/ace/swepam/")
pdata.load()
pdata = sync_h(pdata,he2data)

binres = bintime/pres
pvbin = []	#Bins der Geschwindigkeit
ptbin = []	#Bins der Temperatur
pnbin = []	#Bins der Dichte
for i in range(min(len(pdata.vel),len(pdata.temp))):
	if (i % binres == 0):
		if (i>0):
			pvbin[len(pvbin)-1][1] /= binres
			ptbin[len(ptbin)-1][1] /= binres
			ptbin[len(pnbin)-1][1] /= binres
		pvbin.append([pdata.time[i],pdata.vel[i][1]])
		ptbin.append([pdata.time[i],pdata.temp[i][1]])
		pnbin.append([pdata.time[i],pdata.dens[i][1]])
	else:
		pvbin[len(pvbin)-1][1] += pdata.vel[i][1]
		ptbin[len(ptbin)-1][1] += pdata.temp[i][1]
		pnbin[len(pnbin)-1][1] += pdata.dens[i][1]
if (i % binres != 0):
	pvbin[len(pvbin)-1][1] /= (i % binres)
	ptbin[len(ptbin)-1][1] /= (i % binres)
	pnbin[len(pnbin)-1][1] /= (i % binres)

#Geschwindigkeit plotten
plotdata = Data(pvbin)
plotdata.set_option_colonsep("title","'v'")
mp.panel[mpi].adddata(plotdata)
mp.panel[mpi].adddata(Data([[timeframe[0],500],[timeframe[1],500]]))
mp.panel[mpi].setyrange(2e2,8e2)
mp.panel[mpi].setlogscale(0)
mp.panel[mpi].setylabel("P-vel")
mpi += 1
del plotdata

#Temperatur plotten
plotdata = Data(ptbin)
plotdata.set_option_colonsep("title","'T'")
mp.panel[mpi].adddata(plotdata)
mp.panel[mpi].setyrange(1e2,2e4)
mp.panel[mpi].setlogscale(0)
mp.panel[mpi].setylabel("P-Temp")
mpi += 1
del plotdata

#Dichte plotten
plotdata = Data(pnbin)
plotdata.set_option_colonsep("title","'n_P'")
mp.panel[mpi].adddata(plotdata)
mp.panel[mpi].setyrange(0,700)
mp.panel[mpi].setlogscale(0)
mp.panel[mpi].setylabel("P-Dichte")
mpi += 1
del plotdata

del pdata
# Ende: Swepam auswerten



mp.plot()