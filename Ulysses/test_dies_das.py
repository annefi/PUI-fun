import matplotlib.pyplot as plt
from numpy import arange

fig, ax = plt.subplots(figsize=(6, 5))

def test_diff_sec(D):
    # function to check the difference of w-value between first and last (9th) detector point in one det-sec-combi
    # for different sectors over epq
    for sec in range(8):
        arr = []
        for epq in range(60):
            p1 = D.wspace[10,0,0,epq,0,sec,0,0]
            p2 = D.wspace[10,0,0,epq,0,sec,0,8]
            arr.append(p2-p1)
        ax.plot(arange(0,len(arr)), arr, label="%s"%sec)
        ax.legend()
    plt.show()


def test_diff_vsw(D):
    # function to check the difference of w-value between first and last (9th) detector point in one det-sec-combi
    # for different vsw over epq
    for v in range(0,52,10):
        arr = []
        for epq in range(60):
            p1 = D.wspace[v,0,0,epq,2,7,0,0]
            p2 = D.wspace[v,0,0,epq,2,7,0,8]
            arr.append(p2-p1)
        ax.plot(arange(0,len(arr)), arr, label="%s"%D.vswbins[v])
        ax.legend()
    plt.show()