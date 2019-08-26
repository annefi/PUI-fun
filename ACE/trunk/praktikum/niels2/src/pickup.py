from libacepy.swicsprotondata import swicsprotondata
from libacepy.swicsiondata import swicsiondata
from Gnuplot import Gnuplot,Data
from libacepy.multiplot import multiplot

def frange (start,stop,int):
    res = []
    lauf = start
    while (True):
        if(lauf>stop):
            break
        res.append(lauf)
        lauf += int
    return res

jahr = []
for i in range(1):
	jahr.append([])

#jahr[0] = [2004,[[1,30]]]#120],[150,360]]]
#jahr[1] = [2005,[[1,30]]]#36],[64,103],[105,122],[135,191],[193,230]]]
#jahr[2] = [2006,[[1,30]]]#345],[347,360]]]
jahr[0] = [2007,[[1,360]]]


gp=Gnuplot()
ionnames = ["He1+"] #,"O6+","O7+","O8+"]
intervalrange = 20

intervalrange = 0.1
maxrange = 5
mp=multiplot(len(ionnames))
mp.setxrange(0,maxrange)
mp.setxlabel("vel/swvel")


datamin = []
datamax = []

for i in range(len(ionnames)):
	datamin.append(1e30)
	datamax.append(0)
        
for jh in range(len(jahr)):
    print "Jahr " + str(jahr[jh][0])
    pathh1="/data/wimmer/ace/puis/1hdata/"+str(jahr[jh][0])+"/"
    pathh2="/data/wimmer/ace/1hdata/"+str(jahr[jh][0])+"/"
    
    datadenssum = []

    i = 0

    data = swicsprotondata("He1+",jahr[jh][1],pathh1)
    data.load()
    datah2 = swicsiondata("He2+",jahr[jh][1],pathh2)
    datah2.load()
    print data
    datadenssum.append([])
    for swstart in range(300,800,100):
        print (maxrange/intervalrange)
        for vs in range(int(maxrange/intervalrange)):
            datadenssum[i].append(0)
            
        for ts in range(len(data.countspec)):
            for vs in range(len(data.countspec[ts])):
              if (datah2.vel[ts] > swstart and datah2.vel[ts] < swstart+100):
                interval = int(data.countspec[ts][vs][0]/datah2.vel[ts]/intervalrange)
                #print interval
                if (interval < int(maxrange/intervalrange)):
                    datadenssum[i][interval] += data.countspec[ts][vs][1]

        for interval in range(len(datadenssum[i])):
            datadenssum[i][interval] /= len(data.countspec)
            if (datadenssum[i][interval] > 1.e-24):
                if (datadenssum[i][interval] < datamin[i]):
                    datamin[i] = datadenssum[i][interval]
                if (datadenssum[i][interval] > datamax[i]):
                    datamax[i] = datadenssum[i][interval]

        
        pdata = Data(zip(frange(0,maxrange,intervalrange),datadenssum[i]))
        pdata.set_option_colonsep("title","'"+str(swstart)+"'")
        mp.panel[i].adddata(pdata)
        del pdata
        
               
    del datadenssum    


#data = swicsprotondata(ionnames[i],jahr[jh][1],path)
#data.load()
#gp.plot(Data(data.countspec[0]))

for i in range(len(ionnames)):
    mp.panel[i].setyrange(datamin[i]*0.9,datamax[i]*1.1)
    mp.panel[i].setlogscale(1)
    mp.panel[i].setylabel(ionnames[i] + " counts per hour")

mp.plot()
