import sys
sys.path.append('/home/asterix/fischer/ulysses/swics/software/libulpy')
from uswipha import uswipha
from pylib import dbData
import numpy as np


class test(dbData,uswipha):
	def __init__(self,y=[1992],t=[[1,50]]):
		pass

def load(y=[1992],t=[[1,50]]):
	d = uswipha(year=y,tf=t)
	d.sync_swoops()
	return d
	

def add(a=1,b=2):
	print(a+b)