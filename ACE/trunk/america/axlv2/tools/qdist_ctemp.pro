; Filename: qdist_ctemp.pro
;
; Description:
;   Fit input charge distribution to a coronal temperature using the
;   code of Mazzotta, et. al..  
;
; Author: Jim Raines (jmr)
;
; Method:
;
;   
; Revision controlled by CVS:
; $Id: qdist_ctemp.pro,v 1.1 2005/04/26 18:41:41 jraines Exp $
;
; Major Modification History
;   25Apr2005   jmr   initial coding
;
; Arguments:
;
; I/O Arg         Explanation
; --- ----------  -----------
; I   z           atomic number for element
; I   relab       array of relative abundances
; O   [returned]  coronal temperature
; [I] itmax       optionally specify max. number of iterations
;                 (default: 20)
function qdist_ctemp, z=z, relab=relab, itmax=itmax

thisprog = 'qdist_ctemp'

if (not keyword_set(itmax)) then itmax=20

z_arr = make_array(n_elements(relab), /float, value=z)

;; initial quess for ctemp
ctemp = 1.0e6
;weights = 1.0/relab
weights = make_array(n_elements(relab), /float, value=1.0)

fit_relab = curvefit( z_arr, relab, weights, ctemp, /noderivative, $
function='mazzotta_fit', status=status, itmax=itmax)

if (status ne 0) then begin
  msg = ''
  if (status eq 1) then msg = 'Chi Sq increased without bound' $
  else if (status eq 2) then msg = 'Failed to converge in '+ $
    string(format='(I3)',itmax)+' iterations'

  print, thisprog+' -F- fit failed.  '+msg
  ctemp = -1.
endif

return, ctemp
end

; Filename: mazzotta_fit.pro
;
; Description:
;   
;
; Author: Jim Raines (jmr)
;
; Method:
;   Runs code of Mazzotta, et. al., as external process
;   
; Revision controlled by CVS:
; $Id: qdist_ctemp.pro,v 1.1 2005/04/26 18:41:41 jraines Exp $
;
; Major Modification History
;   25Apr2005   jmr   initial coding
;
; Arguments:
;
; I/O Arg         Explanation
; --- ----------  -----------
; I   z           atomic number for element
; I   ctemp       coronal temperature
; O   relab       array of relative abundances
; I   PDER        (not used, present only to keep curvefit happy)
pro mazzotta_fit, z_arr, ctemp, relab, PDER

z = z_arr[0]

;; location of code
MDIR = '/shrg1/local/mazzotta'

;; run Mazzotta code
;; note: cd is so code can find shared library, simplest way
cmd = 'cd '+MDIR+'; ./mazzotta '+string(z)+' '+string(ctemp)
spawn, cmd, result

;; extract relative abundances from command output
relab = float(strsplit(result, /extract))

return
end

