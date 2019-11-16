import os.path as osp
import numpy as np
import pandas as pd
import torch
import pycgal as m


def test_ot_class():
    fname = osp.abspath("tests/data/stair-noise00.xy")
    print(fname)
    df = pd.read_csv(fname, delim_whitespace=True, header=None)
    x = df.values.astype(float)

    out = m.OptimalTransport(x)
    out.simplify()
    print("input shape", x.shape, x.dtype)
    print("out: segments.shape", out.segments.shape, out.segments.dtype)
    print("out: edges.shape ", out.edges.shape, out.edges.dtype)
    print("out: points.shape ", out.points.shape, out.points.dtype)


def test_ot_class32():
    fname = osp.abspath("tests/data/stair-noise00.xy")
    print(fname)
    df = pd.read_csv(fname, delim_whitespace=True, header=None)
    x = df.values.astype(np.float32)

    out = m.OptimalTransport(x)
    out.simplify()
    print("input shape", x.shape, x.dtype)
    print("out: segments.shape", out.segments.shape, out.segments.dtype)
    print("out: edges.shape ", out.edges.shape, out.edges.dtype)
    print("out: points.shape ", out.points.shape, out.points.dtype)
    


if __name__ == "__main__":
    test_ot_class()
    test_ot_class32()