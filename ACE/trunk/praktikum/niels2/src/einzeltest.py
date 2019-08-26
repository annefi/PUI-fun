from libacepy.swicsiondata import swicsiondata
from Gnuplot import Gnuplot,Data
from libacepy.multiplot import multiplot

gp=Gnuplot()
path="/data/wimmer/ace/1hdata/2007/"
timeframe=[[1.,3.]]

data = swicsiondata("O7+",timeframe,path)
data.load()

dens = []
for i in range(len(data.dens)):
    dens.append([data.time[i],data.dens[i][0]])

gp.plot(Data(dens))
