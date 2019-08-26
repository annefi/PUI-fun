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

f=open("/home/ivar/berger/projects/ionpositions/ion_para_mu_fitmod2_clean_fast_ges.dat")
print "loading ion_para.dat"
s=f.readline()
k=s.split()
numberions=int(k[5])
numberionsstep=numberions
xpos=zeros([numberions,dim],Float)
ypos=zeros([numberions,dim],Float)
srimxpos=zeros([numberions,dim],Float)
srimypos=zeros([numberions,dim],Float)

ion_names=""
s=f.readline()
for j in range(numberionsstep):
    s=f.readline()
    k=s.split()
    ion_names=ion_names+" "+k[0]
ion_name=ion_names.split()        
f.close()
print ion_name

f=open("/home/ivar/berger/projects/ionpositions/ion_para_mu_fitmod2_clean_fast_ges.dat")
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
                xpos[l][i]=float(k[1])
                ypos[l][i]=float(k[2])
f.close()

f=open("/home/ivar/berger/projects/ionpositions/ion_pos_clean_21.dat")
for j in range(dim):
    s=f.readline()
    k=s.split()
    numberionsstep=int(k[6])
    s=f.readline()
    for i in range(numberionsstep):
        s=f.readline()
        m=s.split()
        for k in range(numberions):
            if (ion_name[k]==m[0]):
                srimxpos[k][j]=float(m[3])
                srimypos[k][j]=float(m[4])
    s=f.readline()

diffstch=[]
for ion in range(numberions):
    difftch=[]
    for step in range(cut_left,dim-cut_right):
        difftch.append([epq_arr[step],(srimxpos[ion][step]-xpos[ion][step])])
    diffstch.append(difftch)

diffstchplot=[]
for ion in range(numberions):
    diffdata=Data(diffstch[ion])
    diffdata.set_option_colonsep("using", "1:2")
    diffdata.set_option_colonsep("title",  "'%s'" %(ion_name[ion]))
    diffstchplot.append(diffdata)

diffsech=[]
for ion in range(numberions):
    diffech=[]
    for step in range(cut_left,dim-cut_right):
        diffech.append([epq_arr[step],(srimypos[ion][step]-ypos[ion][step])])
    diffsech.append(diffech)

diffsechplot=[]
for ion in range(numberions):
    diffdata=Data(diffsech[ion])
    diffdata.set_option_colonsep("using", "1:2")
    diffdata.set_option_colonsep("title",  "'%s'" %(ion_name[ion]))
    diffsechplot.append(diffdata)

for ion in range(numberions):
    a=zeros([4],Float)
    b=zeros([4],Float)
    c=zeros([4],Float)
    proceed=0
    skip=0
    if (ion==0):
        fin=open("/home/ivar/berger/projects/ionpositions/ion_para_mu_fitmod2_clean_fast_ges_fit.dat.tmp")
    else:
        fin=open("/home/ivar/berger/projects/ionpositions/ion_para_mu_fitmod2_clean_fast_ges_fit.dat.tmp")
    fout=open("/home/ivar/berger/projects/ionpositions/ion_para_mu_fitmod2_clean_fast_ges_fit.dat","w")

    for chtype in range(2):
        cmnd=""
        gp=Gnuplot()
        if (chtype==1):
            para=2
        elif (chtype==0):
            para=0
        for interv in range(2):
            if (interv==0):
                usesteps=[11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57]
                print "len(usesteps)=",len(usesteps)
                xrange=[0,20]
            if (interv==1):
                usesteps=[0,1,2,3,4,5,6,7,8,9,10]
                xrange=[20,90]
                para+=1
            proceed=0
            while(not proceed):
                difftch=[]
                for step in usesteps:
                    if (srimxpos[ion][step]-xpos[ion][step]):
                        difftch.append([epq_arr[step],(srimxpos[ion][step]-xpos[ion][step])])
                difftchdata=Data(difftch)
                difftchdata.set_option_colonsep("using", "1:2")
                difftchdata.set_option_colonsep("title",  "'%s_tch'" %(ion_name[ion]))
                diffech=[]
                for step in usesteps:
                    if (srimypos[ion][step]-ypos[ion][step]):
                        diffech.append([epq_arr[step],(srimypos[ion][step]-ypos[ion][step])])
                diffechdata=Data(diffech)
                diffechdata.set_option_colonsep("using", "1:2")
                diffechdata.set_option_colonsep("title",  "'%s_ech'" %(ion_name[ion]))

                gp("a=-0.1")
                gp("b=0.01")
                gp("c=-0.1")
                gp("set xrange[%i:%i]" %(xrange[0],xrange[1]))
                #gp("set yrange[-4:4]")
                if (chtype==0):
                    gp("set title '%s_ToF'"%(ion_name[ion]))
                elif (chtype==1):
                    gp("set title '%s_Energy'"%(ion_name[ion]))
                else:
                    gp("set title 'unknown type???!!!'")
                gp("set xlabel 'E/q'")
                gp("set ylabel 'Channel'")
                gp("f(x)= a*x**2+b*x+c")

                if (skip==0):
                    if (chtype==0):
                        gp("fit f(x) '"+difftchdata.filename+"' using 1:2 via a,b,c")
                    elif (chtype==1):
                        gp("fit f(x) '"+diffechdata.filename+"' using 1:2 via a,b,c")

                    if (chtype==0):
                        gp.plot(difftchdata,diffechdata,"f(x)")
                    else:
                        gp.plot(diffechdata,difftchdata,"f(x)")
                        
                        
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

    fin=open("/home/ivar/berger/projects/ionpositions/ion_para_mu_fitmod2_clean_fast_ges_fit.dat")
    fout=open("/home/ivar/berger/projects/ionpositions/ion_para_mu_fitmod2_clean_fast_ges_fit.dat.tmp","w")


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




