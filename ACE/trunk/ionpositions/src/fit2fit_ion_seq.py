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

epq_arr=zeros([dim],float)
epq_arr = [86.6359,75.0485,65.0109,56.3158,48.7837,42.2589,36.6069,31.7108,27.4695,23.7955,20.6129,17.856,16.619,15.4678,14.3962,13.399,12.4708,11.6069,10.8028,10.0545,9.35797,8.70971,8.10635,7.5448,7.02214,6.5357,6.08294,5.66156,5.26936,4.90433,4.56459,4.24839,3.95409,3.68017,3.42523,3.18796,2.96711,2.76157,2.57027,2.39222,2.2265,2.07226,1.92871,1.7951,1.67075,1.55501,1.44729,1.34703,1.25372,1.16687,1.08603,1.0108,0.940778,0.875607,0.81495,0.758496,0.705952,0.657048,0.611532,0.55]

print len(epq_arr)
Eacc=24.868179
#Eacc=21.3
ion_list=["3He2+","He2+","C6+","N5+","O6+","O7+","Ne8+","Mg10+","Si10+","S10+","Fe10+"]
#ion_list=["3He2+","He2+","C6+","13C6+","N5+","O6+","O7+","Ne8+","Mg10+","Si10+","S10+","Ca10+","Fe10+"]
#ion_list=["O6+","O7+","O8+","C4+","C5+","C6+","13C4+","13C5+","13C6+","N5+","N6+","He2+","3He2+","3He1+","Fe9+","Fe8+","Fe10+","Fe11+"]
#ion_list=["O6+","O7+","O8+","He2+","Fe9+","Fe8+","Fe10+","Fe11+"]
#ion_list=["O6+","C5+","N6+","He2+"]

#ion_list=["O6+","He1+","He2+","H1+","C4+","C5+","C6+","N6+","N7+","N5+","O6+","O7+","O8+","Mg6+","Mg7+","Mg8+","Mg9+","Mg10+","Fe12+","Fe11+","Fe10+","Fe8+","Fe9+","Fe7+","S10+","S11+","S9+","S8+","Si10+","Si11+","Si9+","Si8+","Ca6+","Ca10+","Ne8+"]
#ion_list=["Fe24+","Fe23+","Fe22+","Fe21+","Fe20+","Fe19+","Fe18+","Fe17+","Fe16+","Fe15+","Fe14+","Fe13+","Fe12+","Fe11+","Fe10+","Fe8+","Fe9+","Fe7+","Fe6+","Fe5+","Fe4+","Fe3+","Fe2+"]
#ion_list=["O1+","O2+","O3+","O4+","O5+","O6+","O7+","O8+"]
#ion_list=["C1+","C2+","C3+","C4+","C5+","C6+","N1+","N2+","N3+","N4+","N5+","N6+","N7+"]
#ion_list=["Mg6+","Mg7+","Mg8+","Mg9+","Mg10+"]
ion_data=[]
ion_phd=[]
ion_sigp=[]
ion_sigm=[]

for ion in range(len(ion_list)):
    one_ion_data=[]
    one_ion_phd=[]
    one_ion_sigp=[]
    one_ion_sigm=[]
    
#    f=open("/home/ivar/berger/projects/ionpositions/erg_ion_para_mu_24_newtof_clean_all.dat")
#    f=open("/home/ivar/berger/projects/ionpositions/ion_para_mu_24_newtof_clean.dat")
    f=open("/home/ivar/berger/projects/ionpositions/ion_para_fmjim_clean.dat")
#    f=open("/home/ivar/berger/projects/ionpositions/ion_para_mu_24_isotopes_clean_filter.dat")
#    f=open("/home/ivar/berger/projects/ionpositions/erg_ion_para_mu_24_clean_all.dat")
#    f=open("/home/ivar/berger/projects/ionpositions/ion_para_mu_24_clean.dat")
#    f=open("/home/ivar/berger/projects/ionpositions/erg_ion_para_fmjim_clean.dat")
#    f=open("/home/ivar/berger/projects/ionpositions/ion_para_fmjim_mu_24_clean1-15.dat")
#    f=open("/home/ivar/berger/projects/ionpositions/ion_para_fmjim_clean.dat")
#    f=open("/home/ivar/berger/projects/ionpositions/erg_ion_para_fmjim_21_clean.dat")
#    f=open("/home/ivar/berger/projects/ionpositions/ion_para_fmjim_mu_24_clean3_all.dat")
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
            #and ((((step>=7) and (step <=11))) or (((step>=16) and (step <=39))))):
                one_ion_data.append([float(k[1]),float(k[2])])
                one_ion_phd.append([float((epq_arr[step]+Eacc)*float(k[9])),float(k[2])/float(thepos(float(k[9]),epq_arr[step],Eacc)),float(k[9])])
                one_ion_sigp.append([(float(k[1])+float(k[3])),(float(k[2])+float(k[5]))])
                one_ion_sigm.append([(float(k[1])-float(k[4])),(float(k[2])-float(k[6]))])
#                one_ion_phd.append([float(step),float(k[2])/float(thepos(float(k[9]),epq_arr[step],Eacc)),float(k[9])])

    ion_data.append(one_ion_data)
    ion_phd.append(one_ion_phd)
    ion_sigp.append(one_ion_sigp)
    ion_sigm.append(one_ion_sigm)
    f.close()

ion_data_plot=[]
for ion in range(len(ion_list)):
    ion_data_plot_tmp=Data(ion_data[ion])
    ion_data_plot_tmp.set_option_colonsep("using", "1:2")
    ion_data_plot_tmp.set_option_colonsep("title",  "'%s'" %(ion_list[ion]))
    ion_data_plot.append(ion_data_plot_tmp)

ion_phd_plot=[]
for ion in range(len(ion_list)):
    ion_phd_plot_tmp=Data(ion_phd[ion])
    ion_phd_plot_tmp.set_option_colonsep("using", "1:2")
    ion_phd_plot_tmp.set_option_colonsep("title",  "'%s'" %(ion_list[ion]))
    ion_phd_plot.append(ion_phd_plot_tmp)

ion_sigp_plot=[]
for ion in range(len(ion_list)):
    ion_sigp_plot_tmp=Data(ion_sigp[ion])
    ion_sigp_plot_tmp.set_option_colonsep("using", "1:2")
    ion_sigp_plot_tmp.set_option_colonsep("title",  "'%ssigp'" %(ion_list[ion]))
    ion_sigp_plot.append(ion_sigp_plot_tmp)

ion_sigm_plot=[]
for ion in range(len(ion_list)):
    ion_sigm_plot_tmp=Data(ion_sigm[ion])
    ion_sigm_plot_tmp.set_option_colonsep("using", "1:2")
    ion_sigm_plot_tmp.set_option_colonsep("title",  "'%ssigm'" %(ion_list[ion]))
    ion_sigm_plot.append(ion_sigm_plot_tmp)

gp=Gnuplot()
gp("set xrange[50:300]")
gp("set yrange[0:128]")
gp("set title 'Ion Positions from Simon Hefti' ")
gp("f(x)=6.")
gp("a=200.")
gp("b=200.")
gp("c=10.")
gp("a2=0.4")
gp("b2=150.0")
gp("c2=0.75")
gp("a3=500.")
gp("b3=200.")
gp("c3=10.")
gp("a4=3.76693")
gp("b4=3354.86")
gp("c4=4.10341")
gp("a5=500.")
gp("b5=200.")
gp("c5=10.")
gp("d=0.005")
gp("w(x)=a*(1/sqrt(x+b))+c")
gp("e(x)=a2*exp(-(x/b2))+c2")
gp("g(x)=a*exp(-(x/b))+c")
gp("phd(x)=-a2*exp(-(x/b2))+c2")
gp("phd2(x)=-a4*exp(-(x/b4))+c4")
gp("k=0.86")
gp("k2=0.5")
gp("k3=0.5")
gp("k4=0.5")
gp("m0=8.")
gp("x0=100.")
gp("x1=50.")
gp("x2=300.")
gp("He(x)=((2./m0)**k)/(x/x0)**k2*g(x))")
gp("C(x)=(6./m0)**k/(x/x2)**k4*g(x)")
gp("N(x)=(7./m0)**k*g(x)")
gp("O(x)=((8./m0)**k)*g(x)")
gp("Ne(x)=(10./m0)**k*g(x)")
gp("Mg(x)=(12./m0)**k*g(x)")
gp("Si(x)=(14./m0)**k*g(x)")
gp("S(x)=(16./m0)**k*g(x)")
gp("Ca(x)=(20./m0)**k*g(x)")
gp("Fe(x)=((26./m0)**k)/(x/x1)**k3*g(x)")

gp("g2(x)=a3*exp(-(x/b3))+c3")
gp("g3(x)=a3*exp(-(x/b3))+c3")
gp("g4(x)=a4*exp(-(x/b4))+c4")
gp("g5(x)=a5*exp(-(x/b5))+c5")
#gp("fit phd(x) '"+ion_phd_plot[0].filename+"' using 1:2 via a2,b2,c2")
#gp("fit phd2(x) '"+ion_phd_plot[1].filename+"' using 1:2 via a4,b4,c4")
phda=gp.eval("a2")
phdb=gp.eval("b2")
phdc=gp.eval("c2")
#gp("fit g(x) '"+ion_data_plot[0].filename+"' using 1:2 via a,b,c")
#gp("fit He(x) '"+ion_data_plot[1].filename+"' using 1:2 via x0,k2")
#gp("fit C(x) '"+ion_data_plot[2].filename+"' using 1:2 via x2,k3")
#gp("fit Fe(x) '"+ion_data_plot[3].filename+"' using 1:2 via x1,k4")
#gp("fit g3(x) '"+ion_data_plot[1].filename+"' using 1:2 via a3,b3,c3")
k2=gp.eval("k2")
k3=gp.eval("k3")
k4=gp.eval("k4")
x0=gp.eval("x0")
x1=gp.eval("x1")
x2=gp.eval("x2")


seqa=gp.eval("a")
seqb=gp.eval("b")
seqc=gp.eval("c")
#gp.plot(ion_data_plot[0],ion_sigp_plot[0],ion_sigm_plot[0])
#for ion in range(len(ion_list)-1):
#    gp.replot(ion_data_plot[ion+1],ion_sigp_plot[ion+1],ion_sigm_plot[ion+1])
    

#gp.plot(ion_data_plot[0],"g(x)")
gp.plot(ion_data_plot[0])
#gp.replot("He(x)","C(x)","N(x)","O(x)","Ne(x)","Mg(x)","Si(x)","S(x)","Ca(x)","Fe(x)")
for ion in range(len(ion_list)-1):
    gp.replot(ion_data_plot[ion+1])
print k2,k3,k4,x0,x1,x2
gp("set term postscript lw 2")
gp("set grid front noxticks noyticks")
gp.hardcopy("ionpositionshefti.ps",color=True,fontsize=18)
print "seqa=",seqa," seqb=",seqb," seqc=",seqc," phda=",phda," phdb=",phdb," phdc=",phdc
corr_ion_data=[]
for ion in range(len(ion_list)-1):
    corr_one_ion_data=[]
    for step in range(dim):
        energy=(Eacc+epq_arr[step])*ion_phd[ion+1][0][2]
        ephd=energy*phd(energy,phda,phdb,phdc)
        ech=e2ech(ephd)
        tch=tchfit(ech,seqa,seqb,seqc)
#        print "energy = ",energy," ephd = ",ephd," ech = ",ech," tch = ",tch
        corr_one_ion_data.append([tch,ech])
    corr_ion_data.append(corr_one_ion_data)

ion_data_plot_corr=[]
for ion in range(len(ion_list)-1):
    ion_data_plot_corr_tmp=Data(corr_ion_data[ion])
    ion_data_plot_corr_tmp.set_option_colonsep("using", "1:2")
    ion_data_plot_corr_tmp.set_option_colonsep("title",  "'%s'" %(ion_list[ion+1]))
    ion_data_plot_corr.append(ion_data_plot_corr_tmp)

#gp.plot(ion_data_plot[0])
#for ion in range(len(ion_list)-1):
#    gp.replot(ion_data_plot_corr[ion])


#gp.plot(ion_data_plot[0],"f(x)","g(x)")
#for ion in range(len(ion_list)-1):
#    print "fit g%i(x) '"%(ion+2)+ion_data_plot[ion+1].filename+"' using 1:2 via a%i,b%i,c%i"%(ion+2,ion+2,ion+2)
#    gp("fit g%i(x) '"%(ion+2)+ion_data_plot[ion+1].filename+"' using 1:2 via a%i,b%i,c%i"%(ion+2,ion+2,ion+2))
#    gp.replot(ion_data_plot[ion+1],"g%i(x)"%(ion+2))
#gp.replot("g(x)","g2(x)","g3(x)","g4(x)","g5(x)")    

#ion_data_plot[1],ion_data_plot[2],ion_data_plot[3],ion_data_plot[4],ion_data_plot[5],ion_data_plot[6],ion_data_plot[7],ion_data_plot[8],ion_data_plot[9],"f(x)")

#    fin=open("/home/ivar/berger/projects/ionpositions/ion_para_mu_fitmod2_clean_fast_ges_fit.dat")
#    fout=open("/home/ivar/berger/projects/ionpositions/ion_para_mu_fitmod2_clean_fast_ges_fit.dat.tmp","w")


#    for i in range(dim):
#        s=fin.readline()
#        print s
#        k=s.split()
#        s=fin.readline()
#        writeheader(fout,int(k[5]),int(k[2]))
#        for j in range(int(k[5])):
#            s=fin.readline()
#            k=s.split()
#            writeion(fout,k[0],float(k[1]),float(k[2]),float(k[3]),float(k[4]),float(k[5]),float(k[6]),float(k[7]),float(k[8]),float(k[9]),float(k[10]))
#
#    fin.close()
#    fout.close()




