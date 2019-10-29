import scipy.stats as st
import numpy as np

class cos_law_gen(st.rv_continuous):
    """Cosine law distributed continous random variable

    %(before_notes)s

    Notes
    -----
    Useful to generate an evenly distributed isotropic flux through spherical surface
    
        pdf(x) = 2. * cos(x) * sin(x)
   
    Domain: 0 <= x <= pi/2.

    %(example)s
    
    """
    def _pdf(self,x):
        return 2. * np.cos(x) * np.sin(x)
    def _cdf(self,x):
    	return - 0.5 * np.cos(2. * x) + 0.5
    def _ppf(self,q):
        return 0.5 * np.arccos(1. -  2. * q) 
cos_law = cos_law_gen(a=0,b=np.pi/2.,name='cos_law')
    
class cos_sq_law_gen(st.rv_continuous):
    """Cosine squared law distributed continous random variable

    %(before_notes)s

    Notes
    -----
    Useful to generate an steeply distributed isotropic flux through spherical surface
    
        pdf(x) = 3. * cos(x)**2 * sin(x)
   
    Domain: 0 <= x <= pi/2.

    %(example)s
    
    """
    def _pdf(self,x):
        return 3. * np.cos(x)**2. * np.sin(x)
    def _cdf(self,x):
    	return 1 -  np.cos(x)**3.
    def _ppf(self,q):
        return np.arccos((1.-q)**(1./3.))
cos_sq_law = cos_sq_law_gen(a=0,b=np.pi/2.,name='cos_sq_law')
