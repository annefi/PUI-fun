"""
Collection of tools for working with coordinate systems. 
"""
def cart_to_sph(x,y,z,deg=False):
  from numpy import pi
  r, theta, phi = carth_to_sphere(x,y,z)
  if deg:
    theta *= 180./pi
    phi *= 180./pi
  return r,theta,phi
    
def sph_to_cart(r,theta,phi,deg=False):
  from numpy import pi
  if deg:
    theta *= pi/180.
    phi *= pi/180.
  x,y,z = sphere_to_carth(r,theta,phi)
  return x,y,z

def carth_to_sphere(x,y,z):
  """
  Transforms carthesian coords into spherical
  --x,y,z also may be numpy arrays---
  """
  from numpy import arccos, arctan2, sqrt
  r=sqrt(x**2.+y**2.+z**2.)
  theta=arccos(z/r)
  phi=arctan2(y,x)
  return r,theta,phi
def sphere_to_carth(r,theta,phi):
  """
  Transforms sperical coords into carthesian
  --r,theta,phi also may be numpy arrays---
  """
  from numpy import sin, cos
  x=r*sin(theta)*cos(phi)
  y=r*sin(theta)*sin(phi)
  z=r*cos(theta)
  return x,y,z


# Coordinate transformations sph2cart and cart2sph take 3d numpy array/matrix as input instead of x,y,z / r,theta,phi.

def sph2cart(r_vec,deg=False):
  """
  sph2cart(r_vec,deg)

  Transforms a spherical vector r_vec to cartesian coordinates.

  The input vector has to be in spherical coordinates. The angles angles of the input vector phi and theta (r_vec[1],r_vec[2]) are to be given in radians. If deg == True the angles of the input vector phi and theta (r_vec[1],r_vec[2]) are to be given in degrees.

  Parameters
  ----------
  r_vec : numpy.array with shape (3,)
          First argument.
  deg :   bool
          Third argument.

  Returns
  -------
  output : numpy.array with shape (3,)
      Returns the vector r_vec in cartesian coordinates.

  Examples
  --------
  >>> eg.sph2cart(numpy.array([1,70,12]),True)
  [ 0.07110999  0.19537308  0.9781476 ]
  """
  from numpy import sin, cos, pi, array
  r = r_vec[0]
  phi = r_vec[1]
  theta = r_vec[2]
  if deg:
    phi = phi/180.*pi
    theta = theta/180.*pi
  x = r*cos(phi)*sin(theta)
  y = r*sin(phi)*sin(theta)
  z = r*cos(theta)
  return array([x,y,z])


def cart2sph(t,deg=False):
  """
  cart2sph(t,deg)

  Transforms a cartesian t to spherical coordinates.

  The input vector has to be in cartesian coordinates. The angles angles of the output vector phi and theta (r_vec[1],r_vec[2]) will be returned in radians. If deg == True the angles of the output vector phi and theta (r_vec[1],r_vec[2]) will be returned in degrees.

  Parameters
  ----------
  t : numpy.array with shape (3,)
          First argument.
  deg :   bool
          Third argument.

  Returns
  -------
  output : numpy.array with shape (3,)
      Returns the vector t in spherical coordinates.

  Examples
  --------
  >>> eg.cart2sph(numpy.array([1,1,1]),True)
  [  1.73205081  45.          54.73561032]
  """
  from numpy import sqrt, arctan2, arccos, pi, array
  
  x = t[0]
  y = t[1]
  z = t[2]

  r = sqrt(x**2.+y**2.+z**2.)
  phi = arctan2(y,x)
  theta = arccos(z/r)

  if deg:
    out = array([r,phi/pi*180.,theta/pi*180.])
  else:
    out = array([r,phi,theta])

  return out
  
  
def cart2pol(x,y,deg=False):
  """
  cart2pol(x,y,deg=False)
  
  Transforms cartesian coordinates x,y into polar coordinates r, phi.
  
  The input parameters are the cartesian coordinates x and y, the output are the radius r and the angle phi, with the angle counted up from the positive x-axis.
  If deg is True, phi is returned in degrees instead of radians.
  
  Parameters
  ----------
  x : float value (x coordinate)
          First argument.
  y : float value (y coordinate)
          Second argument.
  deg : bool (optional)
          Third (optional) argument.
          
  Returns
  -------
  r : float value (radius coordinate)
          First return value.
  phi : float value (angle coordinate in radians or degrees, depending on deg bool value)
          Second return value.
            
  Examples
  --------
  >>> cart2pol(1,1,True)
  (1.4142135623730951, 45.0)
  """  
  from numpy import arctan2, sqrt, pi
  r = sqrt(x**2+y**2)
  phi = arctan2(y,x)
  if deg:
    phi = phi / pi * 180
  return r,phi
  
  
def pol2cart(r,phi,deg=False):
  """
  pol2cart(r,phi,deg=False)
  
  Transforms polar coordinates r, phi into cartesian coordinates x, y.
  
  The input parameters are the radius r and the angle phi, with the angle counted up from the positive x-axis, the output are the cartesian coordinates x and y.
  If deg is True, phi is to be given in degrees instead of radians.
  
  Parameters
  ----------
  r : float value (radius coordinate)
          First argument.
  phi : float value (angle coordinate in radians or degrees, depending on deg bool value)
          Second argument.
  deg : bool (optional)
          Third (optional) argument.
          
  Returns
  -------
  x : float value (x coordinate)
          First return value.
  y : float value (y coordinate)
          Second return value.
            
  Examples
  --------
  >>> pol2cart(2,45,True)
  (1.4142135623730951, 1.4142135623730949)
  """  
  from numpy import cos, sin, pi
  if deg:
    phi = phi * pi / 180.
  x = r * cos(phi)
  y = r * sin(phi)
  return x,y


# Rotation of 3d vectors around arbitrary axes.

def rot_mat(axis='x',angle=0,deg=False):
  """
  rot_mat(axis,angle,deg)

  Returns the R^3 rotation matrix about angle around axis.

  The value for axis can either be 'x','y','z', or an arbitrary vector. The angle argument is to be given in radians. If deg == True, the angle is to be given in degrees.

  Parameters
  ----------
  axis :  str or numpy.array with shape (3,)
          First argument.
  angle : float
          Second argument.
  deg :   bool
          Third argument.

  Returns
  -------
  output : numpy.matrix with shape (3,3)
      Returns the rotation matrix about angle around axis.

  Examples
  --------
  >>> rot_mat('y',45,True)
  matrix([[ 0.70710678,  0.        ,  0.70710678],
        [ 0.        ,  1.        ,  0.        ],
        [-0.70710678,  0.        ,  0.70710678]])
  """
  import numpy, math
  
  if deg:
    angle = angle * numpy.pi / 180.

  xaxis = numpy.array([1,0,0])
  yaxis = numpy.array([0,1,0])
  zaxis = numpy.array([0,0,1])

  axes = {'x':xaxis,'y':yaxis,'z':zaxis}

  if type(axis) == type(numpy.ndarray(0)):
    n = axis/math.sqrt(axis[0]**2.+axis[1]**2.+axis[2]**2.)
  elif axis in ['x','y','z']:
    n = axes[axis]
  else:
    print "Axis invalid"
    return
  c = math.cos(angle)
  s = math.sin(angle)
  rot_m = numpy.matrix([[c+n[0]**2*(1.-c),n[0]*n[1]*(1.-c)-n[2]*s,n[0]*n[2]*(1.-c)+n[1]*s],[n[1]*n[0]*(1.-c)+n[2]*s,c+n[1]**2*(1.-c),n[1]*n[2]*(1.-c)-n[0]*s],[n[2]*n[0]*(1.-c)-n[1]*s,n[2]*n[1]*(1.-c)+n[0]*s,c+n[2]**2*(1.-c)]])
  return rot_m

def rot3d(axis=0,angle=0,deg=False):
  """
  rotation matrix for rotation of angle around axis.
  axis = 0 => X
  axis = 1 => Y
  axis = 2 => Z
  default angle value is to be given in radians
  if deg is set to True, angle is to be given in degrees
  """
  from numpy import pi,sin,cos,matrix
  if deg:
    angle *= pi/180.
    
  s = sin(angle)
  c = cos(angle)
  
  rot = [matrix([[1,0,0],[0,c,-s],[0,s,c]]),matrix([[c,0,s],[0,1,0],[-s,0,c]]),matrix([[c,-s,0],[s,c,0],[0,0,1]])]
  
  return rot[axis]

def rotate(vec,axis='x',angle=0.,deg=False):
  """
  rotate(vec,axis,angle,deg)

  Returns the vector vec rotated with angle around axis.

  The value for axis can either be 'x','y','z', or an arbitrary vector. The angle argument is to be given in radians. If deg == True, the angle is to be given in degrees.

  Parameters
  ----------
  vec :   numpy.array with shape (3,)
          First argument.
  axis :  str or numpy.array with shape (3,)
          Second argument.
  angle : float
          Third argument.
  deg :   bool
          Fourth argument.

  Returns
  -------
  output : numpy.array with shape (3,)
      Returns the vector rotated about angle around axis.

  Examples
  --------
  >>> rotate(numpy.array([1,1,1]),'y',45,True)
  [ 1.37622551  1.         -0.32558154]
  """
  import numpy
  return numpy.dot(rot_mat(axis,angle,deg),vec).A1
