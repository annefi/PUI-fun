#!/usr/bin/python
from numpy import float
from scipy import zeros
from libacepy.errors import overlapplist
from libacepy.ionerror import ionerror

class lv1data:
    "Class lv1data : contains lv1data\n\t name = array[steps][ions] ionsnames\n\t xpos = ''\n\t ypos = ''\n\t sigxp = ''\n\t sigxm = ''\n\t sigyp = ''\n\t sigym = ''\n\t vel= ''\n\t mass = ''\n\t charge = ''\n\t fiterg = ''\n\t normerg = ''\n\t the same structure as name"
    def __init__(self,filename):
        self.filename=filename
        self.cycles=0
        self.aspang=0.
        self.name=[]
        self.xpos=[]
        self.ypos=[]
        self.sigxp=[]
        self.sigxm=[]
        self.sigyp=[]
        self.sigym=[]
        self.vel=[]
        self.mass=[]
        self.charge=[]
        self.fiterg=[]
        self.normerg=[]
        self.overlapplist=[]
        self.histogram=[]
        self.errornormerg=[]
        
    def readlv1data(self):
        dim=58
        infile=open(self.filename)
        tmp=""
        while(tmp!="*****"):
            s=infile.readline()
            k=s.split()
            tmp=k[0]
            if (tmp=="Cycles"):
                self.cycles=int(k[2])
            if (tmp=="Aspang"):
                self.aspang=float(k[2])
        for step in range(dim):
            stepname=[]
            stepxpos=[]
            stepypos=[]
            stepsigxp=[]
            stepsigxm=[]
            stepsigyp=[]
            stepsigym=[]
            stepvel=[]
            stepmass=[]
            stepcharge=[]
            stepfiterg=[]
            stepnormerg=[]
            steperrornormerg=[]
            s=infile.readline()
            k=s.split()
            numions=int(k[5])
            s=infile.readline()
            for ion in range(numions):
                s=infile.readline()
                k=s.split()
                stepname.append(k[0])
                stepxpos.append(float(k[1]))
                stepypos.append(float(k[2]))
                stepsigxp.append(float(k[3]))
                stepsigxm.append(float(k[4]))
                stepsigyp.append(float(k[5]))
                stepsigym.append(float(k[6]))
                stepvel.append(float(k[7]))
                stepmass.append(float(k[8]))
                stepcharge.append(float(k[9]))
                stepfiterg.append(float(k[10]))
                stepnormerg.append(float(k[11]))
                steperrornormerg.append(float(k[12]))
            self.name.append(stepname)
            self.xpos.append(stepxpos)
            self.ypos.append(stepypos)
            self.sigxp.append(stepsigxp)
            self.sigxm.append(stepsigxm)
            self.sigyp.append(stepsigyp)
            self.sigym.append(stepsigym)
            self.vel.append(stepvel)
            self.mass.append(stepmass)
            self.charge.append(stepcharge)
            self.fiterg.append(stepfiterg)
            self.normerg.append(stepnormerg)
            self.errornormerg.append(steperrornormerg)

    """
    method : reads parameter file (e.g. ion_para.dat, setting fiterg and normerg to 0.)
    input
    filename : name of parameterfile (including path)
    """
    def readionpara(self):
        dim=58
        infile=open(self.filename)
        for step in range(dim):
            stepname=[]
            stepxpos=[]
            stepypos=[]
            stepsigxp=[]
            stepsigxm=[]
            stepsigyp=[]
            stepsigym=[]
            stepvel=[]
            stepmass=[]
            stepcharge=[]
            stepfiterg=[]
            stepnormerg=[]
            steperrornormerg=[]
            s=infile.readline()
            k=s.split()
            numions=int(k[5])
            s=infile.readline()
            for ion in range(numions):
                s=infile.readline()
                k=s.split()
                stepname.append(k[0])
                stepxpos.append(float(k[1]))
                stepypos.append(float(k[2]))
                stepsigxp.append(float(k[3]))
                stepsigxm.append(float(k[4]))
                stepsigyp.append(float(k[5]))
                stepsigym.append(float(k[6]))
                stepvel.append(float(k[7]))
                stepmass.append(float(k[8]))
                stepcharge.append(float(k[9]))
                stepfiterg.append(0.)
                stepnormerg.append(0.)
                steperrornormerg.append(0.)
            self.name.append(stepname)
            self.xpos.append(stepxpos)
            self.ypos.append(stepypos)
            self.sigxp.append(stepsigxp)
            self.sigxm.append(stepsigxm)
            self.sigyp.append(stepsigyp)
            self.sigym.append(stepsigym)
            self.vel.append(stepvel)
            self.mass.append(stepmass)
            self.charge.append(stepcharge)
            self.fiterg.append(stepfiterg)
            self.normerg.append(stepnormerg)
            self.errornormerg.append(steperrornormerg)
        infile.close()

    def calcerrors(self):
        print "calculate countrate errors."
        for step in range(len(self.normerg)):
            for ion in range(len(self.normerg[step])):
                docalc=1
                try:
                    open("/data/wimmer/ace/errors/"+self.name[step][ion]+".err")
                except:
                    docalc=0
                if (docalc):
                    tmperror=ionerror(self.name[step][ion],step+1,self.name[step],self.normerg[step])
                    tmperror.calc()
                    self.errornormerg[step][ion]=tmperror.error

    def getoverlapplist(self,ionname,step):
        overlapplist(self,ionname,step)
    
    def writeerrorpara(self,ionname,step,numsteps,peakh,frac):
        outfilename="error_para_"+ionname+"_step"+str(step+1)+"_"+str(peakh)+"_"+str(frac)+".dat"
        out=open(outfilename,"w")
        self.getoverlapplist(ionname,step)
        out.write("%s\n" %(ionname))
        out.write("%i\n" %(step+1))
        out.write("%i\n" %(numsteps))
        out.write("%i\n" %(int(peakh)))
        out.write("%.1f\n" %(frac))
        out.write("*****\n")
        for tmpstep in range(numsteps):
            if (len(self.overlapplist)>1):
                linetmp="Step : "+str(tmpstep)+ "\tNumberions : "+str(len(self.overlapplist))+"\n"
            else:
                linetmp="Step : "+str(tmpstep)+ "\tNumberions : 0\n"
            out.write(linetmp)
            linetmp="Name\txpos\typos\tsigxp\tsigxm\tsigyp\tsigym\tvel\t\tmass\tcharge\tpeakhigh\n"
            out.write(linetmp)
            for ion in self.overlapplist:
                for tmpion in range(len(self.name[step])):
                    if ((ion==self.name[step][tmpion])and(ion==ionname)):
                        linetmp=("%s\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t\t%.1f\t%.1f\t%.1f\n" %(self.name[step][tmpion],self.xpos[step][tmpion],self.ypos[step][tmpion],self.sigxp[step][tmpion],self.sigxm[step][tmpion],self.sigyp[step][tmpion],self.sigym[step][tmpion],self.vel[step][tmpion],self.mass[step][tmpion],self.charge[step][tmpion],peakh))
                        out.write(linetmp)
                    elif (ion==self.name[step][tmpion]):
                        linetmp=("%s\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t\t%.1f\t%.1f\t%.1f\n" %(self.name[step][tmpion],self.xpos[step][tmpion],self.ypos[step][tmpion],self.sigxp[step][tmpion],self.sigxm[step][tmpion],self.sigyp[step][tmpion],self.sigym[step][tmpion],self.vel[step][tmpion],self.mass[step][tmpion],self.charge[step][tmpion],frac*peakh))
                        out.write(linetmp)
        out.close()

