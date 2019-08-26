       subroutine skalarprodukt(a1,a2,a3,b1,b2,b3,result) 

c    Berechnet das Skalarprodukt der 2 Vektoren die gegeben sind durch
c    a=(a1,a2,a3) und  b=(b1,b2,b3).

c    Calculates the scalar product "resukt" of the vectors a=(a1,a2,a3) and b=(b1,b2,b3).
       
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
     .      result
     
        result=(a1*b1+a2*b2+a3*b3)

        RETURN
        END