def calc_moments(time,v,cr,tbins):
    index=searchsorted(tbins,time)-1
    H,x,y=histogram2d(time,v,bins=[tbins,unique(v)],weights=cr)
    bc=sum(H,axis=1)
    H2,x,y=histogram2d(time,v,bins=[tbins,unique(v)],weights=cr*v)
    bv=sum(H2,axis=1)/sum(H,axis=1)
    H3,x,y=histogram2d(time,v,bins=[tbins,unique(v)],weights=cr*(v-bv[index])**2)
    bvth=sqrt(sum(H3,axis=1)/sum(H,axis=1))
    return bc,bv,bvth
