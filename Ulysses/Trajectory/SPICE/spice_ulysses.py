"""
SPICE trajectory loader for Ulysses

Contains different functions to load Ulysses' trajectory data via SPICE (based on etspice), compare aspect angle
calculations and write the final trajectory file that is used for further data analysis
"""

import datetime
from typing import List
import numpy as np
import matplotlib.pyplot as plt
import sys
from Ulysses.Trajectory.spice_loader import *
from Ulysses.Trajectory.ul_coordinates_utils import *
from Ulysses.Trajectory.SPICE.plot_3d_uly import Plot_3d

# Constants:
km_per_AU = 1.495979e8

# Colours:
bg_blue = '#f2f3fa'
bg_red = '#fff5f8'
bg_creme = '#F4F2EC'
petrol_dk = '#0570b0'
petrol_lg = '#74a9cf'
red_dk = '#cb181d'
red_lg = '#fb6a4a'
gray = '#808080'

class TrajectoryUlysses():
    """
    :param TF: time frame, should be a list of start and end time as
        datetime.datetime objects (one year is assumed if list is empty or contains
        only start time) 
    :param RF: 2-element-list: [source, reference frame]. E.g. ['pool','EQ']
        If source == 'pool': possible reference frames: 'EQ' (equatorial BC1950, HG), 'EC' (ecliptic BC1950, HC)
        If source == 'SPICE': possible reference frames: (...)
    :param DT: time increment in seconds; default is 24 hours
    """
    def __init__(self, TF: List[datetime.datetime], RF: str = None, DT: int = None):
        if DT == None:
            DT = 60 * 60 * 24 # 24 h in seconds
        if len(TF) == 1:
            TF.append(datetime.datetime(TF[0].year+1,TF[0].month,TF[0].day,TF[0].hour))
        elif len(TF) == 0:
            TF = [datetime.datetime(1992,1,1), datetime.datetime(1993,1,1)]
            print("time frame set automatically to %s - %s" %(TF[0],TF[1]))
        self.times = timerange(TF[0],TF[1],DT)
        self.t_southpass = [datetime.datetime(1994, 9, 13), datetime.datetime(2000, 11, 27),
                            datetime.datetime(2007, 2, 7)]
        self.t_northpass = [datetime.datetime(1995, 7, 31), datetime.datetime(2001, 10, 13),
                            datetime.datetime(2008, 1, 14)]
        if RF == None:
            RF = 'EQ'
        self.RF = RF
        self.get_data()
        self.get_aa_data()
        self.get_eigen_vel()

    def get_data(self):
        paras = ['r', 'lat', 'long']
        self.data = {p:[] for p in paras}
        print('get data')

    def get_aa_data(self):
        paras_asp = ['asp_lat', 'asp_long', 'asp_tot']
        self.data.update({p:[] for p in paras_asp})
        print('get asp ang data')

    def get_eigen_vel(self):
        paras_eigenvel = ['vR','vT','vN','vabs']
        self.data.update({p: [] for p in paras_eigenvel})
        print("get eigen velocity data \n")

    def sync_times(self, alien_times, data):
        """ Synchronise the data set times with self.times

        No nearest neighbour sampling etc., just checking for coincidence.
        NaNs for gaps if alien_times has a lower resolution than self.times
        """
        data_sync = np.empty(len(self.times))
        data_sync[:] = np.nan
        mask_t = np.isin(self.times, alien_times)
        mask_at = np.isin(alien_times,self.times)
        data_sync[mask_t] = data[mask_at]
        return data_sync

    def plot_coords(self, axes = None):
        """Plot R, lat, long over time """ 
        # set up the plot:
        if axes is None:
            fig, axes = plt.subplots(nrows = 3, sharex = True)
        ### R ###
        axes[0].plot(self.times, self.data['r'], linestyle = 'None', marker = 'o', ms = 2., label = self.lbl, c = self.clr, alpha= 0.5)
        axes[0].set_xlim(self.times[0],self.times[-1])
        axes[0].set_ylim(0., 6.)
        axes[0].set_ylabel('R in AU')
        lg = axes[0].legend(loc='upper center', ncol=3, fontsize='small', bbox_to_anchor=(0.5, 1.3), fancybox=
                True, framealpha=1., facecolor= bg_creme, shadow=True)
        for legend_handle in lg.legendHandles:
                legend_handle._legmarker.set_markersize(6)
        ### LAT ###
        axes[1].plot(self.times, self.data['lat'], linestyle = 'None', marker = 'o', ms = 2., c = self.clr, alpha= 0.5)
        axes[1].set_ylabel('Lat. in deg.')
        axes[1].set_yticks([-90,-45,0,45,90])
        axes[1].set_ylim(-95,95)
        ### LONG ###
        axes[2].plot(self.times, self.data['long'], linestyle = 'None', marker = 'o', ms = 2., c = self.clr, alpha= 0.5)
        axes[2].set_ylabel('Long. in deg.')
        axes[2].set_yticks([-180,-90,0,90,180])
        axes[2].set_ylim(-185,185)
        # plot vertical lines at polar passes:
        for a in axes:
            a.vlines(self.t_southpass, ymin = -180, ymax = 360, color = gray , alpha = 0.5, linestyle =
            'dashed', linewidth = 1.5)
            a.vlines(self.t_northpass, ymin = -180, ymax = 360, color = gray, alpha = 0.5, linestyles = 'dashed',
                     linewidth = 1.5)
        plt.gcf().autofmt_xdate()
        plt.gcf().tight_layout()
        plt.gcf().align_ylabels()
        for ax in axes:
            ax.grid(True)
        plt.subplots_adjust(hspace=None)
        return axes

    def comp_coords(self, T, axes = None):
        """Plot difference between two sets of trajectory data for R, lat, long"""
        if axes is None:
            fig, axes = plt.subplots(nrows = 3, sharex = True)
        ### R ###
        axes[0].plot(self.times, self.data['r']- T.data['r'], linestyle = 'None', marker = 'o', ms = 1., label = "%s - %s" %(self.lbl, T.lbl))
        axes[0].set_xlim(self.times[0],self.times[-1])
        axes[0].set_ylabel(r'$\Delta$R in AU')
        axes[0].set_ylim(-0.01, 0.01)
        lg = axes[0].legend(loc='upper center', ncol=1, fontsize='small', bbox_to_anchor=(0.5, 1.3), fancybox=
                True, framealpha=1., facecolor= bg_creme, shadow=True)
        for legend_handle in lg.legendHandles:
                legend_handle._legmarker.set_markersize(6)
        ### LAT ###
        axes[1].plot(self.times, self.data['lat'] - T.data['lat'], linestyle = 'None', marker = 'o', ms = 1.)
        axes[1].set_ylabel(r'$\Delta$Lat. in deg.')
        #axes[1].set_ylim(-0.05,0.05)
        ### LONG ###
        axes[2].plot(self.times, self.data['long'] - T.data['long'], linestyle = 'None', marker = 'o', ms = 1.)
        axes[2].set_ylabel(r'$\Delta$Long. in deg.')
        #axes[2].set_ylim(-0.05,0.05)
        # plot vertical lines at polar passes:
        for a in axes:
            a.vlines(self.t_southpass, ymin=-180, ymax=360, color= gray , alpha=0.5, linestyle=
            'dashed', linewidth=1.5)
            a.vlines(self.t_northpass, ymin=-180, ymax=360, color= gray, alpha=0.5, linestyles='dashed',
                     linewidth=1.5)
        plt.gcf().autofmt_xdate()
        plt.gcf().tight_layout()
        plt.gcf().align_ylabels()
        for ax in axes:
            ax.grid(True)
            ax.hlines(y=0.0, xmin = self.times[0], xmax = self.times[-1], color = 'dimgray')
        plt.subplots_adjust(hspace=0.2)
        #axes[0].set_ylim(-0.01, 0.01)
        return axes

    def plot_aspangles(self, axes = None):
        """Plot aspect angles (total, latitude, longitude) over time"""
        # set up the plot:
        if axes is None:
            fig, axes = plt.subplots(nrows = 3, sharex = True)
        ### total ###
        axes[0].plot(self.times, self.data['r'], linestyle = 'None', marker = 'o', ms = 2., label = self.lbl, alpha= 0.5)
        axes[0].set_xlim(self.times[0],self.times[-1])
        axes[0].set_ylabel('Asp. tot. in deg')
        lg = axes[0].legend(loc='upper center', ncol=3, fontsize='small', bbox_to_anchor=(0.5, 1.3), fancybox=
                True, framealpha=1., facecolor= bg_creme, shadow=True)
        for legend_handle in lg.legendHandles:
                legend_handle._legmarker.set_markersize(6)
        ### ASP LAT ###
        axes[1].plot(self.times, self.data['asp_lat'], linestyle = 'None', marker = 'o', ms = 2., alpha= 0.5)
        axes[1].set_ylabel('Asp. Lat. in deg.')
        axes[1].set_yticks([-90,-45,0,45,90])
        axes[1].set_ylim(-95,95)
        ### ASP LONG ###
        axes[2].plot(self.times, self.data['asp_long'], linestyle = 'None', marker = 'o', ms = 2., alpha= 0.5)
        axes[2].set_ylabel('Asp. Long. in deg.')
        axes[2].set_yticks([-180,-90,0,90,180])
        axes[2].set_ylim(-185,185)
        # plot vertical lines at polar passes:
        for a in axes:
            a.vlines(self.t_southpass, ymin=-180, ymax=360, color= gray, alpha=0.5, linestyle=
            'dashed', linewidth=1.5)
            a.vlines(self.t_northpass, ymin=-180, ymax=360, color= gray, alpha=0.5, linestyles='dashed',
                     linewidth=1.5)
        plt.gcf().autofmt_xdate()
        plt.gcf().tight_layout()
        plt.gcf().align_ylabels()
        for ax in axes:
            ax.grid(True)
        plt.subplots_adjust(hspace=0.2)
        return axes

    def comp_aspangles(self, T, axes = None):
        """Plot difference between two sets of trajectory data for aspect angles"""
        if axes is None:
            fig, axes = plt.subplots(nrows = 3, sharex = True)
        ### total ###
        axes[0].plot(self.times, self.data['asp_tot']- T.data['asp_tot'], linestyle = 'None', marker = 'o', ms = 1., label = "%s - %s" %(self.lbl, T.lbl))
        axes[0].set_xlim(self.times[0],self.times[-1])
        axes[0].set_ylabel(r'$\Delta$ Asp. tot. in deg.')
        axes[0].set_ylim(-1, 1)
        lg = axes[0].legend(loc='upper center', ncol=1, fontsize='small', bbox_to_anchor=(0.5, 1.3), fancybox=
                True, framealpha=1., facecolor= bg_creme, shadow=True)
        for legend_handle in lg.legendHandles:
                legend_handle._legmarker.set_markersize(6)
        ### Aspect Angle LAT ###
        axes[1].plot(self.times, self.data['asp_lat'] - T.data['asp_lat'], linestyle = 'None', marker = 'o', ms = 1.)
        axes[1].set_ylabel(r'$\Delta$ Asp. Lat. in deg.')
        axes[1].set_ylim(-1,1)
        ### Aspect Angle LONG ###
        axes[2].plot(self.times, self.data['asp_long'] - T.data['asp_long'], linestyle = 'None', marker = 'o', ms = 1.)
        axes[2].set_ylabel(r'$\Delta$ Asp. Long. in deg.')
        axes[2].set_ylim(-1,1)
        # plot vertical lines at polar passes:
        for a in axes:
            a.vlines(self.t_southpass, ymin=-180, ymax=360, color= gray, alpha=0.5, linestyle=
            'dashed', linewidth=1.5)
            a.vlines(self.t_northpass, ymin=-180, ymax=360, color= gray, alpha=0.5, linestyles='dashed',
                     linewidth=1.5)
        plt.gcf().autofmt_xdate()
        plt.gcf().tight_layout()
        plt.gcf().align_ylabels()
        for ax in axes:
            ax.grid(True)
            ax.hlines(y=0.0, xmin = self.times[0], xmax = self.times[-1], color = 'dimgray')
        plt.subplots_adjust(hspace=0.2)
        return axes

    def plot_eigenvels(self, axes = None):
        """ Plot eigen-velocity RTN components over time """
        # set up the plot:
        if axes is None:
            fig, axes = plt.subplots(nrows = 4, sharex = True)
        ### vabs ###
        axes[0].plot(self.times, self.data['vabs'], linestyle = 'None', marker = 'o', ms = 2., alpha= 0.5, label = self.lbl)
        axes[0].set_ylabel('|v| in km/s')
        axes[0].set_ylim(-80,80)
        lg = axes[0].legend(loc='upper center', ncol=3, fontsize='small', bbox_to_anchor=(0.5, 1.3), fancybox=
                True, framealpha=1., facecolor= bg_creme, shadow=True)
        for legend_handle in lg.legendHandles:
                legend_handle._legmarker.set_markersize(6)
        ### vR ###
        axes[1].plot(self.times, self.data['vR'], linestyle = 'None', marker = 'o', ms = 2., alpha= 0.5)
        axes[1].set_xlim(self.times[0],self.times[-1])
        axes[1].set_ylabel('vR in km/s')
        axes[1].set_ylim(-80,80)
        ### vT ###
        axes[2].plot(self.times, self.data['vT'], linestyle = 'None', marker = 'o', ms = 2., alpha= 0.5)
        axes[2].set_ylabel('vT in km/s')
        #axes[1].set_yticks([-90,-45,0,45,90])
        axes[2].set_ylim(-80,80)
        ### vN ###
        axes[3].plot(self.times, self.data['vN'], linestyle = 'None', marker = 'o', ms = 2., alpha= 0.5)
        axes[3].set_ylabel('vN in km/s')
        axes[3].set_ylim(-80,80)
        # plot vertical lines at polar passes:
        for a in axes:
            a.vlines(self.t_southpass, ymin=-180, ymax=360, color= gray, alpha=0.5, linestyle=
            'dashed', linewidth=1.5)
            a.vlines(self.t_northpass, ymin=-180, ymax=360, color= gray, alpha=0.5, linestyles='dashed',
                     linewidth=1.5)
        plt.gcf().autofmt_xdate()
        plt.gcf().tight_layout()
        plt.gcf().align_ylabels()
        for ax in axes:
            ax.grid(True)
        plt.subplots_adjust(hspace=0.2)
        return axes

    def comp_eigenvels(self, T, axes = None):
        """Plot difference between two sets of Ulysses' eigen velocity in RTN"""
        if axes is None:
            fig, axes = plt.subplots(nrows = 4, sharex = True)
        ### vabs ###
        axes[0].plot(self.times, self.data['vabs']- T.data['vabs'], linestyle = 'None', marker = 'o', ms = 1.,
                     label = "%s - %s" %(self.lbl, T.lbl))
        axes[0].set_xlim(self.times[0],self.times[-1])
        axes[0].set_ylabel(r'$\Delta$ |v| in km/s')
        axes[0].set_ylim(-1, 1)
        lg = axes[0].legend(loc='upper center', ncol=1, fontsize='small', bbox_to_anchor=(0.5, 1.3), fancybox=
                True, framealpha=1., facecolor= bg_creme, shadow=True)
        for legend_handle in lg.legendHandles:
                legend_handle._legmarker.set_markersize(6)
        ### vR ###
        axes[1].plot(self.times, self.data['vR'] - T.data['vR'], linestyle = 'None', marker = 'o', ms = 1.)
        axes[1].set_ylabel(r'$\Delta$ vR in km/s')
        axes[1].set_ylim(-1,1)
        ### vT ###
        axes[2].plot(self.times, self.data['vT'] - T.data['vT'], linestyle = 'None', marker = 'o', ms = 1.)
        axes[2].set_ylabel(r'$\Delta$ vT in km/s')
        axes[2].set_ylim(-1,1)
        ### vN ###
        axes[3].plot(self.times, self.data['vN'] - T.data['vN'], linestyle = 'None', marker = 'o', ms = 1.)
        axes[3].set_ylabel(r'$\Delta$ vN in km/s')
        axes[3].set_ylim(-1,1)
        # plot vertical lines at polar passes:
        for a in axes:
            a.vlines(self.t_southpass, ymin=-180, ymax=360, color= gray, alpha=0.5, linestyle=
            'dashed', linewidth=1.5)
            a.vlines(self.t_northpass, ymin=-180, ymax=360, color= gray, alpha=0.5, linestyles='dashed',
                     linewidth=1.5)
        plt.gcf().autofmt_xdate()
        plt.gcf().tight_layout()
        plt.gcf().align_ylabels()
        for ax in axes:
            ax.grid(True)
            ax.hlines(y=0.0, xmin = self.times[0], xmax = self.times[-1], color = 'dimgray')
        plt.subplots_adjust(hspace=0.2)
        return axes

    def plot_3d(self, ax = None, cs = None, col = None):
        """ Creates a 3D-Plot of Ulysses' position for the loaded timeframe

        Todo: Docstring, axis freigeben, plot_point-Argumente übergeben können
        :return:
        """
        if cs == None:
            cs = self.RF
        if ax == None:
            p = Plot_3d()
        else:
            p = Plot_3d(ax = ax)
        ax3D = p.plot_point(coords = np.array([self.data['r'], self.data['lat'], self.data['long']]).T, cs = cs,
                            col = col)
        return ax3D

class SpiceTra(TrajectoryUlysses):
    """ Spice trajectory data instance

    :example: >> spice_t_hci = SpiceTra(TF=[dt1,dt2], RF = HCI, DT = 24*3600*10)
        (with dt1,dt2 being datetime.datetime objects)
    """
    def get_data(self):
        """ Add Ulysses trajectory data (R in AU, latitude and longitude in degrees) to data dictionary
        and set up the style for the data set 
        """
        super().get_data()
        for t in self.times:
            [R, lat, long] = locateUlysses(t, self.RF)
            self.data['r'].append(R)
            self.data['lat'].append(lat)
            self.data['long'].append(long)
        self.data['r'] = np.array(self.data['r'])
        self.data['lat'] = np.array(self.data['lat'])
        self.data['long'] = np.array(self.data['long'])
        self.lbl = 'SPICE %s' % self.RF.name
        if self.RF == ECLIPJ2000 or ECLIPB1950:
            self.clr = petrol_dk
        if self.RF == HCI:
            self.clr = red_dk

    def get_aa_data(self):
        """ Add Ulysses aspect angle data to data dictionary 

        The aspect angle is the angle between the line-of-sights SC-Sun and SC-Earth (which is the orientation line of Ulysses' antenna)
        measured from the SC.
        Calculated are the total ('flat') angle and the two spherical components in RTN-system (all in degrees):
        Aspect latitude is measured from -90° to +90°, where 0° is within the R-T-plane and +90° along the positive N-axis
        Aspect longitude is measured from -90° to +90°, where 0° is within the R-N-plane and +90° along the negative T-axis
            (i.e., positive asp_phi: "left" from the line-of-sight SC-Sun)
        """
        super().get_aa_data()
        if self.RF in [HCI, HCI_B, HCI_J]: # solar equatorial coord. sys.
            for t in self.times:
                vec_Ul = locateUlysses(t, self.RF)
                vec_Earth = locateBody(EARTH, t, self.RF)
                asp_theta, asp_phi = calc_asp_angles(vec_Ul, vec_Earth)
                self.data['asp_lat'].append(asp_theta)
                self.data['asp_long'].append(asp_phi)
                self.data['asp_tot'].append(calc_SPE(asp_theta, asp_phi))
        elif self.RF in [ECLIPJ2000, ECLIPB1950]: # ecliptic coord. sys.
            t_epoch = datetime.datetime(2000,1,1,12) if self.RF == ECLIPJ2000 else datetime.datetime(2000,1,1,12)+datetime.timedelta(days = (2433282.42345905-2451545.0))
            for t in self.times:
                vec_Ul = locateUlysses(t, self.RF)
                vec_Earth = locateBody(EARTH, t, self.RF)
                asp_theta, asp_phi = calc_asp_angles(hc_to_hg(vec_Ul, ang_ascnode = calc_delta(t_epoch)),
                                                     hc_to_hg(vec_Earth, ang_ascnode = calc_delta(t_epoch)))
                self.data['asp_lat'].append(asp_theta)
                self.data['asp_long'].append(asp_phi)
                self.data['asp_tot'].append(calc_SPE(asp_theta, asp_phi))
        else:
            sys.exit('Reference System %s not suitable for calculating Aspect Angles. \n Please use a solar equatorial or an Earth ecliptic system.' % self.RF)
        self.data['asp_lat'] = np.array(self.data['asp_lat'])
        self.data['asp_long'] = np.array(self.data['asp_long'])
        self.data['asp_tot'] = np.array(self.data['asp_tot'])

    def get_eigen_vel(self):
        """ Add Ulysses eigen-velocity (in RTN components) data to data dictionary """
        super().get_eigen_vel()
        for t in self.times:
            [vR, vT, vN] = velocityUlysses(t, self.RF.name)
            self.data['vR'].append(vR)
            self.data['vT'].append(vT)
            self.data['vN'].append(vN)
            self.data['vabs'].append(np.sqrt(vR**2 + vT**2 + vN**2))
        self.data['vR'] = np.array(self.data['vR'])
        self.data['vT'] = np.array(self.data['vT'])
        self.data['vN'] = np.array(self.data['vN'])
        self.data['vabs'] = np.array(self.data['vabs'])

    def rotate_to_EQ(self):
        """ Rotate a SpiceTra object in ECLIPB1950-RF manually to the HCI(EQ)-RF

        Just for testing! Label, RF etc. won't match anymore, positional coordinates will be overwritten
        """
        if self.RF.name == "ECLIPB1950":
            R = []
            lat = []
            long = []
            for t in range(len(self.data['r'])):
                vec_EC = np.array([self.data['r'][t],self.data['lat'][t],self.data['long'][t]])
                # exact epoch for BC1950:
                t_epoch = datetime.datetime(2000, 1, 1,12) + datetime.timedelta(days=(2433282.42345905 - 2451545.0))
                vec_rotated = hc_to_hg(vec_EC, ang_ascnode = calc_delta(t_epoch))
                R.append(vec_rotated[0])
                lat.append(vec_rotated[1])
                long.append(vec_rotated[2])
            self.data['r'] = R
            self.data['lat'] = lat
            self.data['long'] = long
        else:
            sys.exit('RF has to be \'EC\' for rotation to EQ')

class ArchiveTra(TrajectoryUlysses):
    """ Ulysses Archive trajectory data instance

    :example: >> arch_t_eq = SpiceTra(TF=[dt1,dt2], RF = "EQ", DT = 24*3600*10)
        (with dt1,dt2 being datetime.datetime objects)
    """
    def get_data(self):
        """ Load Ulysses daily position from the Ulysses Archive
        """
        super().get_data()
        pool_data = read_pool()
        if self.RF == 'EQ':
            # Equatorial System is mostly called HG (heliographic) within the archive files
            self.data['r'] = self.sync_times(pool_data['datetimes'], pool_data['R'])
            self.data['lat'] = self.sync_times(pool_data['datetimes'], pool_data['HG_Lat'])
            self.data['long'] = self.sync_times(pool_data['datetimes'], pool_data['HG_Long'])
            self.lbl = 'Ul. Archive Solar Eq.'
            self.clr = red_lg
        elif self.RF == 'EC':
            # Ecliptic System is mostly called HC (heliocentric) within the archive files
            self.data['r'] = self.sync_times(pool_data['datetimes'], pool_data['R'])
            self.data['lat'] = self.sync_times(pool_data['datetimes'], pool_data['HC_Lat'])
            self.data['long'] = self.sync_times(pool_data['datetimes'], pool_data['HC_Long'])
            self.lbl = 'Ul. Archive Ecliptic'
            self.clr = petrol_lg
        else:
            sys.exit("\nArgument RF not recognised. Has to be \'EQ\' or \'EC\' for pool data.\n")

    def get_aa_data(self):
        ''' 
        Load old AA from file for Archive data set
        '''
        super().get_aa_data()
        asp_data = load_aa_data()
        self.data['asp_lat'] = self.sync_times(asp_data['datetimes'], asp_data['ASP_THETA'])
        self.data['asp_long'] = self.sync_times(asp_data['datetimes'], asp_data['ASP_PHI'])
        self.data['asp_tot'] = self.sync_times(asp_data['datetimes'], asp_data['ASP_total'])

    def get_eigen_vel(self):
        """ Load eigen velocities calculated from archive HG-coordinates
        """
        super().get_eigen_vel()
        pool_data = read_pool()
        # Equatorial System is mostly called HG (heliographic) within the archive files
        self.data['vR'] = self.sync_times(pool_data['datetimes'], pool_data['v_R'])
        self.data['vT'] = self.sync_times(pool_data['datetimes'], pool_data['v_T'])
        self.data['vN'] = self.sync_times(pool_data['datetimes'], pool_data['v_N'])
        self.data['vabs'] = self.sync_times(pool_data['datetimes'], pool_data['v'])

    def rotate_to_EQ(self):
        """ Rotate an ArchiveTra object in HC(ECLIPB1950)-RF manually to the EQ(HCI/HG)-RF

        Just for testing! Label, RF etc. won't match anymore, positional coordinates will be overwritten
        """
        if self.RF == "EC":
            R = []
            lat = []
            long = []
            for t in range(len(self.data['r'])):
                vec_EC = np.array([self.data['r'][t],self.data['lat'][t],self.data['long'][t]])
                #print(vec_EC)
                t_epoch = datetime.datetime(2000, 1, 1,12) + datetime.timedelta(days=(2433282.42345905 - 2451545.0))
                # exact epoch for BC1950
                vec_rotated = hc_to_hg(vec_EC, ang_ascnode = calc_delta(t_epoch))
                #print(vec_rotated, '\n')
                R.append(vec_rotated[0])
                lat.append(vec_rotated[1])
                long.append(vec_rotated[2])
            self.data['r'] = R
            self.data['lat'] = lat
            self.data['long'] = long
        else:
            sys.exit('RF has to be \'EC\' for rotation to EQ')

    def rotate_to_EC(self):
        """ Rotate an ArchiveTra object in EQ(HCI/HG)-RF manually to the EC(HC/ECLIPJ1950)-RF

        Just for testing! Label, RF etc. won't match anymore, positional coordinates will be overwritten
        """
        if self.RF == "EQ":
            R = []
            lat = []
            long = []
            for t in range(len(self.data['r'])):
                vec_EQ = np.array([self.data['r'][t],self.data['lat'][t],self.data['long'][t]])
                vec_rotated = hg_to_hc(vec_EQ)
                R.append(vec_rotated[0])
                lat.append(vec_rotated[1])
                long.append(vec_rotated[2])
            self.data['r'] = R
            self.data['lat'] = lat
            self.data['long'] = long
        else:
            sys.exit('RF has to be \'EQ\' for rotation to EC')

###############################################################################################
################################### DATA LOADERS ##############################################
###############################################################################################

def locateUlysses(date, RF):
    '''
    Return Ulysses' position after SPICE data

    :param date: datetime object
    :param RF: etspice.ReferenceFrame
    :return: spherical coordinates [heliocentric range in AU, latitude, longitude] with latitude in [-90 deg, 90 deg], longitude in [-180 deg, 180 deg]
    '''
    xyz = ULYSSES.position(time = date, relative_to = SUN, reference_frame = RF) # in km
    if len(xyz) == 3:
        r, theta, phi = cart2spher(xyz, deg = True)
        return np.array([r/km_per_AU,theta,phi])
    elif len(xyz) > 3:
        pass
        positions = []
        for t in xyz:
            r, theta, phi = cart2spher(t, deg = True)
            positions.append(np.array([r/km_per_AU,theta,phi]))
        return positions

def velocityUlysses(date, RF = "HCI"):
    """
    Get Ulysses' eigen-velocity from SPICE and transform it to RTN-coordinates

    :param date: datetime object
    :param RF: etspice.ReferenceFrame
    :return: eigen-velocity in RTN-coordinates
    """
    from spiceypy import spkezr, datetime2et
    [x, y, z, vx, vy, vz] = spkezr('ULYSSES', datetime2et(date), RF, 'None', 'SUN')[0]  # cart in km(/s)
    r_sph = cart2spher(np.array([x,y,z]))
    v_sph = cart2spher(np.array([vx,vy,vz])) #does not really make sense but is needed for the rtn-function
    if RF in ["HCI", "HCI_B", "HCI_J"]: # solar equatorial coord. sys.
        pass
    elif RF in ["ECLIPJ2000", "ECLIPB1950"]: # ecliptic coord. sys.
        t_epoch = datetime.datetime(2000,1,1,12) if RF == "ECLIPJ2000" else datetime.datetime(2000,1,1,12)+datetime.timedelta(days = (2433282.42345905-2451545.0))
        r_sph = hc_to_hg(r_sph, ang_ascnode = calc_delta(t_epoch))
        v_sph = hc_to_hg(v_sph, ang_ascnode = calc_delta(t_epoch))
    vR, vT, vN = hg_to_rtn(v_sph, r_sph)
    return(np.array([vR,vT,vN]))

def locateBody(body, date, RF):
    '''
    Return a body's position after SPICE data

    :param body: body object, e.g. EARTH
    :param date: datetime object
    :param RF: etspice.ReferenceFrame
    :return: spherical coordinates [heliocentric range in AU, latitude, longitude] with latitude in [-90 deg, 90 deg], longitude in [-180 deg, 180 deg]
    '''
    xyz = body.position(time = date, relative_to = SUN, reference_frame = RF)
    r, theta, phi = cart2spher(xyz, deg = True)
    return(np.array([r/km_per_AU,theta,phi]))

def read_pool():
    '''
    Reader for Ulysses trajectory data from condensed file traj_data_ulysses_pool.dat
    :return: dict with keys 'Year', 'DOY', 'MM', 'DD', 'ESP', 'SPE', 'SEP', 'R', 'R_km', 'HC_Lat', 'HC_Long', 'HG_Lat',
                'HG_Long', 'HG_Long_wrtE', 'v', 'v_R', 'v_T', 'v_N', 'datestring'
    '''
    path_pool = "Ulysses/Trajectory/trajectory_data/traj_data_ulysses_pool.dat"
    fin = open(path_pool,'r')
    keys = fin.readline().split()
    for headerline in range(3):
        fin.readline()
    p_dict = {k:[] for k in keys}
    for line in fin:
        data = line.split()
        for i,k in enumerate(p_dict.keys()):
            if k == 'HG_Long':
                p_dict[k].append(float(data[i])-180.)
            elif k == 'HC_Long' and float(data[i]) > 180.:
                    p_dict[k].append(float(data[i])-360.)
            else:
                p_dict[k].append(float(data[i]))
    p_dict["datetimes"] = []
    for i,year in enumerate(p_dict['Year']):
        p_dict['datetimes'].append(datetime.datetime(int(year),int(p_dict['MM'][i]),int(p_dict['DD'][i])))
    for key in p_dict:
        p_dict[key] = np.array(p_dict[key])
    fin.close()
    return p_dict

def load_aa_data():
    '''
    Reader for "old" aspect angle data in aa_data.dat
    :return: dict with keys "YEAR", "DOY", "D90", "ASP_PHI", "ASP_THETA", "ASP_total", "datestring"
    '''
    path_aa = "Ulysses/Trajectory/trajectory_data/aa_data.dat"
    fin = open(path_aa, 'r')
    paras_aa = fin.readline().split()
    p_aa_dict = {p:[] for p in paras_aa}
    for line in fin:
        data = line.split()
        for i,p in enumerate(p_aa_dict.keys()):
            p_aa_dict[p].append(float(data[i]))
    p_aa_dict["datetimes"] = []
    for i,year in enumerate(p_aa_dict['YEAR']):
        # small workaround as there's only DOY data given aa_data.dat:
        p_aa_dict['datetimes'].append(datetime.datetime(int(year),1,1) + datetime.timedelta(days = p_aa_dict['DOY'][i] - 1))
    for key in p_aa_dict:
        p_aa_dict[key] = np.array(p_aa_dict[key])
    fin.close()
    return p_aa_dict

def write_traj_file(del_t = 3600*24, dt1 = datetime.datetime(1990,10,7), dt2 = datetime.datetime(2009,6,28)):
    ''' 
    Write trajectory data file
    
    :param del_t: time delta in seconds
    :param dt1: start - datetime.datetime-object; default is beginning of mission
    :param dt2: end - datetime.datetime-object; default is end of mission
    '''
    fout = open("Ulysses/Trajectory/trajectory_data/spice_traj.dat",'w')
    fout.write("YYYY  MM  DD  DOY    Hr Min      R      HG_Lat  HG_Long    AA_tot  AA_lat  AA_long     vSC_tot  vSC_R   vSC_T   vSC_N"
               "\n\t\t\t\t["
               "AU] \
    [deg]   [deg]      [deg]   [deg]   [deg]       [km/s]  [km/s]  [km/s]  [km/s]\n\n")
    S = SpiceTra(TF=[dt1,dt2], RF = HCI, DT = del_t) 
    for i in range(len(S.data['r'])): 
        line =(f"{S.times[i].year}  {S.times[i].month:2} {S.times[i].day:2}   {S.times[i].timetuple().tm_yday:3}    "
                f"{S.times[i].hour:02} {S.times[i].minute:02}     "
                f"{S.data['r'][i]:5.3f}   {S.data['lat'][i]:7.3f}  {S.data['long'][i]:7.3f}    "
                f"{S.data['asp_tot'][i]:7.3f} {S.data['asp_lat'][i]:7.3f} {S.data['asp_long'][i]:7.3f}    "
                f"{S.data['vabs'][i]:7.3f} {S.data['vR'][i]:7.3f} {S.data['vT'][i]:7.3f}  {S.data['vN'][i]:7.3f}")
        fout.write(line)
        fout.write('\n')
    fout.close()
    return S

if __name__ == "__main__":
    dt1 = datetime.datetime(1990,10,7)
    dt2 = datetime.datetime(2009,6,28)
    #S_ec = SpiceTra(TF=[dt1,dt2], RF = ECLIPB1950, DT = 24*3600*10)
    S_eq = SpiceTra(TF=[dt1,dt2], RF = HCI, DT = 24*3600*10)
    #A_ec = ArchiveTra(TF=[dt1,dt2], RF = "EC", DT = 24*3600*10)
    #A_eq = ArchiveTra(TF=[dt1,dt2], RF = "EQ", DT = 24*3600*10)