from os import system
from scipy.linalg import inv
from scipy import zeros, dot
from numpy import float
from Gnuplot import Gnuplot, GridData

Float=float
matrixmultiply=dot

x=zeros([50,34],Float)
filename="./caldat/o2daten1p_o_con.f"
mp=open(filename)
l=0
for j in mp:
    t=j.split()
    for k in range(34):
        x[l,k]=float(t[k])
    l+=1
print x
"""
c1=0.1
pf1=0.785
sigma=1
e=2.712
s=0.
for i in range(33):
    y=x[i,0]*c1*22.661
#    print y
    z=x[i,1]
#    print z
    f=(1-(1+y)*e**(-y))*(1-pf1**y)
#    print f
    p=((f-z)/sigma)**2
    print p
    s=s+p
print s/32.
#print x
"""