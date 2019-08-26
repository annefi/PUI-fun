       subroutine evektor(a1,a2,a3,e1,e2,e3) 

c    Berechnet den Einheitsvektor e=(e1,e2,e3) des Vektors a=(a1,a2,a3).
c    Calculates the unit vector e=(e1,e2,e3) of the vector a=(a1,a2,a3). 
       real*4
     .  a1,
     .  a2,
     .  a3,
     .  e1,
     .  e2,
     .  e3,
     .  betrag
     
     
        betrag=(a1**2+a2**2+a3**2)**0.5
        e1=a1/betrag
        e2=a2/betrag
        e3=a3/betrag

        RETURN
        END