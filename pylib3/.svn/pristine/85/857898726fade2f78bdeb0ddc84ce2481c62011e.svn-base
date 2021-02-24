"""
Data: 28.01.2015
Authors: <drews@physik.uni-kiel.de>, <berger@physik.uni-kiel.de>
"""

# Imports TODO


class DataContainer(object):

    """
    Class which stores the data generated during plotting, depending on the
    type of plot:
    hist1d: Stores bins and histogram as returned by
            numpy.histogram for every plotted mask in a dictionary
    hist2d: Stores
    xbins, ybins and histogram as returned by numpy.histogram2d for every
            plotted mask in a dictionary
    timeseries: Stores xdata and a dictionary
            of plotted dataproducts for every plotted mask in a dictionary
    """

    def __init__(self, plot_type, dbData=None):
        """
        INPUT: plot_type - determined hte plot type of the data (hist1d, hist2d, ...)
               dbData - instance of the dbData class
        """
        self.plot_type = plot_type
        self.prodx = None
        self.prody = None
        self.prodz = None
        self.dbData = dbData
        self.data = {}

    def add_data(self, mask, data, prodx=False, prody=False, prodz=False, norm=False):
        """
        Add data to to the plot_data class
        INPUT: MASK - name of the mask that is added
               data - data of the mask
               prodx - x data product label
               prody - y data product label
               prodz - z data product label
        """
        self.prodx = prodx
        self.prody = prody
        self.prodz = prodz
        self.norm = norm
        if self.plot_type in ["hist1D", "hist2D", "timeseries"]:
            self.data.update({mask: data})

    def get_data(self, smask=False):
        """
        Returns the Data of the given Mask
        INPUT: smask: list of masks
        """
        if not smask:
            out = self.data
        elif isinstance(smask, list):
            out = {}
            for mask in smask:
                out.update({mask: self.data[mask]})
        else:
            out = self.data[smask]
        return out

    def save_ascii(self, filename="foobar", lower_lim=0, upper_lim=1e10):
        """
        Routine to save the data of a given plot into ascii file ('filename')
        INPUT: upper_lim, lower_lim (float, float)
                  -> Data is only saved if lower_lim<value<upper_lim, if either is set to False all data is saved
        """
        if self.plot_type == "timeseries":
            print("Writing Data into file %s" % (filename + "_" + self.plot_type + ".dbData"))
            data_file = open(filename + "_" + self.plot_type + ".dbData", "w")
            data_file.write("### Header Start \n")
            data_file.write("## Mask Info \n")
            for key in self.prodz:
                data_file.write("Mask: " + self.dbData.mp[key].get(
                    "name") + " / Plottype: %s \n" % (self.plot_type))
                submask = self.dbData.mask[key]
                for SM in submask.submasks:
                    data_file.write(
                        "# %s: " % (self.dbData.dp[SM].get("name")))
                    for args in submask.submasks[SM]:
                        data_file.write(
                            "[op='%s', arg=%s] / " % (args.operator, args.arg))
                data_file.write("\n")
            data_file.write("## Mask Info End \n")
            data_file.write("Prodx:%s   " %
                            self.dbData.dp[self.prodx].get("name"))
            for key in sorted(self.data.keys()):
                data_file.write("Prody:%s   " % (key))
            data_file.write("\n")
            data_file.write("### Header End \n")
            time = self.data[self.data.keys()[0]][-1]
            for tindex, t in enumerate(time):
                data_file.write("%s   " % (t))
                for key in sorted(self.data.keys()):
                    if lower_lim < self.data[key][0][tindex] < upper_lim or lower_lim == False or upper_lim == False:
                        data_file.write("%s   " % (self.data[key][0][tindex]))
                data_file.write("\n")
            data_file.close()
            return
        for key in self.data:
            print("Writing Data into file %s" % (filename + "_" + key + ".dbData"))
            data_file = open(
                filename + "_" + key + "_" + self.plot_type + ".dbData", "w")
            data_file.write("### Header Start \n")
            data_file.write("Mask: " + self.dbData.mp[key].get(
                "name") + " / Plottype: %s \n" % (self.plot_type))
            data_file.write("## Mask Info \n")
            submask = self.dbData.mask[key]
            for SM in submask.submasks:
                data_file.write("# %s: " % (self.dbData.dp[SM].get("name")))
                for args in submask.submasks[SM]:
                    data_file.write(
                        "[op='%s', arg=%s] / " % (args.operator, args.arg))
                data_file.write("\n")
            data_file.write("## Mask Info End \n")
            if self.plot_type == "hist2D":
                data_file.write("Prodx:%s     Prody:%s     Prodz:%s     Norm:%s \n" %
                                (self.dbData.dp[self.prodx].get("name"), self.dbData.dp[self.prody].get("name"), self.prodz, self.norm))
                data_file.write("### Header End \n")
                C, X, Y = self.data[key]
                for xindex, x in enumerate(X[:-1]):
                    for yindex, y in enumerate(Y[:-1]):
                        if lower_lim < C[xindex, yindex] < upper_lim:
                            data_file.write(
                                "%s %s %s \n" % (x, y, C[xindex, yindex]))
            if self.plot_type == "hist1D":
                data_file.write("Prodx:%s     Norm:%s \n" %
                                (self.dbData.dp[self.prodx].get("name"), self.norm))
                data_file.write("### Header End \n")
                C, X = self.data[key]
                for xindex, x in enumerate(X[:-1]):
                    if lower_lim < C[xindex] < upper_lim:
                        data_file.write("%s %s \n" % (x, C[xindex]))
            data_file.close()
