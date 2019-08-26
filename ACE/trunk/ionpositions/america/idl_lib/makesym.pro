From - Fri Jan 28 17:25:50 2000
Return-Path: <nathanas@engin.umich.edu>
Received: from srvr22.engin.umich.edu (srvr22.engin.umich.edu [141.213.75.21])
	by nightbreed.imap.itd.umich.edu (8.9.3/3.1i) with ESMTP id PAA01085
	for <jraines@j.imap.itd.umich.edu>; Fri, 21 Jan 2000 15:59:02 -0500 (EST)
Received: from ace.engin.umich.edu (nathanas@ace.engin.umich.edu [141.212.196.151])
	by srvr22.engin.umich.edu (8.9.1a/8.9.1) with ESMTP id PAA14199
	for <jraines@j.imap.itd.umich.edu>; Fri, 21 Jan 2000 15:59:01 -0500 (EST)
Received: (from nathanas@localhost)
	by ace.engin.umich.edu (8.9.1a/8.9.1) id PAA01865
	for jraines@j.imap.itd.umich.edu; Fri, 21 Jan 2000 15:59:01 -0500 (EST)
Date: Fri, 21 Jan 2000 15:59:01 -0500 (EST)
From: Nathan A Schwadron <nathanas@engin.umich.edu>
Message-Id: <200001212059.PAA01865@ace.engin.umich.edu>
To: jraines@j.imap.itd.umich.edu

;==============================
pro makesym,ind, fill = fill,scale=scale, color = color, thick = thick
;==============================
; 
; color = color
; fill = 1 to fill the symbol
; scale = 1.0 by default, otherwise scale the symbol
; 
; ind = 1 square
; ind = 2 triangle
; ind = 3 diamond
; ind = 4 circle

if keyword_set(scale) then unit = scale else unit = 1.0

if (ind eq 1) then begin
X = unit/2.0*[-1., -1., 1., 1., -1.]
Y = unit/2.0*[-1.,  1., 1., -1.,-1.]
end

if (ind eq 2) then begin
X = 1.5*unit*[-1./2., 0.,1./2., -1./2.] & y0 = sqrt(3.0)/4.0
Y = 1.5*unit*[-y0,    y0,  -y0, -y0   ]
end

if (ind eq 3) then begin
X = 1.5*unit/2.0*[-1., 0., 1., 0., -1.]
Y = 1.5*unit/2.0*[0., 1., 0., -1., 0.]
end

if (ind eq 4) then begin
A = FINDGEN(17) * (!PI*2/16.); Make a vector of 16 points, A[i] = 2pi/16.
X =  0.75*unit*COS(A)  &  Y =  0.75*unit*SIN(A)
end

USERSYM, X, Y, fill=fill,color=color,thick = thick

return
end
