'''
Workflow:

- d: data dictionary – keeps SWICS PHA (pulse height analysis) data, i.e. date, EpQ, sector, detector, baserate weight, aspect angles, vsw, … for every count (filtered, e.g. for my work only He+ data)
not included below - is based on "Dbdata", which is a huge class based on Python2 written by Lars and a former colleague for working with this kind of data. Basically you have something like:
d = {'datetime' : [12:00, 12:12, 12:30, ...], 'EpQ' : [10, 8, 12, ...], 'sec' : [...]} with the count from 12:00 measured in EpQ-step 10, the count from 12:12 in step 8 etc. - so for every data product an array with values for every count.

- class collimator:
for SWICS very complicated steps in the beginning due to the ugly geometry…
Actually I create vectors that represent the FoV of the instrument while it’s fixed in space (like… lying in a coordinate system’s origin in front of you on your desk). You can interpret these vectors as inverse trajectories of possible acceptance of particles; in my thesis these are f_i.
Then you normalize these vectors.
You can choose as many f_i as you like, they should only cover all of your instrument’s entrance more or less dense. Plus you have to normalise the phase space density  accordingly in the end.
In my case a complete FoV of one collimator consists of 3 x 8 x 3 x n vectors (#detectors x #sectors x [x,y,z] x n: number of vectors in one sector-detector combination – this is the variable number that I can choose to have a more dense grid)

You can then multiply each vector with a velocity (based on a EpQ step and species) to get the accepted velocity (in three components) in spacecraft frame for every f_i.


- class Dist3D: main attribute is d

_calc_FoV(): creates an i_phi x i_theta dimensional array (FoV) - where i_phi and i_theta are the numbers of aspect angles that appear in d (even a bit different in my code but let’s keep it simple here). You fill FoV with collimators that are rotated by the respective phi and theta
(The FoV is independent of the EpQ step!)
...you don’t need this matrix when you don’t have large aspect angles. Then you only need one FoV that you rotate according to the orientation of your instrument and coordinate system

_calc_vspace(): add another dimension for each EpQ step (you can only do this when you have one species in d. Otherwise you would mix velocities): multiply each FoV with each respective velocity for the EpQ-step (for SWICS it’s 64 EpQ steps). Then you have i_EpQ * i_theta * i_phi collimators.

_calc_wspace(): same… add another dimension for present vsw…

_add_3Dv(): here I connect data and collimator again:
assign every measurement the velocities from its resp. asp angles, EpQ step, detector, sector (actually I add the resp. velocity components as data products to d)
This is done by using the huge array as a look-up table

-> then you can histogram the velocity space (or w space) for your data or calculate the phase space density

'''

class collimator(object):
    def __init__(self, nrs_para=4, nrs_perp=2, nrs_sec=6, edges=False, aspphi=0.00001, asptheta=0.00001, vel=600.,
                 vsw=700, offset_sp = 180.):
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
        self.ang_perp = linspace(-2 + self.angoffs_perp, 2. - self.angoffs_perp, nrs_perp)
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
            self.sec0ang = self.offset_sp + self.spang
        else:
            self.sec0ang = (self.offset_sp - self.spang)
        self.det1 = rotate(self.det1, self.rax, -self.sec0ang, deg=True).reshape(self.det1.shape)
        self.det2 = rotate(self.det2, self.rax, -self.sec0ang, deg=True).reshape(self.det2.shape)
        self.det3 = rotate(self.det3, self.rax, -self.sec0ang, deg=True).reshape(self.det3.shape)
        self.rzaxrot = rotate(self.rzax, self.rax, -self.sec0ang, deg=True).reshape(self.rzax.shape)

    def _calc_FoV(self):
        # dimensions of FoV did,sec,(x,y,z)
        self.FoV = zeros((3, 8, 3, self.nrp_sec))
        for sec in range(8):
            for ind, ang in enumerate(self.ang_sec):
                # first det:
                self.FoV[0, sec, :, ind * self.nrp_det:(ind + 1) * self.nrp_det] = rotate(self.det3, self.rax,
                                                                                          sec * 45. + ang,
                                                                                          deg=True).reshape(
                    self.det3.shape)
                # second det:
                self.FoV[1, sec, :, ind * self.nrp_det:(ind + 1) * self.nrp_det] = rotate(self.det2, self.rax,
                                                                                          sec * 45. + ang,
                                                                                          deg=True).reshape(
                    self.det2.shape)
                # third det:
                self.FoV[2, sec, :, ind * self.nrp_det:(ind + 1) * self.nrp_det] = rotate(self.det1, self.rax,
                                                                                          sec * 45. + ang,
                                                                                          deg=True).reshape(
                    self.det1.shape)

class Dist3D(object):
    def __init__(self, d, mass=4., charge=1., aspphistep=2., aspthetastep=2., v_sc_step=1., nrs_perp=3, nrs_para=9,
                 nrs_sec=9, nrs_epq=3, vswstep = 10, ion="He1+", offset_sp=180., sc_vel=False):

        # nrs_perp: 3, nrs_para: 9, nrs_sec: 6, nrs_epq: 3
        """
        d : dbData instance with species predifined by Master mask
        m : Ion mass in amu
        q : Ion charge in e
        """
        self.d = d
        self.aspphistep = aspphistep
        self.aspthetastep = aspthetastep
        self.nrs_para = nrs_para
        self.nrs_perp = nrs_perp
        self.nrs_sec = nrs_sec
        self.nrs_epq = nrs_epq
        self.vswstep = vswstep
        self.mass = mass
        self.charge = charge
        self.ion = ion
        self.sc_vel = sc_vel
        self.offset_sp = offset_sp
        self.col_dim = self.nrs_para * self.nrs_perp * self.nrs_sec
        self.sec_det_dim = self.col_dim * self.nrs_epq
        self.aspphi = arange(around(min(self.d.data["aspphi"])),
                             around(max(self.d.data["aspphi"])) + aspphistep + 0.0001, aspphistep)
        self.asptheta = arange(around(min(self.d.data["asptheta"])),
                               around(max(self.d.data["asptheta"])) + aspthetastep + 0.0001, aspthetastep)

        self.vswbins = arange(around(min(self.d.data["vsw"])),
                              around(max(self.d.data["vsw"])) + vswstep + 0.0001, vswstep)

        self.vr = arange(around(min(self.d.data["vr_sc"])),
                         around(max(self.d.data["vr_sc"])) + v_sc_step + 0.0001, v_sc_step)
        self.vt = arange(around(min(self.d.data["vt_sc"])),
                         around(max(self.d.data["vt_sc"])) + v_sc_step + 0.0001, v_sc_step)
        self.vn = arange(around(min(self.d.data["vn_sc"])),
                         around(max(self.d.data["vn_sc"])) + v_sc_step + 0.0001, v_sc_step)

        self.vels = getvelocity(self.mass, self.charge, arange(0, 64, 1), frac=1.)
        # nrs_epq -> deltaEpQ is +-5% -> delta v is +-2.5% -> nrs_epq equal spaced velocities in epq direction are
        # generated by vels_fac
        self.vels_fac = linspace(0.975 + 0.025 / self.nrs_epq, 1.025 - 0.025 / self.nrs_epq, self.nrs_epq)
        if not "d00" in self.d.data.keys():
            self.d.add_data("d00", calc_day00(self.d.data["year"], self.d.data["doy"]))
        else:
            self.d.data["d00"] = calc_day00(self.d.data["year"], self.d.data["doy"])
        # depends on max vsw, here in SC frame
        self.wshellmax = getvelocity(self.mass, self.charge, 0, frac = 1.) / max(self.d.data["vsw"])
        self._calc_FoV()
        self._calc_vspace()
        self._add_3Dv()

    def _calc_FoV(self):
        # shape self.FoV: (#aspphi, #asptheta, #det, #sec, xyz, col_dim)
        # (col_dim is nrs_para * nrs_perp * nrs_sec)
        self.FoV = zeros((self.aspphi.shape[0], self.asptheta.shape[0], 3, 8, 3, self.col_dim))
        for iphi, phi in enumerate(self.aspphi):
            for itheta, theta in enumerate(self.asptheta):
                c = collimator(aspphi=phi, asptheta=theta, nrs_perp=self.nrs_perp, nrs_para=self.nrs_para,
                               nrs_sec=self.nrs_sec, offset_sp=self.offset_sp)
                self.FoV[iphi, itheta] = c.FoV

    def _calc_vspace(self):
        """
        Calculates vR,vT,vN for all epqsteps and given aspect angles.
        shape self.vspace: (#aspphi, #asptheta, #vr, #vt, #vn, #epq-steps, #det, #sec, xyz, sec_det_dim)
        (sec_det_dim is col_dim * nrs_epq)
        """
        self.vspace = zeros((self.aspphi.shape[0], self.asptheta.shape[0], 64, 3, 8, 3, self.sec_det_dim))
        for i in range(self.nrs_epq):
            for iv, v in enumerate(self.vels):
                self.vspace[:, :, iv, :, :, :, i * self.col_dim:(i + 1) * self.col_dim] = -self.FoV * v * \
                                                                                          self.vels_fac[i]
        self.vspace[:, :, :, :, :, 0, :] = -self.vspace[:, :, :, :, :, 0, :]  # R defined positive from Sun to SC
        self.vspace[:, :, :, :, :, 1, :] = -self.vspace[:, :, :, :, :, 1, :]  # positive T in the regular definition

    def _calc_wspace(self):
        """
        Calculates vR,vT,vN for all epqsteps and given aspect angles
        not used atm: too much memory. Only used for plot_wspace.py with a smaller number of sec_det_dim
        """
        self.w3dspace = zeros(
            (self.vswbins.shape[0], self.aspphi.shape[0], self.asptheta.shape[0], 64, 3, 8, 3, self.sec_det_dim))

        self.wspace = zeros(
            (self.vswbins.shape[0], self.aspphi.shape[0], self.asptheta.shape[0], 64, 3, 8, 1, self.sec_det_dim))

        # self.w3dspace_sc = zeros(
        #     (self.vswbins.shape[0], self.aspphi.shape[0], self.asptheta.shape[0], 64, 3, 8, 3, self.sec_det_dim))
        # self.wspace_sc = zeros(
        #     (self.vswbins.shape[0], self.aspphi.shape[0], self.asptheta.shape[0], 64, 3, 8, 1, self.sec_det_dim))
        for iv, v in enumerate(self.vswbins[:-1]):
            tmpspace = 1. * self.vspace
            tmpspace[..., 0, :] -= (v)
            tmpspace /= (v)
            self.w3dspace[iv, ...] = tmpspace
            self.wspace[iv, ..., 0, :] = sqrt(sum(tmpspace ** 2, axis=5))
            ## SC frame:
            # tmpspace_sc = 1. * self.vspace
            # tmpspace_sc /= v
            # self.w3dspace_sc[iv, ...] = tmpspace_sc
            # self.wspace_sc[iv, ..., 0, :] = sqrt(sum(tmpspace_sc ** 2, axis=5))

    def _add_3Dv(self):
        """
        Adds vR,vT,vN in SC-frame and vRsw,vTsw,vNsw in SW-frame based on aspect angles to pha data
        Also adds vRsw2,vTsw2,vNsw2 in SW-frame based on aspect angles and rounded vsw to pha data 
        In the current version vsw is taken to be stricly radial, i.e. along v_x / v_R!
        sc_vel determines if the velocity of the SC itself should be considered in the v-space.
        """
        # divide the bins each into half and match every count to the central binedge.
        searcharr_phi = arange(self.aspphi[0] + self.aspphistep / 2., self.aspphi[-1], self.aspphistep)
        searcharr_theta = arange(self.asptheta[0] + self.aspthetastep / 2., self.asptheta[-1], self.aspthetastep)

        phiind = searchsorted(searcharr_phi, self.d.get_data('Master', "aspphi"))
        thetaind = searchsorted(searcharr_theta, self.d.get_data('Master', "asptheta"))

        epqind = self.d.get_data('Master', 'epq').astype(int)
        detind = self.d.get_data('Master', 'det').astype(int)
        secind = self.d.get_data('Master', 'sec').astype(int)
        if self.sc_vel == False:
            if not "vR" in self.d.data.keys():
                self.d.add_data("vR", self.vspace[phiind, thetaind, epqind, detind, secind, 0])  # a list of
                # sec_det_dim entries is added!
            else:
                self.d.data["vR"] = self.vspace[phiind, thetaind, epqind, detind, secind, 0]
            if not "vT" in self.d.data.keys():
                self.d.add_data("vT", self.vspace[phiind, thetaind, epqind, detind, secind, 1])
            else:
                self.d.data["vT"] = self.vspace[phiind, thetaind, epqind, detind, secind, 1]
            if not "vN" in self.d.data.keys():
                self.d.add_data("vN", self.vspace[phiind, thetaind, epqind, detind, secind, 2])
            else:
                self.d.data["vN"] = self.vspace[phiind, thetaind, epqind, detind, secind, 2]
            if not "v" in self.d.data.keys():
                self.d.add_data("v",
                                sqrt(self.d.data["vR"] ** 2 + self.d.data["vT"] ** 2 + self.d.data["vN"] ** 2))
            else:
                self.d.data["v"] = sqrt(
                    self.d.data["vR"] ** 2 + self.d.data["vT"] ** 2 + self.d.data["vN"] ** 2)

        elif self.sc_vel == True:
            # considering the velocity of the SC
            if not "vR" in self.d.data.keys():
                self.d.add_data("vR", self.vspace[phiind, thetaind, epqind, detind, secind, 0] + tile(self.d.data[
                    'vr_sc'], ( self.sec_det_dim,1)).T)
                # a list of sec_det_dim entries is added!
            else:
                self.d.data["vR"] = self.vspace[phiind, thetaind, epqind, detind, secind, 0] + tile(self.d.data[
                    'vr_sc'], (self.sec_det_dim, 1)).T

            if not "vT" in self.d.data.keys():
                self.d.add_data("vT", self.vspace[phiind, thetaind, epqind, detind, secind, 1] + tile(self.d.data[
                      'vt_sc'], (self.sec_det_dim,1)).T)
            else:
                self.d.data["vT"] = self.vspace[phiind, thetaind, epqind, detind, secind, 1] + tile(self.d.data[
                         'vt_sc'], (self.sec_det_dim,1)).T

            if not "vN" in self.d.data.keys():
                self.d.add_data("vN", self.vspace[phiind, thetaind, epqind, detind, secind, 2] + tile(self.d.data[
                     'vn_sc'], (self.sec_det_dim,1)).T)
            else:
                self.d.data["vN"] = self.vspace[phiind, thetaind, epqind, detind, secind, 2] + tile(self.d.data[
                     'vn_sc'], (self.sec_det_dim,1)).T

            if not "v" in self.d.data.keys():
                self.d.add_data("v",
                                sqrt(self.d.data["vR"] ** 2 + self.d.data["vT"] ** 2 + self.d.data["vN"] ** 2))
            else:
                self.d.data["v"] = sqrt(
                    self.d.data["vR"] ** 2 + self.d.data["vT"] ** 2 + self.d.data["vN"] ** 2)

        # __________ SW frame _____________________
        if not "vRsw" in self.d.data.keys():
            self.d.add_data("vRsw", (self.d.data["vR"].T - self.d.get_data('Master', 'vsw')).T)
        else:
            self.d.data["vRsw"] = (self.d.data["vR"].T - self.d.get_data('Master', 'vsw')).T
        if not "vTsw" in self.d.data.keys():
            self.d.add_data("vTsw", self.d.data["vT"])
        else:
            self.d.data["vTsw"] = self.d.data["vT"]
        if not "vNsw" in self.d.data.keys():
            self.d.add_data("vNsw", self.d.data["vN"])
        else:
            self.d.data["vNsw"] = self.d.data["vN"]
        if not "v_sw" in self.d.data.keys():
            self.d.add_data("v_sw",
                            sqrt(self.d.data["vRsw"] ** 2 + self.d.data["vTsw"] ** 2 + self.d.data["vNsw"] ** 2))
        else:
            self.d.data["v_sw"] = sqrt(
                self.d.data["vRsw"] ** 2 + self.d.data["vTsw"] ** 2 + self.d.data["vNsw"] ** 2)

        # _________index 2 in names means vsw speed has been rounded__________
        if not "vRsw2" in self.d.data.keys():
            self.d.add_data("vRsw2", (self.d.data["vR"].T - around(self.d.data["vsw"], -1)).T)
        else:
            self.d.data["vRsw2"] = (self.d.data["vR"].T - around(self.d.data["vsw"], -1)).T
        if not "vTsw2" in self.d.data.keys():
            self.d.add_data("vTsw2", self.d.data["vT"])
        else:
            self.d.data["vTsw2"] = self.d.data["vT"]
        if not "vNsw2" in self.d.data.keys():
            self.d.add_data("vNsw2", self.d.data["vN"])
        else:
            self.d.data["vNsw2"] = self.d.data["vN"]

    def _add_w(self):
        """
        Adds wRsw,wTsw,wNsw and wsw in SW-frame to pha data
        Adds wRsw2,wTsw2,wNsw2 and wsw2 in SW-frame to pha data based on rounded vsws!
        Adds wR, wT, wN and wsc in SC-frame to pha data
        """
        if not "wRsw" in self.d.data.keys():
            self.d.add_data("wRsw", (self.d.data["vRsw"].T / self.d.data["vsw"]).T)
        else:
            self.d.data["wRsw"] = (self.d.data["vRsw"].T / self.d.data["vsw"]).T
        if not "wTsw" in self.d.data.keys():
            self.d.add_data("wTsw", (self.d.data["vTsw"].T / self.d.data["vsw"]).T)
        else:
            self.d.data["wTsw"] = (self.d.data["vTsw"].T / self.d.data["vsw"]).T
        if not "wNsw" in self.d.data.keys():
            self.d.add_data("wNsw", (self.d.data["vNsw"].T / self.d.data["vsw"]).T)
        else:
            self.d.data["wNsw"] = (self.d.data["vNsw"].T / self.d.data["vsw"]).T
        if not "wsw" in self.d.data.keys():
            self.d.add_data("wsw", sqrt(self.d.data["wRsw"] ** 2 + self.d.data["wTsw"] ** 2 + self.d.data["wNsw"] ** 2))
        else:
            self.d.data["wsw"] = sqrt(self.d.data["wRsw"] ** 2 + self.d.data["wTsw"] ** 2 + self.d.data["wNsw"] ** 2)

        # # _________index 2 in names means vsw speed has been rounded__________
        # if not "wRsw2" in self.d.data.keys():
        #     self.d.add_data("wRsw2", (self.d.data["vRsw2"].T / self.d.data["vsw"]).T)
        # else:
        #     self.d.data["wRsw2"] = (self.d.data["vRsw2"].T / self.d.data["vsw"]).T
        # if not "wTsw2" in self.d.data.keys():
        #     self.d.add_data("wTsw2", (self.d.data["vTsw2"].T / self.d.data["vsw"]).T)
        # else:
        #     self.d.data["wTsw2"] = (self.d.data["vTsw2"].T / self.d.data["vsw"]).T
        # if not "wNsw2" in self.d.data.keys():
        #     self.d.add_data("wNsw2", (self.d.data["vNsw2"].T / self.d.data["vsw"]).T)
        # else:
        #     self.d.data["wNsw2"] = (self.d.data["vNsw2"].T / self.d.data["vsw"]).T
        # if not "wsw2" in self.d.data.keys():
        #     self.d.add_data("wsw2",
        #                     sqrt(self.d.data["wRsw2"] ** 2 + self.d.data["wTsw2"] ** 2 + self.d.data["wNsw2"] ** 2))
        # else:
        #     self.d.data["wsw2"] = sqrt(
        #         self.d.data["wRsw2"] ** 2 + self.d.data["wTsw2"] ** 2 + self.d.data["wNsw2"] ** 2)
        #
        # if not "wHe1+2" in self.d.data.keys():
        #     self.d.add_data("wHe1+2",
        #                     getvelocity(4., 1., self.d.data["epq"].astype(int)) / around(self.d.data["vsw"], -1))
        # else:
        #     self.d.data["wHe1+2"] = getvelocity(4., 1., self.d.data["epq"].astype(int)) / around(
        #         self.d.data["vsw"], -1)

        # _________index 2 in names means vsw speed has been rounded__________
        if not "wRsw2" in self.d.data.keys():
            self.d.add_data("wRsw2", (self.d.data["vRsw2"].T / around(self.d.data["vsw"], -1)).T)
        else:
            self.d.data["wRsw2"] = (self.d.data["vRsw2"].T / around(self.d.data["vsw"], -1)).T
        if not "wTsw2" in self.d.data.keys():
            self.d.add_data("wTsw2", (self.d.data["vTsw2"].T / around(self.d.data["vsw"], -1)).T)
        else:
            self.d.data["wTsw2"] = (self.d.data["vTsw2"].T / around(self.d.data["vsw"], -1)).T
        if not "wNsw2" in self.d.data.keys():
            self.d.add_data("wNsw2", (self.d.data["vNsw2"].T / around(self.d.data["vsw"], -1)).T)
        else:
            self.d.data["wNsw2"] = (self.d.data["vNsw2"].T / around(self.d.data["vsw"], -1)).T
        if not "wsw2" in self.d.data.keys():
            self.d.add_data("wsw2",
                            sqrt(self.d.data["wRsw2"] ** 2 + self.d.data["wTsw2"] ** 2 + self.d.data["wNsw2"] ** 2))
        else:
            self.d.data["wsw2"] = sqrt(
                self.d.data["wRsw2"] ** 2 + self.d.data["wTsw2"] ** 2 + self.d.data["wNsw2"] ** 2)

        if not "wHe1+2" in self.d.data.keys():
            self.d.add_data("wHe1+2",
                            getvelocity(4., 1., self.d.data["epq"].astype(int)) / around(self.d.data["vsw"], -1))
        else:
            self.d.data["wHe1+2"] = getvelocity(4., 1., self.d.data["epq"].astype(int)) / around(
                self.d.data["vsw"], -1)
