from libacepy.swicselemdata import swicselemdata
from libacepy.ancil import histogram,sig_histogram
from Gnuplot import Gnuplot,Data


path="/data/wimmer/ace/1hdata/2001/"
timeframe=[[85.,105.]]
elem="Fe"

fedata=swicselemdata(elem,timeframe,path)
fedata.load()

cleanmeanch=[]
for val in fedata.meanch:
    if (val[1]>7. and val[1]<26.):
        cleanmeanch.append(val)

onedaym=histogram(cleanmeanch,85,1,20,4)
onedaym2=sig_histogram(cleanmeanch,onedaym,4)
onedaym3=[]
for i in range(len(onedaym)):
    onedaym3.append([onedaym[i][0],onedaym[i][1],onedaym2[i][1]])
#for i in range(16):
#    nrsum=0
#    onedaymean=0.
#    for j in range(24):
#        if (fedata.meanch[i*24+j][1]>0. and fedata.meanch[i*24+j][1]<20.):
#            nrsum+=1
#            onedaymean+=fedata.meanch[i*24+j][1]
#    if (nrsum>0):
#        onedaym.append([90.5+float(i),onedaymean/nrsum])

ponedaym=Data(onedaym3)
ponedaym.set_option_colonsep("using","1:2:3")
ponedaym.set_option_colonsep("with","yerrorbars lw 3 pt 2")


gp=Gnuplot()
gp("set grid xtics mxtics noytics back lt -1 lt 0")
gp("set yrange[0:20]")
gp("set xrange[85:105]")
gp("set mxtics 5")
gp("set mytics 5")
gp("set title 'ACE/SWICS Maximum Likelihood PHA Analyse'")
gp("set ylabel 'Qm(Fe)'")
gp("set xlabel 'Doy 2001'")
gp.plot(ponedaym)
gp.hardcopy("meanchfe.ps",color="true")
