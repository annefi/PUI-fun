       subroutine drehung(x1,x2,phi,y1,y2)
       
c      Dreht den Vektor x=(x1,x2) um den Winkel phi.
c      Der resultierende Vektor ist y=(y1,y2).
c      Rotates the vector x=(x1,x2) by the angle phi.
c      The resulting vector is y=(y1,y2).
       
       real*4
     . x1,
     . x2,
     . y1,
     . y2,
     . phi,
     . psi,
     . d,
     . pi
      
       pi=3.1415927
       d=pi/180.
     
       psi=phi
       y1=x1*cos(-psi)-x2*sin(-psi)
       y2=x1*sin(-psi)+x2*cos(-psi)

       
       return
       end