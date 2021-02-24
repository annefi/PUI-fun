#{{{ Documentation and module imports
"""
Date: 27.04.2015
Author: Jan Steinhagen <steinhagen@physik.uni-kiel.de>
"""

import numpy as np
import pylib3 as pylib
#}}}


def std_ops(datadict, key, value_1, value_2=None, reduced=False, **kwargs):
    """
    Returns a mask (bool array) generated by a standard operator.
    INPUT:
    datadict: data dictionary with dbData.data format
    key:	  string of data product
    value1/2: value(s) - for the operators (value2 only for the operators bn and be)
    op_str:   string (>=, ge, >, gt, ==, eq, <=, le, <, lt, !=, ne, ><, bn, >=<, be, bin) representing a
                      standard operator
    OUTPUT:   bool array (mask) with the length of datadict[key]
    """
    def _be(data, value_1, value_2):
        return np.logical_and(np.greater_equal(data, value_1), np.less_equal(data, value_2))
    def _bin(data, value_1, value_2):
        return np.logical_and(np.greater_equal(data, value_1), np.less(data, value_2))
    def _bn(data, value_1, value_2):
        return np.logical_and(np.greater(data, value_1), np.less(data, value_2))
    def _eq(data, value):
        """
        Operator to replace np.equal. np.equal does not work with strings.
        """
        return data == value

    dd = datadict
    operators = {'>=': np.greater_equal,
                 'ge': np.greater_equal,
                 '>': np.greater,
                 'gt': np.greater,
                 '==': _eq,
                 'eq': _eq,
                 '<=': np.less_equal,
                 'le': np.less_equal,
                 '<': np.less,
                 'lt': np.less,
                 '!=': np.not_equal,
                 'ne': np.not_equal,
                 '><': _bn,
                 'bn': _bn,
                 '>=<': _be,
                 'be': _be,
                 'bin': _bin,
                 }
    op_str = kwargs.pop('op_str', 'be')
    if isinstance(op_str, str):
        if op_str in operators:
            if isinstance(dd, pylib.DataDict) and dd.reduced(key):
                mask_reduced = True
                get_data_func = dd.get_reduced_data
            else:
                mask_reduced = False
                get_data_func = dd.__getitem__
            if value_2 == None:
                mask = operators[op_str](get_data_func(key), value_1)
            else:
                mask = operators[op_str](get_data_func(key), value_1, value_2)
            if mask_reduced and not reduced:
                mask = mask[dd.get_expansion(key)]
        else:
            print("'{}' is not a known standard operator.".format(op_str))
            return
    return mask
