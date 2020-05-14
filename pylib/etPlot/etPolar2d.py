#{{{Documentation and Import
"""
This routine is used to create a Plot in polar coordinates using Gnuplot.py
Klasse polar3D
authout: Christian drews <drews@physik.uni-kiel.de>
last update: 24.08.2011
"""

from numpy import array, max, min, nonzero, zeros, cos, sin, arange, pi, linspace,log10
from Gnuplot import Gnuplot, Data
#}}}
class polar2D:
	def __init__(self,angular_bins,*datasets):
		"""
		Method: __init__(data,angular_bins)
		The polar2D class is used to create a plot using Gnuplot.py in polar coordinates. 
		Typical application would be to show the angular dependence of Count Rates.

		INPUT: datasets - a list of CR, that have the same dimension as angular_bins
		       angular_bins - should be a list or numpy array of the linear-spaced angular bins used in 'data'

		Available Methods: (use help('method') in ipython to learn more)

		AN EXAMPLE HOW TO USE THIS CLASS IS SHOWN AT THE END OF THIS FILE!
		"""
		self.data = []
		for d in datasets:
			self.data.append(array(d))
		self.len_data = len(self.data)
		self.angular_bins=array(angular_bins)
		if len(self.data[0])!=len(self.angular_bins):
			print "--- Dimension of DATA %s differs from angular bins %s! ---"%(self.data[0].shape,self.angular_bins.shape)
			print "--- Press Enter to Exit! ---"
			raw_input()
			exit()
		self.log=0
		self.gp=Gnuplot()
		self.gp("set terminal x11 enhanced")
		self.gp("set size square")
		self.gp("set xlabel ''")
		self.gp("set ylabel ''")
		self.gp("set xtics out autofreq")
		self.gp("set ytics out autofreq")
		self.gp("set mxtics")
		self.gp("set mytics")
		self.gp("unset title")
		self.gp("unset grid")
		self.gp("set angles degrees")
		self.plotmode='S'
		self.set_data_label(["" for i in range(self.len_data)])
	def __polar_to_cart__(self,r,phi):
		"""
		This routine transforms polar coordinates to carthesian coordiantes 
		INPUT: r, phi (polar coord (phi in degree from 0 to 360))
		OUTPUT: x, y in carth. coord
		"""
		phi=360.-phi
		deg_to_arcsec=(2*pi)/360.
		x=r*cos(phi*deg_to_arcsec)
		y=r*sin(phi*deg_to_arcsec)
		return x,y
	def __create_gpdata__(self):
		"""
		This routine create a Gnuplot data object from the given data, angular bins and radial bins
		"""
		"""
		if self.log:
			max_counts=log10(max(self.data[nonzero(self.data)]))
			min_counts=log10(min(self.data[nonzero(self.data)]))
		else:
			max_counts=max(self.data)
			min_counts=min(self.data[nonzero(self.data)])
		"""
		self.gparray=[]
		for data_i,data in enumerate(self.data):
			data-=min(data)
			if self.log: data = log10(data+0.01)
			if self.plotmode=='T':
				data_processed = data/max(data)+0.5 + data_i * 0.
			elif self.plotmode=='S':
				data_processed = data/max(data)+0.5 + data_i * 1.
			datax, datay = self.__polar_to_cart__(data_processed,self.angular_bins)
			dataobj=Data(datax,datay,with_="lines lw 2")
			self.gparray.append(dataobj)
 	def reset(self):
		"""
		This routine resets the current plot window to standard options
		If you change certain parameters (like self.log) you may want to run this again to update the data
		This also 
		"""
		self.__create_gpdata__()
		self.gp=Gnuplot()
		self.gp("set xrange [-%s:%s]"%(self.radial_bins[-1],self.radial_bins[-1]))
		self.gp("set yrange [-%s:%s]"%(self.radial_bins[-1],self.radial_bins[-1]))
		self.gp("set xlabel ''")
		self.gp("set ylabel ''")
		self.gp("set xtics out autofreq")
		self.gp("set ytics out autofreq")
		self.gp("set mxtics")
		self.gp("set mytics")
		self.gp("unset title")
		self.gp("unset grid")
		self.gp("unset label")
		self.gp("unset title")
		self.cb_labels=None
		self.__det_cbtics__()
	def set_title(self,title,corner=0):
		"""
		This routine sets the title
		INPUT: 
			title - title of the plot as a string
			corner - is 0 title is put on top of plot, if 1 title is put in lower left corner
		"""
		if corner==0:
			self.gp("set title '%s'"%(title))
		else:
			self.gp("set label '%s' at graph %s, graph %s"%(title, 0.02,0.03))
	def set_label(self,label):
		"""
		This routine set the x and y label
		"""
		self.gp("set xlabel '%s'"%(label))
		self.gp("set ylabel '%s'"%(label))
	def set_data_label(self,data_labels):
		"""
		Explicitly gives data labels to each data set
		INPUT: 
		       datalabels - corresponding to number of datasets (e.g. ["ZERO","TEN","TWELVE","THIRTEEN","TWENTYFIVE"])
		"""
		if self.plotmode=="S":
			datalabel = ""
			for dindex in range(self.len_data):
				tic = dindex + 0.5
				datalabel+="'%s' %s,"%(data_labels[dindex],tic)
			self.gp("set xtics out (%s) rotate by -90"%(datalabel[0:-1]))
			self.gp("set ytics out (%s)"%(datalabel[0:-1]))
		elif self.plotmode=="T":
			for dindex in range(self.len_data):
				self.gp("set label '%s' at graph %s, graph %s textcolor lt %s"%(data_labels[dindex],0.03,0.97-0.035*dindex,dindex+1))
	def set_grid(self,trig,angles=45,color='black',solid=1):
		"""
		Here you can turn the grid on and off
		INPUT: trig - (0 for 'off', 1 for 'on')
		       angles - number of radial lines in polar grid
		       color - color of the grid
		"""
		if trig==1:
			self.gp("set grid xtics nomxtics polar %s"%(angles))
			self.gp("set grid xtics front lw 0.5")
			self.gp("set grid linecolor rgb '%s'"%(color))
			if solid==1:
				self.gp("set grid linetype 1")
			else:
				self.gp("set grid linetype 0")
			for ang in arange(0,360,angles):
				x,y=self.__polar_to_cart__(0.45,ang)
				self.gp("set label '%s {/Symbol \260}' at graph %s, graph %s textcolor rgb '%s' front"%(ang,x+0.47,y+0.49,color))
		else:
			self.gp("unset grid")
	def set_raxis(self,color="black"):
		"""
		Here you can turn on an additional axis with tics on it 
		This is only possible in plotstyle T !!
		INPUT: color - color of the raxis
		"""
		if self.plotmode=="T":
			xtics = ""
			for major_t in [0,0.2,0.4,0.6,0.8,1.]:
				xtics+="'%s' %s,"%(major_t,major_t+0.5)
				self.gp("set arrow from first %s, first -0.04 to \
					 first %s, first 0.04 \
					 nohead lc rgb '%s' lw 0.3"%(major_t+0.5,major_t+0.5,color))
				self.gp("set arrow from first %s, first -0.04 to \
					 first %s, first 0.04 \
					 nohead lc rgb '%s' lw 0.3"%(-major_t-0.5,-major_t-0.5,color))
				self.gp("set arrow from first -0.04, first %s to \
					 first 0.04, first %s \
					 nohead lc rgb '%s' lw 0.3"%(major_t+0.5,major_t+0.5,color))
				self.gp("set arrow from first -0.04, first %s to \
					 first 0.04, first %s \
					 nohead lc rgb '%s' lw 0.3"%(-major_t-0.5,-major_t-0.5,color))
			for minor_t in linspace(0,1,49):
				self.gp("set arrow from first %s, first -0.02 to \
					 first %s, first 0.02 \
					 nohead lc rgb '%s' lw 0.1"%(minor_t+0.5,minor_t+0.5,color))
				self.gp("set arrow from first %s, first -0.02 to \
					 first %s, first 0.02 \
					 nohead lc rgb '%s' lw 0.1"%(-minor_t-0.5,-minor_t-0.5,color))
				self.gp("set arrow from first -0.02, first %s to \
					 first 0.02, first %s \
					 nohead lc rgb '%s' lw 0.1"%(minor_t+0.5,minor_t+0.5,color))
				self.gp("set arrow from first -0.02, first %s to \
					 first 0.02, first %s \
					 nohead lc rgb '%s' lw 0.1"%(-minor_t-0.5,-minor_t-0.5,color))
			self.gp("set xtics out (%s)"%(xtics[:-1]))
			self.gp("set ytics out (%s)"%(xtics[:-1]))
		else: 
			print "Wrong plotmode %s for setting an r - axis! Please chose another plotmode"%(self.plotmode)
	def set_log(self,trig):
		"""
		Here you can turn on an logarithmic plot
		INPUT: trig - (0 for 'off', 1 for 'on')
		       -- Data set muste be reloaded, which could take while ---
		"""
		if trig==1:
			self.log=trig
		else:
			self.log=0
	def set_plotstyle(self,plotmode):
		"""
		This routines sets the plotstyle. 
		One can choose between plotmode 'S', which means plotting each data set separatly onto a given y=0 line
		or plotmode 'T', which plots all datasets on one y=0 line
		"""
		if plotmode not in ["S","T"]:
			self.plotmode='S'
			print "Invalid Plotmode - Fall back to plotmode 'S'"
		else:
			self.plotmode=plotmode
	def save(self,filename='polar.eps',font="Helvetica",fontsize=15):
		"""
		This routine saves the plot into an eps file
		INPUT: filename - filename
		       font - name of the eps font
		       fontsize - size of the eps font 
		"""
		self.gp.hardcopy(filename,enhanced=1,color=1, solid=1, fontname=font, fontsize=fontsize)
	def plot(self):
		"""
		This routine creates the Gnuplot plot
		"""
		self.__create_gpdata__()
		if self.plotmode=='T':
			self.gp("set xrange[-1.9:1.9]")
			self.gp("set yrange[-1.9:1.9]")
			#self.gp("set tic scale 0")
		elif self.plotmode=='S':
			self.gp("set xrange[-%s:%s]"%(self.len_data+1.5,self.len_data+1.5))
			self.gp("set yrange[-%s:%s]"%(self.len_data+1.5,self.len_data+1.5))

		self.gp.plot(*self.gparray)
	def kill_plot(self):
		"""
		Routines that kills the Gnuplot window
		"""
		del self.gp
		
if __name__=="__main__":
	#TYPICAL EXAMPLE HOW TO USE
	#FIRST CREATE SOME DATA
	from numpy import sin, cos, tan
	angular_bins = linspace(0,2*pi,360)
	data1 = cos(angular_bins*3)
	data2 = cos(angular_bins*30)
	data3 = sin(angular_bins*10)
	data4 = cos(angular_bins*15)
	data5 = sin(angular_bins*5)

	#SECONDS CREATE POLAR2D PLOT INSTANCE
	test=polar2D(angular_bins/pi*180.,data1,data2,data3,data4, data5)
	test.set_plotstyle('T')
	#THIRD SET OPTIONS
	test.set_title("Test Plot", corner=1)
	#test.set_log(1)
	test.set_data_label(["Data 1","Data 2","Data 3","Data 4","Data 5"])
	test.set_grid(1)
	test.set_raxis(color="black")

	#FOURTH PLOT
	test.plot()
	test.save("/home/ep226/drews/Desktop/example_polar2d.eps")
	raw_input()
