# GNUPlot MVC interface

from Gnuplot import Gnuplot, PlotItem
from gp import double_quote_string
from louie import connect, disconnect, send

class Plot:
    def __init__(self, fn=None):
        self.gp=Gnuplot()
        if fn:
            self.gp('load "%s"' % fn)
        self.items=[]
        self.needs_update=False
        
    def markdirty(self, d=True):
        """ Update will be necessary. """
        self.needs_update=d
        
    def update(self):
        """ Update the plot, but only if it necessary. """
        if self.needs_update:
            # only items with 'only_append'?
#            ao=all([i.only_append for i in self.items]) python2.5
            ao=sum([i.only_append for i in self.items])==len(self.items)
            for i in self.items:
                if i.needs_init_plot:
                    ao=False
                    break
            
            if not ao:
                self.gp.plot() # start with empty plot
            for i in self.items:
                if i.needs_update:
                    i.update()
                    i.needs_update=False
                if not ao and not i.empty():
                    self.gp.replot(i)
                    i.needs_init_plot=False
            if ao:
                self.gp.replot() # simply cause plot update (FIXME: is this true?)
            self.needs_update=False
        
    def add(self, item):
        if not item in self.items:
            self.items+=[item]
            self.needs_update=True
            connect(self.markdirty, item.changed, weak=False)
            connect(item.mouseclick, self.mouseclick, weak=False)
            
    def remove(self, item):
        if item in self.items:
            self.items.remove(item)
            disconnect(self.markdirty, item.changed)
            disconnect(item.mouseclick, self.mouseclick)
            self.needs_update=True
            
    def mouseclick(self, x, y, btn):
        send(self.mouseclick, self, x, y, btn)
        

from threading import Thread

class PlotUpdater(Thread):
    """ Asynchronously updates plots. interval is the minimum time between updates. """
    def __init__(self, pl, interval=1.0, mouse=True):
        self.pl=pl
        self.interval=interval
        self.mouse=mouse
        Thread.__init__(self)

        # allow Ctrl-Cing
        from signal import signal, SIGINT
        self.old_sigint=signal(SIGINT, self.shutdown)

        # daemon thread
        self.setDaemon(True)
    def run(self):
        self.stopit=False
        from time import sleep
        if self.mouse:
            omx=self.pl.gp.eval("MOUSE_X")
            omy=self.pl.gp.eval("MOUSE_Y")
            omb=self.pl.gp.eval("MOUSE_BUTTON")
            
        while not self.stopit: # FIXME: needed?
            self.pl.update()
            sleep(self.interval)
            if self.mouse:
                # FIXME: This is a kludge. Expects the mouse
                # to move between clicks!
                nmx=self.pl.gp.eval("MOUSE_X")
                nmy=self.pl.gp.eval("MOUSE_Y")
                nmb=self.pl.gp.eval("MOUSE_BUTTON")
                if omx!=nmx or omy!=nmy or omb!=nmb:
                    omx,omy,omb=nmx,nmy,nmb
                    if nmx!=None and nmy!=None and nmb!=None:
                        self.pl.mouseclick(nmx, nmy, nmb)

        
    def stop(self):
        self.stopit=True

    def shutdown(self, a,b):
        self.stop()
        self.old_sigint(a,b)

class onPlot(PlotItem):
    def __init__(self):
        self.needs_update=True
        self.needs_init_plot=True
        PlotItem.__init__(self)

        # Iff this is set to true, updating only appends values to the plot
        self.only_append=False
        
    # signal used when the plot/data has been changed
    def changed(self):
        self.needs_update=True
        send(self.changed)

    def update(self):
        """ Called by a plot to really update the GNUplot
        data for plotting. """
    
    def mouseclick(self, x, y, btn):
        """ Use this for mouse click notification. """
        print "Unimplemented mouse click:", self, x, y, btn
        pass

    def empty(self):
        """ Iff true, this plot is not shown. """
        return False
    
def sigoncall(func, sig, sender):
    """ Decorates function func so that it emits signal sig on each call,
    from 'sender'. """
    def df(*args):
        func(*args)
        send(sig, sender)
    return df
        


class listView(onPlot):
    """ View on a python list object. """
    def __init__(self, li, dtype="y"):
        import os
        import tempfile
        self.l=li
        self.dtype=dtype
        (self.fd, self.fn) = tempfile.mkstemp(suffix='.gnuplot.mvc', text=True)
        self.fp=os.fdopen(self.fd, "w")
        self.old_len=0
        
        if self.dtype=="y":
            opts=["with", "lines"]
        elif self.dtype=="xy":
            opts=["with", "lines"]
        elif self.dtype=="xyex":
            opts=["with", "xerrorlines"]
        elif self.dtype=="xyey":
            opts=["with", "yerrorlines"]
        elif self.dtype=="xyexey":
            opts=["with", "xyerrorlines"]
        else:
            raise ValueError, "Invalid data type.", dtype
        onPlot.__init__(self)
        self.set_option_colonsep(opts[0], opts[1])

        # mark modifying methods FIXME: complete?
        self.set_option=sigoncall(self.set_option, self.changed, self)
        self.set_option_colonsep=sigoncall(self.set_option_colonsep, self.changed, self)
        self.set_string_option=sigoncall(self.set_string_option, self.changed, self)

    def update(self):
        # process list data depending on data type dtype
        if self.only_append:
            rge=(self.old_len, len(self.l))
        else:
            rge=(0, len(self.l))
            
        for idx in range(*rge):
            i=self.l[idx]
            try:
                len(i)
                for j in i:
                    print>>self.fp, j,
                print>>self.fp
            except TypeError:
                print>>self.fp, i
        self.old_len=len(self.l)
        self.fp.flush()
        if not self.only_append:
            self.fp.seek(0)
        
    def __del__(self):
        import os
        os.unlink(self.fn)

    def get_base_command_string(self):
        return double_quote_string(self.fn)

    def empty(self):
        return len(self.l)==0
