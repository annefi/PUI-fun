from libacepy.newdutycycle import dutycycle

def dutyfunc(c,p,dduty,deriv,ia):
    # c -> constant parameters from meanvalues of obseervations
    v0=c[0]        # c[0] = proton velocity
    valf=c[1]      # c[1] = alfven velocity
    bxy=c[2]       # c[2] = bxy
    bz=c[3]        # c[3] = bz (normally set to 0.)
    axy=c[4]       # c[4] = axy aspect ang
    az=c[5]        # c[5] = az aspect ang
    dens=c[6]      # c[6] = density (not used for fitting yet -> could be set to e.g. 0.1)
    countspec=c[7] # c[7] = ion countspec (not used but has to be set!)
    ionname=c[8]   # c[8] = ion name
    ionmass=c[9]   # c[9] = ion mass
    ioncharge=c[10]# c[10] = ion charge
    effpath=c[11]  # c[11] = efficiency path
    # p -> parameters for fitting
    beampos=p[0] 
    pratio=p[1] 
    vthpara=p[2] 
    vthperp=p[3] 
    twoside=0   # twoside = 0 -> one side derivatives (to save computing time);twoside = 1 -> two side derivatives
    

    # calc dutycycle
    dutyc=dutycycle(v0,beampos*valf,(1-beampos)*valf,bxy,bz,axy,az,dens,pratio,vthpara,vthperp/vthpara,countspec,ionname,ionmass,ioncharge,effpath)
    dutyc.calc_duty_cycle()
    dv=(dutyc.vsvel-v0)/valf
    vth=dutyc.vsvth

    # calc derivatives
    if (deriv==1):
        if (ia[0]==1):
            if (twoside==1):
                deltabpos=0.02
            else:
                deltabpos=0.04
            pdbeampos=dutycycle(v0,(beampos+deltabpos)*valf,(1.-beampos-deltabpos)*valf,bxy,bz,axy,az,dens,pratio,vthpara,vthperp/vthpara,countspec,ionname,ionmass,ioncharge,effpath)
            if (twoside==1):
                mdbeampos=dutycycle(v0,(beampos-deltabpos)*valf,(1.-beampos+deltabpos)*valf,bxy,bz,axy,az,dens,pratio,vthpara,vthperp/vthpara,countspec,ionname,ionmass,ioncharge,effpath)
            pdbeampos.calc_duty_cycle()
            if (twoside==1):
                mdbeampos.calc_duty_cycle()
                dduty[0][0]=((pdbeampos.vsvel-mdbeampos.vsvel)/valf)/(2*deltabpos)
                dduty[0][1]=((pdbeampos.vsvth-mdbeampos.vsvth)/valf)/(2*deltabpos)
            else:
                dduty[0][0]=((pdbeampos.vsvel-dutyc.vsvel)/valf)/(deltabpos)
                dduty[0][1]=((pdbeampos.vsvth-dutyc.vsvth)/valf)/(deltabpos)


        if (ia[1]==1):
            if (twoside==1):
                deltapratio=0.02
            else:
                deltapratio=0.04

            pdpratio=dutycycle(v0,beampos*valf,(1.-beampos)*valf,bxy,bz,axy,az,dens,pratio+deltapratio,vthpara,vthperp/vthpara,countspec,ionname,ionmass,ioncharge,effpath)
            if (twoside==1):
                mdpratio=dutycycle(v0,beampos*valf,(1.-beampos)*valf,bxy,bz,axy,az,dens,pratio-deltapratio,vthpara,vthperp/vthpara,countspec,ionname,ionmass,ioncharge,effpath)
            pdpratio.calc_duty_cycle()
            if (twoside==1):
                mdpratio.calc_duty_cycle()
                dduty[1][0]=((pdpratio.vsvel-mdpratio.vsvel)/valf)/(2*deltapratio)
                dduty[1][1]=((pdpratio.vsvth-mdpratio.vsvth)/valf)/(2*deltapratio)
            else:
                dduty[1][0]=((pdpratio.vsvel-dutyc.vsvel)/valf)/(deltapratio)
                dduty[1][1]=((pdpratio.vsvth-dutyc.vsvth)/valf)/(deltapratio)

        if (ia[2]==1):
            if (twoside==1):
                deltavthpara=0.2
            else:
                deltavthpara=0.4
            pdvthpara=dutycycle(v0,beampos*valf,(1.-beampos)*valf,bxy,bz,axy,az,dens,pratio,vthpara+deltavthpara,vthperp/(vthpara+deltavthpara),countspec,ionname,ionmass,ioncharge,effpath)
            if (twoside==1):
                mdvthpara=dutycycle(v0,beampos*valf,(1.-beampos)*valf,bxy,bz,axy,az,dens,pratio,vthpara-deltavthpara,vthperp/(vthpara-deltavthpara),countspec,ionname,ionmass,ioncharge,effpath)
            pdvthpara.calc_duty_cycle()
            if (twoside==1):
                mdvthpara.calc_duty_cycle()
                dduty[2][0]=((pdvthpara.vsvel-mdvthpara.vsvel)/valf)/(2*deltavthpara)
                dduty[2][1]=((pdvthpara.vsvth-mdvthpara.vsvth)/valf)/(2*deltavthpara)
            else:
                dduty[2][0]=((pdvthpara.vsvel-dutyc.vsvel)/valf)/(deltavthpara)
                dduty[2][1]=((pdvthpara.vsvth-dutyc.vsvth)/valf)/(deltavthpara)

        if (ia[3]==1):
            if (twoside==1):
                deltavthperp=0.2
            else:
                deltavthperp=0.4
            pdvthperp=dutycycle(v0,beampos*valf,(1.-beampos)*valf,bxy,bz,axy,az,dens,pratio,vthpara,(vthperp+deltavthperp)/vthpara,countspec,ionname,ionmass,ioncharge,effpath)
            if (twoside==1):
                mdvthperp=dutycycle(v0,beampos*valf,(1.-beampos)*valf,bxy,bz,axy,az,dens,pratio,vthpara,(vthperp-deltavthperp)/vthpara,countspec,ionname,ionmass,ioncharge,effpath)
            pdvthperp.calc_duty_cycle()
            if (twoside==1):
                mdvthperp.calc_duty_cycle()
                dduty[3][0]=((pdvthperp.vsvel-mdvthperp.vsvel)/valf)/(2*deltavthperp)
                dduty[3][1]=((pdvthperp.vsvth-mdvthperp.vsvth)/valf)/(2*deltavthperp)
            else:
                dduty[3][0]=((pdvthperp.vsvel-dutyc.vsvel)/valf)/(deltavthperp)
                dduty[3][1]=((pdvthperp.vsvth-dutyc.vsvth)/valf)/(deltavthperp)
    return [dv,vth]
