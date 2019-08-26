#!/usr/bin/python
from os import system
from scipy.linalg import inv
from scipy import zeros, dot
from numpy import float
from Gnuplot import Gnuplot, GridData
from math import sin,cos,tan,asin,acos,atan,exp,pi
from os import popen2
from sys import stdin
import random
from scipy.integrate import quad
from Gnuplot.func_ext import *

gp=Gnuplot()

# kappa - Funktion
def k1(x,x1,G1,sk1,kappa1,bg1):
    return bg1+G1*(1+((x-x1)**2/(kappa1*sk1**2)))**-(kappa1)

# Rechteck - Funktion
def f1(x,x1,l,r):
    if (((x-x1) >= l) and ((x-x1) <= r)):
        return 1./(r+l)
    else:
        return 0.

# Links Gauss, rechts Kappa
def gk(x,x1,G1,sg1,sk1,kappa1,bg1):
    if (x <= x1):
        return bg1+G1*exp(-((x-x1)**2)/(2*sg1**2))
    else:
        return bg1+G1*(1+((x-x1)**2/(kappa1*sk1**2)))**-(kappa1)

# Gauss
def g1(x,x1,G1,sg1,bg1):
    return bg1+G1*1/((2*pi)**0.5*sg1)*exp(-((x-x1)**2)/(2*sg1**2))
    #return bg1+G1*exp(-((x-x1)**2)/(2*sg1**2))

# Dreieck
def f2(x,x1,breite1):
    if ((x < (x1-breite1)) or (x > (x1+breite1))):
        return 0.
    if ((x >= (x1-breite1)) and (x < x1)):
        return 1./breite1**2*(x-(x1-breite1))
    if (x == x1):
        return 1./breite1
    if ((x > x1) and (x <= (x1+breite1))):
        return 1./breite1-1./breite1**2*(x-x1)

# Bodmer Energie-Auflösungs-Funktion
def bf(x,breite1):
    if (abs(x/breite1) < 1):
        return 1-0.5*(abs(x/breite1))**2
    if ((abs(x/breite1) >=1) and (abs(x/breite1) <=2)):
        return 0.5*(2-(abs(x/breite1)))**2
    else:
        return 0.

# Links kappa1, Rechts kappa2
def kk(x,x1,G1,sk1,sk2,kappa1,kappa2,bg1):
    if (x <= x1):
        return bg1+G1*(1+((x-x1)**2/(kappa1*sk1**2)))**-(kappa1)
    else:
        return bg1+G1*(1+((x-x1)**2/(kappa2*sk2**2)))**-(kappa2)


# Faltung Gauss und Dreieck
def conv_gd(y,x1,G1,sg1,bg1,breite1):
    return quad(lambda x:g1(y-x,x1,G1,sg1,bg1)*f2(x,0.,breite1),-breite1,breite1)[0]
#gd=ExternalFunction(gp, "gd", ["x1","G1","sg1","bg1","breite1"], conv_gd)

# Faltung Kappa und Dreieck
def conv_kd(y,x1,G1,sk1,kappa1,bg1,breite1):
    return quad(lambda x:k1(y-x,x1,G1,sk1,kappa1,bg1)*f2(x,0.,breite1),-breite1,breite1)[0]
#kd=ExternalFunction(gp, "kd", ["x1","G1","sk1","kappa1","bg1","breite1"], conv_kd)

# Faltung Kappa und Gauss
def conv_kg(y,x1,G1,sk1,kappa1,bg1,sg1):
    return quad(lambda x:k1(y-x,x1,G1,sk1,kappa1,bg1)*g1(x,0.,1.,sg1,bg1),-10.*sg1,10.*sg1)[0]
#kg=ExternalFunction(gp, "kg", ["x1","G1","sk1","sg1","kappa1","bg1"], conv_kg)

# Faltung Dreieck und Rechteck
def conv_dr(y,x1,breite1,l,r):
    return quad(lambda x:f2(y-x,x1,breite1)*f1(x,x1,l,r),l,r)[0]
#dr=ExternalFunction(gp, "dr", ["x1","G1","l","r","breite1"], conv_dr)

# Faltung (links Gauss, rechts Kappa) und Gauss
def conv_gkg(y,x1,G1,sg1,sk1,kappa1,bg1,sg2):
    return quad(lambda x:gk(y-x,x1,G1,sg1,sk1,kappa1,bg1)*g1(x,0.,1.,sg2,bg1),-10.*sg1,10.*sg1)[0]
#gkg=ExternalFunction(gp, "gkg", ["x1","G1","sg1","sk1","sg2","kappa1","bg1"], conv_gkg)

# Faltung (links Gauss, rechts Kappa) und Dreieck
def conv_gkd(y,x1,G1,sg1,sk1,kappa1,bg1,breite1):
    return quad(lambda x:gk(y-x,x1,G1,sg1,sk1,kappa1,bg1)*f2(x,0.,breite1),-breite1,breite1)[0]
#gkd=ExternalFunction(gp, "gkd", ["x1","G1","sg1","sk1","kappa1","bg1","breite1"], conv_gkd)

# Faltung (links Gauss, rechts Kappa) und Bodmer Funktion
def conv_gkbf(y,x1,G1,sg1,sk1,kappa1,bg1,breite1):
    return quad(lambda x:gk(y-x,x1,G1,sg1,sk1,kappa1,bg1)*bf(x,breite1),-2*breite1,2*breite1)[0]

# Faltung (links Kappa1, rechts Kappa2) und Dreieck
def conv_kkd(y,x1,G1,sk1,sk2,kappa1,kappa2,bg1,breite1):
    return quad(lambda x:kk(y-x,x1,G1,sk1,sk2,kappa1,kappa2,bg1)*f2(x,0.,breite1),-breite1,breite1)[0]
#kkd=ExternalFunction(gp, "kkd", ["x1","G1","sk1","sk2","kappa1","kappa2","bg1","breite1"], conv_kkd)


# Faltung (links Kappa1, rechts Kappa2) und Bodmer Funktion
def conv_kkbf(y,x1,G1,sk1,sk2,kappa1,kappa2,bg1,breite1):
    return quad(lambda x:kk(y-x,x1,G1,sk1,sk2,kappa1,kappa2,bg1)*bf(x,breite1),-10*breite1,10*breite1)[0]
#kkbf=ExternalFunction(gp, "kkbf", ["x1","G1","sk1","sk2","kappa1","kappa2","bg1","breite1"], conv_kkbf)
