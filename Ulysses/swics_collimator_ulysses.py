from numpy import *
from pylib.etCoord import rotate
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
from custom_colours import lighten_color

class collimator(object):
    def __init__(self, nrs_para=5, nrs_perp=3, nrs_sec=5, edges=False, aspphi=0.00001, asptheta=0.00001, vel=600.,
                 vsw=300, offset_sp = 135.):
        """
        Class to calculate the field of view of SWICS (Ulysses) nrs_para,nrs_perp -> number of angle steps for
        collimator. The total number of point to represent each detector (three detectors in total) is
        nrs_para*nrs_perp. Opening angles ranges are +-2 deg (abs 4 deg) perpendicular and 30 deg parallel. Note :
        nrs_perp must be at least 1 and nrs_para- nrs_sec -> number of rotation steps that are used to build the
        sectorwise FoV. Each sector covers an angle of 45 deg. edges -> True means the outermost part of the
        detectors and the sector are included (for visualisation of the total FoV). False means the detector and
        sector boundaries are not included, resulting in points representing almost equal phase space volumes (this
        option should be used for data analysis).
        aspphi,ansptheta = Aspect angle in degrees, i.e. orientation of the
        spacecraft spin axis. NOTE rotation around theta is against usual sense of direction therefore the rotation
        has to be by -asptheta!!!!

        Coordinates (reversed RTN): R-axis -> Pointing from Spacecraft to Sun; T-axis ->
        cross product w x R (where w is the suns's spin axis); N-axis -> Completes the right handed
        triad (i.e. North)
        [Normal RTN has positve R axis from sun to SC and T-axis reversed as well.]
        """
        self.nrs_para = nrs_para
        self.nrs_perp = nrs_perp
        self.nrs_sec = nrs_sec
        self.edges = edges
        self.aspphi = aspphi
        self.asptheta = asptheta
        self.vel = vel
        self.vsw = vsw
        self.offset_sp = offset_sp
        if edges:
            self.angoffs_para = 0.
            self.angoffs_perp = 0.
            self.angoffs_sec = 0.
        else:
            self.angoffs_para = 30. / self.nrs_para / 2.
            self.angoffs_perp = 4. / self.nrs_perp / 2.
            self.angoffs_sec = 45. / self.nrs_sec / 2.

        self.ang_para = linspace(-self.angoffs_para, -30. + self.angoffs_para, nrs_para)
        self.ang_perp = linspace(self.angoffs_perp, 4. - self.angoffs_perp, nrs_perp)
        self.ang_sec = linspace(self.angoffs_sec, 45. - self.angoffs_sec, nrs_sec)

        self.base_points = zeros((3, self.ang_perp.shape[0]))
        # number of points per detector
        self.nrp_det = self.nrs_para * self.nrs_perp
        # number of points per detector and sector
        self.nrp_sec = self.nrp_det * self.nrs_sec
        self.det1 = zeros((3, self.nrp_det))
        self.det2 = zeros((3, self.nrp_det))
        self.det3 = zeros((3, self.nrp_det))
        self._calc_points()
        self._rot_aspang()
        self._rot_seczero()
        self._calc_FoV()
        # # self._calc_vspace()

    def test_plot(self):
        fig = plt.figure()
        ax = fig.add_subplot(111, projection='3d')
        ax.set_xlim(0., 1)
        ax.set_ylim(0., 1)
        ax.set_zlim(-1., 0)
        ax.set_xlabel("x")
        ax.set_ylabel("y")
        ax.set_zlabel("z")
        # origin:
        ax.plot([0, 0], [0, 0], [0, 0], 'o', color="k")
        # x-axis:
        ax.plot([-3, 3], [0, 0], [0, 0], '-', color="k", lw=.5)
        # y-axis:
        ax.plot([0, 0], [-3, 3], [0, 0], '-', color="k", lw=.5)
        # z-axis:
        ax.plot([0, 0], [0, 0], [-3, 3], '-', color="k", lw=.5)
        # rax2: 56deg in x-y-sphere for rotating in the beginning
        # ax.plot([0,self.rax2[0]],[0,self.rax2[1]],[0  ,self.rax2[2]],"-",color="peachpuff", ls=":")
        ax.plot(self.det1[0, :], self.det1[1, :], self.det1[2, :], "o", color="k", ms=2.)
        ax.plot(self.det2[0, :], self.det2[1, :], self.det2[2, :], "o", color="forestgreen", ms=2.)
        ax.plot(self.det3[0, :], self.det3[1, :], self.det3[2, :], "o", color="lawngreen", ms=2.)
        # axes for AA-rotation:
        ax.plot([0, self.rphiax[0] * 2.5], [0, self.rphiax[1] * 2.5], [0, self.rphiax[2] * 2.5], "-", color="peru",
                ls=":", label = 'asp_phi rotation axis')
        ax.plot([0, self.rthetaax[0] * 2.5], [0, self.rthetaax[1] * 2.5], [0, self.rthetaax[2] * 2.5], "-",
                color="burlywood",
                ls=":", label = 'asp_phi rotation axis')
        # Spacecraft Z-Axis (Spacecraft rotation axis, direction mostly Sunward):
        ax.plot([0, self.rax[0]], [0, self.rax[1]], [0, self.rax[2]], "-", color="orange", label = 'SC rotation axis')
        # Swics Z-Axis relative to rotation axis:
        ax.plot([0, self.rzax[0]], [0, self.rzax[1]], [0, self.rzax[2]], "-", color="lime", label = 'SWICS z-axis initial')
        # viewing direction sunpulser when triggered (=sec0)
        ax.plot([0, self.spax[0] * 0.5], [0, self.spax[1] * 0.5], [0, self.spax[2] * 0.5], "-", color="yellow",
                lw=3., label = 'sunpulser viewing when triggered')
        # rotated rzax
        ax.plot([0, self.rzaxrot[0]], [0, self.rzaxrot[1]], [0, self.rzaxrot[2]], "-", color="limegreen",
                label = 'SWICS z-axis rotated')
        ax.legend(loc=4)
        return ax

    def _calc_points(self):
        """
        Calculates the unrotatet slit, divided into detectors 1,2,3. rax is the axis from which the entrance slit can
        be constructed by rotating the vector (1,0,0) by ang_para (full 90 degrees, resulting in an opening angle of
        the collimator of ~70 deg against the x-y plane). Each detector is assumed to cover 30 deg. The opening in
        the x-y plane is +-2 deg. det1,2,3 are a representation of the collimator in this coordinate system. And has
        to be rotated to the actual scientific cordinates. This is done later on by, first rotate to the actual spin
        axis direction (_rot_aspang) , then to the direction where the rotation is started,i.e. the sun-pulse is
        triggered (_rot_seczero).
        """
        self.rax2 = array([cos(56. / 180. * pi), sin(56. / 180. * pi), 0]) # for the plot
        rax = array([cos(56. / 180. * pi), sin(56. / 180. * pi), 0])
        for i, ang in enumerate(self.ang_perp):
            self.base_points[:, i] = array([cos(ang / 180. * pi), sin(ang / 180. * pi), 0])
        for i, ang in enumerate(self.ang_para):
            self.det1[:, i * self.nrs_perp:(i + 1) * self.nrs_perp] = rotate(self.base_points, rax, ang,
                                                                             deg=True).reshape(self.base_points.shape)
            self.det2[:, i * self.nrs_perp:(i + 1) * self.nrs_perp] = rotate(self.base_points, rax, ang - 30.,
                                                                             deg=True).reshape(self.base_points.shape)
            self.det3[:, i * self.nrs_perp:(i + 1) * self.nrs_perp] = rotate(self.base_points, rax, ang - 60.,
                                                                             deg=True).reshape(self.base_points.shape)

    def _rot_aspang(self):
        """
        Calculates axes for spacecraft spin axis taking into account the Aspect Angle (ang between vector SC-sun and
        SC's antenna which points to earth basically all the time.
        For consistency with ACE coord.sys. (GSE) we use a reversed RTN system for Ulysses SWICS: (R: SC -sun (!); T:
        cross product w x R (where w is the suns's spin axis); N: completes this right-handed triad -- for
        in-ecliptic SC: R=X, T=Y, N=Z equvalent to GSE).

        AA-rotated SpaceCraft-Spin-Axis is then defined by first rotating (1,0,0) by asp_phi around (0,0,1).
        The resulting vector is then rotated in the T-N-plane around the also rotated T-axis by asp_theta.

        Ulysses asp_phi increases to +90 deg towards positive T-axis ('left' when viewing from SC to the sun) and -90
        deg towards negative T-axis.
        Ulysses asp_theta increases from zero in sun direction (positive R-axis) to +90 deg towards N-axis.

        """
        # Axes for aspect phi and theta angle rotations
        self.rphiax = array([0., 0., 1.])
        self.rthetaax = rotate(array([0., 1., 0]), self.rphiax, self.aspphi, deg=True)
        # Spacecraft Z-Axis (Spacecraft rotation axis, direction mostly Sunward)
        self.rax = rotate(array([1., 0., 0.]), self.rphiax, self.aspphi, deg=True)
        self.rax = rotate(self.rax, self.rthetaax, -self.asptheta, deg=True)
        # Swics Z-Axis relative to rotation axis
        self.rzax = rotate(array([0., 0., 1.]), self.rphiax, self.aspphi, deg=True)
        self.rzax = rotate(self.rzax, self.rthetaax, -self.asptheta, deg=True)
        # Rotate detectors in phi direction
        det1_rot = rotate(self.det1, self.rphiax, self.aspphi, deg=True).reshape(self.det1.shape)
        det2_rot = rotate(self.det2, self.rphiax, self.aspphi, deg=True).reshape(self.det2.shape)
        det3_rot = rotate(self.det3, self.rphiax, self.aspphi, deg=True).reshape(self.det3.shape)
        # Rotate detectors in theta direction (because of theta being defined with opposite sense of rotation,
        # i.e. 0 in ecliptic and positive values northward out of the ecliptic)
        self.det1 = rotate(det1_rot, self.rthetaax, -self.asptheta, deg=True).reshape(self.det1.shape)
        self.det2 = rotate(det2_rot, self.rthetaax, -self.asptheta, deg=True).reshape(self.det2.shape)
        self.det3 = rotate(det3_rot, self.rthetaax, -self.asptheta, deg=True).reshape(self.det3.shape)

    def _rot_seczero(self):
        """
        Rotates slit to 'offset_sp' degrees against sun pulse trigger (so that swics z-axis is 'offset_sp' deg ahead
        of the sp trigger. That is the the starting position for sector 0.

        For ACE SWICS an angle offset_sp of 135 degrees has been inferred from a technical drawing of the ACE-SC.
        (It looks like the detector view direction is 135 deg ahead of the sun-pulse. Which means that the sun-pulse
        direction is typically reached at sector 5!)

        For Ulysses SWICS the positioning of sun pulse sensor direction vs. SWICS has the be found out. Due to that
        we're working with a variable angle here...
        """
        # Sunpulser viewing direction at spin start,i.e. start of sec0 (in plane spanned by spin axis and SC-Sun
        # line, perpendicular to spin axis)
        self.spax = cross(self.rax, cross(array([1., 0., 0.]), self.rax))
        self.spax /= sqrt(sum(self.spax ** 2))
        # Sunpulser angle relative to Swics Z-Axis (always 90 deg?)
        self.spang = arccos(dot(self.spax, self.rzax)) / pi * 180.
        # Rotate slit to Sector 0 starting Position, i.e. rotate by 90-spang
        if self.aspphi < 0.:
            self.sec0ang = self.offset_sp - self.spang
        else:
            self.sec0ang = (self.offset_sp + self.spang)
        self.det1 = rotate(self.det1, self.rax, self.sec0ang, deg=True).reshape(self.det1.shape)
        self.det2 = rotate(self.det2, self.rax, self.sec0ang, deg=True).reshape(self.det2.shape)
        self.det3 = rotate(self.det3, self.rax, self.sec0ang, deg=True).reshape(self.det3.shape)
        self.rzaxrot = rotate(self.rzax, self.rax, self.sec0ang, deg=True).reshape(self.rzax.shape)

    def plot(self):
        fig = plt.figure()
        ax = fig.add_subplot(111, projection='3d')
        ax.set_xlim(0., 1)
        ax.set_ylim(0., 1)
        ax.set_zlim(-1., 0)
        ax.set_xlabel("x")
        ax.set_ylabel("y")
        ax.set_zlabel("z")
        ax.plot(self.det1[0, :], self.det1[1, :], self.det1[2, :], "o", color="k")
        ax.plot(self.det2[0, :], self.det2[1, :], self.det2[2, :], "o", color="b")
        ax.plot(self.det3[0, :], self.det3[1, :], self.det3[2, :], "o", color="r")
        return ax

    def plot_rot(self, ang=0., ax=None):
        if ax == None:
            fig = plt.figure()
            ax = fig.add_subplot(111, projection='3d')
            ax.set_xlim(0., 1)
            ax.set_ylim(-1., 1)
            ax.set_zlim(-1., 1)
            ax.set_xlabel("x")
            ax.set_ylabel("y")
            ax.set_zlabel("z")
        det1_rot = rotate(self.det1, self.rax, ang, deg=True).reshape(self.det1.shape)
        det2_rot = rotate(self.det2, self.rax, ang, deg=True).reshape(self.det2.shape)
        det3_rot = rotate(self.det3, self.rax, ang, deg=True).reshape(self.det3.shape)

        ax.plot(det1_rot[0, :], det1_rot[1, :], det1_rot[2, :], "o", color="k")
        ax.plot(det2_rot[0, :], det2_rot[1, :], det2_rot[2, :], "o", color="b")
        ax.plot(det3_rot[0, :], det3_rot[1, :], det3_rot[2, :], "o", color="r")
        return ax

    def _calc_FoV(self):
        # dimensions of FoV did,sec,(x,y,z)
        self.FoV = zeros((3, 8, 3, self.nrp_sec))
        for sec in range(8):
            for ind, ang in enumerate(self.ang_sec):
                # first det:
                self.FoV[0, sec, :, ind * self.nrp_det:(ind + 1) * self.nrp_det] = rotate(self.det1, self.rax,
                                                                                          sec * 45. + ang,
                                                                                          deg=True).reshape(
                    self.det1.shape)
                # second det:
                self.FoV[1, sec, :, ind * self.nrp_det:(ind + 1) * self.nrp_det] = rotate(self.det2, self.rax,
                                                                                          sec * 45. + ang,
                                                                                          deg=True).reshape(
                    self.det2.shape)
                # third det:
                self.FoV[2, sec, :, ind * self.nrp_det:(ind + 1) * self.nrp_det] = rotate(self.det3, self.rax,
                                                                                          sec * 45. + ang,
                                                                                          deg=True).reshape(
                    self.det3.shape)



    def plot_FoV(self, ax=None, sec='all'):
        if ax == None:
            fig = plt.figure()
            ax = fig.add_subplot(111, projection='3d')
            fig.canvas.set_window_title('FoV')
            #ax.set_title('FoV')
            ax.set_xlabel('x')
            ax.set_ylabel('y')
            ax.set_zlabel('z')
        colors = array([[77, 77, 0], [77, 57, 0], [77, 0, 0], [77, 0, 57], [38, 0, 77], [0, 38, 77], [0, 77, 77],
                        [0, 77, 19]])
        if isinstance(sec, int):
            f = self.FoV[:, sec, :, :]
            nrs = f.shape[-2] * f.shape[-1]
            shade_arr = linspace(0.1, 3.5, nrs)
            rgb = colors[sec]
            cc = zeros((nrs, 3))
            for j in range(nrs):
                cc[j] = lighten_color(rgb, factor=shade_arr[j]) / 255.
            ax.scatter(f[..., 0, :], f[..., 1, :], f[..., 2, :], c=cc)
            ax.scatter(0, 0, 0, c='k', s=5)
            ax.plot([0, 4], [0, 0], [0, 0], c='k', lw=0.8)
        elif sec == 'all':
            f = self.FoV[:, :, :, :]
            for i, s in enumerate(range(f.shape[-3])):
                nrs = f.shape[-2] * f.shape[-1]
                shade_arr = linspace(0.1, 3.5, nrs)
                rgb = colors[i]
                cc = zeros((nrs, 3))
                for j in range(nrs):
                    cc[j] = lighten_color(rgb, factor=shade_arr[j]) / 255.
                ax.scatter(f[..., s, 0, :], f[..., s, 1, :], f[..., s, 2, :], c=cc)
                ax.scatter(0, 0, 0, c='k', s=5)
                ax.plot([0, 4], [0, 0], [0, 0], c='k', lw=0.8)
                # viewing direction sunpulser when triggered (=sec0)
                ax.plot([0, self.spax[0] * 0.5], [0, self.spax[1] * 0.5], [0, self.spax[2] * 0.5], "-", color="yellow",
                        lw=3., label='sunpulser viewing when triggered')
        else:
            print("no valid sector given")
        return ax







#_______________________ not used atm __________________________________

    def _calc_vspace(self):
        """
        convert FoV into v-space (GSE correct for SC eigen-velocity)
        """
        # first invert view direction into v-acceptance
        self.vspace = -self.FoV * self.vel
        self.vspace[:, :, 1, :] -= 30
        self.vspace[:, :, 0, :] = -self.vspace[:, :, 0, :]
        self.vspace[:, :, 1, :] = -self.vspace[:, :, 1, :]
        self.mv = mean(self.vspace, axis=3)

    def plot_detsec(self, det, sec, ax=None):
        if ax == None:
            fig = plt.figure()
            ax = fig.add_subplot(111, projection='3d')
            ax.set_xlim(0., 1)
            ax.set_ylim(-1., 1)
            ax.set_zlim(-1., 1)
            ax.set_xlabel("x")
            ax.set_ylabel("y")
            ax.set_zlabel("z")
        col = zeros(3)
        col[det] = 0.1 + sec * 0.9 / 7.
        ax.plot(self.FoV[det, sec, 0, :], self.FoV[det, sec, 1, :], self.FoV[det, sec, 2, :], "o", markersize=1.,
                alpha=0.5, color=col)
        return ax

    def plot_vseg(self, det, sec, ax=None):
        if ax == None:
            fig = plt.figure()
            ax = fig.add_subplot(111, projection='3d')
            ax.set_xlim(-2 * self.vel, 2 * self.vel)
            ax.set_ylim(-1. * self.vel, 1 * self.vel)
            ax.set_zlim(-1. * self.vel, 1 * self.vse)
            ax.set_xlabel("x")
            ax.set_ylabel("y")
            ax.set_zlabel("z")
        col = zeros(3)
        col[det] = 0.1 + sec * 0.9 / 7.
        ax.plot(self.vspace[det, sec, 0, :], self.vspace[det, sec, 1, :], self.vspace[det, sec, 2, :], "o",
                markersize=1., alpha=0.5, color=col)
        return ax

    def _calc_w(self):
        # first assume vsw radial
        vswspace = 1. * self.vspace
        vswspace[:, :, 0, :] -= self.vsw
        self.wswspace = sqrt(sum(vswspace ** 2, axis=2)) / self.vsw
        self.wscspace = sqrt(sum(self.vspace ** 2, axis=2)) / self.vsw

    def plot_vseg(self, det, sec, ax=None, reduced=False):
        if ax == None:
            fig = plt.figure()
            ax = fig.add_subplot(111, projection='3d')
            ax.set_xlim(0., 2 * self.vel)
            ax.set_ylim(-1. * self.vel, 1 * self.vel)
            ax.set_zlim(-1. * self.vel, 1 * self.vse)
            ax.set_xlabel("x")
            ax.set_ylabel("y")
            ax.set_zlabel("z")
        col = zeros(3)
        col[det] = 0.1 + sec * 0.9 / 7.
        if not reduced:
            ax.plot(self.vspace[det, sec, 0, :], self.vspace[det, sec, 1, :], self.vspace[det, sec, 2, :], "o",
                    markersize=1., alpha=0.5, color=col)
        else:
            ax.plot(self.vspace[det, sec, 0, :], self.vspace[det, sec, 1, :], self.vspace[det, sec, 2, :], "o",
                    markersize=5., alpha=1., color="k")
        return ax

    def plot_FoV_lars(self):
        fig = plt.figure()
        ax = fig.add_subplot(111, projection='3d')
        ax.set_xlim(0., 2.)
        ax.set_ylim(-1., 1)
        ax.set_zlim(-1., 1)
        ax.set_xlabel("x")
        ax.set_ylabel("y")
        ax.set_zlabel("z")
        rotax = zeros((3, 100))
        xax = zeros((3, 100))
        for i in range(100):
            rotax[:, i] = i / 100. * self.rax
            xax[:, i] = i / 100. * array([1., 0., 0.])
        for sec in range(8):
            for det in range(3):
                self.plot_detsec(det, sec, ax=ax)
        ax.plot(rotax[0, :], rotax[1, :], rotax[2, :], color="k")
        ax.plot(xax[0, :], xax[1, :], xax[2, :], "--", color="k")
        return ax

    def plot_vspace(self, ax=None, reduced=False):
        if ax == None:
            fig = plt.figure(figsize=(9., 9.))
            ax = fig.add_subplot(111, projection='3d')
            ax.set_xlim(-1. * self.vel, 2 * self.vel)
            ax.set_ylim(-1.5 * self.vel, 1.5 * self.vel)
            ax.set_zlim(-1.5 * self.vel, 1.5 * self.vel)
            ax.set_xlabel("v$_{sc,x}$ [km/s]")
            ax.set_ylabel("v$_{sc,y}$ [km/s]")
            ax.set_zlabel("v$_{sc,z}$ [km/s]")
        rotax = zeros((3, 201))
        xax = zeros((3, 201))
        for i in range(0, 101, 1):
            rotax[:, i] = -i / 100. * self.rax * self.vel
            xax[:, i] = i / 100. * array([self.vel, 0., 0.])
        for sec in range(8):
            for det in range(3):
                self.plot_vseg(det, sec, ax=ax, reduced=reduced)
        ax.plot(-rotax[0, :], -rotax[1, :], rotax[2, :], ".-", color="k")
        ax.plot(xax[0, :], xax[1, :], xax[2, :], color="k", lw=5)
        ax.view_init(15, 190)
        ax.tick_params(pad=20)
        ax.set_xticklabels([-400, "", 0, "", 400, "", 800, "", 1200])
        return ax
