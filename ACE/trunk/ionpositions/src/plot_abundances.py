#!/usr/bin/python
from scipy import zeros, sqrt,mean
from Gnuplot import Gnuplot, GridData, GnuplotOpts,Data
from numpy import float

GnuplotOpts.prefer_fifo_data=0
GnuplotOpts.prefer_inline_data=0

#ion_list=["O5+","O6+","O7+","O8+"]
#ion_list=["He2+","He1+","C4+","C5+","C6+","N5+","N6+","N7+","O5+","O6+","O7+","O8+","Ne8+","Ne7+","Mg6+","Mg7+","Mg8+","Mg9+","Mg10+","Mg11+","Mg12+","Si5+","Si6+","Si7+","Si8+","Si9+","Si10+","Si11+","Si12+","S5+","S6+","S7+","S8+","S9+","S10+","S11+","S12+","Ca6+","Ca7+","Ca8+","Ca9+","Ca10+","Ca11+","Ca12+","Ca13+","Ca14+","Fe5+","Fe6+","Fe7+","Fe8+","Fe9+","Fe10+","Fe11+","Fe12+","Fe13+","Fe14+","Fe15+","Fe16+","Fe17+"]

ion_list2=["C","N","O","Mg","Si","S","Ca","Fe"]
ion_list=["He2+","He1+","O5+","O6+","O7+","O8+"]
ion_list=["C4+","C5+","C6+"]
ion_list=["N5+","N6+","N7+"]
ion_list=["Mg7+","Mg8+","Mg9+","Mg10+"]
ion_list=["Fe5+","Fe6+","Fe7+","Fe8+","Fe9+","Fe10+","Fe11+","Fe12+","Fe13+","Fe14+","Fe15+","Fe16+","Fe17+"]
ion_list=["O5+","O6+","O7+","O8+"]
ion_list=["N5+","N6+","N7+"]
ion_list=["C4+","C5+","C6+"]
ion_list=["Mg7+","Mg8+","Mg9+","Mg10+"]
ion_list=["Si5+","Si6+","Si7+","Si8+","Si9+","Si10+","Si11+","Si12+"]
ion_list=["Fe5+","Fe6+","Fe7+","Fe8+","Fe9+","Fe10+","Fe11+","Fe12+","Fe13+","Fe14+","Fe15+","Fe16+","Fe17+"]
ion_list=["Si5+","Si6+","Si7+","Si8+","Si9+","Si10+","Si11+","Si12+"]
ion_list=["Ca6+","Ca7+","Ca8+","Ca9+","Ca10+","Ca11+","Ca12+","Ca13+","Ca14+"]
ion_list=["S5+","S6+","S7+","S8+","S9+","S10+","S11+","S12+"]
ion_list=["O5+","O6+","O7+","O8+","Ne8+","Ne7+"]
ion_list=["O5+","O6+","O7+","O8+","Mg6+","Mg7+","Mg8+","Mg9+","Mg10+","Mg11+","Mg12+"]
ion_list=["O5+","O6+","O7+","O8+","Mg10+"]
ion_list=["O5+","O6+","O7+","O8+","Mg6+","Mg7+","Mg8+","Mg9+","Mg10+","Mg11+","Mg12+"]
ion_list=["Si5+","Si6+","Si7+","Si8+","Si9+","Si10+","Si11+","Si12+"]
ion_list=["C4+","C5+","C6+","N5+","N6+","N7+","O5+","O6+","O7+","O8+","Mg6+","Mg7+","Mg8+","Mg9+","Mg10+","Mg11+","Mg12+","Si5+","Si6+","Si7+","Si8+","Si9+","Si10+","Si11+","Si12+","S5+","S6+","S7+","S8+","S9+","S10+","S11+","S12+","Ca6+","Ca7+","Ca8+","Ca9+","Ca10+","Ca11+","Ca12+","Ca13+","Ca14+","Fe5+","Fe6+","Fe7+","Fe8+","Fe9+","Fe10+","Fe11+","Fe12+","Fe13+","Fe14+","Fe15+","Fe16+","Fe17+"]
results=[]
for ion in range(len(ion_list)):
    tmpion=[]
    liste=open("abundancelist.dat")
#    s=liste.readline()
#    k=s.split()
#    path=k[0]
    i=0.
    for s in liste:
        k=s.split()
        resfile=open(k[0])
        print "opening ",k[0]
        s1=resfile.readline()
        for s1 in resfile:
            print s1
            k1=s1.split()
            if (k1[0]==ion_list[ion]):
                tmpion.append([(360.+20.*i),float(k1[2]),float(k1[4])])
        i=i+1.
    results.append(tmpion)

summe=[]
for interv in range(len(results[0])):
    tmpflux=0.
    tmpdens=0.
    for ion in range(len(results)):
        tmpflux=tmpflux+results[ion][interv][1]
        tmpdens=tmpdens+results[ion][interv][2]
    summe.append([results[0][interv][0],tmpflux,tmpdens])

qges=[]
qtmp1=[]
qtmp2=[]
qtmp3=[]
qtmp4=[]
qtmp5=[]
qtmp6=[]
qtmp7=[]
qtmp8=[]
for interv in range(len(results[0])):
    tmpq=0.
    tmpflux=0.
    tmpflux2=0.
    sumfl=0.
    for ion in range(3):
        tmpq=tmpq+(results[ion][interv][1]*(4.+float(ion)))
        sumfl=sumfl+(results[ion][interv][1])
    qtmp1.append([results[0][interv][0],(tmpq/sumfl)])
    tmpq=0.
    sumfl=0.
    for ion in range(3):
        tmpq=tmpq+(results[ion+3][interv][1]*(5.+float(ion)))
        sumfl=sumfl+(results[ion+3][interv][1])
    qtmp2.append([results[0][interv][0],(tmpq/sumfl)])
    tmpq=0.
    sumfl=0.
    for ion in range(4):
        tmpq=tmpq+(results[ion+6][interv][1]*(5.+float(ion)))
        sumfl=sumfl+(results[ion+6][interv][1])
    qtmp3.append([results[0][interv][0],(tmpq/sumfl)])
    tmpq=0.
    sumfl=0.
    for ion in range(7):
        tmpq=tmpq+(results[ion+10][interv][1]*(6.+float(ion)))
        sumfl=sumfl+(results[ion+10][interv][1])
    qtmp4.append([results[0][interv][0],(tmpq/sumfl)])
    tmpq=0.
    sumfl=0.
    for ion in range(8):
        tmpq=tmpq+(results[ion+17][interv][1]*(5.+float(ion)))
        sumfl=sumfl+(results[ion+17][interv][1])
    qtmp5.append([results[0][interv][0],(tmpq/sumfl)])
    tmpq=0.
    sumfl=0.
    for ion in range(8):
        tmpq=tmpq+(results[ion+25][interv][1]*(5.+float(ion)))
        sumfl=sumfl+(results[ion+25][interv][1])
    qtmp6.append([results[0][interv][0],(tmpq/sumfl)])
    tmpq=0.
    sumfl=0.
    for ion in range(9):
        tmpq=tmpq+(results[ion+33][interv][1]*(6.+float(ion)))
        sumfl=sumfl+(results[ion+33][interv][1])
    qtmp7.append([results[0][interv][0],(tmpq/sumfl)])
    tmpq=0.
    sumfl=0.
    for ion in range(13):
        tmpq=tmpq+(results[ion+42][interv][1]*(5.+float(ion)))
        sumfl=sumfl+(results[ion+42][interv][1])
    qtmp8.append([results[0][interv][0],(tmpq/sumfl)])
qges.append(qtmp1)
qges.append(qtmp2)
qges.append(qtmp3)
qges.append(qtmp4)
qges.append(qtmp5)
qges.append(qtmp6)
qges.append(qtmp7)
qges.append(qtmp8)

gpqges=[]
for ion in range(8):
    tmpgpq=Data(qges[ion])
    tmpgpq.set_option_colonsep("using", "1:2")
    tmpgpq.set_option_colonsep("title",  "'%s'" %(ion_list2[ion]))
    gpqges.append(tmpgpq)
    
#    qfe.append([results[0][interv][0],(tmpflux2/tmpflux)])

#gpqfe=Data(qfe)
#gpqfe.set_option_colonsep("using", "1:2")
#gpqfe.set_option_colonsep("title",  "'QFe'")


tmpgpsumme=Data(summe)
tmpgpsumme.set_option_colonsep("using", "1:2")
tmpgpsumme.set_option_colonsep("title",  "'O'")


for ion in range(len(ion_list)):
    print ion_list[ion],results[ion]
    print ""
gpresults=[]
tmpion=[]
for ion in range (len(results)):
    tmpgpresults=Data(results[ion])
    tmpgpresults.set_option_colonsep("using", "1:2")
    tmpgpresults.set_option_colonsep("title",  "'%s'" %(ion_list[ion]))
    gpresults.append(tmpgpresults)

gp=Gnuplot()
#gp("set log y")
first=1
for ion in range (len(ion_list)):
    if (first):
        gp.plot(gpresults[ion])
        first=0
    else:
        gp.replot(gpresults[ion])

gp("set xlabel 'SW-Speed'")
gp("set ylabel 'Mean Charge State' ")

first=1
for ion in range (8):
    if (first):
        gp.plot(gpqges[ion])
        first=0
    else:
        gp.replot(gpqges[ion])

gp("set yrange[0:20]")
gp("set xrange[350:710]")
gp("a1=2.")
gp("b1=0.001")
gp("f1(x)=a1*exp(-b1*x)")
gp("fit f1(x) '"+gpqges[0].filename+"' using 1:2 via a1,b1" )
gp("a2=2.")
gp("b2=0.001")
gp("f2(x)=a2*exp(-b2*x)")
gp("fit f2(x) '"+gpqges[1].filename+"' using 1:2 via a2,b2" )
gp("a3=2.")
gp("b3=0.001")
gp("f3(x)=a3*exp(-b3*x)")
gp("fit f3(x) '"+gpqges[2].filename+"' using 1:2 via a3,b3" )
gp("a4=2.")
gp("b4=0.001")
gp("f4(x)=a4*exp(-b4*x)")
gp("fit f4(x) '"+gpqges[3].filename+"' using 1:2 via a4,b4" )
gp("a5=2.")
gp("b5=0.001")
gp("f5(x)=a5*exp(-b5*x)")
gp("fit f5(x) '"+gpqges[4].filename+"' using 1:2 via a5,b5" )
gp("a6=2.")
gp("b6=0.001")
gp("f6(x)=a6*exp(-b6*x)")
gp("fit f6(x) '"+gpqges[5].filename+"' using 1:2 via a6,b6" )
gp("a7=2.")
gp("b7=0.001")
gp("f7(x)=a7*exp(-b7*x)")
gp("fit f7(x) '"+gpqges[6].filename+"' using 1:2 via a7,b7" )
gp("a8=2.")
gp("b8=0.001")
gp("f8(x)=a8*exp(-b8*x)")
gp("fit f8(x) '"+gpqges[7].filename+"' using 1:2 via a8,b8" )
gp("set autoscale")
gp("set xrange[350:710]")

gp.replot("f1(x) t '' lt 1","f2(x) t '' lt 2","f3(x) t '' lt 3","f4(x) t '' lt 4","f5(x) t '' lt 5","f6(x) t '' lt 6","f7(x) t'' lt 7","f8(x) t '' lt 8")
gp("set term postscript color 18 lw 2")
gp.hardcopy("chargestates.ps", color=True, fontsize=18)

#gp.plot(gpqfe)
#gp("f(x)=3.004*exp(-0.00578*x)")
#gp("a=2.")
#gp("b=0.001")
#gp("f(x)=a*exp(-b*x)")
#gp("fit f(x) '"+gpqfe.filename+"' using 1:2 via a,b" )
#gp.replot("f(x)")
#gp.plot(tmpgpsumme)
#Ion             velocity        Flux                    Temp                    Dens
#He2+            559.15          5.8708e+07              1.1575e+06              1.0472e+00
