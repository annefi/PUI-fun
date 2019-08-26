from Gnuplot import Gnuplot,Data
from math import pi,exp,sqrt

def factor(a,b):
    if (a<=b):
        return 1.
    else:
        return sqrt((a**2*b**2)/(a**2-b**2))

class cascade:
    def __init__(self,B,power,index,eff,ions,vsw,valf):
        "B\t->\t float : magnetic field strength in nT\npower\t->\t float : scales the wavepower spectrum\nindex\t->\t float : spectral index of cascade\neff\t->\t float : efficiency for energy drain from cascade\nions\t->\t [nrions][ioname(str),ionmass(float,in amu),ioncharge(float,in e),iondens(float,in respect to protons)\nvsw\t->\t float : solar wind speed\nvalf\t->\t float : alfven speed"
        self.B=B*1e-9
        self.power=power
        self.index=index
        self.eff=eff
        self.vsw=vsw
        self.valf=valf
        self.name=[]
        self.dens=[]
        self.mass=[]
        self.mqarr=[]
        self.charge=[]
        self.sequence=[]
        for ion in ions:
            self.name.append(ion[0])
            self.mass.append(ion[1])
            self.charge.append(ion[2])
            self.dens.append(ion[3])
            self.mqarr.append(ion[2]/ion[1])
            self.sequence.append(0)
        self.qm0=1.602176487e-19/1.66053886e-27
        self.warr=[]
        self.dim=len(self.mqarr)

        self.get_sequence()
        self.build_warr()
        self.calc_casc()

    def set_index(self,a):
        self.index=a

    def set_B(self,a):
        self.B=a*1e-9

    def set_efficiency(self,a):
        self.eff=a

    def build_warr(self):
        "calculates the resonance frequencies"
        for i in self.sequence:
            self.warr.append(-(self.mqarr[i]*self.qm0*self.B)/(1.-self.vsw/self.valf))

    def get_sequence(self):
        mqarr=[]
        sequence=[]
        for val in self.mqarr:
            mqarr.append(val)
        for i in range(self.dim):
            maxval=min(mqarr)
            maxpos=0
            i=0
            while (mqarr[i]!=maxval):
                i+=1
            maxpos=i
            """    
            for i in range(self.dim):
                if (mqarr[i]==maxval):
                    maxpos=i
            """
            sequence.append(maxpos)
            newmqarr=[]
            for i in range(self.dim):
                if (i!=maxpos):
                    newmqarr.append(mqarr[i])
                else:
                    newmqarr.append(100.)
            mqarr=[]
            for val in newmqarr:
                mqarr.append(val)
        self.sequence=sequence

    def calc_casc(self):
        Parr=[[.01,self.power]]
        dParr=[[.01,0.]]
        for i in range(self.dim):
            Parr.append([self.warr[i],0.])
            dParr.append([self.warr[i],0.])
        Parr[0][1]=(self.power*Parr[0][0]**-self.index)
        dParr[0][1]=(self.power*Parr[0][0]**-self.index)
        #dParr[0][1]=0.
        Parr[1][1]=(self.power*Parr[1][0]**-self.index)-(self.power*Parr[1][0]**-self.index)*self.dens[self.sequence[0]]*self.eff*self.charge[self.sequence[0]]**2/self.mass[self.sequence[0]]
        dParr[1][1]=(self.power*Parr[1][0]**-self.index)*self.dens[self.sequence[0]]*self.eff*self.charge[self.sequence[0]]**2/self.mass[self.sequence[0]]
        for i in range(self.dim-1):
            P0=(self.power*Parr[i+2][0]**-self.index)-((self.power*Parr[i+1][0]**-self.index)-Parr[i+1][1])
            dP=P0*self.dens[self.sequence[i+1]]*self.eff*self.charge[self.sequence[i+1]]**2/self.mass[self.sequence[i+1]]
            print "P0,dP"
            print P0,dP
            if (dP<P0):
                Parr[i+2][1]=P0-dP
            else:
                Parr[i+2][1]=1.
                dP=P0
            dParr[i+2][1]=dP
            if (i==0):
                dParr[i+2][1]=dP
            if (i==1):
                dParr[i+2][1]=dP
            if (i==2):
                dParr[i+2][1]=dP
        self.Parr=Parr
        self.dParr=dParr

        dParr2=[]
        dParr3=[]
        dVarr=[]

        E0=0.
        ppos=0
        hepos=0
        for j in range(len(self.sequence)):
            if (self.name[self.sequence[j]]=="H1+"):
                ppos=j
            if (self.name[self.sequence[j]]=="He2+"):
                hepos=j
        for i in range(self.dim):
            pos=self.sequence[i]
            print "pos = ",i,self.sequence[i],pos
            print "p,hepos = ",ppos,hepos
            dParr2.append([dParr[i+1][0],(dParr[i+1][1]/self.dens[pos])/(dParr[ppos+1][1]/self.dens[self.sequence[ppos]])])
            # dv/dvHe
            #a=sqrt((dParr[i+1][1]*2./self.dens[i]**2)/self.mass[i])*(self.charge[i]**1.5/self.mass[i])/(sqrt((dParr[self.dim-3][1]*2./self.dens[self.dim-4]**2)/self.mass[self.dim-4])*(self.charge[self.dim-4]**1.5/self.mass[self.dim-4]))

            a=sqrt((dParr[i+1][1]*2./self.dens[pos]**1.)/self.mass[pos])*(self.charge[pos]**1.5/self.mass[pos]**1.)/(sqrt((dParr[hepos+1][1]*2./self.dens[self.sequence[hepos]]**1.)/self.mass[self.sequence[hepos]])*(self.charge[self.sequence[hepos]]**1.5/self.mass[self.sequence[hepos]]**1.))
            # b = E/Ep
            b=(dParr[i+1][1]/self.dens[pos])/(dParr[ppos+1][1]/self.dens[self.sequence[ppos]])
            
            print a,b
            #dParr3.append([self.mass[i]/self.charge[i],(a)*(self.charge[i]**1.5/self.mass[i])])
            dParr3.append([self.charge[pos]/self.mass[pos],b])
            dVarr.append([self.charge[pos]/self.mass[pos],a])
        pdParr=[]
        pdVarr=[]
        self.pdVarr=[]
        self.pdParr=[]
        for j in range(self.dim):
            for k in range(self.dim):
                if (self.name[self.sequence[k]]==self.name[j]):
                    pos=k
                    if (self.name[j]!="H1+"):
                        self.pdVarr.append(Data([dVarr[pos]]))
                    self.pdVarr[len(self.pdVarr)-1].set_option_colonsep("with","p pt %i lt 3"%(j+1))
                    self.pdParr.append(Data([dParr3[pos]]))
                    if (self.name[j]=="H1+"):
                        self.pdParr[len(self.pdParr)-1].set_option_colonsep("title","'%s'"%("H^{1+}"))
                    if (self.name[j]=="H1+"):
                        self.pdParr[len(self.pdVarr)-1].set_option_colonsep("with","p pt %i lt 1"%(j+1))
                    else:
                        self.pdParr[len(self.pdVarr)-1].set_option_colonsep("with","p pt %i lt 3"%(j+1))

        self.dParr2=dParr2
        self.dParr3=dParr3
        self.dVarr=dVarr


    def plot(self):

        self.gp=Gnuplot()
        #self.gp("set autoscale")
        self.gp("set size square")
        self.gp("set xrange[0.01:.1]")
        self.gp("set yrange[100.:1000.]")
        self.gp("set format xy '10^%T'")
        self.gp("set xlabel '{/Symbol w} [Hz]'")
        self.gp("set ylabel 'Wave Power [arb.]'")
        self.gp("set logscale xy")
        self.pParr=Data(self.Parr)
        self.pParr.set_option_colonsep("with","lp")
        self.gp.plot(self.pParr)
        #self.gp.replot(Data(self.dParr2))
        #self.gp.replot(Data(self.dParr2))
        self.gp("a=%f"%(self.power))
        self.gp("k=%f"%(self.index))
        self.gp("f(x)=a*x**-k")
        self.gp("f2(x)=(a*.7)*x**-(k+.1)")
        self.gp("f3(x)=(a*1e-5)*x**-(k+4.)")
        #self.gp.replot("f(x) with l lt 3","f2(x) with l lt 4","f3(x) with l lt 5")
        self.gp("set term postscript color 18 lw 2 eps")
        self.gp.hardcopy("Pcascall.ps",color="true",fontsize=18)
        self.gp2=Gnuplot()
        self.gp2("set logscale xy")
        self.gp2("set title 'theocasc dE'")
        #gp2("set yrange[1:1.1]")
        first=1
        for j in range(self.dim):
            if (first==1):
                self.gp2.plot(self.pdParr[j])
                first=0
            else:
                self.gp2.replot(self.pdParr[j])
        self.gp3=Gnuplot()
        self.gp3("set logscale xy")
        self.gp3("set title 'theocasc dV'")
        first=1
        for j in range(self.dim):
            if (first==1):
                self.gp3.plot(self.pdVarr[j])
                first=0
            else:
                self.gp3.replot(self.pdVarr[j])

