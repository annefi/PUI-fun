from os import system
from trim import TRIM
from scipy.linalg import inv
from scipy import zeros, Float, matrixmultiply
from Gnuplot import Gnuplot, GridData



p_data=zeros([100,1000],Float)

l=1
atom_data=open("/home/kleopatra/mu/.wine/drive_c/Programme/SRIM 2003/Data/ATOMDATA")
atom_name=[""]*95
for i in atom_data:
    data=i.split()
    if (l>=3 and l<=94):
        for k in range(1,2):
            atom_name[l]=data[k]
            print atom_name[l]
        for k in range(3,12):
            p_data[l,k]=float(data[k])
    l=l+1
#    print data
#    for j in range(5):
#        print ss[j]




for j in range(3,4):
    energy=10
    for m in range(1):
        print j
        el_name=atom_name[j]
        atom_z=p_data[j,3]
        atom_m=p_data[j,4]
        energy=int(energy*1.1)
        angle=0
        num_ions=100
        bragg_corr=0
        asn=10000
        cascades=1
        rns=0
        reminders=0
        do_ranges=1
        do_backscatter=0
        do_transmit=0
        do_sputter=0
        do_recoil=0
        binding=3
        surface=7.41
        indi_disp=28
        plot_type=0
        x_min=0
        x_max=100
        target_z=6
        target_m=12.011
        thick=100
        density=2.253



        TRIM(el_name,atom_z,atom_m,energy,angle,num_ions,bragg_corr,asn,cascades,rns,reminders,
         do_ranges,do_backscatter,do_transmit,do_sputter,do_recoil,binding,surface,
         indi_disp,plot_type,x_min,x_max,target_z,target_m,thick,density)
        
        system("kwrite")       
#        system("wine /home/kleopatra/mu/.wine/drive_c/Programme/SRIM 2003/TRIM.exe")
         
         
