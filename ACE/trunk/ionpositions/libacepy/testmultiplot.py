from libacepy.multiplot import multiplot
from libacepy.plotdata import plotdata
from Gnuplot import Data,Gnuplot
from scipy import zeros
from numpy import float,sqrt

data1=zeros([100,100],float)
data2=zeros([100,100],float)
data3=zeros([100,100],float)
data4=zeros([100,100],float)
data5=zeros([100,100],float)

for i in range(100):
    data1[i][0]=float(i)
    data2[i][0]=float(i)
    data3[i][0]=float(i)
    data4[i][0]=float(i)
    data5[i][0]=float(i)
    data1[i][1]=float(i)
    data2[i][1]=float(i)**2
    data3[i][1]=sqrt(float(i))
    data4[i][1]=float(i)**3
    data5[i][1]=float(i)**3


panels=4
mp=multiplot(panels)
mp.addplotmark("vline")
mp.addplotmark("vline")
#mp.addplotmark("box")
#mp.addplotmark("box")
mp.plotmarks[0].setvlinepos(10.)
mp.plotmarks[1].setvlinepos(15.)
mp.plotmarks[1].setpanel([0,2])
#mp.plotmarks[2].setpanel([-1])
#mp.plotmarks[2].setboxrange(0.,10.)
#mp.plotmarks[3].setpanel([-1])
#mp.plotmarks[3].setboxrange(15.,40.)

for panel in range(panels):
    mp.panel[panel].setylabel("Test")
    if (panel==1):
        mp.panel[panel].setyrange(.1,1e14)
        #mp.panel[panel].setgrid(1)
    else:
        mp.panel[panel].setyrange(0.,600.)
    if (panel==1 or panel==2):
        mp.panel[panel].setlogscale(1)
    mp.panel[panel].adddata(Data(data1))
    mp.panel[panel].adddata(Data(data2))

mp.plot()
