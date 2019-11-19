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











