#!/usr/bin/env python

import numpy
from numpy import *
from numpy.linalg import norm
from etConst import c_light
import etUnits as eu
from scipy import special

def lorentz_gamma(speed):
    """return the lorentz correction factor"""
    speed=norm(speed)
    if speed > c_light: return "speed has to be less than speed of light!"
    else:
       return 1./sqrt(1.-(speed/c_light)**2)

def heaviside(x):
    if x >0: return 1
    return 0

def gauss(x, x0, s):
    return exp(-0.5*(x-x0)**2/(s*s))*1./s/sqrt(2*pi)

def gaussShape(x, x0, s):
    return exp(-0.5*(x-x0)**2/(s*s))

def normal(x,mu,sig):
    """
    This returns the standard normal distribution with mu beeing the mean and sig the STD of the pdf
    """
    return exp(-0.5*((x-mu)/sig)**2)/sqrt(2*pi*sig**2)
 
def normal_cdf(x,mu,sig):
    """
    This routine calculated the cummulative density of the normal distribution
    """
    return 0.5 * (1. + special.erf((x-mu)/sig/sqrt(2.)))
    
def general_normal(x,eps,alpha,kappa,sig=1,mu=0):
    """
    This returns the generalized normal distribution 
    with location parameter eps, scale parameter alpha and shape parameter kappa
    INPUT: x (real), location eps (real), scale alpha (real positive), shape kappa (real)
           sig=1 and mu=0 are the parameters of the underlying normal distribution
    """
    if kappa != 0:
        y = - 1./kappa * log( 1 - kappa*(x-eps)/alpha)
    else:
        y = (x-eps)/alpha
    if kappa == 0:
        return normal(y,mu,sig)/(alpha - kappa*(x-eps))
    elif (-inf<x<eps+alpha/kappa and kappa>0) or (eps+alpha/kappa<x<inf and kappa < 0):
        return normal(y,mu,sig)/(alpha - kappa*(x-eps))
    else:
        return 0

def general_normal_cdf(x,eps,alpha,kappa,sig=1,mu=0):
    """
    This returns the cdf of the generalized normal distribution 
    with location parameter eps, scale parameter alpha and shape parameter kappa
    INPUT: x (real), location eps (real), scale alpha (real positive), shape kappa (real)
           sig=1 and mu=0 are the parameters of the underlying normal distribution
    """
    if kappa != 0:
        y = - 1./kappa * log( 1 - kappa*(x-eps)/alpha)
    else:
        y = (x-eps)/alpha
    if kappa == 0:
        return normal_cdf(y,mu,sig)
    elif (-inf<x<eps+alpha/kappa and kappa>0) or (eps+alpha/kappa<x<inf and kappa < 0):
        return normal_cdf(y,mu,sig)
    else:
        return 0
def log_normal(x,mu,sig,x0):
    """
    Returns the log normal distribution with given shape parameter sig and mu
    """
    x0-=exp(mu-sig**2)
    if getattr(x,'__iter__', False):
    	res = 1./((x-x0)*sqrt(2*pi*sig**2))*exp(-(log(x-x0)-mu)**2/(2*sig**2))
	res[x-x0<0]=0
	return res
    else:
        if x-x0>0:
	    return 1./((x-x0)*sqrt(2*pi*sig**2))*exp(-(log(x-x0)-mu)**2/(2*sig**2))
	else:
	    return 0

def log_normal_cdf(x,mu,sig,x0):
    """
    Returns the cdf of the log normal distribution with given shape parameter sig and mu
    """
    x0-=exp(mu-sig**2)
    if x-x0>0:
        return 0.5 + 0.5 * special.erf((log(x-x0)-mu)/(sqrt(2*sig**2)))
    else:
        return 0
        
def parker_angle(r=1.*eu.AU,usw=400.*eu.km/eu.s,omega_s=2.*eu.pi/(25.05*eu.day),deg=False):
  """
  Returns the Parker angle at a given distance to the Sun and a given solar wind speed
  """
  r /= eu.m
  angle = numpy.arctan2(omega_s * r, usw)
  if deg:
    angle /= eu.deg
  return angle
   
   


