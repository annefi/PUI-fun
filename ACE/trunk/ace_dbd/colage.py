from numpy import *

def lnlambda(mi,mj,ni,nj,Zi,Zj,Ti,Tj):
    return 23-log((Zi*Zj*(mi+mj))/(mi*Tj+mj*Ti)*sqrt((ni*Zi**2)/Ti+(nj*Zj**2)/Tj))

def nuij(mi,mj,ni,nj,Zi,Zj,Ti,Tj):
    return 6.8e-8*(sqrt(mj)/mi)/sqrt(1+mj/mi)*Tj**-1.5*nj*Zi**2*Zj**2*lnlambda(mi,mj,ni,nj,Zi,Zj,Ti,Tj)


np=arange(0.1,20.1,.1)
nhe=ones(np.shape[0])*np*0.1
nuhep=lnlambda(4.,1.,nhe,np,2.,1.,20.,10.)


    

