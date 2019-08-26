from libacepy.swicsiondata import swicsiondata
from Gnuplot import Gnuplot,Data
from libacepy.multiplot import multiplot



jahr = []
for i in range(4):
	jahr.append([])
jahr[0] = [2004,[[1,120],[150,360]]]
jahr[1] = [2005,[[1,36],[64,103],[105,122],[135,191],[193,230]]]
jahr[2] = [2006,[[1,345],[347,360]]]
jahr[3] = [2007,[[1,360]]]

gp=Gnuplot()
ionnames = ["He2+","O6+","O7+","O8+"]
intervalrange = 20

	
mp=multiplot(len(ionnames))
mp.setxrange(200,900)
mp.setxlabel("Geschwindigkeitsintervalle")


#path="/data/wimmer/ace/1hdata/2007/"
data = []
datamin = []
datamax = []
datadenssum = []
pdata = []

for i in range(len(ionnames)):
	datamin.append(1e10)
	datamax.append(0)

for jh in range(len(jahr)):
	print "jahr " + str(jahr[jh][0])
	path="/data/wimmer/ace/1hdata/"+str(jahr[jh][0])+"/"
	
	data.append([])
	datadenssum.append([])
	pdata.append([])
	for i in range(len(ionnames)):
		data[jh].append(swicsiondata(ionnames[i],jahr[jh][1],path))
		data[jh][i].load()
		datadenssum[jh].append([])

		for j in range(int(1500/intervalrange)):
			datadenssum[jh][i].append(0)
            
		for j in range(len(data[jh][i].time)):
			interval = int(data[jh][i].vel[j]/intervalrange)
			if (interval < int(1500/intervalrange)):
				datadenssum[jh][i][interval] += data[jh][i].temp[j][0]

#		print "Fuer :" + ionnames[i]
		for j in range(len(datadenssum[jh][i])):
			datadenssum[jh][i][j] /= len(data[jh][i].time)
			if (datadenssum[jh][i][j] > 1.e-24):
#				print str(j*intervalrange) + " - " + str((j+1)*intervalrange) + " : " + str(datadenssum[jh][i][j])
				if (datadenssum[jh][i][j] < datamin[i]):
					datamin[i] = datadenssum[jh][i][j]
				if (datadenssum[jh][i][j] > datamax[i]):
					datamax[i] = datadenssum[jh][i][j]
#		print str(datamin[i]) + "-" + str(datamax[i])

		pdata[jh].append([])
		pdata[jh][i] = Data(zip(range(0,1100,intervalrange),datadenssum[jh][i]))
		pdata[jh][i].set_option_colonsep("title","'"+str(jahr[jh][0])+"'")
		mp.panel[i].adddata(pdata[jh][i])

		del data[jh][i]
		data[jh].append(0)
		


for i in range(len(ionnames)):
    mp.panel[i].setyrange(datamin[i]*0.9,datamax[i]*1.1)
    mp.panel[i].setlogscale(1)
    mp.panel[i].setylabel(ionnames[i])

mp.plot()
