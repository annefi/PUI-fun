from threading import Thread

class ExternalFunction(Thread):
    """ A function which can be registered with a GNUplot instance and can be used for fitting etc. """
    def __init__(self, gp, name, pars, func):
        from os import system, remove
        from tempfile import mkdtemp
        """ gp: Gnuplot instance, name: Name of the function in Gnuplot. Initializes this object, with python function func which has a parameter set 'pars' (a list of strings). The function func is called with the first argument being the x-coordinate and all other arguments being the function's fitted parameters. The function needs to return a single float value.
        """
        self.gp=gp
        self.name=name
        self.pars=pars
        self.func=func
        self.dirprefix=mkdtemp("GPExternalFunction")
        
        self.inputfn=self.dirprefix+"/input"
        print "INPUTFN", self.inputfn
        system("mkfifo %s" % self.inputfn)
        # FIXME: Why do we need 'r+'??
        reslimit=False # to check for resource limits
        try:
            self.input=open(self.inputfn, mode="r+", buffering=0) # will be triggered by writing a line with the parameters into it.
        except IOError:
            reslimit=True
        if not reslimit:    
            self.outfn=self.dirprefix+"/output"
            print "OUTPUTFN", self.outfn
            system("mkfifo %s" % self.outfn)
            try:
                self.out=open(self.outfn, "w+")
            except IOError:
                reslimit=True

#        reslimit=True # testing
        
        self.reslimit=reslimit
        if reslimit:
            raise Exception, "Out of ressources (files, processes, ...). Be nice to the machine!"
        Thread.__init__(self)

        s='%s(x)=.0+system(sprintf("echo ' % name
        s+='%f '*(len(self.pars)+1) # parameters and the x value
        s+='",'
        s+=','.join(["x"]+pars)
        s+=')."> %s ; head -1 %s")' % (self.inputfn, self.outfn)
        gp(s)

        import atexit
        atexit.register(self.__del__) # FIXME: WHY??

        self.setDaemon(True)
        self.start()
        
    def __del__(self):
        self.gp.sync()
        from os import remove, rmdir
        try:
            remove(self.inputfn)
            print "DELETED INPUTFN", self.inputfn
        except OSError:
            pass
        except:
            # if we're limited by ressources, we do everything to 'exit normally'
            if self.reslimit:
                print "NO INPUTFN (resource limit)"
                pass
            else:
                raise
        try:
            remove(self.outfn)
            print "DELETED OUTPUTFN", self.outfn
        except OSError:
            pass
        except:
            if self.reslimit:
                print "NO OUTPUTFN (resource limit)"
                pass
            else:
                raise
        try:
            rmdir(self.dirprefix)
            print "DELETED TEMPORARY DIRECTORY", self.dirprefix
        except OSError:
            pass
        except:
            if self.reslimit:
                print "NO TEMPORARY DIRECTORY (resource limit). This is strange."
                pass
            else:
                raise
        
    def run(self):
        print "STARTED (%s, %s)!" % (self.inputfn, self.outfn)
        n=0
        while True:
            from select import select
            if select([self.input], [], [], 1.0)[0]!=[]:
                ls=[float(i) for i in self.input.readline().split()]
                if not (n%100):
                    print "Calling method with", ls
                retval=self.func(*ls)
                print>>self.out, "%f" % retval
                self.out.flush()
            n+=1
        
