import os.path as osp
import numpy as np
_withpd = True
try:
    import pandas as pd
except:
    _withpd = False
import pycgal as m
AU = '\033[0m'
BD = '\033[1m'
GB = '\033[92m\033[1m'
RB = '\033[91m\033[1m'


def readf(fname, dtype):
    print(fname)
    if _withpd:
        df = pd.read_csv(fname, delim_whitespace=True, header=None)
        x = df.values.astype(dtype)
    else:
        with open(fname, 'r') as fi:
            txt = fi.read().split("\n")
        l = [[float(v) for v in t.split()] for t in txt if len([float(v) for v in t.split()]) == 2] 
        x = np.array(l).astype(dtype)
    return x

def test_ot_class(fname, dtype):
    x = readf(fname, dtype)
    print("%s----- Test input %s ----%s"%(BD, dtype, AU))
    try:
        out = m.OptimalTransport(x)
        out.simplify()
        print(" input shape", x.shape, x.dtype)
        print(" out: segments.shape", out.segments.shape, "out dtype:", out.segments.dtype)
        print(" out: edges.shape ", out.edges.shape, "out dtype:", out.edges.dtype)
        print(" out: points.shape ", out.points.shape, "out dtype:", out.points.dtype)
        print("%s=> Test <%s> Succeeed%s"%(GB, dtype, AU))

    except:
        print("%s....Test <%s> Failed%s"%(GB, dtype, AU))

if __name__ == "__main__":
    fname = osp.abspath("tests/data/stair-noise00.xy")
    test_ot_class(fname, "float32")
    test_ot_class(fname, "float64")