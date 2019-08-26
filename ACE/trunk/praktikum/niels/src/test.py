from libacepy.swicsiondata import swicsiondata
from scipy import zeros, sqrt,mean
from Gnuplot import Gnuplot,Data
from libacepy.multiplot import multiplot



temp1 = [[15,142],[20,150.3],[25,158],[30,164.5],[35,170],[40,173],[50,178]]
#temp = [[20,150.3],[30,164.5],[40,172.5],[50,178]]
temp2 = [[15,136],[20,144.1],[25,151],[30,156.2],[35,160.2],[40,163.3],[50,167.1]]


#temp1 = [[20,164.6],[25,172.3],[30,178.4],[35,183.1],[40,186.6],[45,189.2],[50,191.1]]
#temp2 = [[20,173.3],[25,181.5],[30,188],[35,195],[40,199],[45,202],[50,205]]

#quot = []
#for i in range(len(temp2)):
#    quot.append([temp[i][0],temp[i][1]/temp2[i][1]])

#print quot

pardiff = []
for i in range(len(temp2)):
    pardiff.append([temp1[i][0],sqrt(abs(temp1[i][1]**2 - temp2[i][1]**2))])

print pardiff

mp=multiplot(2)
pdata = Data(temp1)
mp.panel[0].adddata(pdata)
pdata = Data(temp2)
mp.panel[0].adddata(pdata)
#pdata = Data(quot)
#mp.panel[0].adddata(pdata)

mp.panel[0].setyrange(140.0,190.)

mp.panel[1].setlogscale(0)
mp.panel[1].setylabel("Abs")
pdata = Data(pardiff)
mp.panel[1].adddata(pdata)
mp.panel[1].setyrange(20.,70.)
mp.panel[1].setlogscale(0)
mp.panel[1].setylabel("swrt(1^2 - 2^2)")
mp.setxrange(0,60)
mp.plot()
