from numpy import *
from scipy import constants

m_p=constants.m_p
e=constants.e

def convsecs70toDoY(t):
    from time import gmtime
    tmpt=gmtime(t)
    DoY=float(tmpt[7])+float(tmpt[3])/24.+float(tmpt[4])/(24.*60.)+float(tmpt[5])/(24.*60.*60.)
    return DoY

#Funktionen zur Umrechnung der ToF in m/q
def epq_step(step):
  """
  Returns energy per charge for ESA-step.
  step -> (list of) ESA-step(s)
  """
  Uo=0.331095e3     #lowest energy per charge
  r=1.040926        #scaling factor
  smax=116          #maximum step number
  epq=Uo*r**(smax-step)
  return epq  
#LEM Mode
def epq_step_lem(step):
	"""
	 Returns energy per charge for ESA-step 
	"""
	epq=0
	return epq
# alpha berechnet den Energyverlust in der Folie bei gegebener primaer energie E unter der Annahme eines bestimmten Elements (elem)
def alpha(E,elem="Carbon"):#E in keV
      if elem=="Helium":
        a=5.25964
        b=14.10724
        c=0.0201180
      elif elem=="Carbon":
        a=8.74008
        b=7.91934
        c=0.0449395
      elif elem=="Nitrogen":
        a=9.08698
        b=6.32469
        c=0.05584
      elif elem=="Oxygen" and all(E>60):
        a=12.89533
        b=18.49764
        c=0.0203987
      elif elem=="Oxygen":
        a=12.87063
        b=12.53791
        c=0.0010569
      elif elem=="Iron":
        a=16.36333
        b=-4.12881
        c=0.00980934
      elif elem=="Iron3":
        a=7.56047
        b=-36.06787
        c=0.056224
      elif elem=="Iron2":
        a=11.31031
        b=-21.10281
        c=0.031347
      elif elem=="Neon":
        a=3.99836
        b=-5.28461
        c=0.10065
      elif elem=="Magnesium":
        a=4.4433
        b=-6.91556
        c=0.059687
      elif elem=="Silicon":
        a=9.34902
        b=-3.36442
        c=0.079775
      else:
        print "No alpha has been calculated for this ion"
        a,b,c=0,0,0
      return a/(E+b)+c 
  
def step_to_en(step,q):     #q in numbers of e, returns total energy in eV
      epq=step_to_epq(step)
      return epq*q

def total_energy(step,q,Up):
      return step_to_en(step,q)+Up*q 

def tch_to_tns(tch):
    a=2.00723e-10
    b=-1.46909e-09
    tof=a*tch+b
    #a=1.99326e-10
    #b=-8.73831e-10
    #tof=a*tch+b 
    return tof

def mq_func2(tof,epq,U_p,elem="Carbon",q=1):
    """
    Returns mq depending on ToF-channel, E/q, and foil loss -> new version by A. Taut
    tof -> (list of) ToF channel(s)
    epq -> (list of) E/q(s)
    U_p -> PAPS (two periods -> DoY < 150 U_p = 19.xxx , DoY > 150 U_p = 23.xx
    elem -> Foil loss is calculated under the assumption that ions were from the given element
    q -> Charge state
    """
    return 2*tof**2/(70.5e-3**2)*(epq+U_p)*(1-alpha((epq*q+U_p*q)/1000.,elem))*e/m_p 

def foil_loss(eq):
  """
  Returns parameter for Foil loss
  eq -> (list of) ESA-step(s)
  """
  return 9.12634e-6*eq**3-1.26741e-3*eq**2+4.55282e-2*eq-7.00777
  # Alt mit q
  #return -9.14732913e-09*eq**3+6.40784258e-07*eq**2-1.80375060e-05*eq-2.03481327e-04  #Parameter aus mq-tof-loop_neu.py

def get_paps(times):
    paps=zeros(times.shape[0])
    paps[(times>=82.)*(times<145.)]=19.81e3
    paps[(times>=150.)*(times<230.)]=23.88e3
    return paps

def mq_func(tof,epq,param):
  """
  Returns mq depending on ToF-channel, E/q, and foil loss
  tof -> (list of) ToF channel(s)
  epq -> (list of) E/q(s)
  param -> (list of) parameter(s) for Foil-loss
  """
  Un=22.69e3   # Post-acceleration voltage in KeV
  d=70.5e-3    # length of ctof ToF section in m
  
  return (5.78748e-7*tof+2.48478e-5)**2*2/d**2*(epq+Un)*(1-param)
  # Alt mit q
  #return 1./(d**2/((1.56558096094e-06*tof+7.75612861593e-05)**2*2*(epq+Un))+param)
  
def tof_to_mq(tof,step):
  """
  Returns mq depending on ToF-channel and ESA-step
  tof -> (list of) ToF channel(s)
  step -> (list of) ESA-step(s)
  """
  return mq_func(tof,epq_step(step),foil_loss(step))

def tof_to_mq2(tch,step,times,elem="Helium",q=1):
  """
  Returns mq depending on ToF-channel and ESA-step
  tof -> (list of) ToF channel(s)
  step -> (list of) ESA-step(s)
  times -> list of timestamps needed to use the correct postacceleration voltage
  elem,(q) -> determines which element (and charge) is used for carbon foil loss
  """
  return mq_func2(tch_to_tns(tch),epq_step(step),get_paps(times),elem,q)


def getionvel(mpc,step):
  """
  Returns ion velocity in km/s.
  mpc -> mass per charge of ion (He2+ -> 2., He1+ -> 1.)
  step -> (list of) ESA-step(s)
  """
  v=sqrt(epq_step(array(step))*2/(mpc*m_p/e))
  return v*1e-3

mpqarr=zeros([128,1024])
for step in range(128):
  for tof in range(1024):
    mpqarr[step,tof]=tof_to_mq(tof,step)

def hist_step(step):
  doubles[step,0:200]=0.
  x,y=histogram(mpqarr[step,:],linspace(0,56,231),weights=doubles[step,:])
  return x,y[:-1]+0.1


