from etspice import SUN, ULYSSES
from etspice import ReferenceFrame, utils
from etspice import kernels
import datetime
import spiceypy as spice

my_kernel = kernels.LocalKernel('PUI/Ulysses/Trajectory/SPICE/metakernel.tm') # load additional kernels via meta kernel
my_kernel.load()

HCI = ReferenceFrame([kernels.heliospheric_frames],'HCI')





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
        r2,phi2,theta2 = cart2sph(xyz,deg = True)
    print(r,phi,theta)
    print(r2,phi2,theta2)