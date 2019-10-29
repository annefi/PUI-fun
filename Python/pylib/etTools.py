#!/usr/bin/env python
from numpy import *
from numpy.fft import rfft, fft, fftfreq
from time import time

def fftPlot(x, dt=1):
    """ A simple interface for numpy rfft.
        returns the power-spectral density of 
        timeseries x ,
        dt is the time between two data points.
        In case of a real valued x, frequency range is positive.
        In case of a complex signal, negative frequencies are returned as well.
        """
    if True in iscomplex(x):
        f= fftfreq(len(x),dt)
        f = append(f[(len(x)+1)/2:], f[:(len(x)+1)/2] )
        return zip(f, abs(fft(x))**2 )
    else:
        f= abs(fftfreq(len(x),dt))
        return zip(f, abs(rfft(x))**2 )

def histPlot(a, bins=100, range=None, normed=False, weights=None):
    """ Creates an easy to plot histogram from numy.histogram.
        Via gp just use style histeps and gp.plot(hist_plot(data)).
        x values are shifted by half a bin and values are returned as zip(x,y)"""
    hy, hx = histogram(a, bins, range, normed, weights)
    return zip( hx + 0.5*(hx[1]-hx[0]), hy  )

def moving_av(signal, width, cut=False):
    """simple moving average implementation 
       width gives the windowwidth in array indices
       cut states if the whole signal is returned, or if the border is omitted"""
    signal = array(signal)
    sma = copy(signal)
    for i in range(1,width):
        sma[i:] += signal[:-i]
    if cut:
        sma = sma[width:]
    return sma/width


def logbins(b_min,b_max,num_bins=20,extra_bins_before=0,extra_bins_after=0):
  """
  creates bins distributed on a logarithmic scale between 
  b_min and b_max for histograms, returns bin edges.

  b_min: left edge of the lowest bin
  b_max: right edge of the highest bin
  num_bins: number of bins (default: 20)
  extra_bins_before: number of extra bins before the given range
  extra_bins_after: number of extra bins after the given range

  returns: bin_edges, len(bin_edges) == num_bins+1
  """
  from numpy import log, arange, exp
  
  delta = (log(b_max)-log(b_min))/num_bins
  bins = b_min*exp((arange(-1*extra_bins_before,num_bins+1+extra_bins_after))*delta)
  
  return bins
  
  
def linbins(b_min,b_max,num_bins=20,extra_bins_before=0,extra_bins_after=0):
  """
  creates bins distributed linearily between 
  b_min and b_max for histograms, returns bin edges.
  
  Note that the extra_bins_before and extra_bins_after are
  just added for interface consistency with logbins()

  b_min: left edge of the lowest bin
  b_max: right edge of the highest bin
  num_bins: number of bins (default: 20)
  extra_bins_before: number of extra bins before the given range
  extra_bins_after: number of extra bins after the given range

  returns: bin_edges, len(bin_edges) == num_bins+1
  """
  from numpy import linspace
  
  delta = float(b_max-b_min)/num_bins
  
  bins = linspace(b_min-(extra_bins_before*delta),b_max+(extra_bins_after*delta),num_bins+(extra_bins_after+extra_bins_before)+1)
    
  return bins
  

def time_fn(fn):
  """
  Decorator to time execution time of a given function fn.
  Prints the execution time to stdout.
  """    
  def dec(*args,**keys):
    print "Timing execution time of "+fn.__name__+" ..."
    ts = time()
    res = fn(*args,**keys)
    te = time()
    dt = te-ts
    print fn.__name__+" took "+str(dt)+" seconds to execute."
    return res
  
  return dec
  
