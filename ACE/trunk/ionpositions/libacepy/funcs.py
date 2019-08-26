from numpy import *

def kappa(grid,p):
    """
    p[0:2] -> x,y,z of centre
    p[3]   -> Peak intensity
    p[4]   -> sigma
    p[5]   -> kappa
    grid   -> input array with points dim(N,3) [x1,y1,z1],[x2,y2,z2]...[xN,yN,zN]
    returns array with function values at grid points
    """
    x=grid[:,0]-p[0]
    y=grid[:,1]-p[1]
    z=grid[:,2]-p[2]
    r=sqrt(x**2+y**2+z**2)
    return p[3]*(1+(r**2)/(p[5]*p[4]**2))**-p[5]
    
def gauss(grid,p):
    """
    p[0:2] -> x,y,z of centre
    p[3:5] -> sigx,sigy,sigz 
    p[6]   -> total density
    grid   -> input array with points dim(N,3) [x1,y1,z1],[x2,y2,z2]...[xN,yN,zN]
    returns array with function values at grid points
    """
    x=-(grid[:,0]-p[0])**2/(2.*p[3]**2)
    y=-(grid[:,1]-p[1])**2/(2.*p[4]**2)
    z=-(grid[:,2]-p[2])**2/(2.*p[5]**2)
    return p[6]/((2*pi)**1.5*p[3]*p[4]*p[5])*exp(x+y+z)


def twogauss(grid,p):
    """
    ...
    """
    x=-(grid[:,0]-p[0])**2/(2.*p[3]**2)
    y=-(grid[:,1]-p[1])**2/(2.*p[4]**2)
    z=-(grid[:,2]-p[2])**2/(2.*p[5]**2)
    x2=-(grid[:,0]-p[0]-60.)**2/(2.*p[3]**2)
    y2=-(grid[:,1]-p[1])**2/(2.*p[4]**2)
    z2=-(grid[:,2]-p[2])**2/(2.*p[5]**2)
    #tmparr=p[6]/((2*pi)**1.5*p[3]*p[4]*p[5])*exp(x+y+z)+0.7*p[6]/((2*pi)**1.5*p[3]*p[4]*p[5])*exp(x2+y2+z2)
    return 1./1.7*p[6]/((2*pi)**1.5*p[3]*p[4]*p[5])*exp(x+y+z)+0.7/1.7*p[6]/((2*pi)**1.5*p[3]*p[4]*p[5])*exp(x2+y2+z2)
    #return tmparr[tmparr>p[6]/((2*pi)**1.5*p[3]*p[4]*p[5])*0.1]


def twobimaxmag(grid,p):
    """
    p[0:2] -> x,y,z of centre
    p[3:5] -> sigx,sigy,sigz 
    p[6]   -> total density
    p[7]   -> peak ratio
    p[8]   -> valf
    p[9]   -> phi-winkel
    p[10]   -> theta-winkel
    """
    from libacepy.ancil import rot2d
    from numpy import pi,exp

    x1=grid[:,0]-p[0]
    y1=grid[:,1]-p[1]
    z1=grid[:,2]-p[2]

    x2,y2=rot2d(x1,y1,-p[9])
    x3,z2=rot2d(x2,z1,-p[10])
    
    x=-(x3)**2/(2.*p[3]**2)
    y=-y2**2/(2.*p[4]**2)
    z=-z2**2/(2.*p[5]**2)
    x2=-(x3-p[8])**2/(2.*p[3]**2)
    y2=-y2**2/(2.*p[4]**2)
    z2=-z2**2/(2.*p[5]**2)
    #tmparr=p[6]/((2*pi)**1.5*p[3]*p[4]*p[5])*exp(x+y+z)+0.7*p[6]/((2*pi)**1.5*p[3]*p[4]*p[5])*exp(x2+y2+z2)
    return (1./(1+p[7]))*p[6]*1e15/((2*pi)**1.5*p[3]*p[4]*p[5])*exp(x+y+z)+(p[7]/(1+p[7]))*p[6]*1e15/((2*pi)**1.5*p[3]*p[4]*p[5])*exp(x2+y2+z2)
    #return tmparr[tmparr>p[6]/((2*pi)**1.5*p[3]*p[4]*p[5])*0.1]

def twobimaxmagring(grid,p):
    """
    p[0:2] -> x,y,z of centre
    p[3:5] -> sigx,sigy,sigz 
    p[6]   -> total density
    p[7]   -> peak ratio
    p[8]   -> valf
    p[9]   -> phi-winkel
    p[10]   -> theta-winkel
    """
    from libacepy.ancil import rot2d
    from numpy import pi,exp,sqrt,arctan,cos,arccos,sin,zeros
    from Gnuplot import Gnuplot,Data

    x1=grid[:,0]-p[0]
    y1=grid[:,1]-p[1]
    z1=grid[:,2]-p[2]

    x2,y2=rot2d(x1,y1,-p[9])
    x3,z2=rot2d(x2,z1,-p[10])

    r=sqrt(x3**2+y2**2+z2**2)
    rr=20.
    r[r<p[8]-rr]=0.
    r[r>p[8]+rr]=0.
    #r[z2>rr]=0.
    #r[x3<-rr]=0.
    r[x3<-rr]=0.
    #print "len(r[r>0.])=",len(r[r>0.])
    #print "len(x3[r>0.])=",len(x3[r>0.])
    if len(r[r>0.]):
        r2=zeros(len(r))
        r[r>0.]=5.*1e15*exp(-(r[r>0.]-p[8])**2/(2.*20.**2))/(2.*pi*10**2)/(2.*pi*p[8])
        ang=arctan(sqrt(y2[r>0.]**2+z2[r>0.]**2)/x3[r>0.])
        #r[r>0.]/=(abs(x3[r>0.])+3.)
        gp=Gnuplot()
        #gp.plot(ang*180./pi)
        #print "ang = ",ang*180./pi
        pr=zeros([len(r[r>0.]),3])
        pr[:,0]=x3[r>0.]
        pr[:,1]=y2[r>0.]
        pr[:,2]=z2[r>0.]
        gp.splot(pr)
        raw_input()
        r[r>0.]*=sin(ang)**2
        #r[r>0.]=1.*p[6]*1e15/(2.*pi*p[8])/20.**2
        #if len(r[(r>=p[8]-10.)*(r<=p[8]+10.)]):
        #r[(r>=p[8]-10.)*(r<=p[8]+10.)]=p[6]*1e15/(100.*float(len(r[(r>=p[8]-10.)*(r<=p[8]+10.)])))
    else:
        r[:]=0.
    x=-(x3)**2/(2.*p[3]**2)
    y=-y2**2/(2.*p[4]**2)
    z=-z2**2/(2.*p[5]**2)
    x2=-(x3-p[8])**2/(2.*p[3]**2)
    y2=-y2**2/(2.*p[4]**2)
    z2=-z2**2/(2.*p[5]**2)
    #tmparr=p[6]/((2*pi)**1.5*p[3]*p[4]*p[5])*exp(x+y+z)+0.7*p[6]/((2*pi)**1.5*p[3]*p[4]*p[5])*exp(x2+y2+z2)
    return (1./(1+p[7]))*p[6]*1e15/((2*pi)**1.5*p[3]*p[4]*p[5])*exp(x+y+z)+(p[7]/(1+p[7]))*p[6]*1e15/((2*pi)**1.5*p[3]*p[4]*p[5])*exp(x2+y2+z2)+r
    #return tmparr[tmparr>p[6]/((2*pi)**1.5*p[3]*p[4]*p[5])*0.1]


def ring(grid,p):
    """
    p[0:2] -> x,y,z of centre
    p[3:5] -> sigx,sigy,sigz 
    p[6]   -> total density
    p[7]   -> peak ratio
    p[8]   -> valf
    p[9]   -> phi-winkel
    p[10]   -> theta-winkel
    """
    from libacepy.ancil import rot2d
    from numpy import pi,exp,sqrt,arctan,cos,arccos

    x1=grid[:,0]-p[0]
    y1=grid[:,1]-p[1]
    z1=grid[:,2]-p[2]

    x2,y2=rot2d(x1,y1,-p[9])
    x3,z2=rot2d(x2,z1,-p[10])

    r=sqrt(x3**2+y2**2+z2**2)
    rr=60.
    r[r<p[8]-rr]=0.
    r[r>p[8]+rr]=0.
    #r[z2>rr]=0.
    #r[x3<-rr]=0.
    r[x3<-rr]=0.
    #print "len(r[r>0.])=",len(r[r>0.])
    #print "len(x3[r>0.])=",len(x3[r>0.])
    if len(r[r>0.]):
        r[r>0.]=5.*1e15*exp(-(r-p[8])**2/(2.*20.**2))/(2.*pi*10**2)/(2.*pi*p[8])
        #ang=arccos(x3[r>0.]/sqrt(y2[r>0.]**2+z2[r>0.]**2+0.1))
        #r[r>0.]/=(abs(x3[r>0.])+3.)
        #print "ang = ",ang
        #r[r>0.]*=cos(ang)
        #r[r>0.]=1.*p[6]*1e15/(2.*pi*p[8])/20.**2
        #if len(r[(r>=p[8]-10.)*(r<=p[8]+10.)]):
        #r[(r>=p[8]-10.)*(r<=p[8]+10.)]=p[6]*1e15/(100.*float(len(r[(r>=p[8]-10.)*(r<=p[8]+10.)])))
    else:
        r[:]=0.
    x=-(x3)**2/(2.*p[3]**2)
    y=-y2**2/(2.*p[4]**2)
    z=-z2**2/(2.*p[5]**2)
    x2=-(x3-p[8])**2/(2.*p[3]**2)
    y2=-y2**2/(2.*p[4]**2)
    z2=-z2**2/(2.*p[5]**2)
    #tmparr=p[6]/((2*pi)**1.5*p[3]*p[4]*p[5])*exp(x+y+z)+0.7*p[6]/((2*pi)**1.5*p[3]*p[4]*p[5])*exp(x2+y2+z2)
    return (1./(1+p[7]))*p[6]*1e15/((2*pi)**1.5*p[3]*p[4]*p[5])*exp(x+y+z)+(p[7]/(1+p[7]))*p[6]*1e15/((2*pi)**1.5*p[3]*p[4]*p[5])*exp(x2+y2+z2)+r
    #return tmparr[tmparr>p[6]/((2*pi)**1.5*p[3]*p[4]*p[5])*0.1]



def vassis(grid,p):
    """
    p[0] -> ionname
    p[1] -> vsw in km/s
    p[2] -> r in AU
    p[3] -> theta in deg
    """

    from plastic.software.functions.vasyl import vasyl

    vas=vasyl(p[0])
    vas.vd_vsw=p[1]
    vas.vd_r=p[2]
    vas.vd_theta=p[3]
    res=[]
    for point in grid:
        res.append(vas.v_dist_sc(point[0]*1e3,point[1]*1e3,point[2]*1e3))
    return array(res)
    
                
