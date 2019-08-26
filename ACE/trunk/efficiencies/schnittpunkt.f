       subroutine schnittpunkt(x1,x2,x3,y1,y2,y3,
     &  a1,a2,a3,b1,b2,b3,c1,c2,c3,s1,s2,s3) 
    

c    Berechnet den Schnittpunkt zwischen Gerade gegeben durch Aufpunkt x und Richtungsvektor y
c    und einer Ebene aufgespannt durch die Punkte a,b und c.

c    Calculates the point of intersection between the straight line "x+t*y" and the plane given 
c    by the points a,b, and c. 

       real*4
     .  x(3),
     .  y(3),
     .  a(3),
     .  b(3),
     .  c(3),
     .  aux(6),
     .  n(3),
     .  ne(3),
     .  d,
     .  t
      
        x(1)=x1
        x(2)=x2
        x(3)=x3
        y(1)=y1
        y(2)=y2
        y(3)=y3
        a(1)=a1
        a(2)=a2
        a(3)=a3
        b(1)=b1
        b(2)=b2
        b(3)=b3
        c(1)=c1
        c(2)=c2
        c(3)=c3
     
        
        aux(1)=b(1)-a(1)
        aux(2)=b(2)-a(2)
        aux(3)=b(3)-a(3)
        aux(4)=c(1)-a(1)
        aux(5)=c(2)-a(2)
        aux(6)=c(3)-a(3)
        
        call kreuzprodukt(aux(1),aux(2),aux(3),aux(4),aux(5),
     &       aux(6),n(1),n(2),n(3))
     
c        write(*,*) aux(1),aux(2),aux(3),aux(4),aux(5),aux(6)
c        write(*,*) n(1),n(2),n(3)
        call evektor(n(1),n(2),n(3),ne(1),ne(2),ne(3))
c        write(*,*) ne(1),ne(2),ne(3)
        call skalarprodukt(ne(1),ne(2),ne(3),-a(1),-a(2),-a(3),d)
c        write(*,*) d
        if(ne(1)*y(1)+ne(2)*y(2)+ne(3)*y(3) .ne. 0.0) then
        t=-(ne(1)*x(1)+ne(2)*x(2)+ne(3)*x(3)+d)/(ne(1)*y(1)+
     &      ne(2)*y(2)+ne(3)*y(3))
c        write(*,*) t
        else 
        write(*,*) "Ionenstrahl ist parallel zur Detektorebene!"
        write(*,*) "Kein Schnittpunkt!"
        end if
        s1=x(1)+t*y(1)
        s2=x(2)+t*y(2)
        s3=x(3)+t*y(3)
 
        RETURN
        END