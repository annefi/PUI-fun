Bx,By,Bz,time -> Arrays der gleichen Länge die Hochaufgelösten Magnetfeldkomponenten bzw. die Zeitstempel enthalten.
timebins -> Array das angibt über welche Zeiten das Magnetfeld gemittelt werden soll.

def transform_mag(Bx,By,Bz,time,timebins):
        indT=searchsorted(timebins,time)-1
        indT=indT[(indT>=0)*indT<timebins.shape[0]-1]
        nrT,x=histogram(time,timebins)
        meanBx,x=histogram(time,timebins,weights=Bx)
        meanBy,x=histogram(time,timebins,weights=By)
        meanBz,x=histogram(time,timebins,weights=Bz)
        meanb=array([meanBx/nrT,meanBy/nrT,meanBz/nrT]).T
        ebx=array([meanb[:,0]/(sqrt(meanb[:,0]**2+meanb[:,1]**2+meanb[:,2]**2)),meanb[:,1]/(sqrt(meanb[:,0]**2+meanb[:,1]**2+meanb[:,2]**2)),meanb[:,2]/(sqrt(meanb[:,0]**2+meanb[:,1]**2+meanb[:,2]**2))]).T
        by=array([0.,0.,1.])
        eby=cross(ebx,by)
        eby=array([eby[:,0]/sqrt(sum(eby**2,axis=1)),eby[:,1]/sqrt(sum(eby**2,axis=1)),eby[:,2]/sqrt(sum(eby**2,axis=1))]).T
        ebz=cross(ebx,eby)
        ebz=array([ebz[:,0]/sqrt(sum(ebz**2,axis=1)),ebz[:,1]/sqrt(sum(ebz**2,axis=1)),ebz[:,2]/sqrt(sum(ebz**2,axis=1))]).T
        Bxm=sum(ebx[indT]*array([Bx,By,Bz]).T,axis=1))
        Bym=sum(eby[indT]*array([Bx,By,Bz]).T,axis=1))
        Bzm=sum(ebz[indT]*array([Bx,By,Bz]).T,axis=1))
        # Hier ist die Transformation fertig im folgenden berechne ich noch dBxm. Per Definition enthalten Bym und Bzm schon die Wellen(Schwankungen) senkrecht zum Magnetfeld, da wir ja den mittleren Magnetfeldvektor als eBx verwendet haben. Bxm enthält nicht direkt die die Wellwn parallel zum Magnetfeld sondern trägt auch die Hauptinformation über den Mittleren Magnetfeldvektor in sich. dBxm enthält dementsrechend die Schwankungen bezüglich des mittleren Vektors in X-Richtung.
        nrT,x=histogram(time,timebins)
        meannbx,x=histogram(time,timebins,Bxm)
        meannbx=meannbx/nrT
        meannbx[isnan(meannbx)]=0.
        indT=searchsorted(timebins,time)-1
        indT=indT[(indT>=0)*indT<timebins.shape[0]-1]
        dBxm=Bxm-meannbx[indT]
        
        return Bxm,Bym,Bzm,dBxm
