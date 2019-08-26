PRO plot_t_spec, x_range, fx1, fx2, name 

		SET_PLOT,'ps',/copy,/interpolate

		DEVICE,FILE=name,XSIZE=29.,YSIZE=19.,/LANDSCAPE,YOFFSET=29.,XOFFSET=0.

		PLOT,fx1,XRANGE=[x_range[0],x_range[1]],$
		TITLE=name,LINESTYLE = 0,THICK = 3,POS=[0.1,.1,0.9,0.9]

		OPLOT,fx2,THICK=3,LINESTYLE=2

		DEVICE,/CLOSE	
END
