from os import system
from scipy.linalg import inv
from scipy import zeros, dot
from numpy import float
from Gnuplot import Gnuplot, GridData, GnuplotOpts
GnuplotOpts.prefer_fifo_data=False
GnuplotOpts.prefer_inline_data=False
#GnuplotOpts.recognizes_binary_splot=False
from math import sin,cos,tan,asin,acos,atan
from os import popen2
from sys import stdin

Float=float
matrixmultiply=dot


gp=Gnuplot()
gp2=Gnuplot()
gp3=Gnuplot()

xx=zeros([500000,3],Float)
ech=zeros([128],Float)
tch=zeros([512],Float)
data=zeros([128,512],Float)
datagrid=None

res=zeros([600,28],Float)
tof_data=zeros([512,5],Float)
e_data=zeros([128,3])
low=300
high=300
do=int(1)
counter=0
ehpl1=zeros([1000],Float)
ehpl2=zeros([1000],Float)


gp("g1(x)=bg+G1*exp(-0.5*((x-x1)/sg1)**2)")
gp("g2(x)=bg+G1*exp(-0.5*((x-x1)/sg2)**2)")
gp("r1(x)=bg+G1*exp(-0.5*((x-x1)/sr1)**2)")
gp("r1(x)=bg+G1*exp(-(x-x1)**2/(2*sr1**2)*(1+((x-x1)**2/(2*sr1**2*gamma1))**0.5))")
gp("r2(x)=bg+G1*exp(-(x-x1)**2/(2*sr1**2)*(1+((x-x1)**2/(2*sr1**2*gamma)))**-0.5)")
gp("l1(x)=bg+G1*(1+((x-x1)**2/(4*sl1**2)))**-2")
gp("l2(x)=bg+G1*(1+((x-x1)**2/(4*sl2**2)))**-2")
gp("k1(x)=bg+G1*(1+((x-x1)**2/(kappa1*sk1**2)))**-(kappa1) ")
gp("k2(x)=bg+G1*(1+((x-x1)**2/(kappa2*sk2**2)))**-(kappa2) ")

gp3("g1(x)=bg+G1*exp(-0.5*((x-x1)/sg1)**2)")
gp3("g2(x)=bg+G1*exp(-0.5*((x-x1)/sg2)**2)")
gp3("r1(x)=bg+G1*exp(-0.5*((x-x1)/sr1)**2)")
gp3("r1(x)=bg+G1*exp(-(x-x1)**2/(2*sr1**2)*(1+((x-x1)**2/(2*sr1**2*gamma1))**0.5))")
gp3("r2(x)=bg+G1*exp(-(x-x1)**2/(2*sr1**2)*(1+((x-x1)**2/(2*sr1**2*gamma)))**-0.5)")
gp3("l1(x)=bg+G1*(1+((x-x1)**2/(4*sl1**2)))**-2")
gp3("l2(x)=bg+G1*(1+((x-x1)**2/(4*sl2**2)))**-2")
gp3("k1(x)=bg+G1*(1+((x-x1)**2/(kappa1*sk1**2)))**-(kappa1) ")
gp3("k2(x)=bg+G1*(1+((x-x1)**2/(kappa2*sk2**2)))**-(kappa2) ")

system("rm neue_fitergebnisse/gebinnt/fit_res_all_lg_rk_obg" )
for ion in ["o2","fe","si","h","mg","ne","o3","s"]:
#for ion in ["o2"]:
    swxli=[]
    file0=open("ncfn/"+ion)
    for i in file0:
        x=i.split()
        swxli+=[int(x[0])]
    file0.close()

    for n in swxli:
        data=zeros([128,512],Float)

        counter+=1
        try:
            file1=open("/home/kleopatra/mu/daten/giessen/swxli"+str(n)+"_binned.hstt")
        except IOError:
            print "swxli"+str(n)+"_binned.hst existiert nicht"
            continue
        l=0
        for i in file1:
            x=i.split()
            for j in range(3):
                tof_data[l,j]=float(x[j])
            l+=1
        file1.close()

        try:
            file1=open("/home/kleopatra/mu/daten/giessen/swxli"+str(n)+"_binned.hste")
        except IOError:
            print "swxli"+str(n)+"_binned.hste existiert nicht"
            continue
        p=0
        for i in file1:
            x=i.split()
            for j in range(3):
                e_data[p,j]=float(x[j])
            p+=1
        file1.close()


        try:
            mp=open("/data/kleopatra/mu/jahresdaten/matrices/swxli"+str(n)+"_matrix_binned")
        except IOError:
            print "swxli"+str(n)+"_matrix_binned existiert nicht"
            continue

        ll=0
        ii=0
        for jj in mp:
            tt=jj.split()
            data[ll,ii]=float(tt[2])
            ii+=1
            if (ii ==512):
                ii=0
                ll+=1
        mp.close()

        datagrid=GridData(data)



# Bestimmen der Startwerte der Maxima, Positionen und Breiten

# ToF
        hd = 0.
        hp = 0.
        for i in range(1,l):
            if (hd < tof_data[i,1]):
                hd = tof_data[i,1]
                hp = float(i)

        sld = hd
        slp = 0.
        for i in range(int(hp),50,-1):
            if (sld > hd*0.6):
                sld = tof_data[i,1]
                slp = float(i)
        srd=hd
        srp = 0.
        for i in range(int(hp),512):
            if (srd > hd*0.6):
                srd = tof_data[i,1]
                srp = float(i)
        sl = hp - slp
        sr = srp - hp

        rld = hd
        rlp = 0.
        twarning = int(0)
        for i in range(int(hp),int(hp)-25,-1):
            if (rld > hd*0.01):
                rld = tof_data[i,1]
                rlp = float(i)
        if (int(rlp) == hp-24):
            twarning += 1

        rrd = hd
        rrp = 0.
        for i in range(int(hp),512):
            if (rrd > hd*0.01):
                rrd = tof_data[i,1]
                rrp = float(i)
        if (int(rrp) == 511):
                twarning += 2

        if (twarning == 1):
            print "**** ToF - WARNUNG **** LINKE RANGE IST HP -24"
        if (twarning == 2):
            print "**** ToF - WARNUNG **** RECHTE RANGE IST 511"
        if (twarning == 3):
            print "**** ToF - WARNUNG **** BEIDE RANGE-LIMITS FEHLGESCHLAGEN"


# Energie

        ehd = 0.
        ehp = 0.
        for i in range(10,p):
            if (ehd < e_data[i,1]):
                ehd = e_data[i,1]
                ehp = float(i)
        ehpl1[n]=ehp
        esld = ehd
        eslp = 0.
        for i in range(int(ehp),6,-1):
            print esld, ehd
            if (esld > ehd*0.6):
                esld = e_data[i,1]
                eslp = float(i)
        esrd=ehd
        esrp = 0.
        for i in range(int(ehp),128):
            if (esrd > ehd*0.6):
                esrd = e_data[i,1]
                esrp = float(i)
        esl = ehp - eslp
        esr = esrp - ehp

        erld = ehd
        erlp = 0.
        ewarning = int(0)
        for i in range(int(ehp),5,-1):
            if ((erld > ehd*0.01) or (erld > 5)):
                erld = e_data[i,1]
                erlp = float(i)
        if (int(erlp) == 6):
            ewarning += 1

        errd = ehd
        errp = 0.
        for i in range(int(ehp),128):
            if ((errd > hd*0.01)or (errd > 5)) :
                errd = e_data[i,1]
                errp = float(i)
        if (int(errp) == 127):
                ewarning += 2

        if (ewarning == 1):
            print "**** E - WARNUNG **** LINKE RANGE ISt 6"
        if (ewarning == 2):
            print "**** E - WARNUNG **** RECHTE RANGE IST 127"
        if (ewarning == 3):
            print "**** E - WARNUNG **** BEIDE RANGE-LIMITS FEHLGESCHLAGEN"

# Fitten

# ToF

        gp("set xrange["+str(int(rlp))+":"+str(int(rrp))+"]")
        gp("sg1="+str(sl))
        gp("sk1="+str(sl))
        gp("sk2="+str(sr))
        gp("G1="+str(hd))
        gp("x1="+str(hp))
        gp("bg=0")
        gp("kappa1=2.")
        gp("kappa2=2.")
        gp("s(x)=x<x1 ? g1(x):k2(x)")
        gp("fit s(x) '~/daten/giessen/swxli"+str(n)+"_binned.hstt' u 1:2:3 via G1,sg1,sk2,x1,kappa2")
        #gp("s(x)=x<x1 ? k1(x):k2(x)")
        #gp("fit s(x) '~/daten/giessen/swxli"+str(n)+"_binned.hstt' u 1:2:3 via G1,sk1,sk2,x1,kappa1,kappa2")
        gp("plot  s(x), '/home/kleopatra/mu/daten/giessen/swxli"+str(n)+"_binned.hstt' u 1:2:3 with errorbars")

        res[n,0]=float(str(gp.eval("x1")))
        res[n,1]=float(str(gp.eval("sg1")))
        #res[n,1]=float(str(gp.eval("sk1")))
        res[n,2]=float(str(gp.eval("sk2")))
        res[n,3]=float(str(gp.eval("kappa1")))
        res[n,4]=float(str(gp.eval("G1")))
        res[n,5]=float(str(gp.eval("bg")))
        res[n,6]=float(str(gp.eval("kappa2")))


# Energie

        gp3("set xrange["+str(int(erlp))+":"+str(int(errp))+"]")
        gp3("sg1="+str(esl))
        gp3("sk1="+str(esl))
        gp3("sk2="+str(esr))
        gp3("G1="+str(ehd))
        gp3("x1="+str(ehp))
        gp3("bg=0")
        gp3("kappa1=2.")
        gp3("kappa2=2.")
        gp3("s(x)=x<x1 ? k2(x):g1(x)")
        gp3("fit s(x) '~/daten/giessen/swxli"+str(n)+"_binned.hste' u 1:2:3 via G1,sg1,sk2,x1,kappa2")
        gp3("set xrange[1:"+str(int(errp)+50)+"]")
        gp3("plot  s(x), '/home/kleopatra/mu/daten/giessen/swxli"+str(n)+"_binned.hste' u 1:2:3 with errorbars")

        res[n,7]=float(str(gp3.eval("x1")))
        res[n,8]=float(str(gp3.eval("sk2")))
        res[n,9]=float(str(gp3.eval("sg1")))
        res[n,10]=float(str(gp3.eval("kappa1")))
        res[n,11]=float(str(gp3.eval("G1")))
        res[n,12]=float(str(gp3.eval("bg")))
        res[n,13]=float(str(gp3.eval("kappa2")))

        gp2("set xrange[1:200]")
        gp2("set yrange["+str(hp-20)+":"+str(hp+50)+"]")
        gp2("set pm3d map")
        gp2("set logscale z")
        gp2.splot(datagrid)

 
#       1. Fitvorgang abgeschlossen

        
    if (do == 1):
        file1=open("neue_fitergebnisse/gebinnt/fit_res_all_lg_rk_obg","a")
        file2=open("neue_fitergebnisse/gebinnt/fit_res_"+ion+"_lg_rk_obg","w")
        for i in swxli:
            if (int(ehpl1[i]) >= 12):
                if (int(res[i,4]) >= 500):
                    file1.write(str(i))
                    file1.write("   ")
                    file2.write(str(i))
                    file2.write("   ")
                    for j in range(14):
                        file1.write(str(res[i,j]))
                        file1.write("   ")
                        file2.write(str(res[i,j]))
                        file2.write("   ")
                    file1.write("\n")
                    file2.write("\n")
        file1.close()
        file2.close()



