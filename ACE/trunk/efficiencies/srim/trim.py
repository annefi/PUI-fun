from template import TemplateReplace
def TRIM(el_name,atom_z,atom_m,energy,angle,num_ions,bragg_corr,asn,cascades,rns,reminders,
         do_ranges,do_backscatter,do_transmit,do_sputter,do_recoil,binding,surface,
         indi_disp,plot_type,x_min,x_max,target_z,target_m,thick,density):
    """ Calculates some weird ion stuff using TRIM. The output is an array which contains all the data in the following format:
    ... """

    repl=[("$el_name",el_name),
          ("$ATOM_Z", atom_z),
          ("$ATOM_M", atom_m),
          ("$ENERGY", energy),
          ("$ANGLE", angle),
          ("$NUM_IONS", num_ions),
          ("$BRAGG_CORR", bragg_corr),
          ("$ASN", asn),
          ("$CASCADES", cascades),
          ("$RNS", rns),
          ("$REMINDERS", reminders),
          ("$DO_RANGES", do_ranges),
          ("$DO_BACKSCATTER", do_backscatter),
          ("$DO_TRANSMIT", do_transmit),
          ("$DO_SPUTTER", do_sputter),
          ("$DO_RECOIL", do_recoil),
          ("$BINDING", binding),
          ("$SURFACE", surface),
          ("$INDI_DISP", indi_disp),
          ("$PLOT_TYPE", plot_type),
          ("$X_MIN", x_min),
          ("$X_MAX", x_max),
          ("$TARGET_Z", target_z),
          ("$TARGET_M", target_m),
          ("$THICK", thick),
          ("$DENSITY", density)]
          
    TemplateReplace(
        open("/home/kleopatra/mu/Desktop/swics/efficiencies/srim/template_TRIM.IN"),
#        open("/home/kleopatra/mu/.wine/drive_c/Programme/SRIM 2003/TRIM.IN", "w"),
        open("/home/kleopatra/mu/Desktop/swics/efficiencies/srim/trim.out", "w"),
        repl)

    # WICHTIG!!
    # HIER NOCH EINEN CHECK AUF BEREITS LAUFENDES TRIM EINBAUEN
    # (flock etc.)

    
#    system("wine ~/.wine/...Programme/.../TRIM.EXE")
    # A long time later
#    return parseTrim()

    
    # HIER ENDE DES TRIM LOCKS


#def parseTrim():
    ### Zerlege TRIM-Ausgabedatei
