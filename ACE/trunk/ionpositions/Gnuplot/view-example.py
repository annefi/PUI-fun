from mvc import *

plot=Plot("plotsettings.gpt")
# initialize plot with settings given in gpt file

# Gnuplot instance is accesible through
# plot.gp

# a list model, only x values
a=List([1,2,3,4,5,6], "x")
# a file to plot 'as is'
b=File("/tmp/test")

plot.add(a)
plot.add(b)

plot.update() # displays plot and updates it, but only if changes have been made in a or b


# starts a asynchronous plot update thread which will
# update the plot as soon as there are any changes, but
# not more often than every tmin seconds.
plot.asyncUpdate(True, tmin=1.0, input=False)
# if input is true, mouse clicks are received and will be
# forwarded to all plots

# kill automatic update thread, if it existed
plot.asyncUpdate(False)


# will change the plot to line type
a.options+=[("with", "lines")]


# Mouse click interaction:
# a.onClick(...) will be called for any mouse click done on the Gnuplot interface, as
# long as this is enabled.




