class plotmark:
    def __init__(self,style,lt=5):
        self.panels=[-1]
        self.style=style
        self.label=""
        self.labelpanels=[-1]
        self.plot=[]
        if (self.style=="vline"):
            self.pos=[[10.,0.,0.,10.]]
            self.arrowhead=0
            self.linetype=lt
            self.linewidth=2
        if (self.style=="box"):
            self.pos=[[1.,10.,1.e-20,1.e20]]
            self.linetype=lt
            self.linewidth=2
        if (self.style=="hline"):
            self.pos=[[0.,0.,0.,0.]]
            self.arrowhead=0
            self.linetype=lt
            self.linewidth=2
        if (self.style=="function"):
            self.pos=[[0.,0.,0.,0.]]
            self.arrowhead=0
            self.linetype=lt
            self.linewidth=2
            self.func=""

    def setlinewidth(self,a):
        self.linewidth=a

    def setlinetype(self,a):
        self.linetype=a
            
    def setpanel(self,a):
        self.panels=a

    def setlabelpanel(self,a):
        self.labelpanels=a

    def setlabel(self,a):
        self.label=a

    def setfunction(self,a,b):
        """
        a=function, b linetype
        """
        if (self.style=="function"):
            self.function=a+" with l lt %i title ''"%(b)
        else:
            print "wrong style : ",self.style

    def setboxrange(self,a,b,c=1e-20,d=1e20):
        if (self.style=="box"):
            self.pos[0][0]=a
            self.pos[0][1]=b
            self.pos[0][2]=c
            self.pos[0][3]=d
        else:
            print "wrong style : ",self.style
    
    def setvlinepos(self,a):
        if (self.style=="vline"):
            self.pos[0][0]=a
        else:
            print "wrong style : ",self.style

    def sethlinepos(self,a):
        if (self.style=="hline"):
            self.pos[0][1]=a
        else:
            print "wrong style : ",self.style

    def addplot(self,a):
        self.plot.append(a)
