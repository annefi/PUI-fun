""" Various functions for transforming between coordinate systems

Heliocentric (HC, 'Solar ecliptic', ECL):
    x-axis pointing towards vernal equinox (intersection celestial & ecliptic plane);
    z-axis normal to ecliptic

Heliographic (HG, solat equatorial, EQ):
    x-axis pointing towards intersection of solar equatorial plane & ecliptic;
    z-axis normal to solar equator

Radial-Tangential-Normal (RTN):
    R: Sun to SC unit vector
    T: wxR with w: Sun's spin axis
    N: completes the right-handed c.s.

"""
import numpy as np
import math
from matplotlib import pylab


def cart2spher(xyz: np.ndarray, deg: bool = True) -> np.ndarray:
    """
    Convert positions in cartesian coordinates xyz to spherical coordinates.

    Spherical coordinates (radius r, latitude theta, longitude phi), 
    where r > 0, theta in [-90°, 90°], phi in [-180°, 180°]
    [https://upload.wikimedia.org/wikipedia/commons/d/dc/3D_Spherical_2.svg]

    :param xyz: data in cartesian coordinates (1D or 2D numpy array)
    :param degrees: whether the angles theta and phi should be in degrees (True) or radians (False). Default: True
    :return: data in spherical coordinates
    """
    if xyz.ndim == 1:
        x, y, z = xyz
        return np.array([
            math.sqrt(x ** 2 + y ** 2 + z ** 2),
            90 - math.degrees(math.acos(z / math.sqrt(x ** 2 + y ** 2 + z ** 2))) if deg else
            math.pi / 2 - math.acos(z / math.sqrt(x ** 2 + y ** 2 + z ** 2)),
            math.degrees(math.atan2(y, x)) if deg else math.atan2(y, x)
        ])
    elif xyz.ndim == 2:
        x, y, z = xyz.T
        return np.array([
            np.sqrt(x ** 2 + y ** 2 + z ** 2),
            90 - np.degrees(np.arccos(z / np.sqrt(x ** 2 + y ** 2 + z ** 2))) if deg else
            np.pi / 2 - np.arccos(z / np.sqrt(x ** 2 + y ** 2 + z ** 2)),
            np.degrees(np.arctan2(y, x)) if deg else np.arctan2(y, x)
        ]).T

def spher2cart(vec_sph: np.ndarray, deg: bool = True):
    """
    Convert positional vector vec_sph in spherical coordinates to cartesian coordinates.

    Spherical coordinates (radius r, latitude theta, longitude phi),
    where r > 0, theta in [-90°, 90°], pi in [-180°, 180°]
    [https://upload.wikimedia.org/wikipedia/commons/d/dc/3D_Spherical_2.svg]

    :param vec_sph: data in spherical coordinates (1D or 2D numpy array)
    :param deg: whether the angles theta and phi should be in degrees (True) or radians (False). Default: True
    :return: data in cartesian coordinates
    """
    if vec_sph.ndim == 1:
        r, theta, phi = np.array([vec_sph[0], np.radians(vec_sph[1]), np.radians(vec_sph[2])]) if deg else vec_sph
        return np.array([r * np.sin(np.pi / 2. - theta) * np.cos(phi), r * np.sin(np.pi / 2. - theta) * np.sin(phi),
                         r * np.cos(np.pi / 2. - theta)])
    if vec_sph.ndim == 2:
        print('KK')
        r, theta, phi = np.array(
            [vec_sph[:, 0], np.radians(vec_sph[:, 1]), np.radians(vec_sph[:, 2])]) if deg else vec_sph.T
        return np.array([r * np.sin(np.pi / 2. - theta) * np.cos(phi), r * np.sin(np.pi / 2. - theta) * np.sin(phi),
                         r * np.cos(np.pi / 2. - theta)]).T

def rot_mat(axis ='x', angle = 0., deg: bool = True):
    """Return the R^3 rotation matrix about angle around axis.

    Example:
    rot_mat('y',45,True)
    >> matrix([[ 0.70710678,  0.        ,  0.70710678],
                    [ 0.        ,  1.        ,  0.        ],
                    [-0.70710678,  0.        ,  0.70710678]])

    :param axis: str x','y','z' or an arbitrary vector (1D numpy array)
    :param angle: angle of rotation in ° or radians
    :param deg: if True angle is in ° (default), if False angle is given in radians
    :return: numpy.matrix with shape (3,3): rotation matrix about angle around axis
    """
    if deg:
        angle = angle * np.pi / 180.
    xaxis = np.array([1, 0, 0])
    yaxis = np.array([0, 1, 0])
    zaxis = np.array([0, 0, 1])
    axes = {'x': xaxis, 'y': yaxis, 'z': zaxis}
    if type(axis) == type(np.ndarray(0)):
        n = axis / math.sqrt(axis[0] ** 2. + axis[1] ** 2. + axis[2] ** 2.) #normalisation
    elif axis in ['x', 'y', 'z']:
        n = axes[axis]
    else:
        print("Axis invalid")
        return
    c = math.cos(angle)
    s = math.sin(angle)
    rot_m = np.matrix(
        [[c + n[0] ** 2 * (1. - c), n[0] * n[1] * (1. - c) - n[2] * s, n[0] * n[2] * (1. - c) + n[1] * s],
         [n[1] * n[0] * (1. - c) + n[2] * s, c + n[1] ** 2 * (1. - c), n[1] * n[2] * (1. - c) - n[0] * s],
         [n[2] * n[0] * (1. - c) - n[1] * s, n[2] * n[1] * (1. - c) + n[0] * s, c + n[2] ** 2 * (1. - c)]])
    return rot_m

def rotate(vec: np.ndarray, axis='x', angle = 0., deg: bool = True):
    """Return the vector vec rotated by angle around axis.

    'Active Rotation'
    Examples:
    rotate(np.array([1,1,1]),'y',45,True)
    >> np.array([ 1.37622551  1.         -0.32558154])

    rotate(np.array([1,0,0]),'z',10,True)
    >> np.array([0.98480775, 0.17364818, 0.        ])

    :param vec: vector to be rotated (1D numpy array)
    :param axis: axis around which the vector will be rotated. Can be 'x','y','z' or an arbitrary vector (1D numpy array)
    :param angle: rotation angle
    :param deg: True the rotation angle is given in degree (default) or False for in radians
    :return: rotated vector as np.ndarray
    """
    return np.dot(rot_mat(axis, angle, deg), vec).A1

def hg_to_hc(hg_vec: np.ndarray, degree=True, long_shift = 0.) -> np.ndarray:
    """Transformation of a positional vector from heliographic (solar equatorial) to heliocentric (ecliptic) coordinate
    system

    :param hg_vec: Heliographic vector [R,lat,long] where lat in [-90°,90°], long: s. long_shift if using Ulysses data
    :param degree: True (default) when angles are given in degrees (False when in radians)
    :param long_shift: Ulysses HG-long data is shifted by pi (long=0 shifted by 75+180 deg against vernal equinox)
    :return: vector [R,lat,long] in heliocentric coordinates
    """
    hg_cart = spher2cart(np.array([hg_vec[0], hg_vec[1], hg_vec[2] - long_shift]), deg=degree)
    # print('hg_cart:', hg_cart)
    int1 = rotate(hg_cart, 'x', 7.25, deg=degree)
    # print('int1', int1)
    int2 = rotate(int1, 'z', 75.0615, deg=degree)
    # print('int2', int2)
    int3 = cart2spher(int2, deg=degree)
    return np.array([int3[0], int3[1], int3[2]])

def hc_to_hg(hc_vec, degree=True, long_shift=0.) -> np.ndarray:
    """ Transformation of a vector from heliocentric to heliographic coordinate system.

    :param hc_vec: Heliocentric vector [R,lat,long] where lat in [-90°,90°]
    :param degree: True (default) when angles are given in degrees (False when in radians)
    :param long_shift: Ulysses HG-long-data is shifted by pi (long=0 shifted by 75+180 deg against vernal equinox)
    :return: vector [R,lat,long] in heliographic coordinates where lat increases towards +z axis to +90 deg and long according to long_shift
    """
    hc_cart = spher2cart(np.array([hc_vec[0], hc_vec[1], hc_vec[2]]), deg=degree)
    # print('hc_cart:', hc_cart)
    int1 = rotate(hc_cart, 'z', -75.0615, deg=degree)
    # print('int1', int1)
    int2 = rotate(int1, 'x', -7.25, deg=degree)
    # print('int2', int2)
    int3 = cart2spher(int2, deg=degree)
    return np.array([int3[0], int3[1], int3[2] + long_shift])

def hg_to_rtn(r_vec: np.ndarray, sc_vec: np.ndarray, long_shift = 0., long_shift_r = 0.):
    """ Transform vector r_vec in heliographic (solar equatorial) coordinates to RTN coordinates

    RTN-system: centered at the Sun

    :param r_vec: in spherical heliographic coordinates (r,lat,long) in deg
    :param sc_vec: in spherical heliographic coordinates (r,lat,long) in deg
    :param long_shift: Ulysses HG-long-data is shifted by pi (long=0 shifted by 75+180 deg against vernal equinox)
    :param long_shift_r: needs to be pi as well, when r_vec is sc_vec itself & SC is Ulysses data ('Ulysses in RTN')
    :return: cartesian coordinates in RTN-system
    """
    r_vec_sph = np.array([r_vec[0], r_vec[1], r_vec[2] - long_shift_r])
    # print("r_vec_sph:")
    # print(r_vec_sph)
    r_vec_cart = spher2cart(r_vec_sph, deg = True)  # conversion to cartesian coordinates
    #print("\n r_vec_cart:")
    #print(r_vec_cart)
    # principle: rotate r_vec like you had to rotate 'R' onto 'x'
    interim_1 = rotate(r_vec_cart, 'z', - (sc_vec[2] - long_shift), deg=True)
    R, T, N = rotate(interim_1, 'y', sc_vec[1], deg=True)
    return np.array([R, T, N])

def calc_asp_angles(sc_vec: np.ndarray, earth_vec: np.ndarray, cs = "hg", long_shift_sc = 0.):
    '''
    Calculates aspect angles phi and theta from position vectors of SC and Earth

    :param sc_vec: Vector from sun to SC in spherical HG/EQ (default) coordinates (specify RTN-coordinates via param cs):
     [r,lat,long] in °
    :param earth_vec: Vector from Sun to Earth in HG/EQ equatorial coordinates (r,lat,long)
    :param cs: "hg" for heliographic spherical coordinates (default) or "rtn" for RTN coordinates
    :param long_shift_sc: longitude shift. Needs to be 180 for Ulysses data in HG (when using Ulysses archive data), otherwise 0.
    :return: asp_theta, asp_phi (PoV from SC) in °, where asp_phi increases to +90 deg towards negative T-axis ('left')
        from viewing line SC-sun and -90 deg towards positive T-axis and asp_theta increases from zero in sun
        direction (negative R-axis) to +90 deg towards N-axis
    '''
    if cs == "hg":
        earth_vec = hg_to_rtn(earth_vec, sc_vec, long_shift = long_shift_sc, long_shift_r = 0.)
        sc_vec = hg_to_rtn(sc_vec, sc_vec, long_shift = long_shift_sc, long_shift_r = long_shift_sc)
        # print('\n vectors in rtn:')
        # print(sc_vec)
        # print(earth_vec)
        cs = "rtn"
    if cs == 'rtn':
        # translation (to shift the center of the c.-s. to the SC)
        earth_vec_trans = earth_vec - sc_vec
        # print("\n translation: earth_vec_trans")
        # print(earth_vec_trans)
        # transform to spherical coordinates
        earth_vec_sph = cart2spher(earth_vec_trans, deg=True)
        # print('\n spherical:')
        # print(earth_vec_sph)
        # ToDo: evtl. noch Richtung anpassen. Momentan: positiver Asp-phi: "links" mit Blick von SC zur Sonne
        asp_phi = earth_vec_sph[2] + 180.
        if asp_phi > 180.:
            asp_phi -= 360.
        #asp_theta = 90. - earth_vec_sph[1]
        asp_theta = earth_vec_sph[1]
        return (asp_theta, asp_phi)
    else:
        print('No coordinate system specification!')








############ above this line: definitely reviewed summer 2021. below: probably not ################





















 






def calc_v(vec1, vec2, dt, R = "km"):
    '''
    Calculates Ulysses' velocity components R,T and N as the "derivation" of position vectors with respect to the time.
    v1 = (pos2 - pos1) / dt
    dt = (t2 - t1) = 1 day as Ulysses' trajectory data is given daily (in seconds)
    :param vec1: location of current measurement in spherical HG (R ,long,lat) coordinates in(AU,deg,deg)
    :param vec2: location of next measurement in spherical HG (R,long,lat) coordinates
    :param dt: time between measurement vec1 and vec2 in seconds
    :return: average vx, vy, vz between measurement 1 and 2 in km/s
    '''
    # vec1 and vec2 in RTN coordinates based on SC being @ vec1:
    vec1_RTN = hg_to_rtn(vec1,vec1,degr = True,long_shift = 180., long_shift_r = 180.)
    vec2_RTN = hg_to_rtn(vec2,vec1,degr = True,long_shift = 180., long_shift_r = 180.)
    # differential quotient:
    delta_RTN = (vec2_RTN - vec1_RTN)
    if R == "AU":
        vx,vy,vz = (delta_RTN / dt) * 1.496*10**8 # conversion from AU to km
        print('HG:')
        print(vec1)
        print(vec2)
        print('RTN:')
        print(vec1_RTN)
        print(vec2_RTN)
        #print(delta_RTN)
    elif R == "km":
        vx, vy, vz = (delta_RTN / dt)
        print('HG:')
        vec1[0] /= 1.496*10**8
        vec2[0] /= 1.496 * 10 ** 8
        print(vec1)
        print(vec2)
        print('RTN:')
        print(vec1_RTN / (1.496 * 10 ** 8))
        print(vec2_RTN / (1.496 * 10 ** 8))
        d = delta_RTN / (1.496 * 10 ** 8)
        print(d)
    #print(vx,vy,vz)
    return vx,vy,vz





def calc_SPE_umstaendlich(asp_phi,asp_theta,R,deg=True):
    '''
    calculates the 'flat' aspect angle (given as SPE in Ulysses traj-data) from aspect phi and theta in spherical RTN coordinates.
    Built for testing if all of the previous transformations were done right.
    Aspect angle: Angle between sun and earth as seen from SC.
    :param asp_phi: Aspect phi angle in spherical RTN coordinates
    :param asp_theta: Aspect theta angle in spherical RTN coordinates
    :param R: Radius vector in spherical RTN coordinates (probably distance SC<->earth)
    :param deg: angles need to be given in degrees (default) or radians
    :return:
    '''
    # auxiliary lines for calculating the leg opposing the angle SPE C
    if deg == True:
        aux_line_a = sqrt(2*R**2(1-cos(asp_phi*pi/180.)))
        aux_line_b = sqrt(2*R**2(1-cos(asp_theta*pi/180.)))
    else:
        aux_line_a = sqrt(2*R**2(1-cos(asp_phi)))
        aux_line_b = sqrt(2*R**2(1-cos(asp_theta)))
    c = sqrt(aux_line_a**2+aux_line_b**2)
    # ToDo: Finish (but found an easier func -> calc_SPE())
    return 1


def calc_SPE(asp_phi,asp_theta,deg=True):
    '''
    calculates the 'flat' aspect angle (given as SPE in Ulysses traj-data) from aspect phi and theta in spherical RTN coordinates.
    Built for testing whether all of the previous transformations were done right.
    Aspect angle: Angle between sun and earth as seen from SC.
    Easy-peasy alternative to calc_SPE_umstaendlich() via some fiddling with Law of Cosine
    :param asp_phi: Aspect phi angle in spherical RTN coordinates
    :param asp_theta: Aspect theta angle in spherical RTN coordinates
    :param deg: angles need to be given in degrees (default) or radians
    :return: SPE, 'flat' aspect angle in degree
    '''
    if deg == True:
        SPE = arccos(cos(asp_phi*pi/180.)+cos(asp_theta*pi/180.)-1)
    else:
        SPE = arccos(cos(asp_phi) + cos(asp_theta) - 1)
    return SPE*180./pi



def plot_deviation_hg():
    '''
    
    :return: 
    '''
    # loading data:
    data = open('/data/etph/Ulysses/trajectory/traj_data_ulysses_pool.dat','r')
    R = []
    hc_long = []
    hc_lat = []
    hg_long = []
    hg_lat = []
    for headerline in range(4):
        data.readline()
    for line in data:
        l = line.split()
        R.append(float(l[8]))
        hc_long.append(float(l[10]))
        hc_lat.append(float(l[9]))
        hg_long.append(float(l[12]))
        hg_lat.append(float(l[11]))
    # calculate HG from HC:
    hg_long_calc = []
    hg_lat_calc = []
    hg_long_diff = []
    hg_lat_diff = []
    days = []
    for i in range(len(R)):
        hg = hc_to_hg(array([R[i],hc_long[i],hc_lat[i]]),long_shift = 180.)
        hg_long_calc.append(hg[1])
        hg_lat_calc.append(hg[2])
        hg_long_diff.append(hg_long[i]-hg[1])
        hg_lat_diff.append(hg_lat[i]-hg[2])
        days.append(i)
    # plot:
    fig = pylab.figure('HG data vs. calculated')
    ax = pylab.subplot(211)

    ax.plot(days,hg_long, label="Long Data")
    ax.plot(days, hg_lat, label="Lat Data")
    ax.plot(days, hg_long_calc, label="Long Calc")
    ax.plot(days, hg_lat_calc, label="Lat Calc")
    ax.set_ylabel('angles / deg')
    ax.legend(loc=1)
    # plot difference:
    ax2 = pylab.subplot(212,sharex=ax)
    ax2.plot(days,hg_long_diff,label='long')
    ax2.plot(days,hg_lat_diff,label='lat')
    ax2.set_ylabel('difference in angle / deg')
    ax2.set_xlabel('days from dec 1990 ')
    ax2.set_ylim(-1.2,1.2)
    ax.set_xlim(-100, 7000)








