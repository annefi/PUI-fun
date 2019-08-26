#!/usr/bin/python
from scipy import zeros,exp
from Gnuplot import Gnuplot,GnuplotOpts,Data
from numpy import float,log

GnuplotOpts.prefer_fifo_data=0
GnuplotOpts.prefer_inline_data=0

dim=58
cut_left=0
cut_right=10

def tchfit(x,a,b,c):
    return log(a/(x-c))*b

def phd(x,a,b,c):
    return -a*exp(-(x/b))+c

def e2ech(energy):
    ech=energy*(255./610.78)
    echb=(ech/2.)+0.75
    return echb

def thepos(charge,epq,uacc):
    energy=(epq+uacc)*charge
    ech=energy*(255./610.78)
    echb=(ech/2.)+0.75
    return echb

def writeheader(file,numions,step):
    file.write("Step : "+str(step)+"\tNumberions : "+str(numions)+"\n")
    file.write("Name\t\txpos\t\typos\t\tsigxp\t\tsigxm\t\tsigyp\t\tsigym\t\tvel\t\tmass\t\tcharge\t\tpeakhigh\n")

def writeion(file,name,xpos,ypos,sigxp,sigxm,sigyp,sigym,velocity,mass,charge,peakh):
    file.write("%s\t\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\n" %(name,xpos,ypos,sigxp,sigxm,sigyp,sigym,velocity,mass,charge,peakh))

#ion_list=["O6+","O7+","O8+","He2+","Fe9+","Fe8+","Fe10+","Fe11+"]
#ion_list=["He2+","C5+","N6+","O6+","Ne8+","Mg8+","Si8+","S10+","Ca10+","Fe9+"]
#ion_list=["C4+","C5+","C6+","C3+"]
#ion_list=["O5+","O6+","O7+","O8+"]
#ion_list=["Fe7+","Fe8+","Fe9+","Fe10+","Fe11+","Fe12+","Fe13+"]
#ion_list=["N4+","N5+","N6+","N7+"]
#ion_list=["Mg7+","Mg8+","Mg9+","Mg10+","Mg11+","Mg12+",]
ion_list=["Si7+","Si8+","Si9+","Si10+","Si11+","Si12+",]
#ion_list=["S7+","S8+","S9+","S10+","S11+","S12+",]
#ion_list=["Ca9+","Ca10+","Ca11+","Ca12+","Ca13+","Ca14+"]
#ion_list=["O6+","He1+","He2+","H1+","C4+","C5+","C6+","N6+","N7+","N5+","O6+","O7+","O8+","Mg6+","Mg7+","Mg8+","Mg9+","Mg10+","Fe12+","Fe11+","Fe10+","Fe8+","Fe9+","Fe7+","S10+","S11+","S9+","S8+","Si10+","Si11+","Si9+","Si8+","Ca6+","Ca10+","Ne8+"]
#ion_list=["Fe24+","Fe23+","Fe22+","Fe21+","Fe20+","Fe19+","Fe18+","Fe17+","Fe16+","Fe15+","Fe14+","Fe13+","Fe12+","Fe11+","Fe10+","Fe8+","Fe9+","Fe7+","Fe6+","Fe5+","Fe4+","Fe3+","Fe2+"]
#ion_list=["O1+","O2+","O3+","O4+","O5+","O6+","O7+","O8+"]
#ion_list=["C1+","C2+","C3+","C4+","C5+","C6+","N1+","N2+","N3+","N4+","N5+","N6+","N7+"]
#ion_list=["Mg6+","Mg7+","Mg8+","Mg9+","Mg10+"]
ion1_sigxp=[]
ion1_sigxm=[]
ion1_sigyp=[]
ion1_sigym=[]
ion2_sigxp=[]
ion2_sigxm=[]
ion2_sigyp=[]
ion2_sigym=[]
ion_sigxp=[]
ion_sigxm=[]
ion_sigyp=[]
ion_sigym=[]
ion_sigx=[]
ion_sigy=[]

for ion in range(len(ion_list)):
    one_ion_sigxp=[]
    one_ion_sigxm=[]
    one_ion_sigyp=[]
    one_ion_sigym=[]
    
    f=open("/home/ivar/berger/projects/ionpositions/erg_ion_para_mu_24_newtof_clean_all.dat")
    for step in range(dim):
        print step
        s=f.readline()
        k=s.split()
        numberions=int(k[5])
        s=f.readline()
        for ionstep in range(numberions):
            s=f.readline()
            k=s.split()
            if ((k[0]==ion_list[ion])and(step<=60)):
                one_ion_sigxp.append([float(step),float(k[3])])
                one_ion_sigxm.append([float(step),float(k[4])])
                one_ion_sigyp.append([float(step),float(k[5])])
                one_ion_sigym.append([float(step),float(k[6])])

    ion1_sigxp.append(one_ion_sigxp)
    ion1_sigxm.append(one_ion_sigxm)
    ion1_sigyp.append(one_ion_sigyp)
    ion1_sigym.append(one_ion_sigym)
    f.close()

for ion in range(len(ion_list)):
    one_ion_sigxp=[]
    one_ion_sigxm=[]
    one_ion_sigyp=[]
    one_ion_sigym=[]
    
    f=open("/home/ivar/berger/projects/ionpositions/ion_para_mu_24_newtof_clean.dat")
    for step in range(dim):
        print step
        s=f.readline()
        k=s.split()
        numberions=int(k[5])
        s=f.readline()
        for ionstep in range(numberions):
            s=f.readline()
            k=s.split()
            if ((k[0]==ion_list[ion])and(step<=60)):
                one_ion_sigxp.append([float(step),float(k[3])])
                one_ion_sigxm.append([float(step),float(k[4])])
                one_ion_sigyp.append([float(step),float(k[5])])
                one_ion_sigym.append([float(step),float(k[6])])

    ion2_sigxp.append(one_ion_sigxp)
    ion2_sigxm.append(one_ion_sigxm)
    ion2_sigyp.append(one_ion_sigyp)
    ion2_sigym.append(one_ion_sigym)
    f.close()

for ion in range(len(ion_list)):
    one_ion_sigxp=[]
    one_ion_sigxm=[]
    one_ion_sigyp=[]
    one_ion_sigym=[]
    for step in range(len(ion1_sigxp[ion])):
        one_ion_sigxp.append([ion1_sigxp[ion][step][0],(ion1_sigxp[ion][step][1]/ion2_sigxp[ion][step][1])])
        one_ion_sigxm.append([ion1_sigxp[ion][step][0],(ion1_sigxm[ion][step][1]/ion2_sigxm[ion][step][1])])
        one_ion_sigyp.append([ion1_sigxp[ion][step][0],(ion1_sigyp[ion][step][1]/ion2_sigyp[ion][step][1])])
        one_ion_sigym.append([ion1_sigxp[ion][step][0],(ion1_sigym[ion][step][1]/ion2_sigym[ion][step][1])])
    ion_sigxp.append(one_ion_sigxp)
    ion_sigxm.append(one_ion_sigxm)
    ion_sigyp.append(one_ion_sigyp)
    ion_sigym.append(one_ion_sigym)

for ion in range(len(ion_list)):
    one_ion_sigx=[]
    one_ion_sigy=[]
    for step in range(len(ion1_sigxp[ion])):
        one_ion_sigx.append([ion1_sigxp[ion][step][0],((ion1_sigxp[ion][step][1]+ion1_sigxm[ion][step][1])/(ion2_sigxp[ion][step][1]+ion2_sigxm[ion][step][1]))])
        one_ion_sigy.append([ion1_sigxp[ion][step][0],((ion1_sigyp[ion][step][1]+ion1_sigym[ion][step][1])/(ion2_sigyp[ion][step][1]+ion2_sigym[ion][step][1]))])
    ion_sigx.append(one_ion_sigx)
    ion_sigy.append(one_ion_sigy)
        
ion_sigxp_plot=[]
for ion in range(len(ion_list)):
    ion_sigxp_plot_tmp=Data(ion_sigxp[ion])
    ion_sigxp_plot_tmp.set_option_colonsep("using", "1:2")
    ion_sigxp_plot_tmp.set_option_colonsep("title",  "'%ssigxp'" %(ion_list[ion]))
    ion_sigxp_plot.append(ion_sigxp_plot_tmp)

ion_sigxm_plot=[]
for ion in range(len(ion_list)):
    ion_sigxm_plot_tmp=Data(ion_sigxm[ion])
    ion_sigxm_plot_tmp.set_option_colonsep("using", "1:2")
    ion_sigxm_plot_tmp.set_option_colonsep("title",  "'%ssigxm'" %(ion_list[ion]))
    ion_sigxm_plot.append(ion_sigxm_plot_tmp)

ion_sigyp_plot=[]
for ion in range(len(ion_list)):
    ion_sigyp_plot_tmp=Data(ion_sigyp[ion])
    ion_sigyp_plot_tmp.set_option_colonsep("using", "1:2")
    ion_sigyp_plot_tmp.set_option_colonsep("title",  "'%ssigyp'" %(ion_list[ion]))
    ion_sigyp_plot.append(ion_sigyp_plot_tmp)

ion_sigym_plot=[]
for ion in range(len(ion_list)):
    ion_sigym_plot_tmp=Data(ion_sigym[ion])
    ion_sigym_plot_tmp.set_option_colonsep("using", "1:2")
    ion_sigym_plot_tmp.set_option_colonsep("title",  "'%ssigym'" %(ion_list[ion]))
    ion_sigym_plot.append(ion_sigym_plot_tmp)

ion_sigx_plot=[]
for ion in range(len(ion_list)):
    ion_sigx_plot_tmp=Data(ion_sigx[ion])
    ion_sigx_plot_tmp.set_option_colonsep("using", "1:2")
    ion_sigx_plot_tmp.set_option_colonsep("title",  "'%ssigx'" %(ion_list[ion]))
    ion_sigx_plot.append(ion_sigx_plot_tmp)

ion_sigy_plot=[]
for ion in range(len(ion_list)):
    ion_sigy_plot_tmp=Data(ion_sigy[ion])
    ion_sigy_plot_tmp.set_option_colonsep("using", "1:2")
    ion_sigy_plot_tmp.set_option_colonsep("title",  "'%ssigy'" %(ion_list[ion]))
    ion_sigy_plot.append(ion_sigy_plot_tmp)

gp=Gnuplot()
#gp("set xrange[100:260]")
gp("set yrange[0:5]")
gp("set title 'ion_sigp'")

gp.plot(ion_sigym_plot[0])
for ion in range(len(ion_list)-1):
    gp.replot(ion_sigym_plot[ion+1])

#gp.plot(ion_sigxp_plot[0],ion_sigxm_plot[0],ion_sigyp_plot[0],ion_sigym_plot[0])
#for ion in range(len(ion_list)-1):
#    gp.replot(ion_sigxp_plot[ion+1],ion_sigxm_plot[ion+1],ion_sigyp_plot[ion+1],ion_sigym_plot[ion+1])
    

gp.hardcopy("ion_sig.ps",color=True,fontsize=18)






