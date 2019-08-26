#!/usr/bin/python
from scipy import zeros, Float, matrixmultiply,exp,sqrt,mean
from Gnuplot import Gnuplot,GnuplotOpts,Data

GnuplotOpts.prefer_fifo_data=0
GnuplotOpts.prefer_inline_data=0

dim=58
cut_left=0
cut_right=10

def echfit(x,a,b,c):
    return a*x**2+b*x+c

def tchfit(x,a,b,c):
    return a*x**2+b*x+c

def writeheader(file,numions,step):
    file.write("Step : "+str(step)+"\tNumberions : "+str(numions)+"\n")
    file.write("Name\t\txpos\t\typos\t\tsigxp\t\tsigxm\t\tsigyp\t\tsigym\t\tvel\t\tmass\t\tcharge\t\tpeakhigh\n")

def writeion(file,name,xpos,ypos,sigxp,sigxm,sigyp,sigym,velocity,mass,charge,peakh):
    file.write("%s\t\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\n" %(name,xpos,ypos,sigxp,sigxm,sigyp,sigym,velocity,mass,charge,peakh))

epq_arr=zeros([dim],Float)
epq_arr_diff=zeros([dim],Float)
epq_arr = [86.6359,75.0485,65.0109,56.3158,48.7837,42.2589,36.6069,31.7108,27.4695,23.7955,20.6129,17.856,16.619,15.4678,14.3962,13.399,12.4708,11.6069,10.8028,10.0545,9.35797,8.70971,8.10635,7.5448,7.02214,6.5357,6.08294,5.66156,5.26936,4.90433,4.56459,4.24839,3.95409,3.68017,3.42523,3.18796,2.96711,2.76157,2.57027,2.39222,2.2265,2.07226,1.92871,1.7951,1.67075,1.55501,1.44729,1.34703,1.25372,1.16687,1.08603,1.0108,0.940778,0.875607,0.81495,0.758496,0.705952,0.657048]
#0.611532,0.55]
epq_arr2=zeros([dim],Float)
epq_arr2=[86.6359,75.0485,65.0109,56.3158,48.7837,42.2589,36.6069,31.7108,27.4695,23.7955,20.6129,17.856,16.619,15.4678,14.3962,13.399,12.4708,11.6069,10.8028,10.0545,9.35797,8.70971,8.10635,7.5448,7.02214,6.5357,6.08294,5.66156,5.26936,4.90433,4.56459,4.24839,3.95409,3.68017,3.42523,3.18796,2.96711,2.76157,2.57027,2.39222,2.2265,2.07226,1.92871,1.7951,1.67075,1.55501,1.44729,1.34703,1.25372,1.16687,1.08603,1.0108,0.940778,0.875607,0.81495,0.758496,0.705952,0.657048,0.611532,0.55]

f=open("/home/ivar/berger/projects/ionpositions/ion_para_mu_fitmod2_clean_fast_ges_fit3fit.dat")
print "loading ion_para.dat"
s=f.readline()
k=s.split()
numberions=int(k[5])
numberionsstep=numberions
sigxp=zeros([numberions,dim],Float)
sigxm=zeros([numberions,dim],Float)
sigyp=zeros([numberions,dim],Float)
sigym=zeros([numberions,dim],Float)

ion_names=""
s=f.readline()
for j in range(numberionsstep):
    s=f.readline()
    k=s.split()
    ion_names=ion_names+" "+k[0]
ion_name=ion_names.split()        
f.close()
print ion_name

f=open("/home/ivar/berger/projects/ionpositions/ion_para_mu_fitmod2_clean_fast_ges_fit3fit.dat")
for i in range(dim):
    s=f.readline()
    k=s.split()
    numberionsstep=int(k[5])
    s=f.readline()
    for j in range(numberionsstep):
        s=f.readline()
        k=s.split()
        for l in range(numberions):
            if (ion_name[l]==k[0]):
                print i,l,ion_name[l]
                sigxp[l][i]=float(k[3])
                sigxm[l][i]=float(k[4])
                sigyp[l][i]=float(k[5])
                sigym[l][i]=float(k[6])
f.close()


for ion in range(numberions):
    a=zeros([8],Float)
    b=zeros([8],Float)
    c=zeros([8],Float)
    proceed=0
    skip=0
    if (ion==0):
        fin=open("/home/ivar/berger/projects/ionpositions/ion_para_mu_fitmod2_clean_fast_ges_fit3fit.dat")
    else:
        fin=open("/home/ivar/berger/projects/ionpositions/ion_para_mu_fitmod2_clean_fast_ges_fit4fit.dat.tmp")
    fout=open("/home/ivar/berger/projects/ionpositions/ion_para_mu_fitmod2_clean_fast_ges_fit4fit.dat","w")

    for chtype in range(4):
        cmnd=""
        gp=Gnuplot()
        para=chtype
        for interv in range(2):
            if (interv==0):
                usesteps=[0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57]
                print "len(usesteps)=",len(usesteps)
                xrange=[0,90]
            if (interv==1):
                usesteps=[0,1,2,3,4,5,6,7,8,9,10]
                xrange=[20,90]
                para+=4
            proceed=0
            while(not proceed):
                gpsigxp=[]
                gpsigxm=[]
                gpsigyp=[]
                gpsigym=[]
                for step in usesteps:
                    if (sigxp[ion][step]):
                        gpsigxp.append([epq_arr[step],sigxp[ion][step]])
                        gpsigxm.append([epq_arr[step],sigxm[ion][step]])
                        gpsigyp.append([epq_arr[step],sigyp[ion][step]])
                        gpsigym.append([epq_arr[step],sigym[ion][step]])
                gpsigxpdata=Data(gpsigxp)
                gpsigxmdata=Data(gpsigxm)
                gpsigypdata=Data(gpsigyp)
                gpsigymdata=Data(gpsigym)
                gpsigxpdata.set_option_colonsep("using", "1:2")
                gpsigxpdata.set_option_colonsep("title",  "'%s_sigxp'" %(ion_name[ion]))
                gpsigxmdata.set_option_colonsep("using", "1:2")
                gpsigxmdata.set_option_colonsep("title",  "'%s_sigxm'" %(ion_name[ion]))
                gpsigypdata.set_option_colonsep("using", "1:2")
                gpsigypdata.set_option_colonsep("title",  "'%s_sigyp'" %(ion_name[ion]))
                gpsigymdata.set_option_colonsep("using", "1:2")
                gpsigymdata.set_option_colonsep("title",  "'%s_sigym'" %(ion_name[ion]))

                gp("a=-0.1")
                gp("b=0.01")
                gp("c=-0.1")
                gp("set xrange[%i:%i]" %(xrange[0],xrange[1]))
                if (chtype==0):
                    gp("set title '%s_sigxp'"%(ion_name[ion]))
                elif (chtype==1):
                    gp("set title '%s_sigxm'"%(ion_name[ion]))
                elif (chtype==2):
                    gp("set title '%s_sigyp'"%(ion_name[ion]))
                elif (chtype==3):
                    gp("set title '%s_sigym'"%(ion_name[ion]))
                else:
                    gp("set title 'unknown type???!!!'")
                gp("set xlabel 'E/q'")
                gp("set ylabel 'Channel'")
                gp("f(x)= a*x+b")
#                gp("f(x)= a*x**2+b*x+c")

                if (skip==0):
                    if (chtype==0):
                        gp("fit f(x) '"+gpsigxpdata.filename+"' using 1:2 via a,b")
                    elif (chtype==1):
                        gp("fit f(x) '"+gpsigxmdata.filename+"' using 1:2 via a,b")
                    elif (chtype==2):
                        gp("fit f(x) '"+gpsigypdata.filename+"' using 1:2 via a,b")
                    elif (chtype==3):
                        gp("fit f(x) '"+gpsigymdata.filename+"' using 1:2 via a,b")

                    if (chtype==0):
                        gp.plot(gpsigxpdata,gpsigxmdata,"f(x)")
                    elif (chtype==1):
                        gp.plot(gpsigxmdata,gpsigxpdata,"f(x)")
                    elif (chtype==2):
                        gp.plot(gpsigypdata,gpsigymdata,"f(x)")
                    elif (chtype==3):
                        gp.plot(gpsigymdata,gpsigypdata,"f(x)")
                        
                        
                # ridiculous loop to delay output (there is no way known to me to prevent !#§$! Gnuplot from output its results!??????) 
                    for time in range(1000000):
                        continue
                    print "Proceed(y) / Remove points (list e.g. 1 3 5 9) / Proceed Old(o) / Reset list(r) / Skip(s):"
                    cmnd = raw_input()
                else:
                    cmnd="s"
                print cmnd
                if (cmnd=="s"):
                    proceed=1
                    skip=1
                elif (cmnd=="y"):
                    proceed=1
                    a[para]=gp.eval("a")
                    b[para]=gp.eval("b")
                    c[para]=gp.eval("c")
                elif (cmnd=="r"):
                    if (interv==0):
                        usesteps=[11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57]
                        xrange=[0,20]
                    if (interv==1):
                        usesteps=[0,1,2,3,4,5,6,7,8,9,10]
                        xrange=[20,90]
                else:
                    liststr=cmnd.split()
                    print len(liststr)
                    liste=zeros([len(liststr)])
                    for i in range(len(liststr)):
                        liste[i]=usesteps[int(liststr[i])-1]
                    tmp=len(usesteps)
                    print tmp,"-",len(liststr),"=",tmp-len(liststr)
                    if (interv==0):
                        l=usesteps[0]
                        lrange=len(usesteps)
                    if (interv==1):
                        l=usesteps[0]
                        lrange=len(usesteps)
                    summatch=0
                    usestepstmp=usesteps
                    usesteps=zeros([tmp-len(liststr)])
                    idx=0
                    for j in range(lrange):
                        match=0
                        for k in range(len(liststr)):
                            if (usestepstmp[j]==liste[k]):
                                match=1
                        if (not match):
                            usesteps[idx]=usestepstmp[j]
                            idx+=1
                    print usesteps            
                                

    for i in range(dim):
        s=fin.readline()
        print s
        k=s.split()
        s=fin.readline()
        writeheader(fout,int(k[5]),int(k[2]))
        for j in range(int(k[5])):
            s=fin.readline()
            k=s.split()
            if (k[0]==ion_name[ion] and (skip==0)):
                if (i<11):
                    writeion(fout,k[0],srimxpos[ion][i]-tchfit(epq_arr[i],a[1],b[1],c[1]),srimypos[ion][i]-echfit(epq_arr[i],a[3],b[3],c[3]),float(k[3]),float(k[4]),float(k[5]),float(k[6]),float(k[7]),float(k[8]),float(k[9]),float(k[10]))
                else:
                    writeion(fout,k[0],srimxpos[ion][i]-tchfit(epq_arr[i],a[0],b[0],c[0]),srimypos[ion][i]-echfit(epq_arr[i],a[2],b[2],c[2]),float(k[3]),float(k[4]),float(k[5]),float(k[6]),float(k[7]),float(k[8]),float(k[9]),float(k[10]))
            else:
                writeion(fout,k[0],float(k[1]),float(k[2]),float(k[3]),float(k[4]),float(k[5]),float(k[6]),float(k[7]),float(k[8]),float(k[9]),float(k[10]))

    fin.close()
    fout.close()

    fin=open("/home/ivar/berger/projects/ionpositions/ion_para_mu_fitmod2_clean_fast_ges_fit4fit.dat")
    fout=open("/home/ivar/berger/projects/ionpositions/ion_para_mu_fitmod2_clean_fast_ges_fit4fit.dat.tmp","w")


    for i in range(dim):
        s=fin.readline()
        print s
        k=s.split()
        s=fin.readline()
        writeheader(fout,int(k[5]),int(k[2]))
        for j in range(int(k[5])):
            s=fin.readline()
            k=s.split()
            writeion(fout,k[0],float(k[1]),float(k[2]),float(k[3]),float(k[4]),float(k[5]),float(k[6]),float(k[7]),float(k[8]),float(k[9]),float(k[10]))

    fin.close()
    fout.close()




