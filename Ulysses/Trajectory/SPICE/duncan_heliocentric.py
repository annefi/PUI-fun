import numpy as np
from etspice import *

# Constants:
km_per_AU = 1.495979e8

#####################
### SPICE kernels ###
#####################

# J2000, ECLIPJ2000 are already loaded

# # SPICE built-in frames:
# B1950 = ReferenceFrame([kernels.planets], 'B1950')
# ECLIPB1950 = ReferenceFrame([kernels.planets], 'ECLIPB1950')
#
# # STEREO Kernel "heliospheric... .tf"
# HCI = ReferenceFrame([kernels.heliospheric_frames],'HCI')


def locateStereo(date, RF = ECLIPJ2000):
    '''
    Return STEREO's position after SPICE data

    :param date: datetime object
    :param RF: etspice.ReferenceFrame
    :return: spherical coordinates [heliocentric range in AU, latitude, longitude] with latitude in [-90 deg, 90 deg], longitude in [-180 deg, 180 deg]
    '''
    xyz = STEREO_A.position(time = date, relative_to = SUN, reference_frame = RF) # in km
    if len(xyz) == 3:
        r, theta, phi = utils.cart2spherical(xyz, degrees = True)
        #print(RF.name , np.array([r/1.496e8,theta,phi]))
        return np.array([r/km_per_AU,theta,phi])
    elif len(xyz) > 3:
        positions = []
        for t in xyz:
            r, theta, phi = utils.cart2spherical(t, degrees = True)
            positions.append(np.array([r/km_per_AU,theta,phi]))
        return positions