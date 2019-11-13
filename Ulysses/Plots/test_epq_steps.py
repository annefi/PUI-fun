from numpy import *
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit


def func_exp(x,pow):
    return(pow**x)

def func_lin(x,m,b):
    return(m*x+b)

steps = array([100.,86.6359,75.0485,65.0109,56.3158,48.7837,42.2589,36.6069,31.7108,27.4695,23.7955,20.6129,17.856,16.619,15.4678,14.3962,13.399,12.4708,11.6069,10.8028,10.0545,9.35797,8.70971,8.10635,7.5448,7.02214,6.5357,6.08294,5.66156,5.26936,4.90433,4.56459,4.24839,3.95409,3.68017,3.42523,3.18796,2.96711,2.76157,2.57027,2.39222,2.2265,2.07226,1.92871,1.7951,1.67075,1.55501,1.44729,1.34703,1.25372,1.16687,1.08603,1.0108,0.940778,0.875607,0.81495,0.758496,0.705952,0.657048,0.611489])
steps_len = arange(len(steps))

steps_log = log(steps)

popt_lin1, pcov_lin1 = curve_fit(func_lin, steps_len[:13], steps_log[:13])
popt_lin2, pcov_lin2 = curve_fit(func_lin, steps_len[13:], steps_log[13:])
print('1. Steigung:',popt_lin1)
print('2. Steigung:', popt_lin2)


# test_array = arange(0,30)
# test_y = (test_array * 2) + 3
# popt_test, pcov_test = curve_fit(func_lin, test_array, test_y)
# print(popt_test)

plt.plot(range(len(steps)),steps,'x')
plt.plot(steps_len[13:], steps_log[13:],'x')
plt.plot(steps_len[:13], steps_log[:13],'x')


plt.plot(steps_len[:13],func_lin(steps_len[:13],popt_lin1[0],popt_lin1[1]))
plt.plot(steps_len[13:],func_lin(steps_len[13:],popt_lin2[0],popt_lin2[1]))
plt.show()