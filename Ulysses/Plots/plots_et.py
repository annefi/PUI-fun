import matplotlib
import matplotlib.pyplot as plt
import matplotlib.colors as colors
import matplotlib.ticker as ticker
from numpy import *
from pylib import dbData
import sys
from DataLoader.uswipha import uswipha
from mpl_toolkits.axes_grid1 import make_axes_locatable


matplotlib.rcParams.update({'font.size': 12,
                            'xtick.major.size': 8,
                            'xtick.major.width': 1.0,
                            'xtick.minor.size': 5,
                            'xtick.minor.width': 1,
                            'ytick.major.size': 8,
                            'ytick.major.width': 1.0,
                            'ytick.minor.size': 5,
                            'ytick.minor.width': 1,
                            'xtick.direction': 'inout',
                            'ytick.direction': 'inout',
                            'figure.subplot.left':0.12,
                            'figure.subplot.bottom': 0.15,
                            'figure.subplot.right': 0.9,
                            'figure.subplot.top': 0.94,
                            'figure.figsize': (7,4.5)})

#matplotlib.rcParams['figure.figsize'] = 5, 10



def plot_et_matrix():
    d = uswipha(year = [1993,1994], tf = [[1,366]])
    d.set_mask('Master','epq',24,24)
    d.set_mask('Master','ech',10,2400)

    d.hist2d('tch','ech',binx = arange(240,560), biny = arange(0,130),
             xlabel = 'TCH', ylabel = 'ECH', cb = 'counts', style = 'contour')


def plot_epq_all():
    d = uswipha(year = [1993,1994], tf = [[1,6]])
    d.set_mask('Master','ech',10,2400)
    d.hist2d('tch', 'epq', binx=arange(200, 430), biny=arange(0, 65),
             xlabel='TCH', ylabel='ECH', cb='normalized counts', style='contour', norm = 'ymax')
    plt.savefig('test.pdf')


def plot_et_matrix_m():
    # manually without dbData
    d = uswipha(year = [1993,1994], tf = [[1,366]])
    d.set_mask('Master','epq',24,24)
    d.set_mask('Master','ech',10,2400)
    fig, ax = plt.subplots()
    valx = d.get_data('Master','tch')
    valy = d.get_data('Master','ech')
    binx = arange(250, 560)
    biny = arange(0, 130)
    C, X, Y = histogram2d(valx, valy, bins=[binx, biny])
    vmin = amin(C[C > 0])
    vmax = amax(C)
    colormap = plt.cm.get_cmap("viridis")
    colormap.set_under('white')
    Mesh = ax.pcolormesh(X, Y, C.T, cmap=colormap, rasterized=True, norm = colors.LogNorm(vmin =vmin,vmax = vmax))
    ax.xaxis.grid(True, c = 'k', ls = ':')
    ax.yaxis.grid(True, c = 'k', ls = ':')
    # colorbar:
    divider = make_axes_locatable(ax)
    cbax = divider.append_axes("right", size="5%", pad=0.05)
    cb = plt.colorbar(Mesh, cax=cbax)
    cb.ax.tick_params(labelsize=10)
    cb.set_label('counts')

    ax.set_xlabel('ToF Channel')
    ax.set_ylabel(r'$\mathrm{E_{SSD}}$ Channel')
    plt.savefig('Plots/et_matrix.pdf')



def plot_epq_all_m():
    # manually without dbData
    d = uswipha(year=[1993, 1994], tf=[[1, 366]])
    d.set_mask('Master', 'ech', 10, 2400)

    fig, ax = plt.subplots()
    valx = d.get_data('Master','tch')
    valy = d.get_data('Master','epq')
    binx = arange(180, 480)
    biny = arange(0, 66)
    C, X, Y = histogram2d(valx, valy, bins=[binx, biny])
    vmin = amin(C[C > 0])
    vmax = amax(C)
    colormap = plt.cm.get_cmap("viridis")
    colormap.set_under('white')
    Mesh = ax.pcolormesh(X, Y, C.T, cmap=colormap, vmin=vmin, vmax=vmax, rasterized=True, norm = colors.LogNorm(vmin =vmin,vmax = vmax))
    ax.xaxis.grid(True, c = 'k', ls = ':')
    ax.yaxis.grid(True, c = 'k', ls = ':')
    # colorbar:
    divider = make_axes_locatable(ax)
    cbax = divider.append_axes("right", size="5%", pad=0.05)
    cb = plt.colorbar(Mesh, cax=cbax)
    cb.ax.tick_params(labelsize=10)
    cb.set_label('counts')
    ax.set_xlabel('ToF Channel')
    ax.set_ylabel('ESA')
    plt.savefig('Plots/epq_all.pdf')



def plot_epq_rng0_m():
    d = uswipha(year=[1993, 1994], tf=[[1, 366]])
    d.set_mask('Master', 'ech', 10, 2400)
    d.set_mask('Master', 'rng', 0, 0)

    fig, ax = plt.subplots()
    valx = d.get_data('Master','tch')
    valy = d.get_data('Master','epq')
    binx = arange(180, 480)
    biny = arange(0, 66)
    C, X, Y = histogram2d(valx, valy, bins=[binx, biny])
    vmin = amin(C[C > 0])
    vmax = amax(C)
    colormap = plt.cm.get_cmap("viridis")
    colormap.set_under('white')
    Mesh = ax.pcolormesh(X, Y, C.T, cmap=colormap, vmin=vmin, vmax=vmax, rasterized=True, norm = colors.LogNorm(vmin =vmin,vmax = vmax))
    ax.xaxis.grid(True, c = 'k', ls = ':')
    ax.yaxis.grid(True, c = 'k', ls = ':')
    # colorbar:
    divider = make_axes_locatable(ax)
    cbax = divider.append_axes("right", size="5%", pad=0.05)
    cb = plt.colorbar(Mesh, cax=cbax)
    cb.ax.tick_params(labelsize=10)
    cb.set_label('counts')
    ax.set_xlabel('ToF Channel')
    ax.set_ylabel('ESA')
    plt.savefig('Plots/epq_rng0.pdf')


def plot_epq_He1_m():
    d = uswipha(year=[1993, 1994], tf=[[1, 366]], path = '/home/asterix/fischer/PUI/Ulysses/data_misc/pha_he/')
    fig, ax = plt.subplots()
    valx = d.get_data('Master','tch')
    valy = d.get_data('Master','epq')
    binx = arange(180, 480)
    biny = arange(0, 66)
    C, X, Y = histogram2d(valx, valy, bins=[binx, biny])
    vmin = amin(C[C > 0])
    vmax = amax(C)
    colormap = plt.cm.get_cmap("viridis")
    colormap.set_under('white')
    Mesh = ax.pcolormesh(X, Y, C.T, cmap=colormap, vmin=vmin, vmax=vmax, rasterized=True, norm = colors.LogNorm(vmin =vmin,vmax = vmax))
    ax.xaxis.grid(True, c = 'k', ls = ':')
    ax.yaxis.grid(True, c = 'k', ls = ':')
    # colorbar:
    divider = make_axes_locatable(ax)
    cbax = divider.append_axes("right", size="5%", pad=0.05)
    cb = plt.colorbar(Mesh, cax=cbax)
    cb.ax.tick_params(labelsize=10)
    cb.set_label('counts')
    ax.set_xlabel('ToF Channel')
    ax.set_ylabel('ESA')
    plt.savefig('Plots/epq_He1.pdf')


def plot_epq_He2_m():
    d = uswipha(year=[1993, 1994], tf=[[1, 366]], path='/home/asterix/fischer/PUI/Ulysses/data_misc/pha_he2/')

    fig, ax = plt.subplots()
    valx = d.get_data('Master','tch')
    valy = d.get_data('Master','epq')
    binx = arange(180, 480)
    biny = arange(0, 66)
    C, X, Y = histogram2d(valx, valy, bins=[binx, biny])
    vmin = amin(C[C > 0])
    vmax = amax(C)
    colormap = plt.cm.get_cmap("viridis")
    colormap.set_under('white')
    Mesh = ax.pcolormesh(X, Y, C.T, cmap=colormap, vmin=vmin, vmax=vmax, rasterized=True, norm = colors.LogNorm(vmin =vmin,vmax = vmax))
    ax.xaxis.grid(True, c = 'k', ls = ':')
    ax.yaxis.grid(True, c = 'k', ls = ':')
    # colorbar:
    divider = make_axes_locatable(ax)
    cbax = divider.append_axes("right", size="5%", pad=0.05)
    cb = plt.colorbar(Mesh, cax=cbax)
    cb.ax.tick_params(labelsize=10)
    cb.set_label('counts')
    ax.set_xlabel('ToF Channel')
    ax.set_ylabel('ESA')
    plt.savefig('Plots/epq_He2.pdf')



def test_plot(size = (10,8)):
    d = uswipha(year=[1993, 1994], tf=[[1, 366]])
    d.set_mask('Master', 'ech', 10, 2400)

    fig, ax = plt.subplots(figsize=size)
    valx = d.get_data('Master','tch')
    valy = d.get_data('Master','epq')
    binx = arange(200, 430)
    biny = arange(0, 65)
    C, X, Y = histogram2d(valx, valy, bins=[binx, biny])
    vmin = amin(C[C > 0])
    vmax = amax(C)
    colormap = plt.cm.get_cmap("viridis")
    colormap.set_under('white')
    Mesh = ax.pcolormesh(X, Y, C.T, cmap=colormap, vmin=vmin, vmax=vmax, rasterized=True)
    ax.xaxis.grid(True, c = 'k', ls = ':')
    ax.yaxis.grid(True, c = 'k', ls = ':')

    divider = make_axes_locatable(ax)
    cbax = divider.append_axes("right", size="5%", pad=0.05)
    cb = plt.colorbar(Mesh, cax=cbax)
    cb.ax.tick_params(labelsize=10)
    cb.set_label('counts')
    ax.set_xlabel('TCH')
    ax.set_ylabel('EPQ')
    plt.savefig('%s_%s.pdf' %(size[0],size[1]))





matplotlib.rcParams.update({'font.size': 12,
                            'xtick.major.size': 8,
                            'xtick.major.width': 1.0,
                            'xtick.minor.size': 5,
                            'xtick.minor.width': 1,
                            'ytick.major.size': 8,
                            'ytick.major.width': 1.0,
                            'ytick.minor.size': 5,
                            'ytick.minor.width': 1,
                            'xtick.direction': 'inout',
                            'ytick.direction': 'inout',
                            'figure.subplot.left':0.12,
                            'figure.subplot.bottom': 0.15,
                            'figure.subplot.right': 0.9,
                            'figure.subplot.top': 0.94,
                            'figure.figsize': (7,4.5)})

def plot_epq():
    fig, ax = plt.subplots(figsize = (5,6.5))

    epq_arr = array(
        [60.50781039, 56.31621253, 52.41498202, 48.78400405, 45.40455724, 42.2592171, 39.3317662, 36.60711056,
         34.0712018, 31.71096474, 29.51422996, 27.46967104, 25.56674622, 23.79564398, 22.14723248, 20.61301249,
         19.18507355, 17.85605316, 16.6190989, 15.46783299, 14.39631949, 13.39903366, 12.47083347, 11.60693312,
         10.80287831, 10.05452332, 9.35800963, 8.709746, 8.10638996, 7.54483061, 7.02217253, 6.53572089, 6.08296755,
         5.66157808, 5.26937981, 4.90435056, 4.56460821, 4.24840107, 3.95409875, 3.68018383, 3.42524401, 3.1879648,
         2.96712279, 2.76157931, 2.57027459, 2.39222225, 2.22650424, 2.07226613, 1.92871266, 1.79510366, 1.67075025,
         1.55501125, 1.44728992, 1.34703084, 1.25371708, 1.1668675, 1.08603431, 1.01080073, 0.94077886, 0.87560766,
         0.81495111, 0.75849646, 0.70595263, 0.6570487])
    steps = arange(0,64)
    err = epq_arr * 0.025
    #ax.plot(steps,epq_arr, ls = 'None', marker = 'o', markersize = .1)
    ax.set_xlabel("Step No.")
    ax.set_ylabel("Energy per Charge / kV")
    ax.errorbar(steps,epq_arr, yerr=err, fmt='o', color='g',ecolor='lightgreen', ms = 3.5)
    ax.grid()
    ax.set_ylim(0,63)





