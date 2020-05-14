"""
Date: 28.01.2015

authors: <drews@physik.uni-kiel.de>, <berger@physik.uni-kiel.de>
"""

import matplotlib as mpl
import numpy as np
import _operators
import pylab


class ShowMask(object):

    def __init__(self, dbData, smask, cmask):
        """
        Class for vizualizing the current masks of dbData. Can be used to alter some
        options and values set on any given mask
        INPUT: dbDATA; instance of dbData
        smask; list of masks masks that are drawn
        """
        np.seterr(all="ignore")
        self.db = dbData
        self.smask = smask
        self.cmask = cmask
        self.ph = 0.8  # Panel Height
        self.axes = {}

    def _prepare_ax(self, kindex, key):
        """
        Routine that prepares the figure
        """
        # Nmask = np.sum(self.mask[key].get()*self.DM())
        ax = pylab.axes([0.1, 0.1 + kindex * self.ph, 0.6, self.ph])
        ax2 = pylab.axes([0.7, 0.1 + kindex * self.ph, 0.2, self.ph])
        ax.set_ylabel("%s" % self.db.mp[key].get("name"),
                      backgroundcolor=self.db.mp[key].get("color"), color="white",
                      weight="bold", fontsize=9)
        for i in ["bottom", "top", "left", "right"]:
            ax.spines[i].set_linewidth(3)
            ax2.spines[i].set_linewidth(3)
            ax.spines[i].set_zorder(50)
        ax.yaxis.set_ticks([])
        ax.yaxis.set_ticklabels([])
        ax.xaxis.set_ticklabels([])
        ax.set_xlim(-0.1, 1.1)
        ax.set_ylim(-0.0, 1.0)
        ax2.yaxis.set_ticks([])
        ax2.yaxis.set_ticklabels([])
        ax2.xaxis.set_ticklabels([])
        ax2.set_xlim(0, 1.4)
        ax2.set_ylim(0, 1)
        return ax, ax2

    def _get_cdata(self, prod, key):
        """
        This routine returns the data product which is used for comparison in show_mask.
        If self.cmask == False this will simply return the current data product array
        INPUT: prod; data product as a string
        OUTPUT: Comparison Data array, Number of total events within that array
        """
        if prod not in self.db.data:
            cdata = np.zeros(10, dtype="S100")
            cdata[9] = "User-Defined Submask: '%s'" % (prod)
            Nevents = np.sum(self.db.mask[self.cmask].get())
        elif prod == "appliedmasks":
            cdata = self.db.mask[key].appliedmasks
            Nevents = np.sum(self.db.mask[self.cmask].get())
        elif prod == "directmasks":
            cdata = self.db.mask[key].directmasks.keys()
            Nevents = np.sum(self.db.mask[self.cmask].get())
        elif self.cmask == False:
            cdata = self.db.data[prod]
            Nevents = len(self.db.data[prod])
        else:
            if key != "Master":
                cdata = self.db.data[prod][self.db.mask[self.cmask].get()]
                Nevents = np.sum(self.db.mask[self.cmask].get())
            else:
                cdata = self.db.data[prod]
                Nevents = len(self.db.data[self.db.data.keys()[0]])
        return cdata, Nevents

    def _prepare_product_plot(self, pindex, prod, key):
        """
        This routine plots the background bars for the show mask plot
        INPUT: TODO
        OUTPUT: TODO
        """
        ax = self.axes[key][0]
        cdata = self.cdata
        if prod in self.db.data and (prod != "appliedmasks") and (prod != "directmasks"):
            ax.text(0.01, self.ypos[pindex], self.db.dp[prod].get("name"),
                    horizontalalignment='left', verticalalignment="top",
                    fontsize=8, weight="bold", backgroundcolor="white",
                    rotation="horizontal", color=self.db.dp[prod].get("color"), zorder=12, clip_on=False)
        if not isinstance(cdata[0], str):
            minval = np.amin(cdata[~np.isinf(cdata) * ~np.isnan(cdata)])
            maxval = np.amax(cdata[~np.isinf(cdata) * ~np.isnan(cdata)])
            nanval = ~np.alltrue(~np.isnan(cdata))
            infval = ~np.alltrue(~np.isinf(cdata))
            rec2 = mpl.patches.Rectangle(
                (0., self.ypos[pindex] - self.dh), 1., self.dh,
                                                 color=self.db.dp[
                                                     prod].get("color"),
                                                 alpha=0.3)
            ax.add_patch(rec2)
            ax.plot([0., 0.], [self.ypos[pindex] - self.dh, self.ypos[pindex]],
                    "-", color=self.db.dp[prod].get("color"), lw=2)
            ax.plot([1., 1.], [self.ypos[pindex] - self.dh, self.ypos[pindex]],
                    "-", color=self.db.dp[prod].get("color"), lw=2)
            ax.text(-0.007, self.ypos[pindex] - self.dh, " %4.2f " % minval,
                    horizontalalignment='right', verticalalignment="bottom",
                    fontsize=6, clip_on=True, rotation="horizontal",
                    zorder=11, color=self.db.dp[prod].get("color"), weight="bold")
            ax.text(1.005, self.ypos[pindex], " %4.2f " % maxval,
                    horizontalalignment='left', verticalalignment="top",
                    fontsize=6, clip_on=True, rotation="horizontal",
                    zorder=11, color=self.db.dp[prod].get("color"), weight="bold")
            if nanval:
                ax.text(-0.007, self.ypos[pindex], " NAN ",
                        horizontalalignment='right', verticalalignment="top",
                        fontsize=6, clip_on=True, rotation="horizontal", weight="bold",
                        zorder=11, color="red")
            if infval:
                ax.text(1.005, self.ypos[pindex] - self.dh, " INF ",
                        horizontalalignment='left', verticalalignment="bottom",
                        fontsize=6, clip_on=True, rotation="horizontal", weight="bold",
                        zorder=11, color="red")
        elif prod == "appliedmasks":
            rec2 = mpl.patches.Rectangle(
                (0., self.ypos[pindex] - self.dh), 1., self.dh,
                                                 fill=False, ec="black", lw=2)
            ax.add_patch(rec2)
            vals = self.db.mask[key].appliedmasks
            ax.text(
                .5, self.ypos[pindex] - self.dh /
                    3., "Applied Masks : %i" % (len(vals)),
                    horizontalalignment='center', verticalalignment="center",
                    fontsize=6, clip_on=True, rotation="horizontal",
                weight="bold", zorder=11)
            if len(vals) > 9:
                for i, val in enumerate(vals[:8]):
                    ax.text(
                        0.1 + i *
                            0.1, self.ypos[
                                pindex] - self.dh * 2. / 3., "%s" % val,
                            horizontalalignment='center', verticalalignment="center",
                            fontsize=6, clip_on=True, rotation="horizontal",
                            backgroundcolor=self.db.mp[val].get("color"), weight="bold", zorder=11,
                            color="white")
                ax.text(
                    0.9, self.ypos[
                        pindex] - self.dh * 2. / 3., "%i more" % (len(vals) - 8),
                        horizontalalignment='center', verticalalignment="center",
                        fontsize=6, clip_on=True, rotation="horizontal",
                        weight="bold", zorder=11,
                        color="black")
            else:
                for i, val in enumerate(vals):
                    ax.text(
                        0.1 + i *
                            0.1, self.ypos[
                                pindex] - self.dh * 2. / 3., "%s" % val,
                            horizontalalignment='center', verticalalignment="center",
                            fontsize=6, clip_on=True, rotation="horizontal",
                            backgroundcolor=self.db.mp[val].get("color"), weight="bold", zorder=11,
                            color="white")
        elif prod == "directmasks":
            rec2 = mpl.patches.Rectangle(
                (0., self.ypos[pindex] - self.dh), 1., self.dh,
                                                 fill=False, ec="black", lw=2)
            ax.add_patch(rec2)
            vals = self.db.mask[key].directmasks.keys()
            ax.text(
                .5, self.ypos[pindex] - self.dh /
                    3., "Direct Masks : %i" % (len(vals)),
                    horizontalalignment='center', verticalalignment="center",
                    fontsize=6, clip_on=True, rotation="horizontal",
                    weight="bold", zorder=11)
            if len(vals) > 9:
                for i, val in enumerate(vals[:8]):
                    ax.text(
                        0.1 + i *
                            0.1, self.ypos[
                                pindex] - self.dh * 2. / 3., "%s" % val,
                            horizontalalignment='center', verticalalignment="center",
                            fontsize=6, clip_on=True, rotation="horizontal",
                            backgroundcolor="black", weight="bold", zorder=11,
                            color="white")
                ax.text(
                    0.9, self.ypos[
                        pindex] - self.dh * 2. / 3., "%i more" % (len(vals) - 8),
                        horizontalalignment='center', verticalalignment="center",
                        fontsize=6, clip_on=True, rotation="horizontal",
                        weight="bold", zorder=11,
                        color="black")
            else:
                for i, val in enumerate(vals):
                    ax.text(
                        0.1 + i *
                            0.1, self.ypos[
                                pindex] - self.dh * 2. / 3., "%s" % val,
                            horizontalalignment='center', verticalalignment="center",
                            fontsize=6, clip_on=True, rotation="horizontal",
                            backgroundcolor="black", weight="bold", zorder=11,
                            color="white")
        else:
            vals = np.unique(cdata)
            vals.sort()
            for i, val in enumerate(vals):
                ax.text(
                    0.1 + i *
                        0.15, self.ypos[pindex] - self.dh / 2., " %s " % val,
                        horizontalalignment='left', verticalalignment="center",
                        fontsize=6, clip_on=True, rotation="horizontal",
                        weight="bold", zorder=11)

    def _plot_line(self, ax, x1, x2, y):
        ax.plot([x1, x2], [y] * 2, linestyle="-", c="k", zorder=11)

    def _plot_marker(self, ax, marker, x, y, color="k"):
        """
        Routine to plot markers in show mask routine
        """
        if marker == "[":
            ax.plot(
                [x, x], [y - self.dh / 2., y + self.dh / 2.], lw=1.5, c=color, zorder=13)
            ax.plot([x, x - 0.005], [y + self.dh / 2.]
                    * 2, lw=1.5, c=color, zorder=13)
            ax.plot([x, x - 0.005], [y - self.dh / 2.]
                    * 2, lw=1.5, c=color, zorder=13)
        if marker == "]":
            ax.plot(
                [x, x], [y - self.dh / 2., y + self.dh / 2.], lw=1.5, c=color, zorder=13)
            ax.plot([x, x + 0.005], [y + self.dh / 2.]
                    * 2, lw=1.5, c=color, zorder=13)
            ax.plot([x, x + 0.005], [y - self.dh / 2.]
                    * 2, lw=1.5, c=color, zorder=13)
        if marker == "|":
            ax.plot(
                [x, x], [y - self.dh / 2., y + self.dh / 2.], lw=1.5, c=color, zorder=13)
        if marker == ">":
            ax.plot([x], [y], linestyle="", c=color,
                    marker=">", markersize=5, zorder=13)
        if marker == "<":
            ax.plot([x], [y], linestyle="", c=color,
                    marker="<", markersize=5, zorder=13)

    def _plot_greater(self, ax, sm, op_str):
        """
        Routine to plot "greater than / equal" operator in show mask
        """
        minv, maxv = (sm.arg[1] - self.minval) / float(self.vr), 1
        if minv < 0:
            minv = 0
        self._plot_marker(ax, ">", maxv, self.height)
        self._plot_line(ax, minv, maxv, self.height)
        if op_str in ["ge", ">="]:
            self._plot_marker(ax, "]", minv, self.height)
        else:
            self._plot_marker(ax, "[", minv, self.height)

        ax.text(
            minv + 0.005, self.height - self.dh / 2. * 0.9, " %s " % sm.arg[1],
                horizontalalignment='left', verticalalignment="bottom",
                fontsize=6, clip_on=True, rotation="horizontal", zorder=11,
                color="white", weight="bold")
        return minv, maxv

    def _plot_equal(self, ax, sm, prod):
        """
        Routine to plot "greater than / equal" operator in show mask
        """
        minv, maxv = (sm.arg[1] - self.minval) / float(self.vr), 1
        if minv < 0:
            minv = 0
        self._plot_marker(
            ax, "|", minv, self.height, color=self.db.dp[prod].get("color"))
        ax.text(minv + 0.005, self.height, " %s " % sm.arg[1],
                horizontalalignment='left', verticalalignment="center",
                fontsize=6, clip_on=True, rotation="horizontal", zorder=11,
                color=self.db.dp[prod].get("color"), weight="bold")
        return 0, 0

    def _plot_lesser(self, ax, sm, op_str):
        """
        Routine to plot "lesser than / equal" operator in show mask
        """
        minv, maxv = 0, (sm.arg[1] - self.minval) / float(self.vr)
        if maxv > 1:
            maxv = 1
        self._plot_marker(ax, "<", minv, self.height)
        self._plot_line(ax, minv, maxv, self.height)
        if op_str in ["le", "<="]:
            self._plot_marker(ax, "[", maxv, self.height)
        else:
            self._plot_marker(ax, "]", maxv, self.height)
        ax.text(
            maxv - 0.005, self.height + self.dh / 2. * 0.9, " %s " % sm.arg[1],
                horizontalalignment='right', verticalalignment="top",
                fontsize=6, clip_on=True, rotation="horizontal", zorder=11,
                color="white", weight="bold")
        return minv, maxv

    def _plot_between(self, ax, sm, op_str):
        """
        Routine to plot "between" operator in show mask
        """
        minv, maxv = (sm.arg[1] - self.minval) / float(
            self.vr), (sm.arg[2] - self.minval) / float(self.vr)
        if maxv > 1 or np.isnan(maxv):
            maxv = 1
        if minv < 0:
            minv = 0
        self._plot_line(ax, minv, maxv, self.height)
        if op_str in ["><", "bn"]:
            self._plot_marker(ax, "]", maxv, self.height)
            self._plot_marker(ax, "[", minv, self.height)
        else:
            self._plot_marker(ax, "[", maxv, self.height)
            self._plot_marker(ax, "]", minv, self.height)
        ax.text(
            minv + 0.005, self.height - self.dh / 2. * 0.9, " %s " % sm.arg[1],
                horizontalalignment='left', verticalalignment="bottom",
                fontsize=6, clip_on=True, rotation="horizontal", zorder=11,
                color="white", weight="bold")
        ax.text(
            maxv - 0.005, self.height + self.dh / 2. * 0.9, " %s " % sm.arg[2],
                horizontalalignment='right', verticalalignment="top",
                fontsize=6, clip_on=True, rotation="horizontal", zorder=11,
                color="white", weight="bold")
        return minv, maxv

    def _plot_percent(self, ax, prod, key):
        """
        This routine plots the percentage on the right site of show_mask plot
        """
        if prod != "appliedmasks" and prod != "directmasks":
            perc = float(
                np.sum(self.db.mask[key].calc_submask(prod) * self.db.mask["Master"].get())) / self.Nevents
            ax.plot([0, perc], [self.height] * 2,
                    color=self.db.dp[prod].get("color"), lw=2)
            ax.plot([perc], [self.height], color=self.db.dp[
                    prod].get("color"), ls="", marker="o", markersize=5)
            ax.text(perc + 0.05, self.height, "%i" % (perc * 100.) + "%",
                    horizontalalignment='left', verticalalignment="center",
                    fontsize=9, clip_on=True, rotation="horizontal", zorder=11)
        elif prod == "appliedmasks":
            if len(self.db.mask[key].appliedmasks) == 0:
                perc = 1.
            else:
                tmpma = np.ones(
                    self.db.mask["Master"].get().shape, bool) * self.db.mask["Master"].get()
                for k in self.db.mask[key].appliedmasks:
                    tmpma *= self.db.mask[k].get()
                perc = float(np.sum(tmpma)) / self.Nevents
            ax.plot([0, perc], [self.height] * 2, color="black", lw=2)
            ax.plot([perc], [self.height], color="black",
                    ls="", marker="o", markersize=5)
            ax.text(perc + 0.05, self.height, "%i" % (perc * 100.) + "%",
                    horizontalalignment='left', verticalalignment="center",
                    fontsize=9, clip_on=True, rotation="horizontal", zorder=11)
        elif prod == "directmasks":
            if len(self.db.mask[key].directmasks.keys()) > 0:
                tmpma = np.ones(
                    self.db.mask["Master"].get().shape, bool) * self.db.mask["Master"].get()
                for k in self.db.mask[key].directmasks.keys():
                    tmpma *= self.db.mask[key].directmasks[k]
                perc = float(np.sum(tmpma)) / self.Nevents
                ax.plot([0, perc], [self.height] * 2, color="black", lw=2)
                ax.plot(
                    [perc], [self.height], color="black", ls="", marker="o", markersize=5)
                ax.text(perc + 0.05, self.height, "%i" % (perc * 100.) + "%",
                        horizontalalignment='left', verticalalignment="center",
                        fontsize=9, clip_on=True, rotation="horizontal", zorder=11)

    def _plot_string(self, ax, prod, key):
        """
        This routine plots the equal operator for strings
        """
        vals = np.unique(self.cdata)
        vals.sort()
        for mindex, sm in enumerate(self.db.mask[key].submasks[prod]):
            try:
                pos = np.where(vals == sm.arg[1])[0][0]
            except:
                continue
            ax.text(0.1 + pos * 0.1, self.height, " %s " % vals[pos],
                    horizontalalignment='left', verticalalignment="center",
                    fontsize=6, clip_on=True, rotation="horizontal", weight="bold",
                    zorder=12, color=self.db.dp[prod].get("color"))

    def plot_ranges(self, pindex, prod, key):
        """
        This routine is used to plot the particular ranges of the given
        submask and data product
        INPUT: TODO
        OUTPUT: TODO
        """
        cdata = self.cdata
        ax = self.axes[key][0]
        ax2 = self.axes[key][1]
        if prod != "appliedmasks" and prod != "directmasks":
            if not isinstance(cdata[0], str):
                self.minval = np.amin(
                    cdata[~np.isinf(cdata) * ~np.isnan(cdata)])
                self.maxval = np.amax(
                    cdata[~np.isinf(cdata) * ~np.isnan(cdata)])
                self.vr = self.maxval - self.minval
                if self.vr == 0:
                    self.vr = 1
            self.height = self.ypos[pindex] - self.dh / 2.
            for mindex, sm in enumerate(self.db.mask[key].submasks[prod]):
                minv, maxv = 0, 0
                if 'op_str' in sm.kwarg:
                    op_str = sm.kwarg['op_str']
                    if sm.operator == _operators.std_ops and op_str in [">", "gt", "ge", ">="]:
                        minv, maxv = self._plot_greater(ax, sm, op_str)
                    if sm.operator == _operators.std_ops and op_str in ["<", "lt", "le", "<="]:
                        minv, maxv = self._plot_lesser(ax, sm, op_str)
                    if sm.operator == _operators.std_ops and op_str in ["><", "bn", ">=<", "be"]:
                        minv, maxv = self._plot_between(ax, sm, op_str)
                    if sm.operator == _operators.std_ops and op_str in ["==", "eq"] and not isinstance(cdata[0], str):
                        minv, maxv = self._plot_equal(ax, sm, prod)
                    if isinstance(cdata[0], str):
                        self._plot_string(ax, prod, key)
                if prod in self.db.data:
                    rec = mpl.patches.Rectangle(
                        (minv, self.ypos[pindex] - self.dh),
                                                       maxv - minv, self.dh,
                                                       color=self.db.dp[prod].get("color"))
                    ax.add_patch(rec)
                    self._plot_percent(ax2, prod, key)
        elif prod == "appliedmasks" or prod == "directmasks":
            self.height = self.ypos[pindex] - self.dh / 2.
            self._plot_percent(ax2, prod, key)

    def compute(self):
        """
        This routine computes the mask and performs all necessary operations
        """
        self.pylabsm2 = pylab.figure("Mask Overview")
        self.pylabsm2.clf()
        if self.smask == False:
            masks = self.db.mask.keys()
        else:
            masks = self.smask
        self.ph = 0.8 / len(masks)  # Panel height
        # Always show Master on top
        if "Master" in masks:
            masks.remove("Master")
            masks.append("Master")
        for kindex, key in enumerate(masks):
            self.axes[key] = self._prepare_ax(kindex, key)
            products = self.db.mask[key].submasks.keys()
            if len(self.db.mask[key].appliedmasks) > 0:
                products.append("appliedmasks")
            if len(self.db.mask[key].directmasks.keys()) > 0:
                products.append("directmasks")
            if len(products) == 0 and key == "Master":
                self.Nevents = float(
                    self.db.data[self.db.data.keys()[0]].shape[0])
                Nmask = np.sum(self.db.get_mask(key))
                self.axes[key][1].set_ylabel(
                    "%i/%i \n (%3.1f" % (Nmask, self.Nevents, float(Nmask) / self.Nevents * 100.) + "%)", fontsize=9)
                self.axes[key][1].yaxis.set_label_position("right")
                continue
            self.dh = .5 / len(products)  # Bar Height
            self.ypos = np.linspace(
                0., 1., len(products) + 2)[1:-1] + self.dh / 2.
            for pindex, product in enumerate(products):
                self.cdata, self.Nevents = self._get_cdata(product, key)
                self._prepare_product_plot(pindex, product, key)
                self.plot_ranges(pindex, product, key)
            Nmask = np.sum(self.db.get_mask(key))
            self.axes[key][1].set_ylabel(
                "%i/%i \n (%3.1f" % (Nmask, self.Nevents, float(Nmask) / self.Nevents * 100.) + "%)", fontsize=9)
            self.axes[key][1].yaxis.set_label_position("right")
