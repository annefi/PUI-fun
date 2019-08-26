; Filename: read_pcc.pro
;
; Description:
;   Read prob. center comparison (pcc) file into an intelligently
;   organized structure.  Returns array of pcc structures where index
;   is simply number of the structure (not E/q step for example).
;
; Author: Jim Raines (jmr)
;
; Method:
;
; Arguments
;   file -- name of a file in the fmcomp format, produced by axlv2_daily
;   or axfmtweak (or the like).
;
;   pcc -- array of pcc structures, one for each ion at each step
;
;   ions -- list of unique ions contained in pcc array (above)
;
;   eqtab -- E/q table indexed by step
;  
; Revision controlled by CVS:
; $Id: read_pcc.pro,v 1.1 2003/11/21 19:06:59 jraines Exp $
;
; Major Modification History
;   20Nov2003   jmr   Adapted from read_fmcomp.pro
;
pro read_pcc, file=file, pcc=pcc, ions=pcc_ions, eqtab=eoqtable
; eqtab un-needed?

;; read center data
if (not keyword_set(file)) then pccfile = 'axlv2_pccomp.dat'
restore, file='axlv2_pccomp_template.save'
pcc_bycol = read_ascii(file,template=template)

;; build unique list of pcc ions -- needed to figure out number of pcc ions
pcc_ions = pcc_bycol.ion(sort(pcc_bycol.ion ))   ; sort pcc_ions
pcc_ions = pcc_ions(uniq(pcc_ions))         ; remove duplicates
npcc_ions = n_elements(pcc_ions)        ; store number of pcc_ions

;; re-organize forward model data into array of structures
;; -------------------------------------------------------
;; This organization, rather than the structure of arrays as read in
;; by read_ascii, makes misalignments (e.g. pairing ion with wrong
;; tof, esd, etc.) more much difficult

;; define structure
pcc_element = $
                 { pcc,       $ ;name of structure
                   step: 0,    $ ;deflection voltage step (DVS)
                   eoq: 0.0,   $ ;E/q
                   ion: '',    $ ;name of ion (e.g. He1+, Fe15+)
                   tof: 0.0,   $ ;prob. center (pc) in time of flight dim.
                   tofsig: 0.0,$ ;pc tof sigma (1/2 width of gaussian)
                   esd: 0.0,   $ ;prob. center (pc) in SSD energy (esd) dim.
                   esdsig: 0.0,$ ;pc esd sigma (1/2 width of gaussian)
                   prate: 0.0  $ ;probabilistic rate
                 }

;; build array of structures
pcc = replicate( pcc_element, n_elements(pcc_bycol.ion))

;; fill structures in pcc array
for i=0,n_elements(pcc_bycol.ion)-1 do begin
  pcc[i].step = pcc_bycol.edb[i]
  pcc[i].eoq  = pcc_bycol.eoq[i]
  pcc[i].ion  = pcc_bycol.ion[i]
  pcc[i].tof  = pcc_bycol.tof[i]
  pcc[i].tofsig  = pcc_bycol.tofsig[i]
  pcc[i].esd  = pcc_bycol.esd[i]
  pcc[i].esdsig  = pcc_bycol.esdsig[i]
  pcc[i].prate  = pcc_bycol.prate[i]
endfor

return
end
