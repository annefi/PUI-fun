      subroutine integrallconv2(x1, y1, x2, y2, x3, y3, x4, y4, 
     & sigma, bb, defl, result)

c    bb ist der Abstand zwischen dem Durchstosspunkt durch die Folie und dem 
c    Auftreffpunkt auf den Detektor.             
c    xi und yi sind die Koordinaten der Projektion der Eckpunkte des Detektors 
c    auf eine Ebene senkrecht zum Ionenstrahl gesehen vom Durchstosspunkt durch die Folie.
c    Die Ebene ist charakterisiert durch den Strahl, der senkrecht darauf steht
c    und den Auftreffpunkt auf den Detektor, der in der Ebene liegt.
c    In dieser Ebene stelle man sich ein Koordinatensystem vor, auf das die
c    Eckpunkte des Detektors projiziert werden.
c    Das heisst, der erste Eckpunkt des Detektors erscheint unter dem Winkel arctan((x1*x1 +y1*y1)^0.5/bb)
      real*4
c     . x1,
c     . x2,
c     . x3,
c     . x4,
c     . y1,
c     . y2,
c     . y3,
c     . y4
c     . sigma,
c     . bb,
     . a,
     . b,
     . s,
     . t,
     . x12,
     . x23,
     . x34,
     . x41,
     . y12,
     . y23,
     . y34,
     . y41,
     . x21,
     . x32,
     . x43,
     . x14,
     . y21,
     . y32,
     . y43,
     . y14,
     . lam(180,4),
     . mu(180,4),
     . beta(180,4),
     . gamma(180,2),
     . d,
     . pi,
     . x,
     . xx,
     . y,
     . result,
     . defl1,
     . defl2,
     . g,       ! a der faltung zwischen rechteck und lorenz
     . z,       ! sigma des lorenz für die integrationsschleife
     . res1,
     . res2,
     . step
     
      pi=3.1415927
      d=pi/180.0
      
c    Berechnung der Beträge der Komponentendifferenzen      
      x12=abs(x1-x2)
      x23=abs(x2-x3)
      x34=abs(x3-x4)
      x41=abs(x4-x1)
      y12=abs(y1-y2)
      y23=abs(y2-y3)
      y34=abs(y3-y4)
      y41=abs(y4-y1)
c      write(*,*) x12,"  ",x23,"  ",x34,"  ",x41
c      write(*,*) y12,"  ",y23,"  ",y34,"  ",y41
c      write(*,*) x1,"  ",x2,"  ",x3,"  ",x4
c      write(*,*) y1,"  ",y2,"  ",y3,"  ",y4
c      result=signum(-0.5)
c      write(*,*) result
      
c    x21 ist die x-Komponente des Richtungsverktors für die Gerade, die von x1,y1 und x2,y2 aufgespannt wird. Aufpunkt ist x1,y1.
c    y21 ist die dazugehörige y-Komponente.
c    Die  anderen lassen sich analog erklären.     
        
      x21=x2-x1
      y21=y2-y1
      x32=x3-x2
      y32=y3-y2
      x43=x4-x3
      y43=y4-y3
      x14=x1-x4
      y14=y1-y4
      
      
c    Hier erfolgt die Berechnung der lams, für die die Geraden, die durch jeweils zwei der vier Eckpunkte einer Fläche 
c    "aufgespannt" werden, den umlaufenden Abtaststrahl schneiden.
c    Um zu vermeiden, dass das Programm abstürzt, falls es den Schnittpunkt zweier kollinearer Geraden berechnen soll,
c    (das ist genau dann der Fall, wenn der Abtaststrahl und einer der oben genannten Geraden parallel verlaufen)
c    wird lam in einem solchen Fall auf zwei gesetzt (was ausserhalb der erlaubten Parameter zwiwschen 0 und 1 ist)
c    Dieser Pfad wird im Laufe des Programms ohnenhin nicht weiter verfolgt, weil sie relevanten Schnittpunkte 
c    nur lam zwischen 0 und 1 haben dürfen, anderenfalls befinden sich die Schnittpunke ausserhalb des konvexen Vierecks und 
c    stellen daher keine relevanten Integrationsgrenzen dar
c    Siehe auch Zeichnung im Laborbuch Seite 76/77. 
c    Die swap-Funktionen dient dazu, dass für den Fall , dass die obige Berechnung einen Bruch mit dem Nenner 0 beinhaltet
c    die Kehrwerte der Steigungen verglichen werden, um auf die gleichen Ergebnisse zu kommen, wie oben beschrieben.
  
c    ++++++++++++++++++++++++++++++++++++++++
  
c    Verbindungslinie Punkt 1 zu Punkt 2 


      do alpha=1,180,1
c      
      phi=alpha-0.5
      a=sin(phi*d)
      b=cos(phi*d)
      s=abs(a)
      t=abs(b)

      if((s*y12) .eq. (t*x12)) then
  
         lam(alpha,1)=2
  
      else
  
         lam(alpha,1)=((x1*b/a)-y1)/(y21-(x21*b/a))

      end if
  
      
      if( (lam(alpha,1) .ge. 0) .and.  (lam(alpha,1) .lt. 1) ) then
  
          mu(alpha,1)=(x1+(lam(alpha,1))*x21)/a
  
      else
  
          mu(alpha,1)=100000
     
      end if
c      write(*,*) phi,"  ",a,"  ",b,"  ",s,"  ",t
c      write(*,*) lam(alpha,1), "   ", mu(alpha,1) 
      
cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
            
      if((s*y23) .eq. (t*x23)) then
  
          lam(alpha,2)=2
  
      else
  
          lam(alpha,2)=((x2*b/a)-y2)/(y32-(x32*b/a))

      end if
      
  
      if( (lam(alpha,2) .ge. 0) .and. (lam(alpha,2) .lt. 1) ) then
  
          mu(alpha,2)=(x2+(lam(alpha,2))*x32)/a
  
      else
  
          mu(alpha,2)=100000

      end if
  
ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc    
        
      if((s*y34) .eq. (t*x34)) then
  
          lam(alpha,3)=2
  
      else
  
          lam(alpha,3)=((x3*b/a)-y3)/(y43-(x43*b/a))
  
      end if

      
      if( (lam(alpha,3) .ge. 0) .and. (lam(alpha,3) .lt. 1) ) then
  
          mu(alpha,3)=(x3+(lam(alpha,3))*x43)/a
  
      else
  
          mu(alpha,3)=100000

      end if
      
ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
            
      if((s*y41) .eq. (t*x41)) then
  
          lam(alpha,4)=2
  
      else
  
          lam(alpha,4)=((x4*b/a)-y4)/(y14-(x14*b/a))

      end if
      
      
      if( (lam(alpha,4) .ge. 0) .and. (lam(alpha,4) .lt. 1) ) then
  
          mu(alpha,4)=(x4+(lam(alpha,4))*x14)/a
  
      else
  
          mu(alpha,4)=100000
  
      end if
      
      
c       write(*,*) lam(alpha,1), "   ", mu(alpha,1), "  ", 
c     . lam(alpha,2), "   ", mu(alpha,2), "  ", lam(alpha,3),
c     . "   ", mu(alpha,3),"  ", lam(alpha,4),
c     . "   ", mu(alpha,4), "  ", phi 
 
c    Berechnung der Winkel, unter denen die Schnittpunkte des Abtaststrahls mit dem Detektorkanten (Viereck, das aus den vier 
c    eingegebenen Punkten aufgespannt wird) aus der Sicht des Beamvektors erscheinen. 
      i=1
      do  i=1,4,1
  
      if(mu(alpha,i) .ne. 100000) then
  
           if(mu(alpha,i) .gt. 0) then
   
                 beta(alpha,i)=atan(((((mu(alpha,i)*a)**2)+
     &           ((mu(alpha,i)*b)**2))**0.5)/bb)
     
           end if
     
           if(mu(alpha,i) .lt. 0) then
   
                 beta(alpha,i)=-atan(((((mu(alpha,i)*a)**2)+
     &           ((mu(alpha,i)*b)**2))**0.5)/bb)

           end if

      else
  
                 beta(alpha,i)=100000
      
      end if

      end do
      
      end do
      
      
c     Bestimmung der gamma[alpha][0]  und gamma[alpha][1]
c     Diese sind für ein bestimtes alpha die beiden Winkel, unter denen aus Sicht des Strahls der Eintritts bz. der Austrittspunkt in das bzw. 
c     aus dem Viereck liegen. Die gammas sind sozusagen die beiden von null verschiedenen betas für ein bestimmtes alpha.
c     Sind alle vier beta-Komponenten für ein bestimmtes alpha gleich null, so sind es die zugehörigen gammas auch.
c     Anschaulich bedeutet das dann ,dass der Abtaststrahl am Viereck vorbeigeht ohne ihn zu berühren.
c     In dem Fall erfolgt für solch ein beta keine Integration, bzw. eine Integration von null bis null (also null).
 
      do alpha=1,180,1
 
      j=1;
      
      do i=1,4,1
   
      if(beta(alpha,i)  .ne.  100000) then
   
           gamma(alpha,j) = beta(alpha,i)
    
           j=j+1
      
      end if
  
      end do
      
c     Falls der Abtaststrahl das Viereck nur streift, (d.h. wenn gamma[alpha][1]==0 ist) dann wird auch 
c     gamma[alpha][0] =0 gesetzt. De facto erfolgt für ein solches alpha keine Integration. 
  
      if(j .eq. 1) then
  
           gamma(alpha,1)=0
           gamma(alpha,2)=0

      end if  
c      write(*,*) alpha, "  ",  gamma(alpha,1), "  ", gamma(alpha,2)
c     Falls der Abtaststrahl das Viereck nur streift, (d.h. wenn gamma[alpha][1]==0 ist) dann wird auch 
c     gamma[alpha][0] =0 gesetzt. De facto erfolgt für ein solches alpha keine Integration.
c     if(gamma[alpha][1]==0)
c    {
c     gamma[alpha][0]=0;
c    }
c    So sah die obige Bedingung vorher aus. Weist einige Lücken auf. Die andere Methode ist sicherer. 
 
 
 
c    Die folgenden if Bedingungen dienen dazu, nicht weiter als im Winkelbereich 10*sigma zu integrieren.


c       if((((gamma(alpha,1)) .gt. 20*sigma) .and. ((gamma(alpha,2))
c     &   .gt. 20*sigma)) .or. (((-1*gamma(alpha,1)) .gt. 20*sigma)
c     &   .and. ((-1*gamma(alpha,2) .gt. 20*sigma)))) then
  
c            gamma(alpha,1)=0
c            gamma(alpha,2)=0
 
c       end if 
  
c       if((abs(gamma(alpha,1)) .gt. 20*sigma)
c     &   .and. (abs(gamma(alpha,2)) .gt. 20*sigma)) then
  
c            gamma(alpha,1)=signum(gamma(alpha,1))*20*sigma
c            gamma(alpha,2)=signum(gamma(alpha,2))*20*sigma

c       end if  
   
c       if((abs(gamma(alpha,1)) .gt. 20*sigma)
c     &   .and. (abs(gamma(alpha,2)) .le. 20*sigma)) then
  
c            gamma(alpha,1)=signum(gamma(alpha,1))*20*sigma
c       end if

  
c       if((abs(gamma(alpha,2)) .gt. 20*sigma)
c     &   .and. (abs(gamma(alpha,1)) .le. 20*sigma)) then
  
c           gamma(alpha,2)=signum(gamma(alpha,2))*20*sigma

c       end if
c      write(*,*) alpha,"  ",gamma(alpha,1),"  ",gamma(alpha,2)
      end do

      
c     Integration über die relevante Fläche (Viereck)
      
      result=0
      res1=0
      res2=0
 
      do alpha=1,180,1
 
 
      if(gamma(alpha,1) .gt. gamma(alpha,2)) then
  
           x=gamma(alpha,2)
           y=gamma(alpha,1)
      
      else 
  
           x=gamma(alpha,1)
           y=gamma(alpha,2)
  
      end if 
      g=defl
      z=sigma
      xx=x
      step=sigma*0.01
      do while (x .lt. y)
        if (defl .eq. 0.0) then
           res1=res1+abs(1/(4*pi*sigma**2
     &     *(1-0.137*sigma-2.57*sigma**2+2.85*sigma**3))
     &     *((1+x**2/(4*sigma**2))**(-2))*sin(x)*pi/180)
           x=x+step
        else
           res1=res1+abs((-(2*(-(g/z)+(x/z)))/(4+(-(g/z)+(x/z))**2)
     &       + 2*((g/z)+(x/z))/(4+((g/z)+(x/z))**2) 
     &       - atan(((x/z)-(g/z))/2)
     &       + atan(((x/z)+(g/z))/2))
     &       / (pi*z**2*(4*(g/z)
     &       + 0.5*pi*(12+(g/z)**2) 
     &       - (12+(g/z)**2)*atan(2*z/g)+(-4+(g/z)**2)*atan(g/(2*z))))
     &       * sin(x)*pi/180)
     &       /(0.998712-4.24825*z**2+9.92229*z**3-9.79119*z**4)
           x=x+step
c           write(*,*) "2 =", res1
        end if
c        write(*,*) alpha,"  ",result
      end do
     
      x=xx
      do while (x .lt. y+step)
        if (defl .eq. 0.0) then
           res2=res2+abs(1/(4*pi*sigma**2
     &     *(1-0.137*sigma-2.57*sigma**2+2.85*sigma**3))
     &     *((1+x**2/(4*sigma**2))**(-2))*sin(x)*pi/180)
           x=x+step
        else
           res2=res2+abs((-(2*(-(g/z)+(x/z)))/(4+(-(g/z)+(x/z))**2)
     &       + 2*((g/z)+(x/z))/(4+((g/z)+(x/z))**2) 
     &       - atan(((x/z)-(g/z))/2)
     &       + atan(((x/z)+(g/z))/2))
     &       / (pi*z**2*(4*(g/z)
     &       + 0.5*pi*(12+(g/z)**2) 
     &       - (12+(g/z)**2)*atan(2*z/g)+(-4+(g/z)**2)*atan(g/(2*z))))
     &       * sin(x)*pi/180)
     &       /(0.998712-4.24825*z**2+9.92229*z**3-9.79119*z**4)
           x=x+step
        end if
c        write(*,*) alpha,"  ",result
      end do

      result=((res1+res2)/2)*step
c      result=res1*step

c       write(*,*) alpha,"  ",gamma(alpha,1),"  ",gamma(alpha,2)
      end do
      
      RETURN
      END