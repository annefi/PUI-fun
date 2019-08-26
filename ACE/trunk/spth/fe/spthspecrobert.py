from libacepy.swicselemdata import swicselemdata
from libacepy.swicsiondata import swicsiondata
from libacepy.ancil import histogram,sig_histogram
from math import sqrt
from Gnuplot import Gnuplot,Data


def vel2epa(vel):
    amu=1.6605e-27
    E=(amu/2.)*(vel*1.e3)**2
    E=E*6.2415e18
    return E/1000.

res=5. # = 1hdata
path="/data/wimmer/ace/1hdata/2007/"
timeframe=[[85.,86.99],[89.,105.]]
timeframe=[[89.94,89.97]]
timeframe=[[29.0,29.2]]
#ions=["Fe7+","Fe8+","Fe9+","Fe10+","Fe11+","Fe12+","Fe13+","Fe14+","Fe15+","Fe16+","Fe17+","Fe18+","Fe19+","Fe20+","Fe21+","Fe22+","Fe23+","Fe24+"]
ions=["He2+","O6+","Fe10+"]
#ions=["He2+"]
hedata=swicsiondata("He2+",timeframe,path)
hedata.load()

fedata=[]
for ion in ions:
    fedata.append(swicsiondata(ion,timeframe,path))
    fedata[len(fedata)-1].load()

epaspec=[]
for ion in fedata:
    epaspec.append([])
    for val in ion.countspec[0]:
        epaspec[len(epaspec)-1].append([vel2epa(val[0]),0.,0.,0.])

depaspec=[]
for ion in fedata:
    depaspec.append([])
    for i in range(len(ion.countspec[0])):
        depaspec[len(depaspec)-1].append([vel2epa(ion.countspec[0][i][0])*0.97,vel2epa(ion.countspec[0][i][0])*1.03])

dim=60
step=.5

distarr=[]
for i in range(len(ions)):
    distarr.append([])
    for j in range(len(fedata[i].countspec[0])):
        distarr[len(distarr)-1].append([])
        for k in range(int(dim/step)):
            distarr[len(distarr)-1][j].append([0.])

for l in range(len(ions)):
    for i in range(len(fedata[l].countspec[0])):
        for j in range(int(dim/step)):
            if (depaspec[l][i][0]>float((j+1)*step) or depaspec[l][i][1]<float(j*step)):
                distarr[l][i][j]=0.
            elif (depaspec[l][i][0]<float(j*step) and depaspec[l][i][1]>float(j*step)):
                distarr[l][i][j]=(depaspec[l][i][1]-float(j*step))/(depaspec[l][i][1]-depaspec[l][i][0])
            elif (depaspec[l][i][0]>float(j*step) and depaspec[l][i][1]>float((j+1)*step)):
                distarr[l][i][j]=(float((j+1)*step)-depaspec[l][i][0])/(depaspec[l][i][1]-depaspec[l][i][0])
            else:
                distarr[l][i][j]=1.

# quantetites for flux calculations
g=0.0225
omega=0.0695
epq_arr = [86.6359,75.0485,65.0109,56.3158,48.7837,42.2589,36.6069,31.7108,27.4695,23.7955,20.6129,17.856,16.619,15.4678,14.3962,13.399,12.4708,11.6069,10.8028,10.0545,9.35797,8.70971,8.10635,7.5448,7.02214,6.5357,6.08294,5.66156,5.26936,4.90433,4.56459,4.24839,3.95409,3.68017,3.42523,3.18796,2.96711,2.76157,2.57027,2.39222,2.2265,2.07226,1.92871,1.7951,1.67075,1.55501,1.44729,1.34703,1.25372,1.16687,1.08603,1.0108,0.940778,0.875607,0.81495,0.758496,0.705952,0.657048]
fconv=1/(g*omega*res*12.)


i=0
for ion in fedata:
    k=0
#    for spec in ion.fluxspec:
    for spec in ion.countspec:
        for j in range(len(spec)):
            if (spec[j][0]>hedata.vel[k]*0.66):
                #epaspec[i][j][1]+=spec[j][1]
                epaspec[i][j][1]+=spec[j][1]
                epaspec[i][j][2]+=spec[j][2]**2
                epaspec[i][j][3]+=1.
        k+=1
    i+=1

for i in range(len(epaspec)):
    for j in range(len(epaspec[i])):
        if (epaspec[i][j][3]!=0.):
            epaspec[i][j][1]=epaspec[i][j][1]
            epaspec[i][j][2]=sqrt(epaspec[i][j][2])
            

histarr=[]
for ion in fedata:
    histarr.append([])
    for i in range(int(dim/step)):
        histarr[len(histarr)-1].append([float(step)/2.+float(i*step),0.,0.])

for i in range(len(epaspec)):
    for j in range(len(epaspec[i])):
        for k in range(int(dim/step)):
            histarr[i][k][1]+=epaspec[i][j][1]*distarr[i][j][k]
            histarr[i][k][2]+=epaspec[i][j][2]*distarr[i][j][k]
#histarr=[]
#for spec in epaspec:
#    histarr.append(histogram(spec,0.,1.,40.,2))

sumhist=[]
for i in range(int(dim/step)):
    sumhist.append([(float(step)/2.)+float(i*step),0.,0.])

for i in range(int(dim/step)):
    for spec in histarr:
        sumhist[i][1]+=spec[i][1]
        sumhist[i][2]+=spec[i][2]

pspec=[]
i=0
for spec in epaspec:
    pspec.append(Data(spec))
    pspec[len(pspec)-1].set_option_colonsep("title","'%s'"%(fedata[i].name))
    pspec[len(pspec)-1].set_option_colonsep("with","yerrorbars lw 3")
    pspec[len(pspec)-1].set_option_colonsep("using","1:2:3")
    i+=1

phist=[]
i=0
for spec in histarr:
    phist.append(Data(spec))
    phist[len(phist)-1].set_option_colonsep("title","'%s'"%(fedata[i].name))
    phist[len(phist)-1].set_option_colonsep("with","yerrorbars lw 3")
    phist[len(phist)-1].set_option_colonsep("using","1:2:3")
    i+=1

psumhist=Data(sumhist)
psumhist.set_option_colonsep("title","'Fe'")
psumhist.set_option_colonsep("with","yerrorbars lw 3")
psumhist.set_option_colonsep("using","1:2:3")

gp=Gnuplot()
#gp("f(x)=3.e6*x**-5.7")
gp("set log yx")
gp("set yrange[0.1:1e5]")
gp("set xrange[.1:100.]")
gp("set format y '10^{%T}'")
gp("set xlabel 'keV/amu'")
gp("set ylabel 'N[#]'")
if (len(hedata.time)==1):
    gp("set title '2007 DoY %.3f'"%(hedata.time[0]))
else: 
    gp("set title '2007 DoY %.3f-%.3f'"%(hedata.time[0],hedata.time[len(hedata.time)-1]))
first=1
for spec in pspec:
    if (first):
        gp.plot(spec)
        first=0
    else:
        gp.replot(spec)
#gp.replot(psumhist)
#gp.replot("f(x)")

if (len(hedata.time)==1):
    name="%.3f"%(hedata.time[0])
else: 
    name="%.3f-%.3f"%(hedata.time[0],hedata.time[len(hedata.time)-1])

gp.hardcopy("%s.ps"%(name),color="true",fontsize=20)


#for i in range(len(fedata[0].time)):
#    sumspec.append([
#    for j in range(len(fedata)):
        
