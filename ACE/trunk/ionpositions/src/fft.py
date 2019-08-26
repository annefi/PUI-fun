def nextpower2(i):
    n = 2
    while n<i: n = n*2
    return n

def bitreverse(x):
    N = len(x)
    if N != nextpower2(N): raise ValueError, 'N is not power of 2'

    x = x[:]
    for i in range(N):
        k, b, a = 0, N>>1, 1
        while b >= a:
            if b&i: k = k|a
            if a&i: k = k|b
            b, a = b>>1, a<<1
        if i < k:               # swap each pair only once, avoid i==k
            x[i], x[k] = x[k], x[i]
    return x
   

def fft(x, sign=-1):
    from cmath import pi, exp
    N = len(x)
    omega = [0]*N
    for i in range(N):
        omega[i] = exp(sign*2j*pi*i/N)
    x = bitreverse(x)
    m = 2
    while m <= N:
        for s in range(0, N, m):
            for i in range(m/2):
                n = i * N/m
                a, b = s + i, s + i + m/2
                x[a], x[b] = x[a]+omega[n%N]*x[b], x[a]-omega[n%N]*x[b]
        m = m * 2
    return x

def ifft(X):
    N = len(X)
    x = fft(X, sign=1)   
    for i in range(N):
        x[i] = x[i]/float(N)
    return x
