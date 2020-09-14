from etspice import SUN, ULYSSES
from etspice import ReferenceFrame, utils
from etspice import kernels
import datetime
import spiceypy as spice
import os
import numpy as np

# os.environ['SPICE_DATA_DIR'] = "../fusessh/data/projects/spice"
os.environ['SPICE_DATA_DIR'] = "/data/projects/spice"

#my_kernel = kernels.LocalKernel('Ulysses/Trajectory/SPICE/metakernel.tm') # load additional kernels via meta kernel
#my_kernel.load()

HCI = ReferenceFrame([kernels.heliospheric_frames],'HCI')
HEEQ = ReferenceFrame([kernels.heliospheric_frames],'HEEQ')

def cart2sph(t, deg=False):
    """
    cart2sph(t,deg)

    Transforms a cartesian t to spherical coordinates.

    The input vector has to be in cartesian coordinates. The angles angles of the output vector phi and theta (r_vec[
    1],r_vec[2]) will be returned in radians. If deg == True the angles of the output vector phi and theta (r_vec[1],
    r_vec[2]) will be returned in degrees.

    Parameters
    ----------
    t : numpy.array with shape (3,)
            First argument.
    deg :   bool
            Third argument.

    Returns
    -------
    output : numpy.array with shape (3,)
        Returns the vector t in spherical coordinates.

    Examples
    --------
    >>> eg.cart2sph(numpy.array([1,1,1]),True)
    [  1.73205081  45.          54.73561032]
    """
    from numpy import sqrt, arctan2, arccos, pi, array

    x = t[0]
    y = t[1]
    z = t[2]

    r = sqrt(x ** 2. + y ** 2. + z ** 2.)
    phi = arctan2(y, x)
    theta = arccos(z / r)

    if deg:
        out = array([r, phi / pi * 180., theta / pi * 180.])
    else:
        out = array([r, phi, theta])

    return out

def locateUlysses(date, RF, spher = True):
    '''
    Returns Ulysses' position after SPICE data

    :param date: datetime object
    :param RF: etspice.ReferenceFrame
    :return:
    '''
    xyz = ULYSSES.position(time = date, relative_to = SUN, reference_frame = RF)
    if spher == True:
        r, theta, phi = utils.cart2spherical(xyz, degrees = True)
    print(r/1.496e8,theta,phi)

def read_pool():
    path_pool = "Ulysses/Trajectory/trajectory_data/traj_data_ulysses_pool.dat"
    fin = open(path_pool,'r')
    paras = fin.readline().split()
    for headerline in range(3):
        fin.readline()
    p_dict = {p:[] for p in paras}
    for line in fin:
        data = line.split()
        for i,p in enumerate(p_dict.keys()):
            p_dict[p].append(float(data[i]))
    p_dict["datestring"] = []
    for i,year in enumerate(p_dict['Year']):
        p_dict['datestring'].append("%i-%i-%i" % (year,p_dict['MM'][i],p_dict['DD'][i]))
    for key in p_dict:
        p_dict[key] = np.array(p_dict[key])
    return p_dict

def get_pool_data(date):
    '''

    :param date: datetime.datetime object
    :return:
    '''
    data = read_pool()
    datestring = "%i-%i-%i" % (date.year, date.month, date.day)
    index = np.where(data['datestring'] == datestring)[0][0]
    print("HC       R_AU: %s Lat: %s, Long: %s \nHG     R_AU: %s  Lat: %s,  Long: %s \n \n" %(data['R'][index],
                                                                                         data['HC_Lat'][index],
                                                                    data['HC_Long'][index],data['R'][index],
                                                                    data['HG_Lat'][index],data['HG_Long'][index]))

def comp_rf(date):
    get_pool_data(date)
    locateUlysses(date, HCI)
