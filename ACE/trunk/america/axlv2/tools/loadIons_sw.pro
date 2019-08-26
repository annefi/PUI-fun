function loadIons_sw

;; array of structures

num_ions = 42

;; set up the structure
one_ion = { some_descriptive_name_here,$
      name: ''      , $
      element: ''   , $
      mass: 0.0     , $
      charge: 0       $        
      }

;; make an array of those structures
ions = replicate(one_ion, num_ions)

i = 0
ions[i].name = 'H+'
ions[i].element = 'H'
ions[i].mass = 1.0
ions[i].charge = 1
i++

ions[i].name = '3He2+'
ions[i].element = 'He'
ions[i].mass = 3.0
ions[i].charge = 2
i++

ions[i].name = 'He2+'
ions[i].element = 'He'
ions[i].mass = 4.0
ions[i].charge = 2
i++

ions[i].name = '12C4+'
ions[i].element = 'C'
ions[i].mass = 12.0
ions[i].charge = 4
i++

ions[i].name = '12C5+'
ions[i].element = 'C'
ions[i].mass = 12.0
ions[i].charge = 5
i++

ions[i].name = '12C6+'
ions[i].element = 'C'
ions[i].mass = 12.0
ions[i].charge = 6
i++

ions[i].name = '14N5+'
ions[i].element = 'N'
ions[i].mass = 14.0
ions[i].charge = 5
i++

ions[i].name = '14N6+'
ions[i].element = 'N'
ions[i].mass = 14.0
ions[i].charge = 6
i++

ions[i].name = '14N7+'
ions[i].element = 'N'
ions[i].mass = 14.0
ions[i].charge = 7
i++

ions[i].name = '16O6+'
ions[i].element = 'O'
ions[i].mass = 16.0
ions[i].charge = 6
i++

ions[i].name = '16O7+'
ions[i].element = 'O'
ions[i].mass = 16.0
ions[i].charge = 7
i++

ions[i].name = '20Ne7+'
ions[i].element = 'Ne'
ions[i].mass = 20.0
ions[i].charge = 7
i++

ions[i].name = '20Ne8+'
ions[i].element = 'Ne'
ions[i].mass = 20.0
ions[i].charge = 8
i++

ions[i].name = '22Ne7+'
ions[i].element = 'Ne'
ions[i].mass = 22.0
ions[i].charge = 7
i++

ions[i].name = '22Ne8+'
ions[i].element = 'Ne'
ions[i].mass = 22.0
ions[i].charge = 8
i++

ions[i].name = '24Mg5+'
ions[i].element = 'Mg'
ions[i].mass = 24.0
ions[i].charge = 5
i++


ions[i].name = '24Mg6+'
ions[i].element = 'Mg'
ions[i].mass = 24.0
ions[i].charge = 6
i++

ions[i].name = '24Mg7+'
ions[i].element = 'Mg'
ions[i].mass = 24.0
ions[i].charge = 7
i++

ions[i].name = '24Mg8+'
ions[i].element = 'Mg'
ions[i].mass = 24.0
ions[i].charge = 8
i++
ions[i].name = '24Mg9+'
ions[i].element = 'Mg'
ions[i].mass = 24.0
ions[i].charge = 9
i++

ions[i].name = '24Mg10+'
ions[i].element = 'Mg'
ions[i].mass = 24.0
ions[i].charge = 10
i++

ions[i].name = '28Si7+'
ions[i].element = 'Si'
ions[i].mass = 28.0
ions[i].charge = 7
i++

ions[i].name = '28Si8+'
ions[i].element = 'Si'
ions[i].mass = 28.0
ions[i].charge = 8
i++

ions[i].name = '28Si9+'
ions[i].element = 'Si'
ions[i].mass = 28.0
ions[i].charge = 9
i++

ions[i].name = '28Si10+'
ions[i].element = 'Si'
ions[i].mass = 28.0
ions[i].charge = 10
i++

ions[i].name = '28Si11+'
ions[i].element = 'Si'
ions[i].mass = 28.0
ions[i].charge = 11
i++

ions[i].name = '28Si12+'
ions[i].element = 'Si'
ions[i].mass = 28.0
ions[i].charge = 12
i++

ions[i].name = '32S7+'
ions[i].element = 'S'
ions[i].mass = 32.0
ions[i].charge = 7
i++

ions[i].name = '32S8+'
ions[i].element = 'S'
ions[i].mass = 32.0
ions[i].charge = 8
i++

ions[i].name = '32S9+'
ions[i].element = 'S'
ions[i].mass = 32.0
ions[i].charge = 9
i++

ions[i].name = '32S10+'
ions[i].element = 'S'
ions[i].mass = 32.0
ions[i].charge = 10
i++

ions[i].name = '32S11+'
ions[i].element = 'S'
ions[i].mass = 32.0
ions[i].charge = 11
i++

ions[i].name = '40Ar8+'
ions[i].element = 'Ar'
ions[i].mass = 40.0
ions[i].charge = 8
i++

ions[i].name = '40Ar9+'
ions[i].element = 'Ar'
ions[i].mass = 40.0
ions[i].charge = 9
i++

ions[i].name = '40Ar10+'
ions[i].element = 'Ar'
ions[i].mass = 40.0
ions[i].charge = 10
i++

ions[i].name = '40Ar11+'
ions[i].element = 'Ar'
ions[i].mass = 40.0
ions[i].charge = 11
i++

ions[i].name = '56Fe9+'
ions[i].element = 'Fe'
ions[i].mass = 56.0
ions[i].charge = 9
i++

ions[i].name = '56Fe10+'
ions[i].element = 'Fe'
ions[i].mass = 56.0
ions[i].charge = 10
i++

ions[i].name = '56Fe11+'
ions[i].element = 'Fe'
ions[i].mass = 56.0
ions[i].charge = 11
i++

ions[i].name = '56Fe12+'
ions[i].element = 'Fe'
ions[i].mass = 56.0
ions[i].charge = 12
i++

ions[i].name = '56Fe13+'
ions[i].element = 'Fe'
ions[i].mass = 56.0
ions[i].charge = 13
i++

ions[i].name = '56Fe14+'
ions[i].element = 'Fe'
ions[i].mass = 56.0
ions[i].charge = 14
i++

msg = '-I- defined '+string(format='(I2)',i-1)+' ions'
message, /info, msg

return, ions
end

; sample usage
pro list_charges, ions=ions

ions = loadIons_sw()

for i=0,n_elements(ions)-1 do begin
  print, format='("ion ",A," has charge ",F6.2)',$
         ions[i].name, ions[i].charge
endfor


return
end
