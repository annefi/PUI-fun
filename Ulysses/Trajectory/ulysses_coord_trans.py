""" Various functions for transforming between coordinate systems

Heliocentric (HC, 'Solar ecliptic'):
    x-axis pointing towards vernal equinox (intersection celestial & ecliptic plane);
    z-axis normal to ecliptic

Heliographic (HG):
    x-axis pointing towards intersection of solar equatorial plane & ecliptic;
    z-axis normal to solar equator

Radial-Tangential-Normal (RTN):
    R: Sun to SC unit vector
    T: wxR with w: Sun's spin axis
    N: completes the right-handed c.s.

"""

from pylib import dbData
from numpy import array, cos, arccos, pi, sqrt
from pylib.etCoord import rotate, sph2cart, cart2sph
from matplotlib import pylab


def hg_to_hc(hg_vec, degree=True, long_shift = 0.):
    '''
    Transformation of a vector from heliographic to heliocentric coordinate system
    :param hg_vec: Heliographic vector [R,long,lat] where lat increases towards +z axis, long: s. long_shift if using Ulysses data
    :param degree: True when angles are given in degrees (False when in radians)
    :param long_shift: Ulysses HG-long-data is shifted by pi (long=0 shifted by 75+180 deg against vernal equinox)
    :return: vector [R,long,lat] in heliocentric coordinates where lat increases towards +z axis
    '''
    hg_cart = sph2cart([hg_vec[0],hg_vec[1]-long_shift,90.-hg_vec[2]],deg=degree)
    print('hg_cart:', hg_cart)
    int1 = rotate(hg_cart,'x',7.25,deg=degree)
    print('int1', int1)
    int2 = rotate(int1,'z',75.062,deg=degree)
    print('int2', int2)
    int3 = cart2sph(int2,deg=degree)
    print('int3', int3)
    return array([int3[0],int3[1],90.-int3[2]])

def hc_to_hg(hc_vec, degree=True, long_shift = 180.):
    '''
    Transformation of a vector from heliocentric to heliographic coordinate system.
    :param hc_vec: Heliocentric vector [R,long,lat] where lat increases towards +z axis
    :param degree: True when angles are given in degrees (False when in radians)
    :param long_shift: Ulysses HG-long-data is shifted by pi (long=0 shifted by 75+180 deg against vernal equinox)
    :return: vector [R,long,lat] in heliographic coordinates where lat increases towards +z axis and long according to long_shift
    '''
    hc_cart = sph2cart([hc_vec[0],hc_vec[1],90-hc_vec[2]],deg=degree)
    int1 = rotate(hc_cart,'z',-75.062,deg=degree)
    int2 = rotate(int1, 'x', -7.25, deg=degree)
    int3 = cart2sph(int2,deg=degree)
    return array([int3[0],long_shift+int3[1],90-int3[2]])

def hg_to_rtn(r_vec, sc_vec, long_shift = 180., long_shift_r = 0.):
    '''
    Transforms heliographic coordinates from vector r_vec to coordinates as seen from an RTN-system (centered at the Sun)s.
    ('active Rotation')
    !! Theta is 90deg when only z-component
    :param r_vec: in spherical heliographic coordinates (r,long,lat)
    :param sc_vec: in spherical heliographic coordinates (r,long,lat)
    :param long_shift: Ulysses HG-long-data is shifted by pi (long=0 shifted by 75+180 deg against vernal equinox)
    :param long_shift_r: needs to be pi as well, when r_vec is sc_vec itself & SC is Ulysses data ('Ulysses in RTN')
    :return: cartesian coordinates in RTN-system
    '''
    r_vec_2conv = array([r_vec[0],r_vec[1]-long_shift_r,90.-r_vec[2]]) # conversion to 'classical' theta-definition
    # print("r_vec_2conv:")
    # print(r_vec_2conv)
    r_vec_cart= sph2cart(r_vec_2conv, deg = True) # conversion to cartesian coordinates
    # print("\n r_vec_cart:")
    # print(r_vec_cart)
    # principle: rotate r_vec like you had to rotate 'R' onto 'x'
    interim_1 = rotate(r_vec_cart, 'z', -(sc_vec[1]-long_shift), deg = True)
    R,T,N = rotate(interim_1, 'y', sc_vec[2], deg = True)
    return array([R, T, N])