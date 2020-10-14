from etspice.kernels import LocalKernel
from etspice import EARTH, ReferenceFrame
import datetime as dt
import os

os.environ['SPICE_DATA_DIR'] = "../fusessh/data/projects/spice"
rf_kernel = LocalKernel('Ulysses/Trajectory/SPICE/data/test_tf.tf')
rf_kernel.load()
HCI_B = ReferenceFrame([rf_kernel],'HCI_B1950')
for i in range(10000):
    print(EARTH.position(dt.datetime.utcnow(), reference_frame = HCI_B))