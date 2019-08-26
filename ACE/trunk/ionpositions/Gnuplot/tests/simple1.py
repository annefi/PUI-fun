#!/usr/bin/python
from common import *

gp.plot("x", "x*x", "x*x*x")
gp.title("Title")
gp.xlabel("X-Label")
gp.ylabel("Y-Label")
gp.replot()
gp.hardcopy(argv[0]+".ps")
