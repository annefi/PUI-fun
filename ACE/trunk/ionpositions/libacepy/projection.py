from Gnuplot import Gnuplot,Data
from math import exp,sqrt,cos,sin
from scipy import pi

def gauss(x,sigma,shift):
    return exp(-((x-shift)**2)/(2*sigma**2))

def int_gausscut(x0,deltax,deltar,alpha,beta,ratio1,ratio2,sigx1,sigr1,sigx2,sigr2,sigx3,sigr3,shift1,shift2,shift3,asym):
    val=0.
    a=1.
    b=ratio1
    c=ratio2
    for y in range(int(3./deltar)):
        y1=(y-(1.5/deltar))*deltar
        for z in range(int(3./deltar)):
            z1=(z-(1.5/deltar))*deltar
            x3=x0*cos(alpha)*cos(beta)-y1*sin(alpha)*cos(beta)-z1*sin(beta)
            y3=x0*sin(alpha)+y1*cos(alpha)
            z3=x0*cos(alpha)*sin(beta)-y1*sin(alpha)*sin(beta)+z1*cos(beta)
            if (x3>shift1):
                sigx1u=sigx1/asym
            else:
                sigx1u=sigx1
            if (x3<shift2):
                sigx2u=sigx2
            else:
                sigx2u=sigx2
            val+=a*(gauss(x3-deltax/2.,sigx1u,shift1)*gauss(y3-deltar/2.,sigr1,0.)*gauss(z3-deltar/2.,sigr1,0.)*deltax*deltar**2)+b*(gauss(x3-deltax/2.,sigx2u,shift2)*gauss(y3-deltar/2.,sigr2,0.)*gauss(z3-deltar/2.,sigr2,0.)*deltax*deltar**2)+c*(gauss(x3-deltax/2.,sigx3,shift3)*gauss(y3-deltar/2.,sigr3,0.)*gauss(z3-deltar/2.,sigr3,0.)*deltax*deltar**2)
    return val

def int_gauss(xdeltaarr,alpha,beta,ratio1,ratio2,sigx1,sigr1,sigx2,sigr2,sigx3,sigr3,shift1,shift2,shift3,deltar,asym):
    ergarr=[]
    for x in xdeltaarr:
        x0=x[0]
        deltax=x[1]
        cut=int_gausscut(x0,deltax,deltar,alpha,beta,ratio1,ratio2,sigx1,sigr1,sigx2,sigr2,sigx3,sigr3,shift1,shift2,shift3,asym)
        ergarr.append([x0,cut])
    maxval=0.
    for i in range(len(ergarr)):
        if (ergarr[i][1]>maxval):
            maxval=ergarr[i][1]
    if (maxval>0.):
        for i in range(len(ergarr)):
            ergarr[i][1]=ergarr[i][1]/maxval
    return ergarr

def calc_projection(xdeltaarr,alpha,beta,ratio1,ratio2,sigx1,sigr1,sigx2,sigr2,sigx3,sigr3,shift1,shift2,shift3,deltar,asym):
    return int_gauss(xdeltaarr,alpha,beta,ratio1,ratio2,sigx1,sigr1,sigx2,sigr2,sigx3,sigr3,shift1,shift2,shift3,deltar,asym)


