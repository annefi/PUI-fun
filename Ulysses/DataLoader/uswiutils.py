""" Ulysses SWICS utils 

Functions
---------
deter_epq()
    Return the 64 energy-per-charge steps of Ulysses SWICS

getvelocity(mass, charge, step, frac = 1)
    Return an ion's (defined by mass, charge) velocity based on the epq step

"""

from numpy import arange,array,sqrt

def deter_epq():
    """Return the 64 energy-per-charge steps of Ulysses SWICS

    Energy per charge is given in keV per e
    """
    a = 0.4271
    b = 1.036547
    epq_arr = a * b ** (138-(2*arange(64)))
    return epq_arr

def getvelocity(mass,charge,step,frac=1.):
    """Return an ion's (defined by mass, charge) velocity based on the epq step

    Mass and charge must be given in multiples of amu and e, resp.
    Velocity is returned in km/s.
    """
    epq_arr = array([ 60.50781039, 56.31621253, 52.41498202, 48.78400405, 45.40455724, 42.2592171, 39.3317662, 36.60711056, 34.0712018, 31.71096474, 29.51422996, 27.46967104, 25.56674622, 23.79564398, 22.14723248, 20.61301249, 19.18507355, 17.85605316, 16.6190989, 15.46783299, 14.39631949, 13.39903366, 12.47083347, 11.60693312, 10.80287831, 10.05452332, 9.35800963, 8.709746, 8.10638996, 7.54483061, 7.02217253, 6.53572089, 6.08296755, 5.66157808, 5.26937981, 4.90435056, 4.56460821, 4.24840107, 3.95409875, 3.68018383, 3.42524401, 3.1879648, 2.96712279, 2.76157931, 2.57027459, 2.39222225, 2.22650424, 2.07226613, 1.92871266, 1.79510366, 1.67075025, 1.55501125, 1.44728992, 1.34703084, 1.25371708, 1.1668675, 1.08603431, 1.01080073, 0.94077886, 0.87560766, 0.81495111, 0.75849646, 0.70595263, 0.6570487 ])
    energy=(epq_arr[step]*charge*1.60217646e-19*1000.)*frac
    tmpmass=mass*1.66053886e-27
    velocity=sqrt(2.*energy)/sqrt(tmpmass)
    velocity=velocity/1000.
    return velocity
