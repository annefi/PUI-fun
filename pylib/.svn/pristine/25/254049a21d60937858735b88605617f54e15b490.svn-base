#{{{ Documentation and module imports
"""
Date: 27.04.2015
Author: Christian Drews <drews@physik.uni-kiel.de>, Lars Berger <berger@physik.uni-kiel.de>, Jan Steinhagen <steinhagen@physik.uni-kiel.de>

"""
#}}}


class Submask(object):

    """
    A submask is the simplest possible filter operation applied for one specific mask.
    """

    def __init__(self, *arg, **kwarg):
        """
        A submask is the simplest possible filter operation applied for one specific mask. It manages only the
        calculation of the submask via a dbData.data dictionary and an operator passed by kwarg['op'].
        Note: The standard operators can now be found in _operators.py.
        """
        self.operator = kwarg.pop('op')
        self.arg = arg
        self.kwarg = kwarg

    def calc(self, datadict):
        """
        Method: Calculates the array that represents the filter and returns it.
                        This is used in class mask where all filters are combined to
                        get the actual filter/mask.
        INPUT:
                datadict: data dictionary
        """
        return self.operator(datadict, *self.arg, **self.kwarg)
