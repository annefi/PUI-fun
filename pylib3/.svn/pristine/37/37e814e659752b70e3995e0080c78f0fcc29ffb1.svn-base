#{{{ Documentation and module imports
"""
Date: 15.08.2012
Author: Christian Drews <drews@physik.uni-kiel.de>, Lars Berger <berger@physik.uni-kiel.de>, Jan Steinhagen <steinhagen@physik.uni-kiel.de>

KNOWN BUGS: #1 Memory leak if you call plot routine too often. Memory is not released. Matplotlib sucks

************************************************
Port to Python3
Date: 07.01.2020
Author: Lars Berger <berger@physik.uni-kiel.de>
************************************************
"""

import copy
import pickle
import functools
import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt
import pylib3.dbData._operators as _operators
import os
import scipy.cluster
import sys

from pylib3.dbData._mask import Mask
from pylib3.dbData._mask1D import Mask1D
from pylib3.dbData._mask2D import Mask2D, mask2d_op
from pylib3.dbData._plotdbData import PlotdbData
# from pylib.etMisc import loading_bar
from pylib3.dbData._showmask import ShowMask

#}}}


def ArgParser(func):
    @functools.wraps(func)
    def funcDEC(self, *args, **kwargs):
        tmp = list(args)
        if isinstance(args[0], str) and args[0].lower() == "all":
            tmp[0] = list(self.mask.keys())
            # tmp[0].remove("Master")
            func(self, *tuple(tmp), **kwargs)
        elif isinstance(args[0], str):
            tmp[0] = [args[0]]
            func(self, *tuple(tmp), **kwargs)
        elif np.iterable(args[0]):
            func(self, *args, **kwargs)
        else:
            print("Invalid Arguments - Function call canceled!")
    return funcDEC


class plot_properties(object):

    def __init__(self, prod):
        self.props = {}
        self.props["color"] = "red"
        self.props["name"] = prod
        self.props["linewidth"] = 1
        self.props["linestyle"] = '-'
        self.props["marker"] = 'None'
        self.props["markersize"] = 1
        self.props["contourcolor"] = "jet"
        self.props["shadeazimuth"] = 45
        self.props["shadepolar"] = 45
        # self.props["contourcolor2"]="binary"
        self.props["label_loc"] = (0.05, 0.05)

    def set_name(self, name):
        self.name = name

    def set(self, prop, val):
        if prop in self.props.keys():
            self.props[prop] = val
        else:
            print( "Property %s not available!" % (prop))

    def get_all(self):
        return self.props

    def get(self, prop):
        if prop in self.props.keys():
            return self.props[prop]
        else:
            return False

    def get_name(self):
        return self.name

    def get_hist1d(self):
        tmp = copy.deepcopy(self.props)
        if tmp.has_key("name"):
            tmp.pop("name")
        tmp["drawstyle"] = "steps"
        print( tmp)
        return tmp


class DataDict(dict):

    """
    This class can be used to tinker with the dbData.data dictionary.
    Remarks: .items() and .values() from dict should not be used since they bypass __getitem__.
    """

    def __init__(self, *args, **kwargs):
        self.expand = {}
        self.expansion = {}
        super(DataDict, self).__init__(*args, **kwargs)

    def __getitem__(self, key, raw=False):
        if raw or key not in self.expand or key not in self:
            value = dict.__getitem__(self, key)
        elif self.expand[key] in self.expansion:
            value = dict.__getitem__(self, key)[
                self.expansion[self.expand[key]]]
        else:
            print( "__getitem__: The expansion '{}' for '{}' is not defined!".format(self.expand[key], key))
            return False
        return value

    def _expansion_in_expand(self, expkey):
        keys_for_exp_in_expand = []
        for key, expkey_in_expand in self.expand.items():
            if expkey_in_expand == expkey:
                keys_for_exp_in_expand.append(key)
        return keys_for_exp_in_expand

    def _remove_expand(self, key):
        self.expand = copy.copy(self.expand)
        del(self.expand[key])
        return

    def _remove_expansion(self, expkey):
        del(self.expansion[expkey])
        return

    def _set_expand(self, key, expkey, verbose=True):
        if verbose:
            if key in self.expand and expkey != self.expand[key]:
                oldexpkey = self.expand[key]
                print( "_set_expand: WARNING - the expansion for the data product '{}' has been changed from '{}' to '{}'.".format(key, oldexpkey, expkey))
                if expkey not in self.expansion:
                    print( "\tThe expansion '{}' still hasn\'t been set.".format(expkey))
                keys_for_oldexp_in_expand = self._expansion_in_expand(
                    oldexpkey)
                keys_for_oldexp_in_expand.remove(key)
                if keys_for_oldexp_in_expand:
                    print( "\tThe old expansion '{}' is still in use for the data products {}.".format(oldexpkey, keys_for_oldexp_in_expand))
                else:
                    print( "\tThe old expansion '{}' is not in use for any data products anymore - If it still exists, consider removing it with the clean_up method.".format(oldexpkey))
        self.expand = copy.copy(self.expand)
        self.expand[key] = expkey
        return

    def _set_expansion(self, expkey, expvalue, verbose=True):
        if verbose:
            if expkey in self.expansion and not (expvalue == self.expansion[expkey]).all():
                print( "_set_expansion: WARNING - the already existing expansion '{}' has been overwritten.".format(expkey))
                keys_for_exp_in_expand = self._expansion_in_expand(expkey)
                if keys_for_exp_in_expand:
                    print( "\tThis changes the expansion for the data products {}.".format(keys_for_exp_in_expand))
        self.expansion[expkey] = expvalue
        return

    def add_reduced_data(self, key, value, expkey, expansion=[], verbose=True, **kwargs):
        self.__setitem__(key, value)
        if expansion != []:
            self._set_expansion(expkey, expansion, verbose)
        if verbose:
            if expkey not in self.expansion:
                print( "add_reduced_data: WARNING - the expansion '{}' still hasn\'t been set.".format(expkey))
        self._set_expand(key, expkey, verbose)
        return

    def all_reduced(self, keys):
        return np.array([self.reduced(key) for key in keys]).all()

    def all_same_expansion(self, keys):
        same_expansion = self.all_reduced(keys)
        if same_expansion:
            exp_array = np.array([self.get_expand(key) for key in keys])
            same_expansion = (exp_array == exp_array[0]).all()
        return same_expansion

    def clean_up(self, verbose=True, getonlyinfo=False):
        key_non_existent = []
        exp_non_existent = []
        keys_for_non_existent_exp = []
        exp_not_in_use = []
        expindex_out_of_bounds = []
        for key, expkey in self.expand.items():
            if key not in self:
                key_non_existent.append(key)
                if not getonlyinfo:
                    self._remove_expand(key)
                continue
            if expkey not in self.expansion:
                exp_non_existent.append(expkey)
                keys_for_non_existent_exp.append(key)
                if not getonlyinfo:
                    self._remove_expand(key)
        for expansion in self.expansion:
            keys_for_exp_in_expand = self._expansion_in_expand(expansion)
            if not keys_for_exp_in_expand:
                exp_not_in_use.append(expansion)
            else:
                for key in keys_for_exp_in_expand:
                    if key not in key_non_existent:
                        if self.expansion[expansion].max() >= self.get_reduced_data(key).shape[0]:
                            expindex_out_of_bounds.append([key, expansion])
        if not getonlyinfo:
            for expansion in exp_not_in_use:
                self._remove_expansion(expansion)
        if verbose and not getonlyinfo:
            if key_non_existent:
                print( "clean_up: The the data products {} were listed to have expansions but don't exist. They have been removed from the expand dictionary.".format(key_non_existent))
            if exp_non_existent:
                print( "clean_up: The expansions {} for the data products {} were not defined - their links have been revoked.".format(exp_non_existent, keys_for_non_existent_exp))
            if exp_not_in_use:
                print( "clean_up: The expansions {} were not in use for any data products - they have been removed.".format(exp_not_in_use))
            if expindex_out_of_bounds:
                print( "clean_up: ERROR - the data product / expansion pairings {} will yield IndexErrors because the expansions contain indices greater than the data product\'s shape. This issue must be solved by the user.".format(expindex_out_of_bounds))
        if getonlyinfo:
            return key_non_existent, exp_non_existent, keys_for_non_existent_exp, exp_not_in_use, expindex_out_of_bounds
        return

    def copy(self, ):
        return copy.copy(self)

    def deepcopy(self, ):
        return copy.deepcopy(self)

    def get_expand(self, key):
        if self.reduced(key):
            expand = self.expand[key]
        else:
            expand = None
            print( "get_expand: The data product is not reduced, None has been returned.")
        return expand

    def get_expansion(self, key):
        if self.reduced(key):
            expansion = self.expansion[self.expand[key]]
        else:
            expansion = np.arange(self[key].shape[0])
            print( "get_expansion: The data product is not reduced, a generic expansion has been returned.")
        return expansion

    def get_info(self, verbose=True):
        key_non_existent, exp_non_existent, keys_for_non_existent_exp, exp_not_in_use, expindex_out_of_bounds = self.clean_up(
            verbose=False, getonlyinfo=True)
        if verbose:
            if key_non_existent:
                print( "get_info: The data products {} are listed to have expansions but don't exist.".format(key_non_existent))
            if exp_non_existent:
                print( "get_info: WARNING - the expansions {} for the data products {} are not defined.".format(exp_non_existent, keys_for_non_existent_exp))
            if exp_not_in_use:
                print( "get_info: The expansions {} are not in use for any data products.".format(exp_not_in_use))
            if expindex_out_of_bounds:
                print( "get_info: ERROR - the data product / expansion pairings {} will yield IndexErrors because the expansions contain indices greater than the data product\'s shape. This issue must be solved by the user.".format(expindex_out_of_bounds))
            if not key_non_existent and not exp_non_existent and not exp_not_in_use and not expindex_out_of_bounds:
                print( "get_info: The data dictionary is consistent.")
        if not exp_non_existent and not expindex_out_of_bounds:
            return True
        return False

    def get_reduced_data(self, key):
        return self.__getitem__(key, raw=True)

    def mask(self, masks):
        '''
        Returns a mixed copy of the DataDict with all masks applied. Masks are applied to
        the expansions, thus the expansion dict is new; but the reduced data and expand
        dicts are shallow copies. Works only properly if all data products and masks have
        the same length, obviously.
        '''
        if isinstance(masks, np.ndarray):
            applied_mask = masks
        elif isinstance(masks, (tuple, list)) and len(masks) == 1:
            applied_mask = masks[0]
        else:
            applied_mask = np.ones(self.__getitem__(list(self.keys())[0]).shape, dtype=bool)
            for mask in masks:
                applied_mask *= mask
        masked_dict = self.copy()
        masked_dict.expansion = {}
        for key in self.expansion:
            masked_dict.expansion[key] = self.expansion[key][applied_mask]
        for key in masked_dict:
            if not masked_dict.reduced(key):
                masked_dict[key] = masked_dict[key][applied_mask]
        return masked_dict

    def reduce_all_data(self, keys_not_to_reduce=[], verbose=True):
        if isinstance(keys_not_to_reduce, str):
            keys_not_to_reduce = [keys_not_to_reduce]
        for key in self:
            if key not in keys_not_to_reduce:
                self.reduce_data(key, verbose)
        return

    def reduce_data(self, key, verbose=True):
        def ret_dtype(red_array, int_array, ignore_ratio=False):
            dtype = None
            ratio = np.float_(red_array.shape[0]) / int_array.shape[0]
            if ignore_ratio:
                ratio = 0.
            max_ = int_array.max()
            if max_ <= 255 and ratio < 0.85:
                dtype = np.uint8
            elif max_ <= 65535 and ratio < 0.7:
                dtype = np.uint16
            elif max_ <= 4294967295 and ratio < 0.4:
                dtype = np.uint32
            return dtype
        if self.reduced(key):
            nd, ex = self.get_reduced_data(key), self.get_expansion(key)
            dtype = ret_dtype(nd, ex, ignore_ratio=True)
            if dtype:
                old_dtype = ex.dtype
                if old_dtype != dtype:
                    ex = ex.astype(dtype)
                    self._set_expansion(self.get_expand(key), ex)
                    if verbose:
                        print( "reduce_data: The '{}' expansion's dtype has been changed from '{}' to '{}'.".format(self.get_expand(key), old_dtype, ex.dtype))
        else:
            nd, ex = np.unique(self.__getitem__(key), return_inverse=True)
            dtype = ret_dtype(nd, ex)
            if dtype:
                ex = ex.astype(dtype)
                if (self.__getitem__(key) == nd[ex]).all():
                    self.add_reduced_data(key, nd, '{} expansion'.format(key), expansion=ex)
                    if verbose:
                        print( "reduce_data: The data product '{}' was successfully reduced.".format(key))
            elif verbose:
                print( "reduce_data: The reduction of the data product '{}' would not yield significant improvements and has therefore not been executed.".format(key))
        return

    def reduced(self, key):
        reduced = False
        if key in self:
            if key in self.expand:
                reduced = True
        else:
            raise KeyError(key)
        return reduced

    def remove_reduction(self, key, cleanup=False, verbose=True):
        if key in self:
            if self.get_info(verbose=False):
                if key in self.expand:
                    self.__setitem__(key, self.__getitem__(key))
                    self._remove_expand(key)
                else:
                    if verbose:
                        print( "remove_reduction: The data product '{}' was not reduced in the first place.".format(key))
                if cleanup:
                    self.clean_up(verbose)
            else:
                print( "remove_reduction: The data dictionary has issues. Please debug it before you run remove_reduction again.")
                self.get_info()
        else:
            raise KeyError(key)
        return

    def remove_reductions(self, cleanup=True):
        if self.get_info(verbose=False):
            for key in self:
                self.remove_reduction(key, verbose=False)
            if cleanup:
                self.clean_up()
        else:
            print( "remove_reductions: The data dictionary has issues. Please debug it before you run remove_reductions again.")
            self.get_info()
        return


class dbData(object):

    def __init__(self, *args, **kwargs):
        self.mask = {}
        self.data = DataDict({})
        self.dp = {}
        self.mp = {}
        self.load_data(*args, **kwargs)
        for key in self.data:
            if not isinstance(self.data[key], np.ndarray):
                self.data[key] = np.array(self.data[key])
        if self.data:
            self.add_mask("Master")
        else:
            print( "Implement load_data method first!")
            exit()
        self.Plot = PlotdbData(self)
        self._init_plot_properties()

    def __getitem__(self, key):
        if (key not in self.data.keys()):
            print( "No data with key ", key)
        return self.data[key]

    def _init_plot_properties(self):
        """
        Initialize Plot properties
        """
        for i, key in enumerate(sorted(self.data.keys())):
            self.dp[key] = plot_properties(key)
            self.dp[key].set("color", self._get_color(i))
        for i, key in enumerate(sorted(self.mask.keys())):
            self.mp[key] = plot_properties(key)
            self.mp[key].set("color", self._get_color(i))

    def _get_color(self, i):
        colors = [
            "red", "blue", "green", "orange", "coral", "navy", "darkgoldenrod", "DarkRed", "Fuchsia", "Maroon", "pink",
            "OrangeRed", "Olive", "Indigo", "Firebrick", "DimGray", "Purple", "Plum", "PaleGreen", "brown", "DarkBlue"] * 20
        return colors[i - 1]

    def get_all_data(self, masks=[]):
        '''
        Returns the data dictionary with masks (logical and) applied. Note
        that the Master mask is also applied!
        If called with masks=[] the data dictionary without any masks (not
        even the Master mask) applied is returned.
        If called with masks='all' all masks will be applied.
        INPUT: (tuple/list of) mask(s). Bool numpy arrays (possible use are temporary
                   masks for instance) are also allowed.
        OUTPUT: data dictionary reduced by mask(s)
        '''
        if masks == 'all':
            masks = list(self.mask.keys())
        if isinstance(masks, (str, np.ndarray)):
            masks = [masks]
        if masks != []:
            applied_mask = np.ones(self.data[list(self.data.keys())[0]].shape, dtype=bool)
            for mask in masks:
                if isinstance(mask, np.ndarray):
                    applied_mask *= mask
                else:
                    applied_mask *= self.get_mask(mask)
            if isinstance(self.data, DataDict):
                datadict = self.data.mask(applied_mask)
            else:
                datadict = {}
                for key in self.data:
                    datadict[key] = self.data[key][applied_mask]
        else:
            datadict = copy.deepcopy(self.data)
        return datadict

    def get_data(self, masks, prods):
        """
        Returns the data arrays with masks (logical and) applied. Note
        that the Master mask is also applied!
        You may also use the string 'all' for masks and/or prods. In case prods
        is set to 'all', the reduced data arrays will be ordered alphabetically
        corresponding to their keywords in dbData.data (get_all_data is somewhat
        preferable to this particular option though, since it does the same but
        returns a dictionary instead).
        INPUT:
        masks: (tuple/list of) mask(s). Bool numpy arrays (possible use are temporary
                   masks for instance) are also allowed.
        prods: (tuple/list of) data product key(s)
        OUTPUT: (list of) data array(s) reduced by mask(s)
        """
        if masks == 'all':
            masks = list(self.mask.keys())
        if prods == 'all':
            prods = list(self.data.keys())
            prods.sort()
        if isinstance(masks, (str, np.ndarray)):
            masks = [masks]
        if isinstance(prods, str):
            prods = [prods]
        applied_mask = np.ones(
            self.data[list(self.data.keys())[0]].shape[0], dtype=bool)
        for mask in masks:
            if isinstance(mask, np.ndarray):
                applied_mask *= mask
            else:
                applied_mask *= self.get_mask(mask)
        return_prod_list = [self.data[prod][applied_mask] for prod in prods]
        if len(return_prod_list) == 1:
            return return_prod_list[0]
        else:
            return return_prod_list

    def get_mask(self, mask):
        """
        Returns an the current mask. Note that the Master mask is also applied!
        INPUT:
        mask - mask you want to get (a string)
        """
        if (isinstance(mask, str)):
            return self.mask[mask].get()
        elif (isinstance(mask, list)):
            ma = self.DM()
            for m in mask:
                ma = ma * self.mask[m].get()
            return ma
        else:
            print( "no valid mask!")

    def DM(self):
        """ Returns the Master Mask"""
        return self.mask["Master"].get()

    def set_data_property(self, prod, prop, val):
        """
        Assigns plot properties to the respective data products
        """
        if prod == "all":
            prods = list(self.data.keys())
        else:
            prods = [prod]
        for prod in prods:
            self.dp[prod].set(prop, val)

    def set_mask_property(self, mask, prop, val):
        """
        Assigns plot properties to the respective masks
        """
        if mask == "all":
            masks = list(self.mask.keys())
            masks.remove("Master")
        else:
            masks = [mask]
        for mask in masks:
            self.mp[mask].set(prop, val)

    def set_global_property(self, prop, val):
        """
        This Changes global properties of the plot. Here you can change the fontsize
        of all labels for instance.
        """
        try:
            mpl.rcParams[prop] = val
        except:
            for key in sorted(mpl.rcParams.keys()):
                print( key, ": ", mpl.rcParams[key])
            print( "")
            print( "################## !!! ERROR !!! #######################")
            print( "Wrong Property used. See the list above for all possible properties and currently set values")

    @ArgParser
    def add_mask(self, name):
        """
        This routine adds a (or a list of) new mask(s) to the total
        INPUT : name --> (list of) str that specifies the added masks ; This argument will converted by self._get_namelist
        """
        for key in name:
            if key not in self.mask:
                self.mask[key] = Mask(self, name=key)
                self.mp[key] = plot_properties(key)
                self.mp[key].set("color", self._get_color(len(self.mask) - 1))
            else:
                print( "add_mask: Mask '{}' already exists, no action performed.".format(key))

    def add_reduced_data(self, key, data, expkey, **kwargs):
        """
        This method adds an additional dataproduct to self.data with keyword 'key'
        """
        if not key in self.data.keys():
            self.data.add_reduced_data(key, np.array(data), expkey, **kwargs)
            self.dp[key] = plot_properties(key)
            self.dp[key].set("color", self._get_color(len(self.data) - 1))
        else:
            print( "add_reduced_data: Keyword '%s' already exists! No action performed!" % (key))

    def add_data(self, key, data):
        """
        This method adds an additional dataproduct to self.data with keyword 'key'
        """
        if not key in self.data.keys():
            if len(self.data[list(self.data.keys())[0]]) == len(data):
                self.data[key] = np.array(data)
                self.dp[key] = plot_properties(key)
                self.dp[key].set("color", self._get_color(len(self.data) - 1))
            else:
                print( "Supplied data has not the same length (%s) as entries in self.data (%s)" % (len(data), len(self.data[list(self.data.keys())[0]])))
        else:
            print( "Keyword '%s' already exists!" % (key))
            if raw_input("Proceed? [Y/N]").lower() in ["yes", "y", "jo", "ja", "j"]:
                print( "You have to add data to all keys to maintain a valid data class.")
                if raw_input(" Do you really really want to do this? [Y/N]").lower() in ["yes", "y", "jo", "ja", "j"]:
                    self.data[key] = np.append(self.data[key], data)
                else:
                    print( "That is really very sensible of you. Thanks you for not endangering my structure.")
            else:
                print( "That is very sensible of you. Thank you for not endangering my structure.")

    def copy_mask(self, nmask, omask):
        """
        Copies mask 'osmask' into new mask 'nmask'! If nmask already exists nmask will be overwritten!
        """
        self.add_mask(nmask)
        self.mask[nmask].submasks = copy.deepcopy(self.mask[omask].submasks)
        if omask == "Master":
            self.mask[nmask].appliedmasks = ["Master"]
        else:
            self.mask[nmask].appliedmasks = copy.deepcopy(
                self.mask[omask].appliedmasks)
        self.mask[nmask].directmasks = copy.deepcopy(
            self.mask[omask].directmasks)
        self.mask[nmask].calc_mask()
        self.mp[nmask] = plot_properties(nmask)
        self.mp[nmask].set("color", self._get_color(len(self.mask) - 1))

    @ArgParser
    def remove_mask(self, name):
        """
        This routine removes specified masks. Beware Master mask must not and cannot be removed!
        INPUT : name --> (list of) str that specifies the remnoved masks ; This argument will converted by self._get_namelist
        """
        if "Master" in name:
            name.remove("Master")
        for mask in name:
            self.mask.pop(mask)
            self.mp.pop(mask)

    @ArgParser
    def remove_submask(self, name, subname):
        """
        This routine removes specified submask of masks.
        INPUT : name --> (list of) str that specifies the masks on which submask will be removed
        subname --> name of the submask to be removed
        """
        for mask in name:
            self.mask[mask].remove_submask(subname)

    @ArgParser
    def remove_appliedmask(self, name, subname):
        """
        This routine removes specified submask of masks.
        INPUT : name --> (list of) str that specifies the masks on which submask will be removed
        subname --> name of the submask to be removed
        """
        for mask in name:
            self.mask[mask].remove_appliedmask(subname)

    @ArgParser
    def remove_directmask(self, name, subname):
        """
        This routine removes specified submask of masks.
        INPUT : name --> (list of) str that specifies the masks on which submask will be removed
        subname --> name of the submask to be removed
        """
        for mask in name:
            self.mask[mask].remove_directmask(subname)

    @ArgParser
    def reset_mask(self, name):
        """
        This routine resets specified masks.
        INPUT : name --> (list of) str that specifies the reseted masks ; This argument will converted by self._get_namelist
        """
        for mask in name:
            self.mask[mask].remove_submask('all')
            self.mask[mask].remove_appliedmask('all')
            self.mask[mask].remove_directmask('all')

    def show_mask(self, smask=False, cmask="Master"):
        SM = ShowMask(self, smask=smask, cmask=cmask)
        SM.compute()

    @ArgParser
    def set_mask(self, name, *args, **kwargs):
        """
        This Routine sets the mask
        INPUT:
        name:	name of the mask
        *args:	arguments for the operator/mask.add_directmask/mask.add_appliedmask
        **kwargs:
                op: - if omitted, standard is set to 'between to values'
                                (call set_mask with name, prod, value_1, value_2)
                        - if set to a string, it will be handled as a standard operator corresponding to that string
                                (call set_mask with name, prod, value_1(, value_2), op=str)
                        - if set to a anything else than a string, it will be handled as a user-defined operator:
                                USER DEFINED OPERATORS MUST TAKE A DATA DICTIONARY OF dbData FORMAT AS FIRST ARGUMENT!!
                                THIS DICTIONARY SHOULD _NOT_ BE PASSED AS AN ARGUMENT HERE. Submask.calc does that for you.
                                This is necessary so that masks may be loaded independently from a dataset and applied to
                                another dataset.
                                (call set_mask with name, *args, **kwargs, op=user_operator)
                reset:			 If set to True all previous masks of the given prod are deleted (has no effect
                                                        if direct or applied is	set to True)
                direct:	 		 If set to True adds given boolean mask to name.directmasks
                                                        (call set_mask with name, prod, directmask, direct=True)
                applied: 		 If set to True adds given mask to name.appliedmasks
                                                        (call set_mask with name, maskname, applied=True)
                set_custom_prod: If a user defined operator is used, you may set a name/prod with this keyword.
                                                        Be aware that, if a prod is used, a visualization for used-defined masks in
                                                        show_mask is not implemented.
        """
        for mask in name:
            if mask not in self.mask:
                self.add_mask(mask)
                print( "set_mask: Mask '{}' has been added automatically before setting.".format(mask))
            if 'applied' in kwargs:
                if kwargs['applied'] == True:
                    self.mask[mask].add_appliedmask(*args, **kwargs)
            elif 'direct' in kwargs:
                if kwargs['direct'] == True:
                    self.mask[mask].add_directmask(*args, **kwargs)
            else:
                if 'op' not in kwargs:
                    kwargs['op'] = 'be'
                if isinstance(kwargs['op'], str):
                    kwargs['op_str'] = kwargs['op']
                    kwargs['op'] = _operators.std_ops
                    self.mask[mask].add_submask(args[0], *args, **kwargs)
                else:
                    if 'set_custom_prod' in kwargs:
                        set_custom_prod = kwargs.pop('set_custom_prod')
                    else:
                        set_custom_prod = 'data product not specified'
                    self.mask[mask].add_submask(
                        set_custom_prod, *args, **kwargs)

    def set_mask2D(self, name, prodx, prody, *arg, **kwarg):
        """
        This Routine sets a 2Dimensional mask, which is achieved by drawing a polygron onto a 2d contour
        INPUT: name: name of the mask
        prodx: 1st dataproduct key
        prody: 2nd dataproduct key
        arg,kwarg: additional keywords for 2dhist plot
        """
        print( "HowTO")
        print( "----------")
        print( "'a': Add Point")
        print( "'r': Remove Last Point")
        print( "'c': Cancel")
        print( "'Enter': Apply Mask")
        M = Mask2D(self, name, prodx, prody)
        M.create_mask2D(*arg, **kwarg)

    def set_mask1D(self, name, prody, prodx="time", *arg, **kwarg):
        """
        This Routine sets a 2Dimensional mask, which is achieved by drawing a polygron onto a 2d contour
        INPUT: name: name of the mask
        prodx: 1st dataproduct key
        prody: dataproducts used for timeseries plot (can be a list)
        arg,kwarg: additional keywords for timeseries plot
        """
        print( "HowTO")
        print( "----------")
        print( "'y': Add Start Point of Time Frame")
        print( "'x': Add End Point of Time Frame")
        print( "'v': Remove Last Time Frame")
        print( "'c': Cancel")
        print( "'Enter': Apply Mask")
        M = Mask1D(self, name, prodx, prody)
        M.create_mask1D(*arg, **kwarg)

    def save_all(self, filename, overwrite=False):
        """
        This routine saves the complete dbData instance including data, masks etc.
        INPUT:     (/path/to/)filename as string
        overwrite: enable with True if you wish to overwrite a potentially existing file with the
                   same name
        """
        if not overwrite and os.path.isfile(filename):
            print( "File '{}' already exists; choose another filename or enable overwrite.".format(filename))
        else:
            of = open(filename, 'wb')
            pickle.dump(self, of, -1)
            of.close()
        return

    def save_masks(self, filename, overwrite=False, smask=False):
        """
        This routine saves dbData masks.
        INPUT:
        filename:  (/path/to/)filename as string
        overwrite: enable with True if you wish to overwrite a potentially existing file with the
                   same name
        smask:	   if a tuple/list of masks is passed as smask, only these masks will be saved
        """
        if not overwrite and os.path.isfile(filename):
            print( "File '{}' already exists; choose another filename or enable overwrite.".format(filename))
        else:
            mask_dict = copy.deepcopy(self.mask)
            for key in mask_dict:
                del(mask_dict[key].dbd)
                del(mask_dict[key].ma)
                if smask and key not in smask:
                    del(mask_dict[key])
            of = open(filename, 'wb')
            pickle.dump(mask_dict, of, -1)
            of.close()
        return

    def save_subset(self, mask, filename="tmp.dat", prods="all"):
        """
        This routine save all data of a current mask into a given file.
        It can be loaded later to work with a reduced data set
        INPUT: mask - the mask that should be saved as a subset
        filename - filepath+filename to which the subset is saved
        prods - either "all" or a list of products
        """
        subset = {}
        if prods == "all":
            for prod in self.data:
                subset[prod] = self.data[prod][self.get_mask(mask)]
        else:
            for prod in prods:
                subset[prod] = self.data[prod][self.get_mask(mask)]
        pickle.dump(subset, open(filename, "w"), protocol=2)

    @staticmethod
    def load_all(filename):
        """
        This routine loads a complete dbData instance including data, masks etc.
        It is a staticmethod, meaning that you call it with dbData.load_all(...)
        In case you inherited dbData in one of your own classes, you'll need to use that
        class's name instead.
        INPUT:  (/path/to/)filename as string
        OUTPUT: dbData instance
        """
        if os.path.isfile(filename):
            with open(filename, 'rb') as of:
                return pickle.load(of)
        else:
            print( "'{}' doesn't exist.".format(filename))
        return

    def load_masks(self, filename, overwrite=False, load_direct_masks=False):
        """
        This routine loads previously saved masks.
        INPUT:			   (/path/to/)filename as string
        overwrite:		   enable with True if you wish to overwrite a potentially existing mask
                                           with the same name
        load_direct_masks: set to True if you want to load direct masks. They will be removed
                                           nevertheless if they have the wrong length.
        """
        if os.path.isfile(filename):
            of = open(filename, 'rb')
            mask_dict = pickle.load(of)
            of.close()
            existing_masks = []
            dir_mask = []
            dir_mask_len_nok = []
            print( dir_mask_len_nok)
            if type(mask_dict) != dict:
                print( "'{}' does not contain masks, load aborted.".format(filename))
                return
            for key in mask_dict:
                if key in self.mask:
                    existing_masks.append(key)
                    if overwrite:
                        self.remove_mask(key)
            for key in existing_masks:
                if not overwrite:
                    del(mask_dict[key])

            def _add_submasks(key):
                self.add_mask(key)
                self.mask[key].submasks = mask_dict[key].submasks
                self.mask[key].calc_mask()
                return

            def _add_directmasks(key):
                if load_direct_masks and mask_dict[key].directmasks:
                    dir_mask.append(key)
                    for key2 in mask_dict[key].directmasks:
                        if mask_dict[key].directmasks[key2].shape[0] == self.data[list(self.data.keys())[0]].shape[0]:
                            self.mask[key].directmasks[
                                key2] = mask_dict[key].directmasks[key2]
                            self.mask[key].calc_mask()
                        else:
                            dir_mask_len_nok.append([key, key2])
                return

            def _add_appliedmasks(key):
                for key2 in mask_dict[key].appliedmasks:
                    if key2 != 'Master':
                        self.set_mask(key, key2, applied=True)
                return
            if 'Master' in mask_dict:
                del(self.mask['Master'])
                _add_submasks('Master')
                _add_directmasks('Master')
                del(mask_dict['Master'])
            for key in mask_dict:
                _add_submasks(key)
            for key in mask_dict:
                _add_directmasks(key)
            for key in mask_dict:
                _add_appliedmasks(key)

            if existing_masks != []:
                print( "The masks:")
                for mask in existing_masks:
                    print( "  '{}'".format(mask))
                if overwrite:
                    print( "already existed and have been overwritten.")
                else:
                    print( "already exist and have not been replaced. If you wish to load all masks from '{}', enable overwrite or rename your existing masks (call copy_mask and then remove_mask on the masks in question).".format(filename))
            if dir_mask:
                print( "WARNING: The masks:")
                for mask in dir_mask:
                    print( "\t'{}'".format(mask))
                print( "contain direct (binary) masks; be sure you know what you do.")
                if dir_mask_len_nok:
                    print( "ERROR: The direct masks:")
                    for m1, m2 in dir_mask_len_nok:
                        print( "\t'{}' in '{}'".format(m2, m1))
                    print( "do not correspond to the length of your dataset and have been removed.\nPlease also check your applied masks, if they depend on any of these direct masks\nthey might now be useless.")
        else:
            print( "'{}' doesn't exist.".format(filename))
        return

    def load_subset(self, filename="tmp.dat", force=False):
        """
        Loads a subset that is used for further analysis
        !!! This overrides all data loaded by method self.load_data() !!!
        INPUT: mask:
        """
        subset = pickle.load(open(filename, "r"))
        print( "!!! Warning !!! - If you Proceed current data set will be overwritten!")
        if force == True or raw_input("Proceed? [Y/N]").lower() in ["yes", "y", "jo", "ja", "j"]:
            keys = list(self.data.keys())
            # Replace old self.data with the loaded data
            for key in keys:
                self.data.pop(key)
            for key in subset:
                self.data[key] = subset[key]
            # Now deal with masks
            for mask in self.mask:
                self.mask[mask].calc_mask()
            pkeys = list(self.dp.keys())
            dkeys = list(self.data.keys())
            for key in pkeys:
                if not key in dkeys:
                    self.dp.pop(key)
            pkeys = list(self.dp.keys())
            for key in dkeys:
                if not key in pkeys:
                    self.dp[key] = plot_properties(key)
                    self.dp[key].set(
                        "color", self._get_color(len(self.dp) - 1))
                # self.mask[mask].calc_mask()
            return True
        else:
            print( "Loading subset has been canceled!")
            return False

    def load_data(self, fnames, path="./", header=True, keys=True, *args, **kwargs):
        """
        This is a standard Loader that works only with a standard dbd format ... basically a plain ascii file. For different data sets user should define his own load_data
        kwargs:
        header : if True expect header in file. Header starts with #StartHeader# and ends with '#EndHeader#'
        """
        if isinstance(fnames, str):
            fnames = [fnames]
        # initialise data dictonary, getting settings from header of first
        # exisitng file in fnames and use args,kwargs (args,kwargs should
        # overrule header!)
        for fname in fnames:
            if not fname in os.listdir(path):
                print( "File ,", fname, ", in ", path, " does not exist")
            else:
                fin = open(path + fname, "r")
            if header == True:
                if not self.read_header(fin, fname, path):
                    print( "load_data: No Header found! Continue with standard settings")
                    header = False
                    fin.close()
                    fin = open(path + fname, "r")
                else:
                    print( "load_data: Header loaded")
                    header = False
            if isinstance(keys, bool):
                l = fin.readline()
                s = l.split()
                keys = s
                dat = np.loadtxt(fin)
            for k, key in enumerate(keys):
                self.data[key] = dat[:, k]
        return True

    def read_header(self, fin, fname, path):
        startheaderfound = False
        endheaderfound = False
        l = fin.readline()
        if l == "":
            print( "read_header: ", path + fname, " empty file! File skipped!")
            return False
        s = l.split()
        while not (len(s) == 1 and s[0] == "#StartHeader#"):
            l = fin.readline()
            s = l.split()
            if l == "":
                print( "read_header: Found no #StartHeader# in file ", path + fname, " ! File skipped!")
                return False
        print( "read_header: Found #StartHeader# in file ", path + fname)
        while not (len(s) == 1 and s[0] == "#EndHeader#"):
            l = fin.readline()
            s = l.split()
            if l == "":
                print( "read_header: Found no #EndHeader# in file ", path + fname, " ! File skipped!")
                return False
            """
			TODO: Header content should be read!!!
			"""
        print( "read_header: Found #EndHeader# in file ", path + fname)
        return True

    def addsubset(self, file_U, prodx=False, prody=False, prodz=False, norm=False):
        '''
        This method extends the current date set with a previously saved subset. The keys of the current data set and those of the subset must be the same
        File_U: path were the subset is saved
        '''
        o = open(file_U)
        subset = pickle.load(o)
        o.close()
        old_keys, new_keys = list(self.data.keys()), list(subset.keys())
        keys_fit = np.intersect1d(old_keys, new_keys)
        if len(keys_fit) != len(old_keys):
            print( 'keys do not fit, cannot add this subset to current data, shame on you')
        elif len(keys_fit) == len(old_keys):
            for key in old_keys:
                self.data[key] = np.append(self.data[key], subset[key])
            for mask in self.mask:
                self.mask[mask].calc_mask()
            print( 'done, subset added')

    def hist2d(self, *arg, **kwarg):
        return self.Plot.hist2d(*arg, **kwarg)

    def hist1d(self, *arg, **kwarg):
        return self.Plot.hist1d(*arg, **kwarg)

    def animate1d(self, *arg, **kwarg):
        return self.Plot.animate1d(*arg, **kwarg)

    def animate2d(self, *arg, **kwarg):
        return self.Plot.animate2d(*arg, **kwarg)

    def timeseries(self, *arg, **kwarg):
        return self.Plot.timeseries(*arg, **kwarg)

    def quicklook(self, *arg, **kwarg):
        return self.Plot.quicklook(*arg, **kwarg)

# Set Doc Strings of plot routines
#dbData.hist2d.__func__.__doc__ = PlotdbData.hist2d.__func__.__doc__
#dbData.hist1d.__func__.__doc__ = PlotdbData.hist1d.__func__.__doc__
#dbData.animate1d.__func__.__doc__ = PlotdbData.animate1d.__func__.__doc__
#dbData.animate2d.__func__.__doc__ = PlotdbData.animate2d.__func__.__doc__
#dbData.quicklook.__func__.__doc__ = PlotdbData.quicklook.__func__.__doc__
#dbData.timeseries.__func__.__doc__ = PlotdbData.timeseries.__func__.__doc__


def generatekmeansmasks(data, k, name="Default", prodlist=[]):
    """
    For a given data set and expected number of clusters k generatekmeansmasks returns a dictionary of k masks for the products given in prodlist using the k-means algorithm. standard k means assumes that each cluster is a Gaussian
    The dictionary keys are constructed as "name k".
    """
    traindata = []
    traindata = np.array([data[i] for i in prodlist])
    centeroid, classmask = scipy.cluster.vq.kmeans2(traindata.transpose(), k)
    masks = {}
    for i in range(0, k):
        masks[name + ' ' + str(i + 1)] = np.zeros(
            data[list(data.keys())[0]].shape[0], dtype=bool)
    for j in range(1, len(data[list(data.keys())[0]])):
        masks[name + ' ' + str(classmask[j] + 1)][j] = 1
    return masks

# For debugging and testi
if __name__ == "__main__":

    plt.ion()
    # EXAMPLE

    # Here a new class MyData is created that inherits from dbData
    class MyData(dbData):
        # A load_data method is defined that saves data products into the
        # dictionary self.data

        def load_data(self):
            # This small code snippet creates 200000 samples of 2 2D Gaussians
            # at position (3,2) and (14,8)
            self.data["Detector_A"] = np.append(
                np.random.normal(3, 3, size=900000), np.random.normal(14, 2, size=900000))
            self.data["Detector_B"] = np.append(
                np.random.normal(2, 4, size=900000), np.random.normal(8, 3, size=900000))
            # Each events gets a time stamp
            self.data["time"] = np.linspace(
                0, 100, self.data["Detector_A"].shape[0])
    # Create an instance of your class
    d = MyData()
    # Adds 2 masks that separates the 2 2D Gaussians
    d.add_mask("Ion_1")
    d.set_mask("Ion_1", "time", 0, 50)
    d.add_mask("Ion_2")
    d.set_mask("Ion_2", "time", 50, 100)

    # Show the Masks (broken for "direct masks" as from generatekmeansmask
    # because it currently abuses the master mask)
    d.show_mask()

    # Create a 2d Histogram of all masks
    d.hist2d('Detector_A', "Detector_B", binx=np.linspace(-20, 20, 101),
             biny=np.linspace(-20, 20, 101), style="contour", shade=False)
    d.hist2d('Detector_A', "Detector_B", binx=np.linspace(-20, 20, 101),
             biny=np.linspace(-20, 20, 101), style="contour", shade=True)
    # Create a 1d Histogram of Detector A for all masks (normalized to the sum
    # of the data)
    d.hist1d("Detector_A", binx=100, norm="ysum")
    # Plot a time series of the Detector A of masks Ion 1 and Ion 2
    d.timeseries("Detector_A", time=np.linspace(
        0, 100, 1001), mode="mean", smask=["Ion_1", "Ion_2"])

    """
	# example for applied masks:
	d.reset_mask("Ion_1")
	d.set_mask("Ion_1","time", direct=True)
	d.reset_mask("Ion_2")
	d.set_mask("Ion_2","time", direct=True)
	d.timeseries("Detector_A",time=np.linspace(0,100,1001),mode="mean",smask=["Ion_1","Ion_2"])
	"""
