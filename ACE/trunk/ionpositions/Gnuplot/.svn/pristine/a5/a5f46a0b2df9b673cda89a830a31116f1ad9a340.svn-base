#!/usr/bin/python
from common import *
from Gnuplot.funcif import *
from Gnuplot import GnuplotOpts

# *THIS* is very important to have the function interface to GNUplot working.
GnuplotOpts.prefer_fifo_data=False

# create 1D function in Gnuplot space
f=Function(gp, # GNUplot instance this function will be defined in
           "f", # name of the function (in GNUplot)
           "exp(a*x+b)" # the expression of the function
           )

# set parameters a and b
f.pars["a"]=3.0
f.pars["b"]=0.0

# evaluate f (in python)
print [f(x) for x in range(0, 3)]

# create some data points
from tempfile import mkstemp
fname=mkstemp()[1]
file=open(fname, "w")
print>>file, "0.0 0.9"
print>>file, "1.0 25.0"
print>>file, "2.0 378.3"
print>>file, "3.0 8100.0"
file.close()

print "Fit data in %s." % file.name

# fit f to data in file
f.fit(file.name, "1:2")

# plot f and data
gp.plot(f, '"'+file.name+'"')

gp.hardcopy(argv[0]+".ps")
#
#from os import remove
#remove(fname)
