#!/usr/bin/python
from numpy import float
from Gnuplot import Gnuplot
from scipy import zeros
import os

gp=Gnuplot()
gp("f(x)=x")
gp("set term postscript enhanced color")
gp("set output 'testmulti.ps'")
gp("unset key")
gp("set grid")
gp("set xtics nomirror")
gp("set multiplot")
gp("set size 0.916,1.001")
gp("set origin 0.083,0.001")
gp("set xlabel 0,0.2")
gp("set xlabel 'Time in doy'")
gp("unset ytics")
gp("set yrange [-5:-4]")
gp("plot sin(x)")
gp("set ytics")
gp("set autoscale")
gp("set xrange[1:1e11]")
gp("set key box")
gp("unset xtics")
gp("unset xlabel")
gp("set size 1,0.285")
gp("set origin 0,0.045")
gp("set lmargin 10")
gp("set logscale y")
gp("set format y '10^{%03T}'")
gp("set ylabel -1.85")
gp("set ylabel 'Proton density in cm^{-3}' font 'Helvetica,10'")
#gp("plot 1000*f(x) w l title 'Proton density'")
gp.plot("1e100*f(x)")
gp("set border 10")
gp("set format y '10^{%03T}'")
gp("set size 1,0.29")
gp("set origin 0,0.264")
gp("set ylabel -1.85")
gp("set ylabel 'Proton temperature in K'")
#gp("plot f(x) w l title 'Proton temperature'")
gp.plot("1e-4*f(x)")
gp("set origin 0,0.487")
gp("set format y '%g'")
gp("set border 11")
gp("set ylabel -0.6")
gp("set ylabel 'Alpha to proton ratio'")
#gp("plot f(x) w l title 'Alpha to proton ratio'")
gp.plot("1000*f(x)")
gp("set origin 0,0.711")
gp("set size 1,0.34")
gp("set border 15")
gp("set ylabel -1.2")
gp("set ylabel 'Proton speed in km/s'")
gp("set title 'bla'")
gp.plot("1000*f(x)")
#gp("plot f(x) w l title 'Proton speed'")
gp("unset tmargin")
gp("unset title")
gp("unset multiplot")
gp("set size 1,1")
gp("set xtics")
gp("set autoscale")
os.system("ps2eps -f -B -l testmulti.ps")
os.system("rm testmulti.ps")
os.system("gv testmulti.eps")
