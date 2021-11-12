#{{{ Documentation and module imports
"""
Date: 23.01.2015
Author: Christian Drews <drews@physik.uni-kiel.de>,
        Lars Berger <berger@physik.uni-kiel.de>

"""

from numpy import array, sum,zeros,argmin,linspace,transpose,where,sqrt,exp, arange, max, min, nonzero, cos, sin, mean,std, isnan,isinf,inf, ones,NAN, ndarray,average,alltrue,greater_equal,equal,greater,less_equal,less,not_equal,logical_or,iterable,unique,meshgrid,ravel,swapaxes,reshape,asarray, hstack,vstack, searchsorted,seterr,log10
import matplotlib
#}}}
class mask(object):
	"""
	This class is crucial for the understanding of dbData. A mask as defined by this class is a combination of any number
	of filter operations that is used in dbData. It can be visulaised using the show_mask method from dbData.
	"""
	def __init__(self,dbd,name="Default"):
		"""
		This class is crucial for the understanding of dbData. A mask as defined by this class is a combination of any number
		of filter operations that is used in dbData. It can be visulaised using the show_mask method from dbData.
		"""
		self.dbd = dbd
		self.ma = ones(self.dbd.data[self.dbd.data.keys()[0]].shape[0],dtype=bool)
		self.submasks = {}
		if name == "Master":
			self.appliedmasks = []
		else:
			self.appliedmasks = ["Master"]
		self.directmasks ={}
		self.name = name
	def apply_mask(self,key):
		self.ma=self.ma*self.dbd.get_mask(key)
		return True
	def add_directmask(self,key,dmask):
		if key in self.directmasks.keys():
			print "Direct mask with the name "+key+" already exists! No action performed!"
			return False
		if (type(dmask)!=ndarray):
			print "Given directmask should be a numpy array (dtype=bool)! No action performed!"
			return False
		elif dmask.dtype!=bool:
			print "Given directmask should be have dtype=bool! No action performed!"
			return False
		elif self.ma.shape[0]!=dmask.shape[0]:
			print "Direct mask has correct type but different lenght than data! No action performed!"
			return False
		else:
			self.directmasks[key]=dmask
			self.calc_mask()
			return True
	def remove_directmask(self,key):
		if key=="all":
			self.directmasks={}
			self.calc_mask()
		elif self.directmasks.has_key(key):
			self.directmasks.pop(key,False)
			self.calc_mask()
		else:
			print "No directmask with name "+key+" found! No action performed!"
		return True
	def add_appliedmask(self,key):
		if key in self.appliedmasks:
			print key+" is already applied! No action performed!"
		elif key == self.name:
			print "Mask cannot be applied to itself! No action performed!"
		elif key not in self.dbd.mask.keys():
			print "Mask "+key+" does not exist! No action performed!"
		elif self.name == "Master":
			print "Master Mask must not have any applied Masks! No action performed!"
		else:
			if not self.check_infinite_loop(key):
				self.appliedmasks.append(key)
				self.calc_mask()
			else:
				print "Mask "+key+" not added to applied masks!"
		return True
	def check_infinite_loop(self,key):
		"""
		This routine checks if appliedmasks would end in infinite loop (or rather an undefined mask setting)! 
		"""
		applied_list=[key]
		stop=False
		while not stop:
			stop=True
			for k in set(applied_list):
				for kk in self.dbd.mask[k].appliedmasks:
					if kk==self.name:
						print self.name+".check_infinite_loop("+key+"): Mask "+k+" would be applied in Mask "+self.name+" but applies "+self.name+" itself! This would cause infinite loop or undefined state of at least one Mask!"
						return True
					elif kk!="Master":
						applied_list
						while k in applied_list:
							applied_list.remove(k)
						applied_list.append(kk)
						stop=False
					else:
						applied_list.remove(k)
		return False
	def remove_appliedmask(self,key):
		if key in self.appliedmasks:
			if key == "Master":
				print "Master Mask can not be removed from appliedmasks! No action performed!"
			else:
				self.appliedmasks.remove(key)
				self.calc_mask()
		elif key=="all":
			if self.name == "Master":
				self.appliedmasks=[]
			else:
				self.appliedmasks=["Master"]
			self.calc_mask()
		else:
			print key+" is not in appliedmasks! No action performed!"
		return True
	def add_submask(self,key,operator,*arg,**kwarg):
		if kwarg.has_key("reset") and kwarg["reset"]==True:
			self.remove_submask(key)
		if not self.dbd.data.has_key(key) and "MASK2D" not in key:
			print "add_submask : Invalid Data Product (wrong key)"
			return False
		if self.submasks.has_key(key):
			self.submasks[key].append(submask(key,operator,*arg))
		else:
			self.submasks[key]=[submask(key,operator,*arg)]
		self.calc_mask()
	def remove_submask(self,key,N=False):
		if key!='all' and N==False:
			self.submasks.pop(key,False)
		elif key!='all':
			self.submasks[key].pop(N)
		else:
			self.submasks={}
		self.calc_mask()
	def calc_mask(self):
		self.ma = ones(self.dbd.data[self.dbd.data.keys()[0]].shape[0],dtype=bool)
		for key in self.submasks:
			tmp_ma = zeros(self.ma.shape[0],dtype=bool)
			for subm in self.submasks[key]:
				if key in self.dbd.data.keys(): #If key is found in self.dbd.data, pass data prod to calc
					tmp_ma = logical_or(tmp_ma,subm.calc(self.dbd.data[key]))
				elif "MASK2D" in key: #If it's a MASK2D mask, pass data[key_1] and data[key_2] to calc
					key_1, key_2 = key.split()[1].split('/')
					tmp_ma = logical_or(tmp_ma,subm.calc(array([self.dbd.data[key_1], self.dbd.data[key_2]])))
				else: # If key not found, pass False (for user defined functions)
					tmp_ma = logical_or(tmp_ma,subm.calc(False))
			self.ma*=tmp_ma
		# Apply all Masks that are in appliedmasks
		for key in self.appliedmasks:
			self.apply_mask(key)
		# Apply all directmasks
		for key in self.directmasks.keys():
			self.ma*=self.directmasks[key]
		# Mask is now up to date now finaly check if Mask is applied in any other Mask and update if applicable
		for key in self.dbd.mask.keys():
			if self.name in self.dbd.mask[key].appliedmasks:
				self.dbd.mask[key].calc_mask()
	def calc_submask(self,prod):
		if self.submasks.has_key(prod):
			tmp_ma = zeros(self.ma.shape[0],dtype=bool)
			for subm in self.submasks[prod]:
				tmp_ma = logical_or(tmp_ma,subm.calc(self.dbd.data[prod]))
			return tmp_ma
		else:
			return zeros(self.ma.shape[0],dtype=bool)
	def cleanup_mask(self):
		nkeys=self.dbd.data.keys()
		okeys=self.submasks.keys()
		for sm in okeys:
			if not sm in nkeys:
				self.submasks.pop(sm)
	def update_mask(self):
		self.cleanup_mask()
		self.calc_mask()
	def get(self):
		return self.ma
	def set(self,ma):
		self.ma=ma
