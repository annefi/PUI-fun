       subroutine kreuzprodukt(a1,a2,a3,b1,b2,b3,c1,c2,c3) 

c    Berechnet das Kreuzprodukt der 2 Vektoren die gegeben sind durch
c    a=(a1,a2,a3) und  b=(b1,b2,b3)
c    Calculates the cross product c=(c1,c2,c3) of the vectors 
c    a=(a1,a2,a3) and  b=(b1,b2,b3)
        real*4
     .      a1,
     .      a2,
     .      a3,
     .      b1,
     .      b2,
     .      b3,
     .      c1,
     .      c2,
     .      c3,
     .      aux1,
     .      aux2,
     .      aux3,
     .      result
     
        c1=a2*b3-a3*b2
        c2=a3*b1-a1*b3
        c3=a1*b2-a2*b1

        RETURN
        END