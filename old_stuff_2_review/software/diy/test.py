import sys
sys.path.append('/home/asterix/fischer/ulysses/swics/software/libulpy')
from uswipha import uswipha
from pylib import dbData
import numpy as np
from matplotlib import pylab
from matplotlib.animation import FuncAnimation


d_uswi = uswipha(year=[1994],tf=[[1,36]])
d = d_uswi.get_data('Master','det')

