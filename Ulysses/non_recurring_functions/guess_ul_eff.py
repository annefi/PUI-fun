'''
Script determines matching measuring efficiencies per epq-step for Ulysses SWICS based inter-/extrapolation of ACE
SWICS efficiencies
'''

from numpy import array, loadtxt, arange
from matplotlib import pylab as plt
from scipy.optimize import curve_fit
import matplotlib




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
                            'figure.figsize': (9,4.5)})

def guess_from_ace():
    fin = open("/data/projects/ace/efficencies/He1+.eff", "r")
    dat = loadtxt(fin)
    epq_ace = dat[:, 0]
    eff_ace = dat[:, 1]

    epq_ul = array(
        [60.50781039, 56.31621253, 52.41498202, 48.78400405, 45.40455724, 42.2592171, 39.3317662, 36.60711056,
         34.0712018, 31.71096474, 29.51422996, 27.46967104, 25.56674622, 23.79564398, 22.14723248, 20.61301249,
         19.18507355, 17.85605316, 16.6190989, 15.46783299, 14.39631949, 13.39903366, 12.47083347, 11.60693312,
         10.80287831, 10.05452332, 9.35800963, 8.709746, 8.10638996, 7.54483061, 7.02217253, 6.53572089, 6.08296755,
         5.66157808, 5.26937981, 4.90435056, 4.56460821, 4.24840107, 3.95409875, 3.68018383, 3.42524401, 3.1879648,
         2.96712279, 2.76157931, 2.57027459, 2.39222225, 2.22650424, 2.07226613, 1.92871266, 1.79510366, 1.67075025,
         1.55501125, 1.44728992, 1.34703084, 1.25371708, 1.1668675, 1.08603431, 1.01080073, 0.94077886, 0.87560766,
         0.81495111, 0.75849646, 0.70595263, 0.6570487])

    fig = plt.figure()
    ax = fig.add_subplot(111)
    ax.plot(epq_ace, eff_ace, marker='o')

    def poly(x, a, b, c, d, e, f):
        return (a + b * x + c * x ** 2 + d * x ** 3 + e * x ** 4 + f * x ** 5)

    # do the fit:
    init_vals = [-3.97167435e-03, 2.01624045e-03, 8.28846505e-05, -7.20948144e-07, 2.41401215e-08, 2.41401215e-08]
    best_vals, covar = curve_fit(poly, epq_ace, eff_ace, p0=init_vals)
    print(best_vals)

    # plot the fitted values:
    ax.plot(epq_ace, poly(epq_ace, best_vals[0], best_vals[1], best_vals[2], best_vals[3], best_vals[4], best_vals[5]))

    # operate Ulysses epq-steps in fitted function and write into file
    # out = open('He1+.eff', 'w')
    #
    # for i in epq_ul:
    #     eff_ul = poly(i, best_vals[0], best_vals[1], best_vals[2], best_vals[3], best_vals[4], best_vals[5])
    #     out.write('%s' % i + '   ' + '%s\n' % eff_ul)
    #
    # out.close()


def linear_guess():

    fin = open("/data/projects/ace/efficencies/He1+.eff", "r")
    dat = loadtxt(fin)
    epq_ace = dat[:, 0]
    eff_ace = dat[:, 1]


    val0 = 0.2501016717412423
    val17 = 0.0

    epq_ul = array(
        [60.50781039, 56.31621253, 52.41498202, 48.78400405, 45.40455724, 42.2592171, 39.3317662, 36.60711056,
         34.0712018, 31.71096474, 29.51422996, 27.46967104, 25.56674622, 23.79564398, 22.14723248, 20.61301249,
         19.18507355, 17.85605316])

    fig = plt.figure()
    ax = fig.add_subplot(111)
    #ax.plot([60.50781039,17.85605316], [val0, val17], marker='o')

    def lin(x,m,b):
        return (m*x + b)

    best_vals, covar = curve_fit(lin, [60.50781039,17.85605316], [val0, val17])

    ax.plot(epq_ace, eff_ace, marker='.', ms=10, c='lightsteelblue', label="ACE SWICS", linestyle="None")

    ax.plot(epq_ul, lin(epq_ul, best_vals[0], best_vals[1]), marker = '.', ms = 10, c = 'darkblue',
            label = "Ulysses SWICS", linestyle = "None")

    # step_name = arange(0,18)
    # for i,x in enumerate(epq_ul):
    #     ax.text(x+3, lin(epq_ul, best_vals[0], best_vals[1])[i] -0.005 ,str(step_name[i]), fontsize = 8)

    ax.set_xlabel('Energy-per-Charge / keV')
    ax.set_ylabel('Efficiency')
    ax.legend(bbox_to_anchor=(0.35, 0.75), loc="lower right", bbox_transform=fig.transFigure)
    ax.grid()
    ax.set_xlim(-3, 91)
    ax.set_ylim(-0.015, 0.359)

    # out = open('He1+_new.eff', 'w')
    #
    # for i in epq_ul:
    #     eff_ul = lin(i, best_vals[0], best_vals[1])
    #     out.write('%s' % i + '   ' + '%s\n' % eff_ul)
    #
    # out.close()

















