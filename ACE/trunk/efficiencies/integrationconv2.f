       subroutine integrationconv2(a1,a2,a3,b1,b2,b3,c1,c2,c3,
     &            d1,d2,d3,p1,p2,p3,v1,v2,v3,sigmal,sigmag,
     &            defl,bwl,bwg)
       
       
       real*4
     . a(3),   ! Eckpunkt a des Detektors, b, c und d analog
     . b(3),
     . c(3),
     . d(3),
     . ab(3),  ! ab ist der Vektor, der a und b verbindet
     . bc(3),  ! bc, cd und da analog
     . cd(3),
     . da(3),
     . v(3),   ! Ionenstrahlvektor
     . ve(3),  ! normierter Ionenstrahlvektor
     . sp,     ! Skalarprodukt zwischen v und ve
     . p(3),   ! Durchstosspunkt des Ionenstrahls durch die Folie
     . sigmal, ! Sigma des Lorenzprofils nach der Folie
     . sigmag, ! Sigma des Gaussprofils nach der Folie
     . bwl,    ! bwl=berechneter wert für einen lorentz
     . bwg,    ! bwg=berechneter wert für einen gauss
     . s(3),   ! Auftreffpunkt des Strahls auf den Detektor
     . n(3),   ! Normalenvektor auf der Detektorfläche
     . ne(3),  ! normierter n(3)
     . ps(3),  ! Vektor von p zu s
     . psb,    ! Entfernung von s zu p
     . auxa(3),! Vektor, der p und a verbindet, auxb, auxc und auxd analog
     . auxb(3),
     . auxc(3),
     . auxd(3),
     . ta,     ! Prameter zur Darstellung der Geraden mit Aufpunkt p und Richtungsvektor auxa
     . tb,     ! tb, tc und td analog
     . tc,
     . td,
     . sa(3),  ! Schnittpunkt zwischen der Ebene, die senkrecht auf ve steht
     . sb(3),  ! in der Entfernung psb von p, und dem Vektor, der p und a verbindet.
     . sc(3),  ! sb,sc und sd analog
     . sd(3),
     . ae(3),  ! ae ist der Vektor, der s und sa verbindet, also von s nach sa.
     . be(3),  ! be, ce und de analog
     . ce(3),
     . de(3),
     . aev,    ! aev ist der Betrag von ae
     . bev,    ! bev, cev und dev analog
     . cev,
     . dev,
     . beta,   ! beta ist der Winkel zwischen ae und be, rechtsdrehend
     . gamma,  ! gamma ist der Winkel zwischen ae und ce, rechtsdrehend
     . delta,  ! delta ist der Winkel zwischen ae und de, rechtsdrehend
     . abk(3), ! abk ist das kreuzprodukt aus ae und be
     . ack(3), ! abk ist das kreuzprodukt aus ae und ce
     . adk(3), ! abk ist das kreuzprodukt aus ae und de
     . pi,     ! pi
c     . wpa,    ! Winkel zwischen p und auxa
c     . wpb,    ! Winkel zwischen p und auxb
c     . wpc,    ! Winkel zwischen p und auxc
c     . wpd,    ! Winkel zwischen p und auxd
     . ai(2),  ! ai, bi, ci und di sind die Übergabewerte für die Integrationsroutine
     . bi(2),  ! integrall.f
     . ci(2),
     . di(2),
     . h(10)
     
       integer
     . i,j,k
     
       a(1)=a1
       a(2)=a2
       a(3)=a3
       b(1)=b1
       b(2)=b2
       b(3)=b3
       c(1)=c1
       c(2)=c2
       c(3)=c3
       d(1)=d1
       d(2)=d2
       d(3)=d3
       p(1)=p1
       p(2)=p2
       p(3)=p3
       v(1)=v1
       v(2)=v2
       v(3)=v3
       pi=3.1415927
       
c       write(*,*) sigmal,"<-sigmal sigmag->", sigmag
       do i=1,3,1
       auxa(i)=a(i)-p(i)
       auxb(i)=b(i)-p(i)
       auxc(i)=c(i)-p(i)
       auxd(i)=d(i)-p(i)
       ab(i)=b(i)-a(i)
       bc(i)=c(i)-b(i)
       cd(i)=d(i)-c(i)
       da(i)=a(i)-d(i)                    
       end do
       
c       write(*,*) (auxa(i), i=1,3)
c       write(*,*) (auxb(i), i=1,3)
c       write(*,*) (auxc(i), i=1,3)      
c       write(*,*) (auxd(i), i=1,3)

c       write(*,*) (ab(i), i=1,3)
c       write(*,*) (bc(i), i=1,3)
c       write(*,*) (cd(i), i=1,3)      
c       write(*,*) (da(i), i=1,3)         

       call schnittpunkt(p1,p2,p3,v1,v2,v3,a1,a2,a3,
     &      b1,b2,b3,c1,c2,c3,s(1),s(2),s(3))
c       write(*,*) s(1), s(2), s(3)

       do i=1,3,1
       ps(i)=s(i)-p(i)
       end do
       
       call betrag(ps(1),ps(2),ps(3),psb)
       
c       write(*,*) "psb", psb

       call evektor(v(1),v(2),v(3),ve(1),ve(2),ve(3))
c       write(*,*) "ve  ", ve(1), ve(2), ve(3)          
           
  
       call skalarprodukt(ve(1),ve(2),ve(3),s(1),s(2),s(3),sp)
c       write(*,*) "sp  ", sp
       
c      Zur Erklärung der folgenden if-Bedingungen siehe:
c      http://theorie.informatik.uni-ulm.de/Lehre/WS9798/Computergrafik/Engels/node6.html       
  
       if(ve(1)*auxa(1)+ve(2)*auxa(2)+ve(3)*auxa(3) .ne. 0.0) then
       ta=-(ve(1)*p(1)+ve(2)*p(2)+ve(3)*p(3)-sp)/(ve(1)*auxa(1)+
     &     ve(2)*auxa(2)+ve(3)*auxa(3))
       else 
       write(*,*) "Ionenstrahl ist parallel zum Vektor von p zu a!"
       write(*,*) "Kein Schnittpunkt!"
       end if
       
       if(ve(1)*auxb(1)+ve(2)*auxb(2)+ve(3)*auxb(3) .ne. 0.0) then
       tb=-(ve(1)*p(1)+ve(2)*p(2)+ve(3)*p(3)-sp)/(ve(1)*auxb(1)+
     &     ve(2)*auxb(2)+ve(3)*auxb(3))
       else 
       write(*,*) "Ionenstrahl ist parallel zum Vektor von p zu b!"
       write(*,*) "Kein Schnittpunkt!"
       end if
       
       if(ve(1)*auxc(1)+ve(2)*auxc(2)+ve(3)*auxc(3) .ne. 0.0) then
       tc=-(ve(1)*p(1)+ve(2)*p(2)+ve(3)*p(3)-sp)/(ve(1)*auxc(1)+
     &     ve(2)*auxc(2)+ve(3)*auxc(3))
       else 
       write(*,*) "Ionenstrahl ist parallel zum Vektor von p zu c!"
       write(*,*) "Kein Schnittpunkt!"
       end if
       
       if(ve(1)*auxd(1)+ve(2)*auxd(2)+ve(3)*auxd(3) .ne. 0.0) then
       td=-(ve(1)*p(1)+ve(2)*p(2)+ve(3)*p(3)-sp)/(ve(1)*auxd(1)+
     &     ve(2)*auxd(2)+ve(3)*auxd(3))
       else 
       write(*,*) "Ionenstrahl ist parallel zum Vektor von p zu d!"
       write(*,*) "Kein Schnittpunkt!"
       end if
       
c       write(*,*) "die t s", ta,tb,tc,td
       
       do i=1,3,1
       sa(i)=p(i)+ta*auxa(i)
       sb(i)=p(i)+tb*auxb(i)
       sc(i)=p(i)+tc*auxc(i)
       sd(i)=p(i)+td*auxd(i)
       end do
       
c       write(*,*) "s",(s(i), i=1,3)
c       write(*,*) "jetzt kommen die sa"     
c       write(*,*) (sa(i), i=1,3)
c       write(*,*) (sb(i), i=1,3)
c       write(*,*) (sc(i), i=1,3)      
c       write(*,*) (sd(i), i=1,3)         
              
       do i=1,3,1
       ae(i)=sa(i)-s(i)
       be(i)=sb(i)-s(i)       
       ce(i)=sc(i)-s(i)       
       de(i)=sd(i)-s(i)
       end do
       
c       write(*,*) "und jetzt die ae, be, ce, de"
c       write(*,*) (ae(i), i=1,3)
c       write(*,*) (be(i), i=1,3)
c       write(*,*) (ce(i), i=1,3)      
c       write(*,*) (de(i), i=1,3)         
       
       
       call betrag(ae(1),ae(2),ae(3),aev)
       call betrag(be(1),be(2),be(3),bev)
       call betrag(ce(1),ce(2),ce(3),cev)       
       call betrag(de(1),de(2),de(3),dev)
       
c       write(*,*) "aev und so weiter"
c       write(*,*) aev
c       write(*,*) bev
c       write(*,*) cev      
c       write(*,*) dev         
             
       
              
       call winkel(ae(1),ae(2),ae(3),be(1),be(2),be(3),beta)
       call winkel(ae(1),ae(2),ae(3),ce(1),ce(2),ce(3),gamma)   
       call winkel(ae(1),ae(2),ae(3),de(1),de(2),de(3),delta)
       call winkel(be(1),be(2),be(3),ce(1),ce(2),ce(3),h(1))
       call winkel(ce(1),ce(2),ce(3),de(1),de(2),de(3),h(2))       
       call winkel(de(1),de(2),de(3),ae(1),ae(2),ae(3),h(3))
       
c       write(*,*) "jippie", beta, h(1), h(2), h(3)      
       
             
       call kreuzprodukt(ae(1),ae(2),ae(3),be(1),be(2),be(3),
     &                  abk(1),abk(2),abk(3))
       call kreuzprodukt(ae(1),ae(2),ae(3),ce(1),ce(2),ce(3),
     &                  ack(1),ack(2),ack(3))       
       call kreuzprodukt(ae(1),ae(2),ae(3),de(1),de(2),de(3),
     &                  adk(1),adk(2),adk(3))
       
       
       do j=1,3,1
       if(v(j) .ne. 0.0) then
       i=j
       end if
       end do
       
c       write(*,*) beta, gamma, delta       
       
       if((abk(i)/v(i)) .lt. 0.0) then
       beta=(2*pi)-beta
       end if      
       
       if((ack(i)/v(i)) .lt. 0.0) then
       gamma=(2*pi)-gamma
       end if
       
       if((adk(i)/v(i)) .lt. 0.0) then
       delta=(2*pi)-delta
       end if
c       write(*,*) "beta, gamma, delta"
c       write(*,*) beta, gamma, delta
       
c       call winkel(p(1),p(2),p(3),auxa(1),auxa(2),auxa(3),wpa)
c       call winkel(p(1),p(2),p(3),auxb(1),auxb(2),auxb(3),wpb)
c       call winkel(p(1),p(2),p(3),auxc(1),auxc(2),auxc(3),wpc)              
c       call winkel(p(1),p(2),p(3),auxd(1),auxd(2),auxd(3),wpd)
       
       
       ai(1)=0.0
       ai(2)=aev
       call drehung(ai(1),ai(2),beta,bi(1),bi(2))
       call drehung(ai(1),ai(2),gamma,ci(1),ci(2))
       call drehung(ai(1),ai(2),delta,di(1),di(2))
       
       do i=1,2,1
       bi(i)=(bi(i)/aev)*bev     
       ci(i)=(ci(i)/aev)*cev
       di(i)=(di(i)/aev)*dev
       end do
       
c       write(*,*) (ai(i),i=1,2)
c       write(*,*) (bi(i),i=1,2)     
c       write(*,*) (ci(i),i=1,2)
c       write(*,*) (di(i),i=1,2)      
     
c      write(*,*) sigmag 
       call integrallconv2(ai(1),ai(2),bi(1),bi(2),ci(1),ci(2),
     &                di(1),di(2),sigmal,psb,defl,bwl)
      
       call integralg(ai(1),ai(2),bi(1),bi(2),ci(1),ci(2),
     &                di(1),di(2),sigmag,psb,bwg)
     
c       write(*,*) bwl,"  ",bwg
       
       return
       end
            
       
       