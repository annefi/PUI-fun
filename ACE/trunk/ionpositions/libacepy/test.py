from numpy import *
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit


def fit_func_lin(x,m,b):
    return(m*x+b)
def fit_func_exp(x,m,a,b):
    return(m*exp(a*x)+b)


e = [100.,86.6359,75.0485,65.0109,56.3158,48.7837,42.2589,36.6069,31.7108,27.4695,23.7955,20.6129,17.856,16.619,15.4678,14.3962,13.399,12.4708,11.6069,10.8028,10.0545,9.35797,8.70971,8.10635,7.5448,7.02214,6.5357,6.08294,5.66156,5.26936,4.90433,4.56459,4.24839,3.95409,3.68017,3.42523,3.18796,2.96711,2.76157,2.57027,2.39222,2.2265,2.07226,1.92871,1.7951,1.67075,1.55501,1.44729,1.34703,1.25372,1.16687,1.08603,1.0108,0.940778,0.875607,0.81495,0.758496,0.705952,0.657048,0.611489]

x_arr = arange((len(e)))

plt.plot(x_arr,log(e),'x')
plt.plot(x_arr,e,'x')
plt.show()

popt_exp, pcov_exp = curve_fit(fit_func_exp, x_arr[10:], e[10:])
# print(popt_exp)
# print('\n')
# print(pcov_exp)
#plt.plot(x_arr[10:60],fit_func_exp(x_arr[10:60],popt_exp[0],popt_exp[1],popt_exp[2]))

popt_lin, pcov_lin = curve_fit(fit_func_lin, x_arr[0:9], log(e[0:9]))
popt_lin2, pcov_lin2 = curve_fit(fit_func_lin, x_arr[15:61], log(e[15:61]))
print(popt_lin)
print(popt_lin2)
# print('\n')
# print(pcov_exp)
plt.plot(x_arr[0:9],fit_func_lin(x_arr[0:9],popt_lin[0],popt_lin[1]))
plt.plot(x_arr[10:61],fit_func_lin(x_arr[10:61],popt_lin2[0],popt_lin2[1]))


m = popt_lin[0]
b = popt_lin[1]
m2 = popt_lin2[0]
b2 = popt_lin2[1]

plt.plot(x_arr[0:9],fit_func_exp(x_arr[0:9],exp(b),m,1.))
plt.plot(x_arr[15:61],fit_func_exp(x_arr[15:61],exp(b2),m2,1.))

popt_exp,pcov_exp = curve_fit(fit_func_exp, x_arr[15:61], e[15:61])
plt.plot(x_arr[15:61],fit_func_exp(x_arr[15:61],popt_exp[0],popt_exp[1],popt_exp[2]))