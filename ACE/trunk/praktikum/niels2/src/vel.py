from libacepy.swicsiondata import swicsiondata
from Gnuplot import Gnuplot,Data
from libacepy.multiplot import multiplot

#Integralfunktion
def integral(liste,anfang,ende):
    #Integral ueber linearen Fit
    summe_linfit = 0
    for i in range(anfang,ende-1):
        summe_linfit += abs(liste[i][0]-liste[i+1][0])*(liste[i][1]+liste[i+1][1])/2
    
#    print "Summe (linfit):"+str(summe_linfit)
        
    #Integral ueber mittlere Breite bei voller Hoehe
    summe_rechteck = 0
    for i in range(anfang,ende):
        if (i == 0):
            breite = abs(liste[i][0]-liste[i+1][0])/2
        if (i == len(liste)-1):
            breite = abs(liste[i][0]-liste[i-1][0])/2
        if (i != len(liste)-1 and i != 0):
            breite = abs(liste[i][0]-liste[i+1][0])/2 + abs(liste[i][0]-liste[i-1][0])/2
        summe_rechteck += breite * liste[i][1]

#    print "Summe (rechteck):"+str(summe_rechteck)
    return ((summe_linfit+summe_rechteck)/2)
#Ende der Integralfunktion

swbreite = 1.6


gp=Gnuplot()
path="/data/wimmer/ace/12mdata/2007/"
timeframe=[[100.,150.]]
ionname = "He2+"

data = swicsiondata(ionname,timeframe,path)
data.load()



#Zeittakte durchlaufen
vergleich = []
for takt in range(len(data.densspec)):
    #Maximum ermitteln
    #maximum = 0
    #test = 0
    #for i in range(len(data.densspec[takt])):
    #    if (test < data.densspec[takt][i][1]):
    #        maximum = i
    #        test = data.densspec[takt][i][1]
    #Ende Maximum Ermitteln

    #Index der Schwerpunktsgeschwindigkeit
    for i in range(len(data.densspec[takt])):
        if (data.densspec[takt][i][0]<data.vel[takt]):
            maximum = i
            break

    sw_anfang = 0
    sw_ende = 0
    for i in range(maximum,len(data.densspec[takt])):
        if (data.densspec[takt][i][0]<(data.densspec[takt][maximum][0]-3*data.vth[takt])):
            sw_anfang = i
            break
    
    for i in range(maximum):
        if (data.densspec[takt][i][0]<(data.densspec[takt][maximum][0]+3*data.vth[takt])):            
            sw_ende = i
            break


    integral_sw = integral(data.densspec[takt],sw_ende,sw_anfang)
    integral_spth = integral(data.densspec[takt],0,sw_ende)

    if (integral_sw > 0):
        vergleich.append(integral_spth/integral_sw)
    else:
        vergleich.append(0)


#Zeittakte durchlaufen
vergleich2 = []
for takt in range(len(data.densspec)):
    #Maximum ermitteln
    #maximum = 0
    #test = 0
    #for i in range(len(data.densspec[takt])):
    #    if (test < data.densspec[takt][i][1]):
    #        maximum = i
    #        test = data.densspec[takt][i][1]
    #Ende Maximum Ermitteln

    #Index der Schwerpunktsgeschwindigkeit
    for i in range(len(data.densspec[takt])):
        if (data.densspec[takt][i][0]<data.vel[takt]):
            maximum = i
            break

    sw_anfang = len(data.densspec[takt])-1
    sw_ende = 0
    for i in range(len(data.densspec[takt])):
        if (data.densspec[takt][i][0]<(data.densspec[takt][maximum][0] * swbreite)):
            sw_ende = i
            break

    integral_sw = integral(data.densspec[takt],sw_ende,sw_anfang)
    integral_spth = integral(data.densspec[takt],0,sw_ende)

    if (integral_sw > 0):
        vergleich2.append(integral_spth/integral_sw)
    else:
        vergleich2.append(0)
    



    
#print sw_anfang
#print sw_ende
#gp("set style data lines")
#gp.plot(vergleich)


mp=multiplot(3)
mp.setxrange(timeframe[0][0],timeframe[-1][1])

#marks = [data.densspec[takt][sw_anfang][0],data.densspec[takt][sw_ende][0], data.densspec[takt][maximum][0]]
#for i in range(len(marks)):
#        mp.addplotmark("vline")
#        mp.plotmarks[i].setvlinepos(marks[i])


mp.panel[0].adddata(Data(zip(data.time,data.vel)))
mp.panel[0].setyrange(0.,1000.)
mp.panel[0].setlogscale(0)
mp.panel[0].setylabel("Geschwindigkeit")

mp.panel[1].adddata(Data(zip(data.time,vergleich)))
mp.panel[1].setyrange(0.,0.04)
mp.panel[1].setlogscale(0)
mp.panel[1].setylabel("swth/sw mit 3vth")

mp.panel[2].adddata(Data(zip(data.time,vergleich2)))
mp.panel[2].setyrange(0.,0.005)
mp.panel[2].setlogscale(0)
mp.panel[2].setylabel("swth/sw mit 1.6sw")

mp.plot()
