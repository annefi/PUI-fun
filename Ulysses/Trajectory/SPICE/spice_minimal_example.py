import datetime
from etspice import *

# STEREO Kernel "heliospheric... .tf"
HCI = ReferenceFrame([kernels.heliospheric_frames],'HCI')
# DIY kernels:
my_kernel = kernels.LocalKernel('Ulysses/Trajectory/SPICE/data/test_tf.tf')
my_kernel.load()

date = datetime.datetime(1992,2,18,9,30)

pos = ULYSSES.position(time = date, relative_to = SUN, reference_frame = HCI)

from spiceypy import spkezr, datetime2et
[x, y, z, vx, vy, vz] = spkezr('ULYSSES', datetime2et(date), 'HCI', 'None', 'SUN')[0]

print(f"\nPosition of Ulysses @ {date}:\n", pos)
print(f"\nVelocity of Ulysses @ {date}:\n", [vx, vy, vz])





