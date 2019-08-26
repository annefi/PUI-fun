from math import sqrt,cos,acos,asin,sin,atan,pi
from libacepy.mag import magdata
from Gnuplot import Gnuplot,Data,GridData

timeframe=[[25.25,26.5]]#[15.,22.5]]#[6.25,12.2]]
#timeframe=[[6.25,12.2],[15.,22.5],[25.25,26.5],[33.,37.8],[42.5,49.],[50.,53.5],[61.,64.],[69.5,77.5],[88.5,91.5],[97.75,105.75],[115.5,118.5],[126.,130.],[143.,147.5],[151.,155.],[168.,171.],[172.5,175.5],[179.,181.5],[194.5,200.5],[223.25,226.75],[232.,234.75],[248.5,253.5],[259.5,261.],[276.5,281.5],[286.,288.5],[303.5,308.75],[313.25,314.25],[331.,335.],[341.5,344.],[359.,361.5]]
magpath="/data/wimmer/ace/mag/"


#mag=magdata(1.,2008,timeframe,magpath)
binres=64.
thetaarr=[]
phiarr=[]
THETAarr=[]
magbarr=[]
phiser=[]
for tf in timeframe:
    mag=magdata(1.,2008,[tf],magpath)
    for i in range(len(mag.time)/binres):
        tmpmag=0.
        tmpmag2=0.
        tmpmagx=0.
        tmpmagy=0.
        tmpmagz=0.
        tmpmagphi1=0.
        tmpmagphi2=0.
        tmpmagphi3=0.
        tmpmagtheta1=0.
        tmpmagtheta2=0.
        tmpmagtheta3=0.
        tmpmagTHETA1=0.
        tmpmagTHETA2=0.
        tmpmagTHETA3=0.
        N1=0.
        for j in range(binres):
            if mag.magb[i*binres+j]>0.:
                tmpmag+=mag.magb[i*binres+j]
                tmpmagx+=mag.magbx[i*binres+j]
                tmpmagy+=mag.magby[i*binres+j]
                tmpmagz+=mag.magbz[i*binres+j]
                if (mag.phi[i*binres+j]>0.):
                    tmpmagphi1+=mag.phi[i*binres+j]
                    tmpmagphi2+=mag.phi[i*binres+j]*mag.magb[i*binres+j]
                else:
                    tmpmagphi1+=mag.phi[i*binres+j]+2*pi
                    tmpmagphi2+=(mag.phi[i*binres+j]+2*pi)*mag.magb[i*binres+j]
                tmpmagphi3=0.
                tmpmagtheta1+=mag.theta[i*binres+j]
                tmpmagtheta2+=mag.theta[i*binres+j]*mag.magb[i*binres+j]
                tmpmagtheta3=0.
                tmpmagTHETA1+=mag.THETA[i*binres+j]
                tmpmagTHETA2+=mag.THETA[i*binres+j]*mag.magb[i*binres+j]
                N1+=1.

        if N1>0.:
            tmpmagTHETA2/=tmpmag
            tmpmagphi2/=tmpmag
            if tmpmagphi2>pi:
                tmpmagphi2-=2*pi
            tmpmagtheta2/=tmpmag
            tmpmagTHETA1/=N1
            tmpmagphi1/=N1
            if tmpmagphi1>pi:
                tmpmagphi1-=2*pi
            tmpmagtheta1/=N1
            tmpmag/=N1
            tmpmagx/=N1
            tmpmagy/=N1
            tmpmagz/=N1
            tmpmag2=sqrt(tmpmagx**2+tmpmagy**2+tmpmagz**2)
            # calculate phi
            if (tmpmagx>0. and tmpmagy<0.):
                tmpmagphi3=atan(tmpmagy/tmpmagx)
            elif (tmpmagx>0. and tmpmagy>0.):
                tmpmagphi3=atan(tmpmagy/tmpmagx)
            elif (tmpmagx<0. and tmpmagy<0.):
                tmpmagphi3=-atan(tmpmagx/tmpmagy)-pi/2.
            elif (tmpmagx<0. and tmpmagy>0.):
                tmpmagphi3=pi/2.+atan(abs(tmpmagx)/abs(tmpmagy))
            elif (tmpmagx==0.and tmpmagy>0.):
                tmpmagphi3=pi/2.
            elif (tmpmagx==0.and tmpmagy<0.):
                tmpmagphi3=-pi/2.
            else:
                tmpmagphi3=0.
            # calculate theta
            if (tmpmag>0.):
                #print newtime[newi],tmpmagz,tmpmag
                tmpmagtheta3=asin(tmpmagz/tmpmag2)
            else:
                tmpmagtheta3=0.
            tmpmagTHETA3=acos(cos(tmpmagphi3)*cos(tmpmagtheta3))
            magbarr.append([tmpmag,tmpmag2])
            THETAarr.append([tmpmagTHETA1*180./pi,tmpmagTHETA2*180./pi,tmpmagTHETA3*180./pi])
            thetaarr.append([tmpmagtheta1*180./pi,tmpmagtheta2*180./pi,tmpmagtheta3*180./pi])
            phiarr.append([tmpmagphi1*180./pi,tmpmagphi2*180./pi,tmpmagphi3*180./pi])
            phiser.append([i,tmpmagphi3*180./pi])

gp=Gnuplot()
gp("set title 'magb'")
gp("set xlabel 'magb1'")
gp("set ylabel 'magb2'")
gp.plot(magbarr)

gp2=Gnuplot()
gp2("set title 'THETA'")
gp2("set xlabel 'THETA1'")
gp2("set ylabel 'THETA2'")
gp2("set zlabel 'THETA3'")
gp2.splot(THETAarr)

gp3=Gnuplot()
gp3("set title 'theta'")
gp3("set xlabel 'theta1'")
gp3("set ylabel 'theta2'")
gp3("set zlabel 'theta3'")
gp3.splot(thetaarr)

gp4=Gnuplot()
gp4("set title 'phi'")
gp4("set xlabel 'phi1'")
gp4("set ylabel 'phi2'")
gp4("set zlabel 'phi3'")
gp4.splot(phiarr)


gp5=Gnuplot()
gp5.plot(phiser)
