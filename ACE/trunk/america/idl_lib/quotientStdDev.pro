; Filename: quotientStdDev.pro
;
; Description:
;   Calculates the std. dev. (sigma) of a quotient of two data sets from their
;   respective sigmas.
;
; Author: Jim Raines (jmr)
;
; Method:
;   This is only strictly true if errors are random and independent.
;   J. Taylor, _Introduction to Error Analysis..._
;
;   If the errors are systematic, the error is more like
;     To divide A +/- sigmaA by B +/- sigmaB, the error is
;     Low:   (A - sigmaA)/(B + sigmaB)
;     High:  (A + sigmaA)/(B - sigmaB)
;   
; Major Modification History
;   21Feb2003   jmr   initial coding
;   24Feb2003   jmr   changed from variance to std. dev.
;
; Arguments:
;   num  -- numerator
;   snum -- sigma (std. dev.) of numerator
;   den  -- denominator
;   sden -- sigma of denominator
;   q    -- quotient
;   sq   -- (returned) sigma of quotient
function quotientStdDev, num,snum, den, sden, q

sq = sqrt(q^2*(snum^2/num^2 + sden^2/den^2))

return, sq
end
