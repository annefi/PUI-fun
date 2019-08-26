from numpy import *


def gauss2d(p,x,y):
    return 1/(2*pi*p[:,2]*p[:,3])*exp(-(x-p[:,0])**2/(2.*p[:,2]**2))*exp(-(y-p[:,1])**2/(2.*p[:,3]**2))

class response(object):
    def __init__(self,parafile="../ion_para.dat"):
        self.pfname = parafile
        self.ionpara={}
        self.load_para()
        
    def load_para(self):
        fin = open(self.pfname,"r")
        ionlist = []
        for s in fin:
            k = s.split()
            if (k[0]!="Name") and (k[0]!="Step") and (k[0] not in self.ionpara.keys()):
                self.ionpara[k[0]] = zeros((60,4))

        fin = open(self.pfname,"r")
        step = None
        for s in fin:
            k = s.split()
            if k[0]=="Step":
                step = int(k[2])
            elif k[0]=="Name":
                pass
            else:
                self.ionpara[k[0]][step,0] = float(k[1])*2-0.5
                self.ionpara[k[0]][step,1] = float(k[2])*2-0.5
                self.ionpara[k[0]][step,2] = float(k[3])*2
                self.ionpara[k[0]][step,3] = float(k[5])*2

    def calc_response(self,epq,tof,esd):
        R = zeros((len(self.ionpara.keys()),epq.shape[0]))
        ions = sort(self.ionpara.keys())
        for ind,k in enumerate(ions):
            m = sum(self.ionpara[k][epq],axis=1)!=0
            m*= sqrt(((tof-self.ionpara[k][epq][:,0])/self.ionpara[k][epq][:,2])**2+((esd-self.ionpara[k][epq][:,1])/self.ionpara[k][epq][:,3])**2)<3.
            #m *= (abs(tof-self.ionpara[k][epq][:,0])<3.*self.ionpara[k][epq][:,2])*(abs(esd-self.ionpara[k][epq][:,1])<3.*self.ionpara[k][epq][:,3])
            R[ind][m]=gauss2d(self.ionpara[k][epq[m]],tof[m],esd[m])
        return R,ions
    
