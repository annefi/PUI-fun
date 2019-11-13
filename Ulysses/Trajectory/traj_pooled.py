from numpy import array, sqrt
from matplotlib import pylab
from ul_calc_traj import hc_to_hg, calc_v



# Paths to the two data files
path_h = "trajectory_data/helio.dat"
path_u = "trajectory_data/ulysses_daily_heliocentric_data_1990-2009.txt"

# Read in Helio.dat
year_h = []
doy_h = []
esp_h = []
spe_h = []
sep_h = []
r_h = []
hg_lat_h = []
hg_long_h = []
hc_lat_h = []
hg_long_wrt_earth_h = []

fin_h = open(path_h,'r')
for headerline in range(18):
    fin_h.readline()
for line in fin_h:
    data = line.split()
    year_h.append(float(data[0]))
    doy_h.append(float(data[1]))
    esp_h.append(float(data[5]))
    spe_h.append(float(data[6]))
    sep_h.append(float(data[7]))
    r_h.append(float(data[8]))
    hg_lat_h.append(float(data[9]))
    hg_long_h.append(float(data[10]))
    hc_lat_h.append(float(data[11]))
    hg_long_wrt_earth_h.append(float(data[12]))

fin_h.close()

# extend for calculation from beginning of 2007 (s.b.):
for i in range(6266,6814):
    year_h.append(0.)
    doy_h.append(0.)
    esp_h.append(0.)
    spe_h.append(0.)
    sep_h.append(0.)
    r_h.append(0.)
    hg_lat_h.append(0.)
    hg_long_h.append(0.)
    hc_lat_h.append(0.)
    hg_long_wrt_earth_h.append(0.)




# Read in ulysses_daily_heliocentric_data_1990-2009.txt
year_u = []
month_u = []
day_u = []
doy_u = []
jd_u = []
hour_u = []
min_u = []
sec_u = []
esp_u = []
spe_u = []
sep_u = []
r_u = []
r_km_u = []
v_u = []
hg_lat_u = []
hc_long_u = []
hc_lat_u = []
hg_long_wrt_earth_u = []



fin_u = open(path_u,'r')
for headerline in range(35):
    fin_u.readline()
for line in fin_u:
    data = line.split()
    year_u.append(float(data[0]))
    month_u.append(float(data[1]))
    day_u.append(float(data[2]))
    doy_u.append(float(data[4]))
    jd_u.append(float(data[5]))
    hour_u.append(float(data[6]))
    min_u.append(float(data[7]))
    sec_u.append(float(data[8]))
    esp_u.append(float(data[9]))
    spe_u.append(float(data[10]))
    sep_u.append(float(data[11]))
    r_u.append(float(data[12]))
    r_km_u.append(float(data[13]))
    v_u.append(float(data[15]))
    hg_lat_u.append(float(data[16]))
    hc_long_u.append(float(data[17]))
    hc_lat_u.append(float(data[18]))
    hg_long_wrt_earth_u.append(float(data[19]))

fin_u.close()

year_h = array(year_h)
doy_h = array(doy_h)
esp_h = array(esp_h)
spe_h = array(spe_h)
sep_h = array(sep_h)
r_h = array(r_h)
hg_lat_h = array(hg_lat_h)
hg_long_h = array(hg_long_h)
hc_lat_h = array(hc_lat_h)
hg_long_wrt_earth_h = array(hg_long_wrt_earth_h)
year_u = array(year_u)
month_u = array(month_u)
day_u = array(day_u)
doy_u = array(doy_u)
jd_u = array(jd_u)
hour_u = array(hour_u)
min_u = array(min_u)
sec_u = array(sec_u)
esp_u = array(esp_u)
spe_u = array(spe_u)
sep_u = array(sep_u)
r_u = array(r_u)
r_km_u = array(r_km_u)
v_u = array(v_u)
hg_lat_u = array(hg_lat_u)
hc_long_u = array(hc_long_u)
hc_lat_u = array(hc_lat_u)
hg_long_wrt_earth_u = array(hg_long_wrt_earth_u)


# year_h = array(year_h)
# doy_h = array(doy_h)
# esp_h = array(esp_h)
# spe_h = array(spe_h)
# sep_h = array(sep_h)
# r_h = array(r_h)
# hg_lat_h = array(hg_lat_h)
# hg_long_h = array(hg_long_h)
# hc_lat_h = array(hc_lat_h)
# hg_long_wrt_earth_h = array(hg_long_wrt_earth_h)
# year_u = array(year_u[:-548])
# month_u = array(month_u[:-548])
# day_u = array(day_u[:-548])
# doy_u = array(doy_u[:-548])
# jd_u = array(jd_u[:-548])
# hour_u = array(hour_u[:-548])
# min_u = array(min_u[:-548])
# sec_u = array(sec_u[:-548])
# esp_u = array(esp_u[:-548])
# spe_u = array(spe_u[:-548])
# sep_u = array(sep_u[:-548])
# r_u = array(r_u[:-548])
# r_km_u = array(r_km_u[:-548])
# v_u = array(v_u[:-548])
# hg_lat_u = array(hg_lat_u[:-548])
# hc_long_u = array(hc_long_u[:-548])
# hc_lat_u = array(hc_lat_u[:-548])
# hg_long_wrt_earth_u = array(hg_long_wrt_earth_u[:-548])



# __________ fill up data gap ______________
def fill_up_gap():
    '''
    No data in helio.dat for 20 days at the end of 2001, so HG long is missing there. Is getting calculated by
    hc_to_hg-function. Plot shows that the transition is smooth.
    '''
    for i in range(4057,4076):
        hc_arr = array([r_u[i],hc_long_u[i],hc_lat_u[i]])
        hg_arr = hc_to_hg(hc_arr, degree = True, long_shift = 180.)
        hg_long_h[i] = hg_arr[1]
#fill_up_gap()


# __________ fill up data end______________
def fill_up_end():
    '''
    No data in helio.dat for from end of 2007, so HG long is missing there. Is getting calculated by
    hc_to_hg-function.
    '''
    for i in range(6266,6814):
        hc_arr = array([r_u[i],hc_long_u[i],hc_lat_u[i]])
        hg_arr = hc_to_hg(hc_arr, degree = True, long_shift = 180.)
        hg_long_h[i] = hg_arr[1]
#fill_up_end()


# __________ calc velocities _______________

vr_list = []
vt_list = []
vn_list = []
v_abs = []
diff = []


def calc_velocities():
    '''
    calculates velocities vR, vR, vN and v_abs based on the difference of position of one measurement and the next.
    '''
    for i in range(len(year_u)-1):
        t = 24*60*60
        R_vec_1 = array([r_km_u[i], hg_long_h[i], hg_lat_u[i]])
        R_vec_2 = array([r_km_u[i + 1], hg_long_h[i + 1], hg_lat_u[i + 1]])
        print(R_vec_1, R_vec_2)
        vx, vy, vz = calc_v(R_vec_1, R_vec_2, t)
        #print(doy_u[i], r_u[i], vx)
        vr_list.append(vx)
        vt_list.append(vy)
        vn_list.append(vz)
        v_abs.append(sqrt(vx ** 2 + vy ** 2 + vz ** 2))
#calc_velocities()



# _________ MAIN: writing the file ______________

def write_new_file():
    fid_out = open('trajectory_data/traj_data_ulysses_pool2.dat','w')
    headline1 = 'Year   DOY MM DD     ESP   SPE    SEP       R       R_km       HC_Lat  HC_Long    HG_Lat HG_Long  ' \
                'HG_Long_wrtE  v     v_R    v_T    v_N\n'
    headline2 = '\t\t    [deg] [deg]  [deg]     [AU]     [km]       [deg]    [deg]      [deg]  [deg]      [deg]   ' \
                ' [km/s] [km/s] [km/s] [km/s]\n'
    fid_out.write(headline1)
    fid_out.write(headline2)
    fid_out.write('\n\n')
    for i in range(len(year_u)-1):
        fid_out.write('%i  %3i  %2i %2i  %6.2f %6.2f %6.2f     %4.3f %4.1f  '
                      '%6.2f  %6.2f     %6.2f  %6.2f      %5.2f    %5.2f  %5.2f  %5.2f  %5.2f \n' %(year_u[i], doy_u[i],
                                                                                           month_u[i],day_u[i],
                                                                     esp_u[i],spe_u[i],sep_u[i],r_u[i],r_km_u[i],
                                                                     hc_lat_u[i],hc_long_u[i],hg_lat_u[i],hg_long_h[i],
                                                                     hg_long_wrt_earth_u[i], v_abs[i], vr_list[i],vt_list[i], vn_list[i]))
    fid_out.close()









# # Overview plot ESP angle
# fig_esp = pylab.figure('esp')
# ax_esp = pylab.subplot(111)
# esp = esp_h - esp_u
# ax_esp.plot(range(len(esp)),esp)
# ax_esp.plot(range(len(esp)),esp_h)
# ax_esp.plot(range(len(esp)),esp_u)
#
# # Overview plot SPE angle
# fig_spe = pylab.figure('spe')
# ax_spe = pylab.subplot(111)
# spe = spe_h - spe_u
# ax_spe.plot(range(len(spe)),spe)
# ax_spe.plot(range(len(spe)),spe_h)
# ax_spe.plot(range(len(spe)),spe_u)
#
# # Overview angle SEP angle
# fig_sep = pylab.figure('sep')
# ax_sep = pylab.subplot(111)
# sep = sep_h - sep_u
# ax_sep.plot(range(len(sep)),sep)
# ax_sep.plot(range(len(sep)),sep_h)
# ax_sep.plot(range(len(sep)),sep_u)
#
# # Overview plot Radius from Sun
# fig_r = pylab.figure('R')
# ax_r = pylab.subplot(111)
# r = r_h - r_u
# ax_r.plot(range(len(r)),r)
# ax_r.plot(range(len(r)),r_h)
# ax_r.plot(range(len(r)),r_u)
#
# # Overview plot Heliographic Latitude
# fig_hg_lat = pylab.figure('hg_lat')
# ax_hg_lat = pylab.subplot(111)
# hg_lat = hg_lat_h - hg_lat_u
# ax_hg_lat.plot(range(len(hg_lat)),hg_lat)
# ax_hg_lat.plot(range(len(hg_lat)),hg_lat_h)
# ax_hg_lat.plot(range(len(hg_lat)),hg_lat_u)
#
# # Overview plot Heliocentric Latitude
# fig_hc_lat = pylab.figure('hc_lat')
# ax_hc_lat = pylab.subplot(111)
# hc_lat = hc_lat_h - hc_lat_u
# ax_hc_lat.plot(range(len(hc_lat)),hc_lat)
# ax_hc_lat.plot(range(len(hc_lat)),hc_lat_h)
# ax_hc_lat.plot(range(len(hc_lat)),hc_lat_u)
#
# # Overview plot Heliographic Longitude wrt Earth
# fig_hg_long_wrt_earth = pylab.figure('hg_long_wrt_earth')
# ax_hg_long_wrt_earth = pylab.subplot(111)
# hg_long_wrt_earth = hg_long_wrt_earth_h - hg_long_wrt_earth_u
# ax_hg_long_wrt_earth.plot(range(len(hg_long_wrt_earth)),hg_long_wrt_earth)
# ax_hg_long_wrt_earth.plot(range(len(hg_long_wrt_earth)),hg_long_wrt_earth_h)
# ax_hg_long_wrt_earth.plot(range(len(hg_long_wrt_earth)),hg_long_wrt_earth_u)
#
#
# pylab.show()