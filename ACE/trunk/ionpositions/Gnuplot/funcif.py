# function/interface logic
from PlotItems import Func
from sys import stdout


# TODO:
# -Clean up messy interface for multiple functions with the same parameter names
# At the moment, each function parameter needs to have it's own suffix and these
# suffixes have to be used from the code using this library.
# A better approach would be complete handling of specially named function parameters
# through a string-replace and transparent pars[] and errs[] accessors. The function
# would be defined like this:
# f(x)=1/...*scale@*exp((x-mu@)/sigma@)')
# and every occurance of @ would be replaced with either a number or the basename
# of the function itself, so that the above string for example gets send to Gnuplot
# as
# f(x)=1/...*scale_f*exp((x-mu_f)/sigma_f)
#

# array of additional functions which may be known to Gnuplot but not to
# python
_gpfuncs={}

def reg_func(name, f):
    """ Register GNUplot function 'name' with python function 'f'. """
    _gpfuncs[name]=f

import math
for i in [("sqrt", math.sqrt),
          ("exp", math.exp),
          ("pi", math.pi),
          ("sin", math.sin),
          ("cos", math.cos),
          ("tan", math.tan),
          ("acos", math.acos),
          ("atan", math.atan),
          ("asin", math.asin)]:
    reg_func(i[0], i[1])


def rangeSelect(gp, inrange, n):
    if inrange=="SELECT":
        print "Please select %s_min" % (["xy"][n])
        mi=self.gp.getxy()[n]
        print "Please select %s_max" % (["xy"][n])
        ma=self.gp.getxy()[n]
        return (mi, ma)
    else:
        return inrange


class Function(Func):
    """ 1D/2D function with a string-gnuplot-side and a usual python interface.
    self.pars contains the function's parameter list. gp is the gnuplot
    instance to link to.
    """
    def __init__(self, gp, name, function, dim=1, debug=False):
        # using fit functions together with prefer_fifo_data will
        # cause A LOT of hassle!
        from Gnuplot import GnuplotOpts
        if GnuplotOpts.prefer_fifo_data:
            print "Gnuplot.funcif: WARNING: prefer_fifo_data was set. Please make sure that your plots are done after you set this to zero when using Gnuplot.funcif."
        GnuplotOpts.prefer_fifo_data=0
        Func.__init__(self, function)
        self.debug=debug
        self.gp=gp
        self.name=name
        self.pars={}
        self.errs={}
        self.fit_var_list=None
        if dim<1 or dim>2:
            raise ValueError, "Functions must have 1 or 2 arguments."
        self.dim=dim # number of dimensions
        self.send()

    def setFitVars(self, l):
        self.fit_var_list=l

    def __getitem__(self, i):
        if i in self.errs:
            return (self.pars[i], self.errs[i])
        else:
            return (self.pars[i], None)
    def __setitem__(self, i, val):
        self.pars[i]=val
        
    def __call__(self, x, y=None):
        """ Returns the value given x (and maybe y) and the parameters in self.pars."""
        nstr=self.function
        for i,j in self.pars.iteritems():
            nstr=nstr.replace(i, str(j))
        if self.debug:
            print "eval:%s" % nstr
        _gpfuncs["x"]=x
        if self.dim==2:
            _gpfuncs["y"]=y
        return eval(nstr, _gpfuncs)

    def get_base_command_string(self):
        self.send()
        return Func.get_base_command_string(self)
    
    def __str__(self):
        """ Returns the function's GNUPlot description string. """
        return self.function
    
    def send(self):
        """ Sends the function definition as well as the current parameter
        values to GNUPlot. """
        for i,j in self.pars.iteritems():
            if self.debug:
                print "gp: %s=%s" % (str(i), str(j))
            self.gp("%s=%s" % (str(i), str(j)))

        if self.dim==1:
            if self.debug:
                print "gp: %s(x)=%s" % (self.name, str(self))
            self.gp("%s(x)=%s" % (self.name, str(self)))
        else:
            if self.debug:
                print "gp: %s(x,y)=%s" % (self.name, str(self))
            self.gp("%s(x,y)=%s" % (self.name, str(self)))

    def recv(self):
        for i in self.pars.iterkeys():
            self.pars[i]=self.gp.eval(i)

        self.errs={}
        for i in self.pars.iterkeys():
            self.errs[i]=self.gp.eval(i+"_err")
        
    def fit(self, inp, xrange=None, using="1:2:(sqrt($2))"):
        """ Fits the function's parameters in the given xrange value pair (or
        everywhere) to the data in file 'file', in GNUPlot instance gp."""
        xrange=rangeSelect(self.gp, xrange, "x")
        self.send()
        self.gp("set fit errorvariables")

        fcmd="fit "
        if xrange:
            fcmd+="[x=%f:%f] " % xrange

        if self.dim==1:
            fcmd+="%s(x)" % self.name
        else:
            fcmd+="%s(x, y)" % self.name
            
        fcmd+=' "%s"' % inp
        fcmd+=' using %s' % using
        fcmd+=" via "

        if self.fit_var_list:
            for i in self.fit_var_list:
                fcmd+="%s," % i
        else:
            for i in self.pars.keys():
                fcmd+="%s," % i
        fcmd=fcmd[:-1]

        if self.debug:
            print "gp: fit:", fcmd
        self.gp(fcmd+"\n\n")
        self.recv()

    def showPars(self, out=stdout):
        """ Print the parameters of this function, including error bars in a
        more-or-less nicely formatted way. out is an optional output file."""
        sep="-"*79

        print "Parameter set for"
        print "%s(x)=%s" % (self.name, self.function)
        print sep

        for i,j in self.pars.iteritems():
            if i in self.errs:
                print "%s: %f (+- %f)" % (i, j, self.errs[i])
            else:
                print "%s: %f (no error given)" % (i, j)
        print sep


class Sum(Func):
    """ sum of several functions. FIXME: Make a proper class hierarchy. """
    def __init__(self, functions, debug=False):
        Func.__init__(self, "invalid")
        self.functions=functions
        if not len(functions):
            raise Exception, "At least one function has to be given for Sum."
        self.gp=functions[0].gp
        self.dim=functions[0].dim
        for i in functions:
            if i.gp!=self.gp:
                raise Exception, "Functions need to use the same Gnuplot instance."
            if i.dim!=self.dim:
                raise Exception, "Functions need to have the same number of arguments."
        self.debug=debug
        def __call__(self, x):
            s=0.0
            for i in self.functions:
                s+=i(x)
            return s

    def add(self, f):
        if self.gp!=f.gp:
            raise Exception, "Function need to use the same Gnuplot instance."
        self.functions.append(f)
        
    def get_base_command_string(self):
        s=""
        for i in self.functions:
            s+=i.get_base_command_string()+"+"
        return s[:-1]

    def __str__(self):
        s=""
        for i in self.functions:
            s+=str(i)+"+"
        return s[:-1]
        
    def fit(self, inp, xrange=None, yrange=None, using="1:2:(sqrt($2))"):
        xrange, yrange=rangeSelect(gp, xrange, "x"), rangeSelect(gp, yrange, "y")

        for i in self.functions:
            i.send()
        self.gp("set fit errorvariables")

        fcmd="fit "
        if xrange:
            fcmd+="[x=%f:%f] " % xrange
        if yrange:
            fcmd+="[y=%f:%f] " % yrange

        if self.dim==1:
            for i in self.functions:
                fcmd+="%s(x)+" % i.name
        else:
            for i in self.functions:
                fcmd+="%s(x,y)+" % i.name
            
        fcmd=fcmd[:-1]
        fcmd+=' "%s"' % inp
        if self.dim==2 and using=="1:2:(sqrt($2))": # FIXME: Document this somewhere!
            using="using 1:2:3:(sqrt($3))"
        fcmd+="using %s" % using
        fcmd+=" via "

        pars=set()
        for j in self.functions:
            if j.fit_var_list:
                for i in j.fit_var_list:
                    pars.add(i)
            else:
                for i in k.pars.keys():
                    pars.add(i)

        for i in pars:
                fcmd+="%s," % i
        fcmd=fcmd[:-1]

        if self.debug:
            print "gp: fit:", fcmd
        self.gp(fcmd+"\n\n")

        for i in self.functions:
            i.recv()
            
        # unfortunately, there is a bug in GNUplot which
        # prevents further plots after a 2D fit. The following sequence of commands
        # works around this problem.
        if self.dim==2:
            self.gp("set pm3d map")
            self.gp("replot")
            self.gp("unset pm3d")
            self.gp("set view 87, 266, 1, 1")
            self.gp("replot")
    
