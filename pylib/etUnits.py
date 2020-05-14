#!/usr/bin/env python

pi = 3.1415926535

rad = 1.
radians = 1.
deg = pi/180.
degrees = deg

m = 1.  # Meter
kg = 1.  # Kilogram
s = 1.  # Second
A = 1.  # Ampere
K = 1.  # Kelvin
V = kg * m**2 / A * s**-3  # Volt
C = A * s  # Coulomb
J = kg * m**2 * s**-2  # Joule
F = s**4 * A**2 * m**-2 / kg  # Farad
T = V * s / m**2  # Tesla

pm = 1.e-12 * m
nm = 1.e-9 * m
um = 1.e-6 * m
mm = 1.e-3 * m
cm = 1.e-2 * m
km = 1.e3 * m
AU = 149597870691. * m

g  = 1.e-3 * kg
mg = 1.e-6 * kg
t = 1e3 * kg

fs = 1e-15 * s
ps = 1e-12 * s
ns = 1e-9 * s
us = 1e-6 * s
ms = 1e-3 * s
min = 60. * s
hour  = 60. * min
day   = 24. * hour

h = 6.62606957e-34 * J * s
hbar = h/(2.*pi)

me = 9.10938291e-31 * kg
mp = 1.67262158e-27 * kg
mn = 1.67492735e-27 * kg
c0 = 299792458. * m / s
e = 1.602176487e-19 * C
epsilon_0 = 8.854187817620e-12 * F / m
mu_0 = 1.2566370614e-6 * V * s / A / m

eV   = e * V
keV  = 1e3 * eV
MeV  = 1e6 * eV
GeV  = 1e9 * eV
TeV  = 1e12 * eV

kb = 1.3806488e-23 * J / K


def energy2ms(e,m=me,c=c0):
  """
  Calculates the particle velocity in m/s from a given energy in Joules
  
  INPUT: 
  e: Particle energy in eV
  m: Particle mass in kg (default: electron mass)
  c: Speed of light (default: vacuum speed of light)  
  
  OUTPUT:
  Particle velocity in m/s
  """
  from numpy import sqrt
  E0 = m*c**2
  return c * sqrt( 1. - (E0/(E0+e))**2)


def eV2ms(e,m=me,c=c0):
  """
  Calculates the particle velocity in m/s from a given energy in electronvolts
  
  INPUT: 
  e: Particle energy in eV
  m: Particle mass in kg (default: electron mass)
  c: Speed of light (default: vacuum speed of light)  
  
  OUTPUT:
  Particle velocity in m/s
  """
  return energy2ms(e*eV,m,c)
  
def keV2kms(e,m=me,c=c0):
  """
  Calculates the particle velocity in km/s from a given energy in kiloelectronvolts
  
  INPUT: 
  e: Particle energy in keV
  m: Particle mass in kg (default: electron mass)
  c: Speed of light (default: vacuum speed of light)  
  
  OUTPUT:
  Particle velocity in km/s
  """
  return eV2ms(e*1000.,m,c) / 1000.

def kms2eV(v,m=me,c=c0):
  """
  Calculates the particle energy in electronvolts from a given particle velocity in km/s
  
  INPUT: 
  v: Particle velocity in km/s
  m: Particle mass in kg (default: electron mass)
  c: Speed of light (default: vacuum speed of light)  
  
  OUTPUT:
  Particle energy in electronvolts
  """
  return (0.5*m*(v*km)**2)/eV	

def kms2keV(v,m=me,c=c0):
  """
  Calculates the particle energy in kiloelectronvolts from a given particle velocity in km/s
  
  INPUT: 
  v: Particle velocity in km/s
  m: Particle mass in kg (default: electron mass)
  c: Speed of light (default: vacuum speed of light)  
  
  OUTPUT:
  Particle energy in kiloelectronvolts
  """
  return kms2eV(v,m,c) / 1000.
