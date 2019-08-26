def func2tics(f, mi, ma, ntics=10, fmt="%g"):
    z=[]
    for n in range(ntics):
        x=float(ma-mi)/ntics*n+mi
        z.append((fmt % x, f(x)))
    return z
