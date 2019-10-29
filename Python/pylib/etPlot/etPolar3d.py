#{{{Documentation and Import
"""
This routine is used to create a Color Contour Plot in polar coordinates using Gnuplot.py
Klasse polar3D
authout: Christian drews <drews@physik.uni-kiel.de>
last update: 08.03.2011
"""

from numpy import array, max, min, nonzero, zeros, cos, sin, arange, pi, linspace,log10
from Gnuplot import Gnuplot, Data
#}}}
class polar3D:
	def __init__(self,data,angular_bins,radial_bins):
		"""
		Method: __init__(data,angular_bins,radial_bins)
		The polar3D class is used to creates a color contour plot using Gnuplot.py in polar coordinates. 
		The countour pixel will therefore be small fraction of a circles depending on the chosen angular bins and 
		radial bins. Typical application would be to show the angular dependence of a spectrum.

		INPUT: data - which should be a list or numpy array containing the bin intensity for each angular
			      bin and radial bin. Must have the dimension: [x: len(angular_bins), y: len(radial_bins)]
		       angular_bins - should be a list or numpy array of the linear-spaced angular bins used in 'data'
		       radial_bins - should be a list or numpy array of the linear-spaced radial bins used in 'data'

		Available Methods: (use help('method') in ipython to learn more)

		self.plot()    - Plots the data
		self.reset()   - Resets the plot
		self.save(filename) - saves the plot to an eps
		self.set_title(arg) - set the plot title
		self.set_label(arg) - set the plot xy label
		self.set_cblabel(arg) - set the plot colorbar label
		self.set_range(arg) - set the maximum r-range of the plot
		self.set_tics(ticlist,ticlabels=arg) - define your own tics
		self.add_2ddata(data) - This adds additional 2d date to the plot
		self.cbtics(cbtics,cb_labels=arg)  - define you own cb tics
		self.grid(trig,angles=arg,color=arg,solid=arg) - turn on the polar grid
		self.set_log(arg) -Turn on logarithmic cb

		AN EXAMPLE HOW TO USE THIS CLASS IS SHOWN AT THE END OF THIS FILE!
		"""
		self.data=array(data)
		self.angular_bins=array(angular_bins)
		self.radial_bins=array(radial_bins)
		self.data2d = []
		if len(self.data[:,0])!=len(self.angular_bins) or len(self.data[0,:])!=len(self.radial_bins):
			print "--- Dimension of DATA %s differs from angular bins %s or radial bins %s! ---"%(self.data.shape,self.angular_bins.shape,self.radial_bins.shape)
			print "--- Press Enter to Exit! ---"
			raw_input()
			exit()
		self.log=0
		self.gp=Gnuplot()
		self.gp("set terminal x11 enhanced")
		self.gp("set size square")
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
		self.gp("set angles degrees")
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
	def __det_rgb__(self,rgb_color):
		"""
		This routine calculated the RGB from an rgb value (0-1020; calculated like i
		long(1020.*(counts-min_counts)/(max_counts-min_counts))).
		INPUT: rgb color value (0,1020)
		OUTPUT: r, g, b (0-255,0-255,0-255)
		"""
		if rgb_color>=765:
			r=255
			g=1020-rgb_color
			b=0
		elif 765>rgb_color>510:
			r=rgb_color-510
			g=255
			b=0
		elif 510>=rgb_color>255:
			r=0
			g=rgb_color-255
			b=510-rgb_color
		elif 255>=rgb_color>0:
			r,g=0,0
			b=rgb_color
		else:
			r,g,b=0,0,0
		if rgb_color==-1: r,g,b=0,0,1
		if rgb_color==0: r,g,b=255,255,255
		if rgb_color==0: r,g,b=1,0,0
		return r,g,b
	def __create_gpdata__(self):
		"""
		This routine create a Gnuplot data object from the given data, angular bins and radial bins
		"""
		self.__det_cbtics__()
		if self.log:
			max_counts=log10(max(self.data[nonzero(self.data)]))
			min_counts=log10(min(self.data[nonzero(self.data)]))
		else:
			max_counts=max(self.data)
			min_counts=min(self.data[nonzero(self.data)])
		self.gparray=[]
		for rindex,radius in enumerate(self.radial_bins):
			for aindex,angle in enumerate(self.angular_bins):
				counts=self.data[aindex,rindex]
				if counts>0:
					if self.log: counts=log10(counts)
					rgb_color=long(1020.*(counts-min_counts)/(max_counts-min_counts))
					r,g,b=self.__det_rgb__(rgb_color)
					r_s=radius-(self.radial_bins[1]-self.radial_bins[0])/2.
					r_e=radius+(self.radial_bins[1]-self.radial_bins[0])/2.
					a_s=angle-(self.angular_bins[1]-self.angular_bins[0])/2.
					a_e=angle+(self.angular_bins[1]-self.angular_bins[0])/2.
					a_s=angle
					a_e=angle+(self.angular_bins[1]-self.angular_bins[0])
					bin_koord=[]
					x1,y1=self.__polar_to_cart__(r_s,a_s)
					x2,y2=self.__polar_to_cart__(r_e,a_s)
					x3,y3=self.__polar_to_cart__(r_e,a_e)
					x4,y4=self.__polar_to_cart__(r_s,a_e)
					bin_koord.append([x1,y1])
					bin_koord.append([x2,y2])
					bin_koord.append([x3,y3])
					bin_koord.append([x4,y4])
					bin_koord.append([x1,y1])
					dataobj=Data(bin_koord,with_='filledcurves lc rgb "#%02X%02X%02X"'%(r,g,b))
					self.gparray.append(dataobj)
	def __det_cbtics__(self):
		"""
		This routine determines the cb tics drawn onto the colorbar
		"""
		max_counts=max(self.data)
		min_counts=min(self.data[nonzero(self.data)])
		cbrange=max_counts-min_counts
		tic_interval=[1,2,5]
		tic_level=range(long(log10(min_counts)-1),long(log10(max_counts)+1)+1)
		ntic_tmp=1e9
		for ti in tic_interval:
			for tl in tic_level:
				ntic=abs(round(cbrange/(ti*10**tl))-10)
				if ntic<ntic_tmp:
					cti,ctl=ti,tl
					ntic_tmp=ntic
		if cti==5:self.mtn=5.
		if cti==1:self.mtn=10.
		if cti==2: self.mtn=4.
		if self.log:
			self.cb_tics=arange(tic_level[0],tic_level[-1])
		else:
			self.cb_tics=arange(10**tic_level[0],10**tic_level[-1],cti*10**ctl)-10**tic_level[0]
		self.cb_labels=None
	def __create_colorbar__(self):
		"""
		This routine creates the colorbar for the contour plot
		"""
		if self.log:
			max_counts=log10(max(self.data[nonzero(self.data)]))
			min_counts=log10(min(self.data[nonzero(self.data)]))
		else:
			max_counts=max(self.data)
			min_counts=min(self.data[nonzero(self.data)])
		cbrange=max_counts-min_counts
		if self.log:
			mtn=10.
		else:
			mtn=self.mtn
		cb_tics=self.cb_tics
		cbw=self.cb_tics[1]-self.cb_tics[0]
		xs,xe=1.05,1.1
		self.gp("set arrow from graph %s, graph -0.01 to graph %s, graph 1. nohead"%(xs,xs))
		self.gp("set arrow from graph %s, graph -0.01 to graph %s, graph 1. nohead"%(xe,xe))
		self.gp("set arrow from graph %s, graph -0.01 to graph %s, graph -0.01 nohead"%(xs,xe))
		self.gp("set arrow from graph %s, graph 1. to graph %s, graph 1. nohead"%(xs,xe))
		for rgb_color in arange(0,1020.):
			r,g,b=self.__det_rgb__(rgb_color)
			ys=rgb_color/1020.-0.01
			ye=rgb_color/1020.

			self.gp('set obj %s rect from graph %s, graph %s to graph %s, graph %s fc rgb "#%02X%02X%02X" fs noborder'%(rgb_color+1,xs,ys,xe,ye,r,g,b))
		for index,t in enumerate(cb_tics):
			rgb_color=long(1020.*(float(t)-min_counts)/cbrange)
			ye=rgb_color/1020.
			if t>min_counts and t<max_counts:
				self.gp("set arrow from graph %s, graph %s to graph %s, graph %s nohead"%(xs,ye,xs+(xe-xs)*0.3,ye))
				self.gp("set arrow from graph %s, graph %s to graph %s, graph %s nohead"%(xe,ye,xe-(xe-xs)*0.3,ye))
				if self.cb_labels==None:
					if self.log:
						self.gp("set label '10^{%s}' at graph %s, graph %s front"%(t,xe+(xe-xs)*0.4,ye))
					else:
						self.gp("set label '%s' at graph %s, graph %s front"%(t,xe+(xe-xs)*0.4,ye))
				else:
					self.gp("set label '%s' at graph %s, graph %s front"%(self.cb_labels[index],xe+(xe-xs)*0.4,ye))
			if self.log:
				mts=log10(arange(10**t,10**(t+1),10**t)) #HIER WEITER
			else:
				mts=range(long(mtn)) #HIER WEITER
			for mt in mts:
				if self.log:
					mtic=mt
				else:
					mtic=t+(mt/mtn)*cbw
				if mtic>min_counts and mtic<max_counts:
					if self.log:
						rgb_color=long(1020.*(mtic-min_counts)/cbrange)
					else:
						rgb_color=long(1020.*(t+(mt/mtn)*cbw-min_counts)/cbrange)
					ye=rgb_color/1020.
					self.gp("set arrow from graph %s, graph %s to graph %s, graph %s nohead"%(xs,ye,xs+(xe-xs)*0.15,ye))
					self.gp("set arrow from graph %s, graph %s to graph %s, graph %s nohead"%(xe,ye,xe-(xe-xs)*0.15,ye))
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
			corner - if 0 title is put on top of the plot, if 1 title is put in lower left corner 
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
	def set_cblabel(self,label,xoff=0,yoff=0):
		"""
		This routine sets the cb label
		INPUT: label - string of the cblabel
		       xoff - optional offset to the label in x direction
		       yoff - optional offset to the label in y direction
		"""
		x,y=1.23,0.6
		self.gp("set label '%s' at graph %s, graph %s rotate by 90 right front"%(label,x+xoff,y+yoff))
	def set_range(self,arg):
		"""
		This routine sets the r-range of the plot
		"""
		self.gp("set xrange [-%s:%s]"%(arg,arg))
		self.gp("set yrange [-%s:%s]"%(arg,arg))
	def set_tics(self,tics,ticlabels=None):
		"""
		Explicitly gives tics to the plot. This also affects at what location the polar grid is drawn
		INPUT: tics      - list of tics (e.g. [0,10,12,13,25])
		       ticlabels - corresponding tic labels (e.g. ["ZERO","TEN","TWELVE","THIRTEEN","TWENTYFIVE"])
		                 -- if names is not given, the tic location is used as a ticlabel instead --
		"""
		ticlabel=""
		if ticlabels!=None:
			if len(tics)!=len(ticlabels):
				print " --- Tics and ticlabels must have the same size! ---"
				print " --- Ignoring call of set_tics! ---"
				return 0
		for index,tic in enumerate(tics):
			if ticlabels!=None:
				ticlabel+="'%s' %s,"%(ticlabels[index],tic)
			else:
				ticlabel+="'%s' %s,"%(tic,tic)
		self.gp("set xtics out (%s) rotate by -90"%(ticlabel[0:-1]))
		self.gp("set ytics out (%s)"%(ticlabel[0:-1]))
	def set_cbtics(self,cb_tics,cb_labels=None):
		"""
		This routine sets the tics for the colorbar
		INPUT: cbtics - list of cbtics (e.g. [10,100,1000])
		       cb_labels - list of cbticlabels
		       -- if cbticlabels are not given, the cbtics are used as labels instead
		"""
		self.cb_tics=cb_tics
		self.cb_labels=cb_labels
		self.mtn=0
	def add_2ddata(self,data,linewidth=2,color='red'):
		"""
		Here you can add additional 2 dimensional data to the color contour plot
		INPUT: data (must be of dimension of angular_bins, values must be in range of radial_bins)
		       linewidth of the data
		       color of the data
		"""
		from numpy import append
		datax,datay = self.__polar_to_cart__(append(data,data[0]),append(self.angular_bins,self.angular_bins[0]))
		dataobj = Data(datax,datay,with_="lines lw %s lc rgb '%s'"%(linewidth,color))
		self.data2d.append(dataobj)
	def set_grid(self,trig,angles=45,color='black',solid=1,linewidth=0.5):
		"""
		Here you can turn the grid on and off
		INPUT: trig - (0 for 'off', 1 for 'on')
		       angles - number of radial lines in polar grid
		       color - color of the grid
		INPUT: trig - (0 for 'off', 1 for 'on')
		"""
		if trig==1:
			self.gp("set grid xtics nomxtics polar %s"%(angles))
			self.gp("set grid xtics front lw %s"%(linewidth))
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
	def save(self,filename='polar.eps',font="Helvetica",fontsize=15):
		"""
		This routine saves the plot into an eps file
		INPUT: filename - filename
		       font - name of the eps font
		       fontsize- size of eps font
		"""
		self.gp.hardcopy(filename,enhanced=1,color=1,solid=1,fontname=font,fontsize=fontsize)
	def plot(self):
		"""
		This routine creates the Gnuplot plot
		"""
		self.__create_gpdata__()
		self.__create_colorbar__()
		if self.data2d:
			for d in self.data2d:
				self.gparray.append(d)
		self.gp.plot(*self.gparray)
	def kill_plot(self):
		"""
		Routines that kills the Gnuplot window
		"""
		del self.gp
		
if __name__=="__main__":
	#TYPICAL EXAMPLE HOW TO USE
	#FIRST CREATE SOME DATA
	a=zeros((36,100))+10.
	for i in range(len(a[:,0])):
		for j in range(len(a[0,:])):
			a[i,j]+=i+j
	b,c=linspace(0,350,36),range(100)

	#SECONDS CREATE POLAR3D PLOT INSTANCE
	test=polar3D(a,b,c)
	#THIRD SET OPTIONS
	test.set_grid(1,color="black",angles=20)
	test.set_label("RADIUS")
	test.set_tics([10,30,60,80],["C+","K^{+}","Spam","Eggs"])
	test.set_title("TEST TITLE",corner=1)
	test.set_cblabel("Intensity [kg/m^{3}]")
	from numpy import sin
	data2d = (sin(b*pi/180.*5)+2)*25
	test.add_2ddata(data2d, linewidth=2, color='blue')
	#test.set_log(1)
	#test.set_cbtics([1500,2000],cb_labels=["1S0o","200o"])

	#FOURTH PLOT
	test.plot()
	test.save("/home/ep226/drews/Desktop/example_polar3d.eps")
	raw_input()
