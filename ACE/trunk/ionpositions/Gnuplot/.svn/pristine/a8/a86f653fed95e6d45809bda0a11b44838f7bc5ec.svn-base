#!/usr/bin/python
from Gnuplot import Gnuplot
from func_ext import *
gp=Gnuplot()
ef=ExternalFunction(gp, "test", ["a"], lambda x, a: a*x*x)
gp("a=3")
gp.plot("test(x)")
