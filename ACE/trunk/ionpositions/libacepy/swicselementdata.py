from libacepy.swicsiondata import swicsiondata
from libacepy.ancil import readlist,mittelwert
from scipy import array
from math import sqrt,log10

class swicselement:
    def __init__(self,element,timeframe,path):
        self.name=element
        self.path=path
        self.timeframe=timeframe
        self.time=[]
        self.meancharge=[]
        self.ioncharge=[]
        self.dens=[]
        self.totaldens=[]
        self.ratio=[]
        self.lowcharge=0.
        self.highcharge=0.
        self.densspec=[]
        self.year=path[len(path)-5:len(path)-1]
        self.vel=[]

    def load(self):
        self.checkcharge()
        for i in range(self.lowcharge,self.highcharge):
            ion=self.name+str(i)+"+"
            temp=swicsiondata(ion,self.timeframe,self.path)
            temp.load()
            self.time=temp.time
            self.dens.append(temp.dens)
            self.densspec.append(temp.densspec)
            self.ioncharge.append(temp.charge)
            vel=temp.vel
            velerror=temp.velerr
            temp2=[]
            for k in range(len(vel)):
                temp2.append([vel[k],velerror[k]])
            self.vel.append(temp2)
            
        for j in range(len(self.dens[0])):
            sum=0.
            err=0.
            err2=0.
            for i in range(self.lowcharge,self.highcharge):
                if (self.dens[i-self.lowcharge][j][0]>0.):
                    sum=sum+self.dens[i-self.lowcharge][j][0]
                    err=err+self.dens[i-self.lowcharge][j][1]**2
                    err2=err2+self.dens[i-self.lowcharge][j][2]**2
            self.totaldens.append([sum,sqrt(err),sqrt(err2)])
        self.calcmeancharge()
       
    def calcmeancharge(self):
        for j in range(len(self.dens[0])):
            sum=0.
            sum2=0.
            err=0.
            err2=0.
            for i in range(self.lowcharge,self.highcharge):
                if (self.dens[i-self.lowcharge][j][0]>0.):
                    sum=sum+self.dens[i-self.lowcharge][j][0]
                    sum2=sum2+self.dens[i-self.lowcharge][j][0]*i
            for i in range(self.lowcharge,self.highcharge):
                if (sum!=0.):
                    if (self.dens[i-self.lowcharge][j][0]>0.):
                        err=err+((i/sum-sum2/sum**2)*self.dens[i-self.lowcharge][j][1])**2
                        err2=err2+((i/sum-sum2/sum**2)*self.dens[i-self.lowcharge][j][2])**2
                else:
                    err=0.
                    err2=0.
            if (sum!=0.):
                self.meancharge.append([sum2/sum,sqrt(err),sqrt(err2)])
            else:
                self.meancharge.append([0.,sqrt(err),sqrt(err2)])
        #print self.meancharge
              
    def calcratio(self,chargestate):
        for j in range(len(self.dens[0])):
            sum=0.
            err=0.
            err2=0.
            for i in range(chargestate,self.highcharge):
                if (self.dens[i-self.lowcharge][j][0]>0.):
                    sum=sum+self.dens[i-self.lowcharge][j][0]
            for i in range(chargestate,self.highcharge):
                if (self.totaldens[j][0]!=0.):
                    if (self.dens[i-self.lowcharge][j][0]>0.):
                        err=err+(self.dens[i-self.lowcharge][j][1]/self.totaldens[j][0])**2
                        err2=err2+(self.dens[i-self.lowcharge][j][2]/self.totaldens[j][0])**2
                else:
                    err=0.
                    err2=0.
            if (self.totaldens[j][0]!=0.):
                err=err+(self.totaldens[j][1]*sum/(self.totaldens[j][0]**2))**2
                err2=err2+(self.totaldens[j][2]*sum/(self.totaldens[j][0]**2))**2
            else:
                err=0.
                err2=0.
            if (self.totaldens[j][0]!=0.):
                self.ratio.append([sum/self.totaldens[j][0],sqrt(err),sqrt(err2)])
            else:
                self.ratio.append([0.,sqrt(err),sqrt(err2)])
                
    def checkcharge(self):
        if (self.name=="He"):
            self.lowcharge=2
            self.highcharge=3
        if (self.name=="C"):
            self.lowcharge=4
            self.highcharge=7
        if (self.name=="N"):
            self.lowcharge=5
            self.highcharge=8
        if (self.name=="O"):
            self.lowcharge=5
            self.highcharge=9
        if (self.name=="Ne"):
            self.lowcharge=7
            self.highcharge=9
        if (self.name=="Mg"):
            self.lowcharge=6
            self.highcharge=13
        if (self.name=="Si"):
            self.lowcharge=6
            self.highcharge=13
        if (self.name=="S"):
            self.lowcharge=7
            self.highcharge=13
        if (self.name=="Ca"):
            self.lowcharge=7
            self.highcharge=15
        if (self.name=="Fe"):
            self.lowcharge=7
            self.highcharge=25


def getmeandensspec(self):
    spec=[]
    for i in range(len(self.densspec)):
        speclv2=[]
        for j in range(len(self.densspec[i][0])):
            speclv3=[]
            for l in range(len(self.densspec[i][0][j])):
                temp=[]
                for k in range(len(self.densspec[i])):
                    temp.append(self.densspec[i][k][j][l])
                if (l==0 or l==1):
                    speclv3.append(mittelwert(temp))    
                else:
                    error=0.
                    for m in range(len(temp)):
                        error=error+temp[m]**2
                    error=sqrt(error)/len(temp)
                    speclv3.append(error)
            speclv2.append(speclv3)
        spec.append(speclv2)
    return spec
    
def elemratio(elem1, elem2):
    erg=[]
    for j in range(len(elem1.totaldens)):
        if (elem2.totaldens[j][0]!=0.):
            ratio=elem1.totaldens[j][0]/elem2.totaldens[j][0]
            err=(elem1.totaldens[j][1]/elem2.totaldens[j][0])**2+(elem1.totaldens[j][0]*elem2.totaldens[j][1]/elem2.totaldens[j][0]**2)**2
            err2=(elem1.totaldens[j][2]/elem2.totaldens[j][0])**2+(elem1.totaldens[j][0]*elem2.totaldens[j][2]/elem2.totaldens[j][0]**2)**2
        else:
            ratio=0.
            err=0.
            err2=0.
        erg.append([ratio,sqrt(err),sqrt(err2)])
    return erg

def freezein(element,charge):
    """
    calculate freezing in temperature for element_charge+/element_(charge+1)+
    """
    path="/home/zechine/rodde/swics/ionpositions/freezein/"
    file=path+element.name+".tab"
    Tlist=[]
    input=open(file)
    for line in input:
        s=line.split()
        temp=[]
        for k in range(1,len(s)):
            temp.append(float(s[k]))
        Tlist.append(temp)
    input.close()
    T=[]
    for i in range(len(element.totaldens)):
        try:
            ratioerror=sqrt((element.dens[charge-element.lowcharge][i][1]/element.dens[charge-element.lowcharge+1][i][0])**2+(element.dens[charge-element.lowcharge+1][i][1]*element.dens[charge-element.lowcharge][i][0]/element.dens[charge-element.lowcharge+1][i][0]**2)**2)
        except:
            ratioerror=0.
        try:
            low=log10(element.dens[charge-element.lowcharge][i][0])
            high=log10(element.dens[charge-element.lowcharge+1][i][0])
            ratio=low-high
        except:
            ratio=-50
        if (ratio!=-50):
            ratio4=log10(10**ratio+ratioerror)
            count=1
            T1=0.
            for k in range(len(Tlist)-1):
                if (Tlist[k][charge+1]<=0. and Tlist[k+1][charge+1]<=0. and Tlist[k][charge+2]<=0. and Tlist[k+1][charge+2]<=0.):
                    ratio2=Tlist[k][charge+1]-Tlist[k][charge+2]
                    ratio3=Tlist[k+1][charge+1]-Tlist[k+1][charge+2]
                    if (ratio4<=ratio2 and ratio4>ratio3):
                        T1=0.1*(ratio2-ratio4)/(ratio2-ratio3)+Tlist[k][0]
                    if (ratio<=ratio2 and ratio>ratio3):
                        Tf=0.1*(ratio2-ratio)/(ratio2-ratio3)+Tlist[k][0]
                        if(Tf!=T1 and T1!=0.):
                            Terr=log10(10**Tf-10**T1)
                        else:
                            Terr=0.
                        T.append([Tf,Terr])
                        count=0
            if (count):
                T.append([0.,0.])
        else:
            T.append([0.,0.])
    return T
    
