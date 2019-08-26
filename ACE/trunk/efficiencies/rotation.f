       subroutine rotation(x1,x2,x3,v1,v2,v3,phi,y1,y2,y3)

c      Dreht den Vektor x=(x1,x2) um den Winkel phi.
c      Der resultierende Vektor ist y=(y1,y2).
c      Rotates the vector x=(x1,x2) by the angle phi.
c      The resulting vector is y=(y1,y2)

       real*4
     . x1,
     . x2,
     . x3,
     . y1,
     . y2,
     . y3,
     . v1,
     . v2,
     . v3,
     . phi,
     . a,
     . d,
     . pi

       pi=3.1415927
       d=pi/180.
       a=phi
       y1=(cos(a)+v1**2*(1-cos(a)))*x1 
     .    +(v1*v2*(1-cos(a))-v3*sin(a))*x2
     .    +(v1*v3*(1-cos(a))+v2*sin(a))*x3
       y2=(v2*v1*(1-cos(a))+v3*sin(a))*x1
     .    +(cos(a)+v2**2*(1-cos(a)))*x2
     .    +(v2*v3*(1-cos(a))-v1*sin(a))*x3
       y3=(v3*v1*(1-cos(a))-v2*sin(a))*x1
     .    +(v3*v2*(1-cos(a))+v1*sin(a))*x2
     .    +(cos(a)+v3**2*(1-cos(a)))*x3

       return
       end