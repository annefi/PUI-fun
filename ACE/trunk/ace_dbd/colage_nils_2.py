from numpy import *
from scipy.special import erf

iondens = {
    "Fe": 4e-6,
    "Si": 6e-6,
    "O": 3.4e-4,
    "C": 1.1e-4,
    "He": 0.05,
    "H" : 1.
}
 

 

 

def calc_kintemps_eV(m,vth):
    """
    calculates kinetic temperatures,
    m in amu, vth in km/s, returns kinetic temperatures in eV (= energy),
    """
    M=m*1.66e-27
    Vth=vth*1000.
    k_B=1.38e-23
    T=M*Vth**2/(2*1.60e-19)
    return T

def calc_logcoul(Z_i,A_i,n_p,T_i,T_p,ion):
    """ calculates Coulomb logarithm,
    n_p in SI, T_i, T_p in eV """

    Z_p=1.
    A_p=1.

    arg_1=Z_i*Z_p*(A_i+A_p)/(A_i*T_p+A_p*T_i)
    arg_2=sqrt(iondens[ion]*n_p*Z_i**2/T_i+n_p*Z_p**2/T_p)
    #return arg_1,arg_2
    lc=29.9-log(arg_1*arg_2)
    return lc


def calc_diffstream_norm(vth_i,vth_p,dv):#in km/s, idea: make dv variable in dependence of v_p
    """
    calculates normalized diff. streaming, vth in km/s
    """
    x=abs(dv)/sqrt(vth_i**2+vth_p**2)
    return x

def calc_ftherm(Z_i,A_i,q_i,n_p,vth_i,vth_p,dv,ion):
    """
    calculate thermalization rate (in s), q_i in e, m_i in amu, n_p in SI, vth_i,vth_p,dv in km/s
    """
    ep0=8.854e-12
    Q_i=1.60e-19*q_i
    Q_p=1.60e-19*1.
    M_i=1.66e-27*A_i
    M_p=1.66e-27*1.
    Vth_i=1000.*vth_i
    Vth_p=1000.*vth_p
    N_p=float(1e6)*n_p

    T_i=calc_kintemps_eV(m=A_i,vth=vth_i)
    T_p=calc_kintemps_eV(m=1.,vth=vth_p)

    lc=calc_logcoul(Z_i,A_i,n_p,T_i,T_p,ion)
    dvn=calc_diffstream_norm(vth_i=Vth_i,vth_p=Vth_p,dv=dv)

    enum=Q_i**2*Q_p**2*N_p*lc
    denom=(3*pi*ep0**2)*M_i*M_p*(Vth_i**2+Vth_p**2)**(3./2)
    fth=enum/denom*erf(dvn)/dvn
    return fth


def calc_Ac(ftherm,vsw,R=1.5e11):#vsw in km/s
    """
    calculate collisional age at 1AU, ftherm in s, vsw in km/s
    """
    VSW=vsw*1000.
    A_c=ftherm*R/VSW
    return A_c


def calc_colage(Z,A,q_i,n_p,vth_i,vth_p,vsw,dv,ion,R=1.5e11):
    ftherm=calc_ftherm(Z,A,q_i,n_p,vth_i,vth_p,dv,ion)
    colage=calc_Ac(ftherm,vsw,R)
    return colage
 
def calc_colage_2(Z,A,q_i,n_p,vth_i,vth_p,vsw,dv,ion,R=1.5e11):
    ftherm=calc_ftherm(Z,A,q_i,n_p,vth_i,vth_p,dv,ion)
    colage=calc_Ac(ftherm,vsw,R)
    return colage
 
 
 
 
 

