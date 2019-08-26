from libacepy.swicselemdata import swicselemdata
from libacepy.swicsiondata import swicsiondata
from libacepy.ancil import histogram,sig_histogram
from math import sqrt,sin,pi
from Gnuplot import Gnuplot,Data, GnuplotOpts

GnuplotOpts.prefer_fifo_data=0
GnuplotOpts.prefer_inline_data=0

# convertiert geschwindigkeit [km/s] in energy pro amu [keV/amu]
def vel2epa(vel):
    amu=1.6605e-27
    E=(amu/2.)*(vel*1.e3)**2
    E=E*6.2415e18
    return E/1000.

fi=5
fg=4.
fk=-1.5
res=5. # = 1hdata
path="/data/wimmer/ace/1hdata/2001/"
timeframe=[[85.,86.99],[89.,105.]]
timeframe=[[89.94,89.97]]
timeframe=[[90.01,90.04]]
ions=["Fe7+","Fe8+","Fe9+","Fe10+","Fe11+","Fe12+","Fe13+","Fe14+","Fe15+","Fe16+","Fe17+","Fe18+","Fe19+","Fe20+","Fe21+","Fe22+","Fe23+","Fe24+"]
#ions=["He2+"]

# lade ionen daten
hedata=swicsiondata("He2+",timeframe,path)
hedata.load()

fedata=[]
for ion in ions:
    fedata.append(swicsiondata(ion,timeframe,path))
    fedata[len(fedata)-1].load()


# erzeugt container für energy pro amu spektren in nativer instrumenteller aufloesung
epaspec=[]
for ion in fedata:
    epaspec.append([])
    for val in ion.countspec[0]:
        epaspec[len(epaspec)-1].append([vel2epa(val[0]),0.,0.,0.,0.])

# enthält die breiten der E/amu Punkte
depaspec=[]
for ion in fedata:
    depaspec.append([])
    for i in range(len(ion.countspec[0])):
        depaspec[len(depaspec)-1].append([vel2epa(ion.countspec[0][i][0])*0.97,vel2epa(ion.countspec[0][i][0])*1.03])


dim=60
step=4.

# container für E/amu binning  
distarr=[]
for i in range(len(ions)):
    distarr.append([])
    for j in range(len(fedata[i].countspec[0])):
        distarr[len(distarr)-1].append([])
        for k in range(int(dim/step)):
            distarr[len(distarr)-1][j].append([0.])

# berechnet den prozentualen beitrag von gegebenen ion in gegebenen step zu gegebenen energy/amu bin
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
# convert to MeV/nuc
for i in range(len(epq_arr)):
    epq_arr[i]*=0.001
# conversion factor including geometry factor, solid angle, and time resolution
fconv=1/(g*omega*res*12.)


# convertiert v zählratenspektren in E/amu flux spektren  
i=0
for ion in fedata:
    k=0
#    for spec in ion.fluxspec:
    for spec in ion.countspec:
        for j in range(len(spec)):
            if (spec[j][0]>hedata.vel[k]*0.66):
                #epaspec[i][j][1]+=spec[j][1]
                efff=open("/data/wimmer/ace/efficencies/"+ion.name+".eff")
                for stepeff in range(j+1):
                    s=efff.readline()
                    k1=s.split()
                    eff=float(k1[1])
                #if (i==4):
                #    print j,eff,0.06*epq_arr[j]*ion.charge/ion.mass
                if (eff>0.):
                    epaspec[i][j][1]+=spec[j][1]*fconv/(0.06*epq_arr[j]*(ion.charge/ion.mass))/eff
                    epaspec[i][j][2]+=(spec[j][2]*fconv/(0.06*epq_arr[j]*(ion.charge/ion.mass))/eff)**2
                    epaspec[i][j][3]+=1.
                    epaspec[i][j][4]=epq_arr[j]*1000.*0.03*(ion.charge/ion.mass)
        k+=1
    i+=1

# normiert E/amu spektren und berechnet den Fehler (derzeit einfach sqrt)
for i in range(len(epaspec)):
    for j in range(len(epaspec[i])):
        if (epaspec[i][j][3]!=0.):
            epaspec[i][j][1]=epaspec[i][j][1]/epaspec[i][j][3]
            epaspec[i][j][2]=sqrt(epaspec[i][j][2]/epaspec[i][j][3]**2)
            

# container für künstlich gebinnte spektren! 
histarr=[]
for ion in fedata:
    histarr.append([])
    for i in range(int(dim/step)):
        histarr[len(histarr)-1].append([float(step)/2.+float(i*step),0.,0.,0.])

binarr=[]
for i in range(int(dim/step)):
#    binarr.append([float(step)/2.+float(i*step),9e6,step/2.,0.])
    binarr.append([float((i)*step)+float(step)/2.,1e7,step])


# berechnung der künstlich gebinnten spektren
for i in range(len(epaspec)):
    for j in range(len(epaspec[i])):
        for k in range(int(dim/step)):
            
            histarr[i][k][1]+=epaspec[i][j][1]*distarr[i][j][k]
            histarr[i][k][2]+=epaspec[i][j][2]*distarr[i][j][k]
            histarr[i][k][3]=step/2.
#histarr=[]
#for spec in epaspec:
#    histarr.append(histogram(spec,0.,1.,40.,2))

# container für summen spektrum künstlich gebinnt
sumhist=[]
for i in range(int(dim/step)):
    sumhist.append([(float(step)/2.)+float(i*step),0.,0.,0.])

# einzel gebinnte spektren werden zu summen gebinnten spektrum zusammengefasst
for i in range(int(dim/step)):
    for spec in histarr:
        sumhist[i][1]+=spec[i][1]
        sumhist[i][2]+=spec[i][2]
        sumhist[i][3]=step/2.

deg=pi/180.

#corrarr=[1.,sin(.2*deg),sin(5.*deg),sin(90.*deg),0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.]
#for i in range(int(dim/step)):
#    sumhist[i][1]=sumhist[i][1]*corrarr[i]

# Plotobjekte werden erzeugt

fitspec=[]
for val in epaspec[fi]:
    if (val[0]>fg):
        fitspec.append(val)
pfitspec=Data(fitspec)
pfitspec.set_option_colonsep("title","'%s'"%(fedata[i].name))
pfitspec.set_option_colonsep("with","xyerrorbars")
pfitspec.set_option_colonsep("using","1:2:5:3")

i=0
while (epaspec[fi][i][0]>fg):
    i+=1
i=i-1
print "i = ",i
normval=[]
xval=[]
for j in range(i):
    if (epaspec[fi][i-j]!=0.):
        normval.append(epaspec[fi][i-j][1])
        xval.append(epaspec[fi][i-j][0])
astring="("
for j in range(len(normval)):
    if (j==0):
        astring+="(%e/%e**k)"%(normval[j],xval[j])
    elif(j==len(normval)-1):
        astring+="+(%e/%e**k))/%f"%(normval[j],xval[j],float(len(normval)))
    else:
        astring+="+(%e/%e**k)"%(normval[j],xval[j])

pspec=[]
i=0
for spec in epaspec:
    pspec.append(Data(spec))
    pspec[len(pspec)-1].set_option_colonsep("title","'%s'"%(fedata[i].name))
    pspec[len(pspec)-1].set_option_colonsep("with","xyerrorbars")
    pspec[len(pspec)-1].set_option_colonsep("using","1:2:5:3")
    #pspec[len(pspec)-1].set_option_colonsep("with","xerrorbars")
    #pspec[len(pspec)-1].set_option_colonsep("using","1:2:5")
    i+=1

pbin=Data(binarr)
#pbin.set_option_colonsep("title","'bin width'")
pbin.set_option_colonsep("with","boxes lt -1 lw 1")
#pbin.set_option_colonsep("using","1:3")

phist=[]
i=0
for spec in histarr:
    phist.append(Data(spec))
    phist[len(phist)-1].set_option_colonsep("title","'%s'"%(fedata[i].name))
    phist[len(phist)-1].set_option_colonsep("with","xyerrorbars")
    phist[len(phist)-1].set_option_colonsep("using","1:2:4:3")
    i+=1

psumhist=Data(sumhist)
psumhist.set_option_colonsep("title","'Fe'")
psumhist.set_option_colonsep("with","xyerrorbars lw 3")
psumhist.set_option_colonsep("using","1:2:4:3")

print "astring = ",astring

# Plot wird initialisiert + geplottet
gp=Gnuplot()
#gp("f(x)=3.e6*x**-5.7")
gp("set size square")
#gp("set grid front")
#gp("unset grid")
gp("set key default")
gp("set key box below")
gp("unset key")
gp("set log xy")
gp("set yrange[1e2:1e7]")
gp("set xrange[1.:20.]")
gp("set xlabel 'keV/amu'")
gp("set ylabel 'Fe Flux (cts/cm^{2} sr MeV/n)'")
#gp("set boxwidth %f"%(step/2.))
gp("set mytics 10")
gp("set mxtics 10")
#gp("set xtics ('1' '1','' '2' 1,'' '3' 1,'' '4' 1,'' '5' 1,'' '6' 1,'' '7' 1,'' '8' 1,'' '9' 1,'10' '10','' '20' 1,'' '30' 1,'' '40' 1,'' '50' 1,'' '60' 1,'' '70' 1,'' '80' 1,'' '90' 1,'100' '100')")
gp("set format y '10^{%T}'")
gp("a=1.7e4")
gp("k=%f"%(fk))
#gp("f(x)=((%f/%f**k)+(%f/%f**k)+(%f/%f**k)+(%f/%f**k))/4.*(x)**k"%(normval[0],xval[0],normval[1],xval[1],normval[2],xval[2],normval[3],xval[3]))
gp("f(x)=%s*(x)**k"%(astring))
gp("f2(x)=5.e8*(x)**-5.5")
gp("f3(x)=2.e6*(x)**-3.")
gp("f4(x)=1.7e6*(x)**-2.5371")
gp("f5(x)=5.7e8*(x)**-7.")
#gp("fit f(x) '"+pfitspec.filename+"' using 1:2:3 via a,k")
gp("fit f(x) '"+pfitspec.filename+"' using 1:2:3 via k")
gp("fit f(x) '"+pfitspec.filename+"' using 1:2:3 via k")
gp("fit f(x) '"+pfitspec.filename+"' using 1:2:3 via k")
#gp("f(x)=2.0131e9*(x)**-4.5271")
if (len(hedata.time)==1):
    gp("set title 'Fe - SWICS-2001-DoY-%.3f'"%(hedata.time[0]))
else: 
    gp("set title 'Fe - SWICS-2001-DoY-%.3f-%.3f'"%(hedata.time[0],hedata.time[len(hedata.time)-1]))

#first=1
#for spec in pspec:
#    if (first):
#        gp.plot(spec)
#        first=0
#    else:
#        gp.replot(spec)
#gp.replot(pbin)
#gp.plot(pspec[0],pspec[3],pspec[6],pspec[9],pspec[12],pbin)
gp.plot(pspec[fi],"f(x)")#,"f2(x)","f3(x)","f4(x)","f5(x)")
#gp.replot(psumhist,"f(x) with l lt 3 title 'Y=M0*X^{M1}'")
#gp.replot("f(x)")
#gp.replot()
if (len(hedata.time)==1):
    name="fe16%.3f"%(hedata.time[0])
else: 
    name="fe16%.3f-%.3f"%(hedata.time[0],hedata.time[len(hedata.time)-1])

gp.hardcopy("%s.ps"%(name),color="true")


#for i in range(len(fedata[0].time)):
#    sumspec.append([
#    for j in range(len(fedata)):
        
