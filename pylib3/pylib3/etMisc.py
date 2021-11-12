"""
Collection of routines that dont fit anywhere else. Mainly non-Physics related stuff
"""
import sys
def loading_bar(LEN,i,SIGN,MSG=False):
	"""
	Routine that prints a progress bar.
	INPUT: LEN - Total number of Iterations
	       i   - Current iteration number
	       SIGN- Style of the progress bar, must be a string (e.g. '#')
	EXAMPLE:
		for i in range(100):
			loading_bar(100,i,'#')
	"""
	b=" %2.2f  "%(100./LEN*i)
	if 100./LEN*i+1>100: 
		sys.stdout.write("\b"*111),
	n_signs=int(50./LEN*i)+1
	sys.stdout.write("\b"*60),
	PTEXT="["+(SIGN*n_signs)+("-"*(50-n_signs))+"]"+b
	if MSG:
		if n_signs-4<0: n_signs=4
		PTEXT=PTEXT[0:5]+MSG[0:n_signs-4].upper()+MSG[n_signs-4:].lower()+PTEXT[len(MSG)+5:-2]
	sys.stdout.write(PTEXT)
	sys.stdout.flush()
	
	
def shift(a,n):
  """
  Shift the entries of an array a by n steps
  n can be negative, to shift backwards
  elements shifted out on either end will be 
  shifted in on the other end
  
  a : array_like
  n : int
  
  example:
    a = arange(5)
    shift(a,2)
    print a
     => [3,4,0,1,2]
  """
  import numpy
  return numpy.append(a[-n:],a[:-n])
