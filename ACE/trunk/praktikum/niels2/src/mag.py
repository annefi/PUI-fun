"""
Dieses Script wurde genutzt um den Wechsel des Magnetfeldes genau zu bestimmen wobei als Parameter der große Zeitpunkt übergeben wird.
"""

import sys
from libacepy.mag import magdata
from libacepy.swepamdata import swepamdata
from libacepy.swicsiondata import swicsiondata
from Gnuplot import Gnuplot,Data
from libacepy.multiplot import multiplot
from math import sqrt,atan,pi,acos,cos

if (len(sys.argv)>1):
    mark = int(sys.argv[1])
else:
    mark = 8

ionnames = ["He2+","O6+","O7+"]

parkerwinkel = pi*0.2
marks = []#15.35,29.38,58.2,91.,117.7,127.6,138.5,144.,165.,172.3,180.8,192.,207.5,210.7,219.,222.5,227.,243.8,249.7,257.9,263.5,271.,298.5,324.5,345.,351.3]

mres = 240
pres = 720
sires = 3600

bintime = 4*3600
year = 2007
timeframe = [mark-4,mark+4]

#Multiplotklasse initialisieren
mp=multiplot(6,0)
mp.setgv(0)
mp.setxrange(timeframe[0],timeframe[1])
mpi = 0
#vertikale Marks setzen
for i in range(len(marks)):
        mp.addplotmark("vline")
        mp.plotmarks[i].setvlinepos(marks[i])



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
pdata = swepamdata(pres,year,timeframe[0],timeframe[1],"/data/ivar/ace/swepam/")
pdata.load()

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
		ptbin[len(pnbin)-1][1] += pdata.dens[i][1]
if (i % binres != 0):
	pvbin[len(pvbin)-1][1] /= (i % binres)
	ptbin[len(ptbin)-1][1] /= (i % binres)
	ptbin[len(pnbin)-1][1] /= (i % binres)

#Geschwindigkeit plotten
plotdata = Data(pvbin)
plotdata.set_option_colonsep("title","'v'")
mp.panel[mpi].adddata(plotdata)
mp.panel[mpi].setyrange(2e2,8e2)
mp.panel[mpi].setlogscale(0)
mp.panel[mpi].setylabel("P-vel")
mpi += 1
del plotdata

#Temperatur plotten
plotdata = Data(ptbin)
plotdata.set_option_colonsep("title","'T'")
mp.panel[mpi].adddata(plotdata)
mp.panel[mpi].setyrange(3e3,4e5)
mp.panel[mpi].setlogscale(0)
mp.panel[mpi].setylabel("P-Temp")
mpi += 1
del plotdata

#Dichte plotten
plotdata = Data(pnbin)
plotdata.set_option_colonsep("title","'n_P'")
mp.panel[mpi].adddata(plotdata)
mp.panel[mpi].setyrange(0,30)
mp.panel[mpi].setlogscale(0)
mp.panel[mpi].setylabel("P-Dichte")
mpi += 1
del plotdata

del pdata
# Ende: Swepam auswerten

"""
# Anfang: Swicsdaten auswerten
binres = bintime/sires
sibin = []
sivbin = []
for ion in range(len(ionnames)):
	sidata = swicsiondata(ionnames[ion],[timeframe],"/data/wimmer/ace/1hdata/"+str(year)+"/")
	sidata.load()
	
	sibin.append([])
	sivbin.append([])
	for i in range(len(sidata.time)):
		if (i % binres == 0):
			if (i>0):
				sibin[ion][len(sibin[ion])-1][1] /= binres
				sivbin[ion][len(sivbin[ion])-1][1] /= binres
			sibin[ion].append([sidata.time[i],sidata.dens[i][0]])
			sivbin[ion].append([sidata.time[i],sidata.vel[i]])
		else:
			sibin[ion][len(sibin[ion])-1][1] += sidata.dens[i][0]
			sivbin[ion][len(sivbin[ion])-1][1] += sidata.vel[i]
	del sidata
if (i % binres != 0):
	sibin[ion][len(sibin)-1][1] /= (i % binres)
	sivbin[ion][len(sivbin)-1][1] /= (i % binres)

# Verhaeltnis aus O7/O6
verho7o6 = []
low = 1e10
high = 0.
for i in range (min(len(sibin[ionnames.index("O6+")]),len(sibin[ionnames.index("O7+")]))):
	if (sibin[ionnames.index("O6+")][i][1] == 0):
		div = 0.
	else:
		div = sibin[ionnames.index("O7+")][i][1]/sibin[ionnames.index("O6+")][i][1]
	verho7o6.append([sibin[ionnames.index("O6+")][i][0],div])
	if (verho7o6[i][1] > high):
		high = verho7o6[i][1]
	elif (verho7o6[i][1] < low and verho7o6[i][1] > 1e-20):
		low = verho7o6[i][1]

plotdata = Data(verho7o6)
plotdata.set_option_colonsep("title","'O7+/O6+'")
mp.panel[mpi].adddata(plotdata)
mp.panel[mpi].setyrange(low/3,3*high)
mp.panel[mpi].setlogscale(1)
mp.panel[mpi].setylabel("Dichte")
mpi += 1
del plotdata

# Verhaeltnis aus He2/O6
verhhe2o6 = []
low = 1e10
high = 0.
for i in range (min(len(sibin[ionnames.index("O6+")]),len(sibin[ionnames.index("He2+")]))):
	if (sibin[ionnames.index("O6+")][i][1] == 0):
		div = 0.
	else:
		div = sibin[ionnames.index("He2+")][i][1]/sibin[ionnames.index("O6+")][i][1]
	verhhe2o6.append([sibin[ionnames.index("O6+")][i][0],div])
	if (verhhe2o6[i][1] > high):
		high = verho7o6[i][1]
	elif (verhhe2o6[i][1] < low and verhhe2o6[i][1] > 1e-20):
		low = verho7o6[i][1]
		
plotdata = Data(verhhe2o6)
plotdata.set_option_colonsep("title","'He2+/O6+'")
mp.panel[mpi].adddata(plotdata)
mp.panel[mpi].setyrange(low/3,high*3)
mp.panel[mpi].setlogscale(1)
mp.panel[mpi].setylabel("Dichte")
mpi += 1
del plotdata

# Differenz der Geschwindigkeiten von O6+ und He2+
diffhe2o6 = []
low = 1e10
high = 0.
for i in range (min(len(sivbin[ionnames.index("O6+")]),len(sivbin[ionnames.index("He2+")]))):
	diff = sivbin[ionnames.index("O6+")][i][1] - sivbin[ionnames.index("He2+")][i][1]
	diff = abs(diff) + 1e-21
	diffhe2o6.append([sivbin[ionnames.index("O6+")][i][0],diff])
	if (diffhe2o6[i][1] > high):
		high = diffhe2o6[i][1]
	elif (diffhe2o6[i][1] < low and diffhe2o6[i][1] > 1e-20):
		low = diffhe2o6[i][1]
		
plotdata = Data(diffhe2o6)
plotdata.set_option_colonsep("title","'V_{O6} - V_{He2}'")
mp.panel[mpi].adddata(plotdata)
mp.panel[mpi].setyrange(low * 0.7,high* 1.3)
mp.panel[mpi].setlogscale(1)
mp.panel[mpi].setylabel("Vel")
mpi += 1
del plotdata
# Ende: Swicsdaten auswerten
"""


# Anfang: Swics vs Swepam
swics = swicsiondata("He2+",[timeframe],"/data/wimmer/ace/1hdata/"+str(year)+"/")
swics.load()
swepam = swepamdata(720,year,timeframe[0],timeframe[1],"/data/ivar/ace/swepam/")
swepam.load()
v_heh = []
dens_heh = []

binres = bintime/720

vel_low = 1e10
vel_high = 0.
dense_low = 1e10
dense_high = 0.
for i in range(len(swics.time)):
	j = i
	while ((swics.time[i]-swepam.time[j]) > 0.01):
		j += 1
	if ((swics.time[i]-swepam.time[j]) < -0.01):
		continue
	if (j >= len(swepam.dens)):
		continue
	
	if (i % binres == 0):
		if (len(v_heh)>0):
			 v_heh[len(v_heh)-1][1] /= binres
		v_heh.append([swics.time[i],swics.vel[i]-swepam.vel[j][1]])
	else:
		v_heh[len(v_heh)-1][1] += swics.vel[i]-swepam.vel[j][1]
		
	if (v_heh[len(v_heh)-1][1] > vel_high):
		vel_high = v_heh[len(v_heh)-1][1]
	elif (v_heh[len(v_heh)-1][1] < vel_low and v_heh[len(v_heh)-1][1] > 1e-20):
		vel_low = v_heh[len(v_heh)-1][1]
		
	if (swepam.dens[j][1] > 1e-20):
		if (i % binres == 0):
			if (len(dens_heh)>0):
				dens_heh[len(dens_heh)-1][1] /= binres
			dens_heh.append([swics.time[i],swics.dens[i][0]/swepam.dens[j][1]])
		else:
			dens_heh[len(dens_heh)-1][1] += swics.dens[i][0]/swepam.dens[j][1]
			
		if (dens_heh[len(dens_heh)-1][1] > dense_high):
			dense_high = dens_heh[len(dens_heh)-1][1]
		elif (dens_heh[len(dens_heh)-1][1] < dense_low and dens_heh[len(dens_heh)-1][1] > 1e-20):
			dense_low = dens_heh[len(dens_heh)-1][1]

# Differenzgeschwindigkeit plotten
plotdata = Data(v_heh)
plotdata.set_option_colonsep("title","'V_{He2+} - V_{H1+}'")
mp.panel[mpi].adddata(plotdata)
mp.panel[mpi].setyrange(vel_low * 0.7,vel_high* 1.3)
mp.panel[mpi].setlogscale(1)
mp.panel[mpi].setylabel("Vel")
mpi += 1
del plotdata

# Dichteverhaeltnis plotten
plotdata = Data(dens_heh)
plotdata.set_option_colonsep("title","'He2+/H1+'")
mp.panel[mpi].adddata(plotdata)
mp.panel[mpi].setyrange(dense_low * 0.7,dense_high* 1.3)
mp.panel[mpi].setlogscale(1)
mp.panel[mpi].setylabel("dens")
mpi += 1
del plotdata

del swics
del swepam
# Ende: Swics vs Swepam


mp.plot()