#{{{ Documentation and module imports
"""
Date: 23.01.2015
Authors: Christian Drews <drews@physik.uni-kiel.de>,
		 Lars Berger <berger@physik.uni-kiel.de>
		 Jan Steinhagen <steinhagen@physik.uni-kiel.de>
"""

import numpy as np
from pylib3.dbData._submask import Submask
#}}}


class Mask(object):

    """
    This class is crucial for the understanding of dbData. A mask as defined by this class is a combination of any number
    of filter operations that is used in dbData. It can be visualised using the show_mask method from dbData.
    """

    def __init__(self, dbd, name="Default"):
        """
        This class is crucial for the understanding of dbData. A mask as defined by this class is a combination of any number
        of filter operations that is used in dbData. It can be visualised using the show_mask method from dbData.
        Input:
        dbd : dbData instance
        name : Name of the mask
        """
        self.dbd = dbd
        self.submasks = {}
        if name == "Master":
            self.appliedmasks = []
            self.ma = np.ones(
                self.dbd.data[list(self.dbd.data.keys())[0]].shape[0], dtype=bool)
        else:
            self.appliedmasks = ["Master"]
            self.ma = self.dbd.get_mask("Master")
        self.directmasks = {}
        self.name = name

    def apply_mask(self, key):
        """
        Method: Another Mask is applied to the current mask (via loagical_and or rather *)
        Input
        key : Name of the Mask that should be applied
        """
        self.ma = self.ma * self.dbd.get_mask(key)
        return True

    def add_directmask(self, key, dmask, *args, **kwargs):
        """
        Method: Adds a direct mask to the current Mask
        Input
        key : Name under which the direct mask will be added
        dmask : an array of dtype=bool that must have the full length of the data
        """
        if key in self.directmasks.keys():
            print("Direct mask with the name " + key + " already exists! No action performed!")
            return False
        if (type(dmask) != np.ndarray):
            print("Given directmask should be a numpy array (dtype=bool)! No action performed!")
            return False
        elif dmask.dtype != bool:
            print("Given directmask should be have dtype=bool! No action performed!")
            return False
        elif self.ma.shape[0] != dmask.shape[0]:
            print("Direct mask has correct type but different length than data! No action performed!")
            return False
        else:
            self.directmasks[key] = dmask
            self.calc_mask()
            return True

    def remove_directmask(self, key):
        """
        Method: Removes a direct mask from the current Mask
        Input
        key : Name of the direct mask that should be removed. Takes 'all'
        """
        if key == "all":
            self.directmasks = {}
            self.calc_mask()
        elif key in list(self.directmasks.keys()):
            self.directmasks.pop(key, False)
            self.calc_mask()
        else:
            print("No directmask with name " + key + " found! No action performed!")
        return True

    def add_appliedmask(self, key, *args, **kwargs):
        if key in self.appliedmasks:
            print(key + " is already applied! No action performed!")
        elif key == self.name:
            print("Mask cannot be applied to itself! No action performed!")
        elif key not in self.dbd.mask.keys():
            print("Mask " + key + " does not exist! No action performed!")
        elif self.name == "Master":
            print("Master Mask should not have any applied Masks! No action performed!")
        else:
            if not self.check_infinite_loop(key):
                self.appliedmasks.append(key)
                self.calc_mask()
            else:
                print("Mask " + key + " not added to applied masks!")
        return True

    def check_infinite_loop(self, key):
        """
        This routine checks if appliedmasks would end in infinite loop (or rather an undefined mask setting)!
        """
        applied_list = [key]
        stop = False
        while not stop:
            stop = True
            for k in set(applied_list):
                for kk in self.dbd.mask[k].appliedmasks:
                    if kk == self.name:
                        print(self.name + ".check_infinite_loop(" + key + "): Mask " + k + " would be applied in Mask " + self.name + " but applies " + self.name + " itself! This would cause infinite loop or undefined state of at least one Mask!")
                        return True
                    elif kk != "Master":
                        while k in applied_list:
                            applied_list.remove(k)
                            applied_list.append(kk)
                            stop = False
                    else:
                        applied_list.remove(k)
        return False

    def remove_appliedmask(self, key):
        if key in self.appliedmasks:
            if key == "Master":
                print("Master Mask can not be removed from appliedmasks! No action performed!")
            else:
                self.appliedmasks.remove(key)
                self.calc_mask()
        elif key == "all":
            if self.name == "Master":
                self.appliedmasks = []
            else:
                self.appliedmasks = ["Master"]
                self.calc_mask()
        else:
            print(key + " is not in appliedmasks! No action performed!")
        return True

    def add_submask(self, key, *args, **kwargs):
        if "reset" in kwargs and kwargs["reset"] == True:
            self.remove_submask(key)
        """
		Adds a submask, if subm.calc doesn't throw an error.
		"""
        subm = Submask(*args, **kwargs)
        try:
            subm.calc(self.dbd.data)
            if key in self.submasks:
                self.submasks[key].append(subm)
            else:
                self.submasks[key] = [subm]
            self.calc_mask()
        except:
            raise

    def remove_submask(self, key, N=False):
        if key != 'all' and N == False:
            self.submasks.pop(key, False)
        elif key != 'all':
            self.submasks[key].pop(N)
        else:
            self.submasks = {}
        self.calc_mask()

    def calc_mask(self):
        self.ma = np.ones(
            self.dbd.data[list(self.dbd.data.keys())[0]].shape[0], dtype=bool)
        for key in self.submasks:
            tmp_ma = np.zeros(self.ma.shape[0], dtype=bool)
            for subm in self.submasks[key]:
                tmp_ma = np.logical_or(tmp_ma, subm.calc(self.dbd.data))
            self.ma *= tmp_ma
        # Apply all Masks that are in appliedmasks
        for key in self.appliedmasks:
            self.apply_mask(key)
            # Apply all directmasks
        for key in self.directmasks:
            self.ma *= self.directmasks[key]
        # Mask is now up to date now finaly check if Mask is applied in any
        # other Mask and update if applicable
        for key in self.dbd.mask:
            if self.name in self.dbd.mask[key].appliedmasks:
                self.dbd.mask[key].calc_mask()

    def calc_submask(self, prod):
        if prod in self.submasks:
            tmp_ma = np.zeros(self.ma.shape[0], dtype=bool)
            for subm in self.submasks[prod]:
                tmp_ma = np.logical_or(tmp_ma, subm.calc(self.dbd.data))
            return tmp_ma
        else:
            return np.zeros(self.ma.shape[0], dtype=bool)
    '''
	def cleanup_mask(self):
		nkeys = self.dbd.data.keys()
		okeys = self.submasks.keys()
		for sm in okeys:
			if not sm in nkeys:
				self.submasks.pop(sm)
	def update_mask(self):
		self.cleanup_mask()
		self.calc_mask()
	'''

    def get(self):
        return self.ma

    def set(self, ma):
        self.ma = ma
