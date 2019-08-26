       subroutine betrag(a1,a2,a3,b) 

c    Calculates the absolute value b of the vector a=(a1,a2,a3)       
c    Berechnet den Betrag b des Vektors a=(a1,a2,a3)
       real*4
     .  a1,
     .  a2,
     .  a3,
     .  b
     
     
        b=(a1**2+a2**2+a3**2)**0.5

        RETURN
        END