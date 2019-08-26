       subroutine winkel(a1,a2,a3,b1,b2,b3,omega) 

c    Berechnet den Winkel omega zwischen 2 Vektoren die gegeben sind durch
c    a=(a1,a2,a3) und  b=(b1,b2,b3)

c    Calculates the angle between the vectors a=(a1,a2,a3) and  b=(b1,b2,b3)


        real*4
     .      a1,
     .      a2,
     .      a3,
     .      b1,
     .      b2,
     .      b3,
     .      aux1,
     .      aux2,
     .      aux3,
     .      omega
          
        aux1=(a1**2+a2**2+a3**2)**0.5
        aux2=(b1**2+b2**2+b3**2)**0.5
        aux3=(a1*b1+a2*b2+a3*b3)
        omega=acos(aux3/(aux1*aux2))



        RETURN
        END