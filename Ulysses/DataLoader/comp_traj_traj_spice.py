'''
Dieses Skript ist überflüssig, denn diese Funktion sollte es schon auf Ebene des Spice-Moduls geben.
Allerdings nicht auf PHA-Worte gemappt, sondern reine Trajektorienbetrachtung
'''

from Ulysses.DataLoader.uswipha import uswipha
import matplotlib.pyplot as plt

y = 1991
t = [1,50]

d_old = uswipha(year = [y], tf = [t])
d_old.sync_traj()

d_spice = uswipha(year = [y], tf = [t])
d_spice.sync_traj_spice()

fig, ax = plt.subplots()
ax.plot(d_old.data['doy'], d_old.data['asptheta'], linestyle = 'None', marker = '.', label = 'old')
ax.plot(d_spice.data['doy'], d_spice.data['asptheta'], linestyle = 'None', marker = '.', label = 'SPICE')
ax.legend()
plt.show()