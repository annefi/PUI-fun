from numpy import histogram,linspace,zeros,where,sqrt,array,isnan,amax,exp,mean,ones,amin,arange,equal,greater,greater_equal,less,less_equal,not_equal
import copy


class submask(object):
    def __init__(self,*args):
        """
        args[0] must be any function or string that can be 'translated' into function by method set_function
        args[1:n] number of arguments that are given to function
        """
        self.function=None
        self.mask=None
        self.calc_mask(args)
            
    def calc_mask(self,arg):
        self.set_function(arg[0])
        if self.function.nin==1:
            self.mask=self.function(arg[1])
        if self.function.nin==2:
            self.mask=self.function(arg[1],arg[2])
        if self.function.nin==3:
            self.mask=self.function(arg[1],arg[2],arg[3])
        
    def set_function(self,name):
        if isinstance(name,str):
            if name==">=":
                self.function=greater_equal
            if name==">":
                self.function=greater
            if name=="<=":
                self.function=less_equal
            if name=="<":
                self.function=less
            if name=="==":
                self.function=equal
            if name=="!=":
                self.function=not_equal
        else:
            self.function=name


    def build_submask(self,dat,val):
        if isinstance(val[0],str):   # if val[0] is a string it should be like '>=','>','<=','<','==','!='. In this Case val[1] should be the value against which is tested
            self.submaskstr+="(dat "+val[0]+" "+str(val[1])+")"
            self.submask*=eval(self.submaskstr)
        else:
            #for i,v in enumerate(val):
            self.submaskstr+=val[0].__name__+"(dat,"+str(val[1])+")"
            self.submask*=val[0](dat,val[1])

class submask2(object):
    def __init__(self,dat,val):
        self.submask=ones(dat.shape[0],bool)
        self.submaskstr=""

    def build_submask(self,dat,val):
        if isinstance(val[0],str):   # if val[0] is a string it should be like '>=','>','<=','<','==','!='. In this Case val[1] should be the value against which is tested
            self.submaskstr+="(dat "+val[0]+" "+str(val[1])+")"
            self.submask*=eval(self.submaskstr)
        else:
            #for i,v in enumerate(val):
            self.submaskstr+=val[0].__name__+"(dat,"+str(val[1])+")"
            self.submask*=val[0](dat,val[1])

class mask(object):
    def __init__(self,key,dat,vals=[]):
        """
        Class to handle masks on numpy arrays.
        key -> name of mask (e.g. string that contains the name of the array) it is used to build the maskstr
        dat -> numpy array
        vals -> list(/tupel) that contains the filter : e.g. [['>=',5],'*',['<=',10],'*',['~isnan']] -> (dat>=5)*(dat<=10) would be the mask returned by get_mask.
        func -> similar to val but function like isnan can be handled : e.g. ('~isnan') -> ~isnan(dat) will be linked with vals by '*'
        """
        self.maskstr=key+" : "
        self.key=key
        self.vals=vals
        self.dat=dat
        self.mask=ones(dat.shape[0],bool)
        self.build_maskstr()
        
        
    def build_maskstr(self):
        """
        Builds the mask as a string.
        """
        maskstr=""
        #maskstr=self.key+" : "
        for i,val in enumerate(self.vals):
            if i%2==0: 
                if isinstance(val[0],str):   # if val[0] is a string it should be like '>=','>','<=','<','==','!='. In this Case val[1] should be the value against which is tested
                    maskstr+="(self.dat "+val[0]+" "+str(val[1])+")"
                else:
                    maskstr+=val[0].__name__+"(self.dat)"#"+str(val[1])+")"
            else:
                maskstr+=val
        #for i,val in enumerate(self.funcs):
        #    if maskstr!="":
        #        maskstr+="*"
        #    maskstr+=val+"(self.dat)"
        self.maskstr=maskstr
        
    def get_maskstr(self):
        """
        Returns the mask. 
        """
        return self.maskstr.replace("self.dat",self.key)
        
    def get_mask(self):
        """
        Returns the mask. (First builds the mask string with the actual settings, if nothing is set an array with all True is returned)
        """
        self.build_maskstr()
        if self.maskstr=="":
            return ones(self.dat.shape,bool)
        else:
            return eval(self.maskstr)#,self.maskstr.replace("self.dat",self.key)


class etData(object):
    def __init__(self):
        self.data={}
        self.masks = {}
        self.appmasks = []
        self.filtered_data = {}
        self.reset_mask()

    def load(self):
        """
        Should be implemented by user.
        """
        pass

    def reset_mask(self):
        for key in self.data:
            self.masks = {}
            #self.masks[key] = min(self.data[key]),max(self.data[key]) # min val includes missing data indicated by value = -999., but excludes bad data indicated by nan or inf

    def show_mask(self):
        print "### Current mask ###"
        for arg in self.masks:
            print self.masks[arg].get_maskstr()

    def show_info(self):
        print "### Apllied mask ###"
        print "Datavolume = ",self.filtered_data[self.filtered_data.keys()[0]].shape[0],"/",self.data[self.data.keys()[0]].shape[0],"=",1.*self.filtered_data[self.filtered_data.keys()[0]].shape[0]/(1.*self.data[self.data.keys()[0]].shape[0])*100.,"%"
        for s in self.appmasks:
            print s
            #print arg,": ",self.appmasks[arg]

    def set_mask(self,arg,val=[]):
        """	
        Sets a filter to the raw data. The data can be filtered by a value range (val) of a given data paramater arg
        """
        if arg=="all":
            for arg in self.data:
                self.masks[arg] = mask(arg,self.data[arg],vals=val)
        else:
            self.masks[arg] = mask(arg,self.data[arg],vals=val)

    def apply_mask(self):
        """
        Apllies the filter to the mask
        """
        mask = ones(self.data[(self.data.keys())[0]].shape[0],bool)
        appmasks=[]
        for arg in self.masks:
            mask*=self.masks[arg].get_mask()
            #mask*=(self.data[arg]>=self.masks[arg][0])*(self.data[arg]<=self.masks[arg][1])
            appmasks.append(self.masks[arg].get_maskstr())
        for arg in self.data:
            self.filtered_data[arg] = copy.deepcopy(self.data[arg][mask])
        self.appmasks=appmasks
        
    def add_data(self,arg,y):
        """
        Adds new data column 'y' to 'data' with keyword 'arg'
        """
        self.data[arg]=y
        self.apply_mask()
        
    
    def get_hist(self,arg,xvals):
        y,x=histogram(self.filtered_data[arg],xvals)
        return x[:-1]+(x[1]-x[0])/2.,y


