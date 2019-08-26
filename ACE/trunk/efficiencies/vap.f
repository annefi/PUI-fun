       subroutine vap(a1,a2,a3,b1,b2,b3,c1,c2,c3,d1,d2,d3) 

c    Gegeben seien drei Punkte (hier a,b und c)
c    Diese Punkte spannen eine Ebene auf.
c    vap berechnet den Punkt d (verschobener Punkt a), der sich ergibt, wenn
c    man die Seiten (b-a) und (c-a) um eine Einheit nach aussen verschiebt.

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
     .      d1,
     .      d2,
     .      d3,
     .      aux1(3),
     .      aux2(3),
     .      eaux1(3),
     .      eaux2(3),
     .      omega,
     .      x,
     .      result
     
        aux1(1)=b1-a1
        aux1(2)=b2-a2
        aux1(3)=b3-a3

        aux2(1)=c1-a1
        aux2(2)=c2-a2
        aux2(3)=c3-a3

        call winkel(aux1(1),aux1(2),aux1(3),
     .              aux2(1),aux2(2),aux2(3),omega)
        
        call evektor(aux1(1),aux1(2),aux1(3),eaux1(1),eaux1(2),eaux1(3))
        call evektor(aux2(1),aux2(2),aux2(3),eaux2(1),eaux2(2),eaux2(3))

        aux1(1)=-(eaux1(1)+eaux2(1))
	aux1(2)=-(eaux1(2)+eaux2(2))
	aux1(3)=-(eaux1(3)+eaux2(3))
        
        call evektor(aux1(1),aux1(2),aux1(3),aux2(1),aux2(2),aux2(3))
        
        
c       Die Seiten verschieben sich hier um x Einheiten nach aussen.
        x=1       
        d1=aux2(1)*x/sin(omega/2)
        d2=aux2(2)*x/sin(omega/2)
        d3=aux2(3)*x/sin(omega/2)
  
	d1=d1+a1
	d2=d2+a2
	d3=d3+a3
        RETURN
        END