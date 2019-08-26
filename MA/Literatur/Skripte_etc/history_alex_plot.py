# -*- coding: utf-8 -*-
"""
Created on Wed Jul 25 14:16:27 2018

@author: fischer
""

17/31: u = unique(d.data['wHe+'])
17/32: x = numpy.arange(len(u))
17/35: import matplotlib.pyplot as plt
17/40: pylab.close('all')
17/41: plt.plot(x,u,'x')
17/42: max(u)
17/43: numpy.max(u)
17/44: u[u!=inf]=0
17/45: plt.plot(x,u,'x')
17/46: u = unique(d.data['wHe+'])
17/47: u[u==inf]=0
17/48: pylab.close('all')
17/49: max(u)
17/50: plt.plot(x,u,'x')
17/51: pylab.close('all')
17/52: plt.plot(x,u,'x')
   1: %history -g
