from libacepy.swicsiondata import swicsiondata
from Gnuplot import Gnuplot,Data
from libacepy.multiplot import multiplot

gp=Gnuplot()
path="/data/wimmer/ace/1hdata/2007/"
timeframe=[[330,336]]
ionnames = ["He2+","O6+","O7+"]

data = []
datatemp = []
datavel = []
datadens = []
for i in range(len(ionnames)):
        data.append(swicsiondata(ionnames[i],timeframe,path))
        data[i].load()
        datatemp.append([])
        datavel.append([])     
        datadens.append([])      
        for j in range(len(data[i].time)):
                datatemp[i].append([data[i].time[j],data[i].temp[j][0]])
                datavel[i].append([data[i].time[j],data[i].vel[j]])
                datadens[i].append([data[i].time[j],data[i].dens[j][0]])
        
if (ionnames.index("O6+") != ValueError and ionnames.index("O7+") != ValueError ):
        relationo6o7 = []
        for i in range(len(data[ionnames.index("O7+")].time)):
                if (data[ionnames.index("O7+")].dens[i][0]>0.):
                        relationo6o7.append([data[ionnames.index("O7+")].time[i],data[ionnames.index("O6+")].dens[i][0]/data[ionnames.index("O7+")].dens[i][0]])



  
#gp("set yrange[1000:]")
#gp.plot(newdata)
#pdata=Data(temp)
#pdata.set_option_colonsep("with","l lt 3")
#pdata.set_option_colonsep("title","'bla'")
#gp("set style data lines")
#gp("set logscale y")
#gp.plot(pdata)
#gp.hardcopy("test.ps",color="true")


mp=multiplot(4)

marks = [15.35,29.38,58.2,91.,117.7,127.6,138.5,144.,165.,172.3,180.8,192.,207.5,210.7,219.,222.5,227.,243.8,249.7,257.9,263.5,271.,298.5,324.5,345.,351.3]

for i in range(len(marks)):
        mp.addplotmark("vline")
        mp.plotmarks[i].setvlinepos(marks[i])        


pdata0 = []
pdata2 = []
pdata3 = []
for i in range(len(ionnames)):
        pdata0.append(Data(datatemp[i]))
        pdata0[i].set_option_colonsep("title","'"+ionnames[i]+"'")
        mp.panel[0].adddata(pdata0[i])
        
        pdata2.append(Data(datavel[i]))
        pdata2[i].set_option_colonsep("title","'"+ionnames[i]+"'")
        mp.panel[2].adddata(pdata2[i])
        
        pdata3.append(Data(datadens[i]))
        pdata3[i].set_option_colonsep("title","'"+ionnames[i]+"'")
        mp.panel[3].adddata(pdata3[i])
        
if (ionnames.index("O6+") != ValueError and ionnames.index("O7+") != ValueError ):
        pdata1 = Data(relationo6o7)
        pdata1.set_option_colonsep("title","'o6/o7'")
        mp.panel[1].adddata(pdata1)
        
mp.setxrange(timeframe[0][0],timeframe[-1][1])
mp.panel[0].setyrange(1.e4,1.e8)
mp.panel[0].setlogscale(1)
mp.panel[0].setylabel("Temperatur")
mp.panel[1].setyrange(.1,1.e3)
mp.panel[1].setlogscale(1)
mp.panel[1].setylabel("Ionenverhaeltnis")
mp.panel[2].setyrange(250,800)
mp.panel[2].setlogscale(0)
mp.panel[2].setylabel("Geschwindigkeit")
mp.panel[3].setyrange(1.e-6,1.e-1)
mp.panel[3].setlogscale(1)
mp.panel[3].setylabel("Dichte")
mp.plot()
