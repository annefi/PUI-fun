""" Various functions for transforming between coordinte systems

Heliocentric (HC, 'Solar ecliptic'):
    x-axis pointing towards vernal quinox (intersection celestial plane & ecliptic);
    z-axis normal to ecliptic

Heliographic (HG):
    x-axis pointing towards intersection of solar equatorial plane & ecliptic; z-axis normal to solar
    equator

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
    int1 = rotate(hg_cart,'x',7.25,deg=degree)
    int2 = rotate(int1,'z',75.062,deg=degree)
    int3 = cart2sph(int2,deg=degree)
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

def hg_to_rtn(r_vec,sc_vec,spherical = True, degr = True, long_shift = 180.,long_shift_r = 0.):
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
    if spherical:
        r_vec_2conv = array([r_vec[0],r_vec[1]-long_shift_r,90.-r_vec[2]]) # conversion to 'classical' theta-definition
        # print("r_vec_2conv:")
        # print(r_vec_2conv)
        r_vec_cart= sph2cart(r_vec_2conv,deg=degr)
        # print("\n r_vec_cart:")
        # print(r_vec_cart)
    if degr:
        interim_1 = rotate(r_vec_cart,'z',-(sc_vec[1]-90-long_shift),deg=True)
        # print("\n interim_1:")
        # print(interim_1)
        interim_2 = rotate(interim_1,'x',-sc_vec[2],deg=True)
        # print("\n interim_2:")
        # print(interim_2)
        R,T,N = rotate(interim_2,'z',-90.,deg=True)
    return array([R,T,N])


def calc_v(vec1, vec2, dt, R = "km"):
    '''
    Calculates Ulysses' velocity components R,T and N as the "derivation" of position vectors with respect to the time.
    v1 = (pos2 - pos1) / dt
    dt = (t2 - t1) = 1 day as Ulysses' trajectory data is given daily
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


# def calc_earth(sc_vec, long_wrt_earth, deg=True, long_shift=180.):
#     '''
#     Calculates position of earth in heliographic coordinates based on Ulysses trajectory data
#     :return:
#     '''
#     # Longitude:
#     long_hg = sc_vec[1]+long_shift-long_wrt_earth
#
#     # Latitude:
#     long_hg_cart = sph2cart(long_hg,deg=True)
#     diff_vec = long_hg_cart - array([1.,0.,0.,])
#     A = '1'
#     pass
#     #return array([r,long,lat])


def calc_asp_angles(sc_vec,earth_vec,cs = "hg", l_s_sc = 180.):
    '''
    Calculates aspect angles phi and theta from position vectors of SC and earth
    :param sc_vec: Vector from sun to SC in cartesian HG (default) coordinates (specify RTN-coordinates via param cs)
    :param earth_vec: Vector from sun to earth
    :param cs: "hg" for heliographic cartesian coordinates (default) or "rtn" for RTN cartesian coordinates
    :param l_s_sc: longitude shift. Needs to be 180 for Ulysses data in HG, otherwise 0.
    :return: asp_phi, asp_theta (PoV from SC)
    asp_phi increases to +90 deg towards negative T-axis ('left') from viewing line SC-sun and -90 deg towards positive
    T-axis
    asp_theta increases from zero in sun direction (negative R-axis) to +90 deg towards N-axis
    '''
    if isinstance(sc_vec,list):
        sc_vec = array(sc_vec)
    if isinstance(earth_vec,list):
        earth_vec = array(earth_vec)
    # check for c.-s. of given vectors and change HG to RTN if neccessary
    if cs == "hg":
        earth_vec = hg_to_rtn(earth_vec,sc_vec,long_shift = l_s_sc, long_shift_r = 0.)
        sc_vec = hg_to_rtn(sc_vec, sc_vec, long_shift = l_s_sc, long_shift_r = l_s_sc)
        # print('\n vectors in rtn:')
        # print(sc_vec)
        # print(earth_vec)
        cs = "rtn"
    if cs == 'rtn':
        # translation (to shift the center of the c.-s. to the SC)
        earth_vec_trans = earth_vec -  sc_vec
        # print("\n translation: earth_vec_trans")
        # print(earth_vec_trans)
        # transform to spherical coordinates
        earth_vec_sph = cart2sph(earth_vec_trans, deg=True)
        # print('\n spherical:')
        # print(earth_vec_sph)
        # ToDo: evtl. noch Richtung anpassen. Momentan: positiver Asp-phi: "links" mit Blick von SC zur Sonne
        asp_phi = earth_vec_sph[1]+180.
        if asp_phi > 180.:
            asp_phi -= 360.
        asp_theta = 90. -earth_vec_sph[2]
        return(asp_phi,asp_theta)
    else:
        print('No coordinate system specification!')



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








