#!/usr/bin/python
from scipy import zeros, sqrt, mean
from Gnuplot import Gnuplot, GridData, GnuplotOpts, Data
from numpy import float
from math import atan

gp=Gnuplot()
gp("set terminal postscript enhanced color solid")
gp("set output 'bm2058.ps'")
gp("plot '/data/idefix/soho/eit/carrington_maps/284/carr2058_eit284.avs' binary filetype=avs axis x1y2 notitle with rgbimage")






