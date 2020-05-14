#! /usr/bin/env python
"""
cascade.py 0.1.1
Provides mathods to analyze and vialize the particle cascades from the geant4 tracking output
Usage: Start Geant4 run with tracking verbosity 2 and pipe output to file
       create Cascades object with file as argument.
Cascades stores particles, visited volumes, secondaries ... for each event and provides statistical information.
For the use of drawXXXGraph() functions pygraphviz needs to be installed.
Author: Jan Koehler   koehler@physik.uni-kiel.de
"""


class ParticleTrack:
    def __init__(self, pName, tid, createdByProc):
        """ contruct particle track with p(article)Name, t(rack)id and process """
        self.pName = pName
        self.tid = tid
        self.initialEnergy = 0
        self.initialVolume = ""
        self.createdByProc = createdByProc
        self.volumes = {}  #stores each vsited Volume
        self.path = []     #stores volumes along particles path
        self.secondaries = {} #dict of trackId:ParticleTrack()

    def __str__(self, indent=""):
        s = "%s*%s E=%gMeV in %s by %s\n"%(indent, self.pName, 
                                          self.initialEnergy, 
                                          self.initialVolume, 
                                          self.createdByProc)
        s+=" %straveled through:\n"%(indent)
        for v in self.volumes.itervalues():
            s+=" %s%s eDep=%gMeV. Procs: "%(indent, v.name,v.eDep)
            for proc in v.procs:
                s+=" %s"%(proc)
            s+="\n"
        if len(self.secondaries)>0:
            s+= " %sCreated secondaries:\n"%(indent)
        for pt in self.secondaries.itervalues():
            s+=pt.__str__(indent+"  ")
        return s
            
    def getAllTracks(self):
        """Returns a list containing all Particle Tracks, main and secondaries """
        tracks = [self]
        for pt in self.secondaries.values():
            tracks += pt.getAllTracks()
        return tracks

    def enterNewVolume(self, name):
        """ update volumes dict and path list """
        if not self.volumes.has_key(name):
            self.volumes[name]=Volume(name)
        if len(self.path)==0 or self.path[-1].name != name:
            self.path.append(Volume(name))

    def createSecondary(self, name, tid, createdByProc):
        """ Create secondary ParticleTrack 
            with (particle)name t(rack)id and process """
        self.secondaries[tid]=ParticleTrack( name, tid, createdByProc)

    def getSecondary(self, tid):
        """ Returns ParticleTack object with t(rack)id"""
        if self.secondaries.has_key(tid):
            return self.secondaries[tid]
        for s in self.secondaries.itervalues():
            t = s.getSecondary(tid)
            if t != None:
                return t
        return None

    def getVolumeNames(self):
        """ Returns a list of all occuring volume names for primary and secondary particles"""
        Volumes = []
        for t in self.getAllTracks():
            for v in t.volumes.keys():
                if v not in Volumes:
                    Volumes.append(v)
        return Volumes

class Volume:
    def __init__(self, name):
        self.name = name
        self.eDep = 0
        self.procs = []



class Cascades:
    """ Creates and stores a list of ParticleTrack objects """
    def __init__(self, fn=None):
        """ optional fn string contains filename to G4 stdout file"""
        self.Tracks = []
        self.ignore = ["WARNING", "WARNING:", '@', '#', '>>Events', 'Graphics', 'Visualization']
        #ignore lines which begin with these strings
        self.colors = ["blue",\
                      "red",\
                      "green",\
                      "purple",\
                      "deeppink",\
                      #"darkorchid",\
                      "darkorange",\
                      "grey",\
                      "deepskyblue",\
                      "forestgreen",\
                      "yellow",\
                      "steelblue",\
                      "magenta",\
                      "navajowhite",\
                      "olivedrab",\
                      "orange",\
                      "palegreen",\
                      "yellow3",\
                      "yellow4",\
                      "violetred4",\
                      "red4"]
        self.volumeColor  = {}
        self.processColor = {}

        self.pathsGraphDepth = 8    #recursion depth of the drawPathGraph method
        self.pathsGraphMinI  = 0.1  #ignore paths with I<0.1%
        self.pathsGraphHVol  = []   #mark nodes from this list
        self.graphStyle      ='dot' #visualization style

        if fn != None:
            self.read(fn)


    def read(self, fn):
        """ read from file fn, and append ParticleTracks to Tracks """
        from os.path import getsize #preliminary status bar
        from numpy import arange
        fnSize = getsize(fn)
        fnPos=0
        printPos = 0
        print "Reading '%s' "%(fn),

        pt = None
        proc=""
        vol=""
        readSecondaries=False
        linesToTrack=-1
        import fileinput
        for line in fileinput.input(fn):
            fnPos+=len(line) #status bar
            if float(fnPos)/fnSize >= printPos:
                print "...%d%%"%(100*printPos),
                printPos+=0.1
            if linesToTrack>0:
                linesToTrack-=1
                continue
            if len(line.split())==0 or  line.split()[0] in self.ignore:
                linesToTrack=-1
                continue
            if line.count("* G4Track Information:   Particle = ")  :
                tId = int(line.split()[9].rstrip(","))
                if tId == 1:
                    tIdCount=1
                    proc="gun"
                    name=line.split()[5].rstrip(",")
                    pt = ParticleTrack(name,tId, proc)
                    self.Tracks.append(pt)
                else:
                    pt = self.Tracks[-1].getSecondary(tId)
                linesToTrack=3
                continue
            if line.count("    :----- List of 2ndaries - #SpawnInStep= "):
                readSecondaries=True
                continue
            if line.count("---------- EndOf2ndaries Info -"):
                readSecondaries=False
                continue
            if readSecondaries:
                name = line.split()[5]
                tIdCount+=1
                pt.createSecondary(name,tIdCount, proc)
                continue
            if linesToTrack == 0:
                edep = float(line.split()[5])
                vol = line.split()[8]
                vol = vol.split("_") #remove the detector ID
                if vol[-1].isdigit():
                    vol.pop(-1)
                vol = "_".join(vol)
                proc = line.split()[9]
                pt.enterNewVolume(vol)
                pt.volumes[vol].eDep+=edep
                pt.volumes[vol].procs.append(proc)
                pt.path[-1].eDep+=edep
                pt.path[-1].procs.append(proc)
                if proc =="initStep":
                    pt.initialEnergy = float(line.split()[4])
                    pt.initialVolume = vol
        print " ... done."
    def getSecondaries(self,  volume='all', gen='all', initialEnergy=[0,1e30]):
        """ returns a dict of produced secondaries for 
            volume: Volume where secondary was generated
            gen : process of generation
            initialEnergy: initial energy range [min, max]                
        """
        particles = {}
        for pt in self.getAllSubTracks('all', volume, gen, initialEnergy):
            if pt.createdByProc == 'gun':
                continue
            if particles.has_key(pt.pName):
                particles[pt.pName]+=1.
            else:
                particles[pt.pName]=1.
        N = len(self.Tracks)
        for p in particles.keys():
            particles[p] /= N                
        return particles

    def printAllSecondaries(self, gen='all', initialEnergy=[0,1e30]):
        """Prints out a list of produced secondaries 
            and their rate of occurence for each volume and for:
            gen : process of generation
            initialEnergy: initial energy range [min, max]
        """
        print "Produced secondaries per primary particle event"
        for v in self.getVolumeNames():
            print v, ":"
            s = self.getSecondaries(v, gen, initialEnergy )
            for p in s.keys():
                print " ", p, s[p]


    def getProcs(self, volume, pName='all', initialVolume='all', gen='all', initialEnergy=[0,1e30]):
        """ returns a dict of produced interaction for volume by 
            pName: particle Type
            initialVolume: Volume where particle was generated
            gen : process of generation
            initialEnergy: initial energy of particle, range [min, max]        
        """
        procs = {}
        for pt in self.getAllSubTracks(pName, initialVolume, gen, initialEnergy):
            if pt.volumes.has_key(volume):
                for proc in pt.volumes[volume].procs:
                    if procs.has_key(proc):
                        procs[proc]+=1.
                    else:
                        procs[proc]=1.
        N = len(self.Tracks)
        for p in procs.keys():
            procs[p] /= N                
        return procs


    def getEDeps(self, volume, pName='all', initialVolume='all', gen='all', initialEnergy=[0,1e30]):
        """ returns for each subTrack eDeps in volume caused by 
            pName: particle Type
            initialVolume: Volume where particle was generated
            gen : process of generation
            initialEnergy: initial energy range [min, max]        
        """
        eDeps = []
        for pt in self.getAllSubTracks(pName, initialVolume, gen, initialEnergy):
            if pt.volumes.has_key(volume):
                eDeps.append(pt.volumes[volume].eDep)
        return eDeps


    def drawTrackGraph(self, fn=None, index=0 ,drawEDeps=False):
        """ drawGraph of ParticleTrack[index], and write to file fn.
            If fn is set to none, the Graph object is returned.
            Colorscheme can be adjusted via colors, volumeColor, processColor.
            volumeColor and processColor are set the first time drawGraph() is called.
            Following calls will only expand the color dicts if necessary."""
        col=self.colors 
        vCol=self.volumeColor
        pCol=self.processColor
        vUsed = [] #volumes actually used in this run
        pUsed = [] #processes actually used in this run
        mainTrack = self.Tracks[index]
        import pygraphviz
        G = pygraphviz.AGraph(directed=True)
        #G.node_attr['shape']='box'
        G.graph_attr['outputorder']='edgesfirst'
        G.node_attr['fontname']='Helvetica'
        G.edge_attr['fontname']='Helvetica'
        G.node_attr['style']='filled'
        G.node_attr['fontsize']='8'
        if not vCol.has_key(mainTrack.initialVolume):
             vCol[mainTrack.initialVolume]=col[len(vCol)%len(col)]
        if not mainTrack.initialVolume in vUsed:
            vUsed.append(mainTrack.initialVolume)
        G.add_node(mainTrack.tid,
                   label="%s, %gMeV"%(mainTrack.pName,mainTrack.initialEnergy),
                   fillcolor=vCol[mainTrack.initialVolume],
                   fontsize='12')

        def genTree(parentTrack):
            """ Recursively step throough all secondaries """
            if drawEDeps:
                for v in parentTrack.volumes.keys():
                    if parentTrack.volumes[v].eDep>0 and v != "OutOfWorld":
                        if not vCol.has_key(v):#create color dict
                            vCol[v]=col[len(vCol)%len(col)]
                        if not v in vUsed:
                            vUsed.append(v)
                        G.add_edge(parentTrack.tid, str(parentTrack.tid)+v,
                                   color="grey",
                                   arrowhead='none',
                                   label='%gMeV'%parentTrack.volumes[v].eDep,
                                   fontsize="6",
                                   fontcolor='grey')
                        n=G.get_node(str(parentTrack.tid)+v)
                        n.attr['shape']="point"
                        n.attr['fillcolor']=vCol[v]
                        n.attr['color']=vCol[v]                        
            for track in parentTrack.secondaries.itervalues():
                if not vCol.has_key(track.initialVolume):#create color dict
                    vCol[track.initialVolume]=col[len(vCol)%len(col)]
                if not track.initialVolume in vUsed:
                    vUsed.append(track.initialVolume)
                if not pCol.has_key(track.createdByProc):
                    pCol[track.createdByProc]=col[len(pCol)%len(col)]
                if not track.createdByProc in pUsed:
                    pUsed.append(track.createdByProc)
                G.add_edge(parentTrack.tid, track.tid, #add edge between tid
                           color= pCol[track.createdByProc],
                           shape='normal')
                n = G.get_node(track.tid)
                n.attr["label"]="%s, %gMeV"%(track.pName,track.initialEnergy)
                n.attr["fillcolor"] =vCol[track.initialVolume]
                genTree(track)
                
        genTree(mainTrack)
        #Generate key for procsses and volumes
        keys = vCol.keys()
        keys.reverse()
        for vol in vUsed:
            G.add_node(vol,  color=vCol[vol])
            G.add_edge(vol, 1, color='white', dir='none', penwidth="0")#to set key position
        keys = pCol.keys()
        keys.reverse()
        for proc in pUsed:
            G.add_node(proc,color="white", fontcolor=pCol[proc])
            G.add_edge(proc, 1, color='white', dir='none', penwidth="0")#ugly workaround   
        G.layout(prog=self.graphStyle) 
        if fn != None:
            G.draw(fn)
        else:
            return G

    def getSubTracks(self, track, pName='all', initialVolume='all', gen='all', initialEnergy=[0,1e30]):
        """ Returns a list of all subTracks of track with 
            pName: particle Type
            initialVolume: Volume where particle was generated
            gen : process of generation
            initialEnergy: initial energy range [min, max]
        """
        subTracks = []
        for t in track.getAllTracks():
            if ( t.pName==pName or pName == 'all') and \
               ( t.initialVolume==initialVolume or initialVolume == 'all') and \
               ( t.createdByProc==gen or gen == 'all' ) and\
               ( initialEnergy[0] < t.initialEnergy < initialEnergy[1]):
                subTracks.append(t)            
        return subTracks
        
    def getAllSubTracks(self, pName='all', initialVolume='all', gen='all', initialEnergy=[0,1e30]):
        """ Returns a list of all subTracks of Tracks list with 
            pName: particle Type
            initialVolume: Volume where particle was generated
            gen : process of generation
            initialEnergy: initial energy range [min, max]
        """
        subTracks = []
        for track in self.Tracks:
            subTracks += self.getSubTracks(track, pName, initialVolume, gen, initialEnergy)
        return subTracks

    def getVolumeNames(self):
        """Return a list of names of all visited volumes"""
        volumes = []
        for track in self.Tracks:
            for v in track.getVolumeNames():
                if v not in volumes:
                    volumes.append(v)
        return volumes
            

    def getPaths(self,  pName='all',  initialVolume='all', gen='gun', initialEnergy=[0,1e30]):
        """ Returns statistics abouth the order in which particles visit volumes 
            Path is stored as nested dict object. The dict contains 
            pName: particle Type
            initialVolume: Volume where particle was generated
            gen : process of generation
            initialEnergy: initial energy range [min, max]
        """
        pathTree = {}  
        for t in self.Tracks:
            for st in self.getSubTracks(t, pName, initialVolume, gen,initialEnergy):
                pathLimb = pathTree
                for v in st.path:
                    if v.name.count("world") and st.path.index(v)!=0 and st.path.index(v)!=len(st.path)-1:
                        continue
                    if v.name not in pathLimb.keys():
                        pathLimb[v.name]=[0, {}]
                    pathLimb[v.name][0]+=1
                    pathLimb = pathLimb[v.name][1]
        return pathTree

    def printPaths(self, pName='all', initialVolume='all', 
                   gen='gun', initialEnergy=[0,1e30]):
        """ drawPathGraph in ascii mode"""
        paths = self.getPaths(pName,  initialVolume, gen)
        scale = 0
        for v in paths.keys():
            scale += paths[v][0]
        def printThis(paths, indent = ""):
            for v in paths.keys():
                print indent+"|=> %s %g percent"%(v, paths[v][0]*100./scale)
                printThis(paths[v][1], indent+"  ")
        printThis(paths)

    def drawPathsGraph(self, fn, pName='all',  
                       initialVolume='all', 
                       gen='gun',
                       initialEnergy=[0,1e30]):
        """Draw particle paths to file fn.
           Particles paths are generated from 
           pName: particle type
           initialVolume: volumes in which partucles were generated
           gen: particle generation process, 'gun' for primary particles
           initialEnergy: initial energy range [min, max]
           Additional option via class propteries
           pathsGraphDepth:   recursion depth of the drawPathGraph method
           pathsGraphMinI: ignore paths with Intensity < 
           pathsGraphHVol: highlight nodes from this list
           graphStyle: visualization style, check pygraphviz for different options
           
        """
        from numpy import sqrt
        import pygraphviz
        G = pygraphviz.AGraph(directed=True) 
        G.graph_attr['outputorder']='edgesfirst'
        G.node_attr['fontname']='Helvetica'
        G.edge_attr['fontname']='Helvetica'
        G.node_attr['style']='filled'
        paths = self.getPaths(pName,  initialVolume, gen, initialEnergy)
        scale = 0
        for v in paths.keys():
            scale += paths[v][0]
        def genTree(paths, depth=0):
            if depth >= self.pathsGraphDepth:
                return
            for v in paths.keys():
                if paths[v][0] *100./scale < self.pathsGraphMinI:
                    continue
                fillcolor='white'
                if v in self.pathsGraphHVol:
                    fillcolor='gray'
                if depth==0:#head nodes
                    label = v
                    if len(paths)>1:  #more than one head -> add percentage
                        label += " %3.1f"%(paths[v][0] *100./scale)+"%"
                    G.add_node(id(paths[v][1]), 
                               label=label,
                               fontsize="23",
                               fillcolor=fillcolor)
                else:
                    if len(paths[v][1])==0: #if volume is the last, create global node
                        nName= v
                        fontsize="20"
                    else:                   #else create unambigous node via object id
                        nName=id(paths[v][1])
                        fontsize="14"
                    G.add_edge(id(paths), nName ,
                               penwidth="%g"%(sqrt(paths[v][0] *100./scale)),
                               label="%3.2f"%(paths[v][0] *100./scale)+"%")
                    n = G.get_node(nName)
                    n.attr['label']=v
                    n.attr['fontsize']=fontsize
                    n.attr['fillcolor']=fillcolor
                genTree(paths[v][1],depth+1)
        genTree(paths)
        G.layout(prog=self.graphStyle) 
        if fn != None:
            G.draw(fn)
        else:
            return G

if __name__=="__main__":
    c=Cascades("bsp.g4out") #create Cascades object with Events from 'bsp.g4out' file
#    print c.getProcs(volume='world') #print a list of process which occured in world
#    print c.Tracks[0]                #print the First event from list  
    #print c.getEDeps('neutron_channel_6')
    #print c.getPaths()
    #c.drawGraph("e.png",6 , drawEDeps=True)
    c.pathsGraphMinI=0
    c.pathsGraphDepth=10
    c.pathsGraphHVol=['A','B']
    c.drawPathsGraph("test.svg",pName='all', gen='all',initialVolume='all')
    #c.printAllSecondaries()
    #print c.getVolumeNames()
