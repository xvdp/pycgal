# edges
A few routines to deal with edges in python, pytorch, numpy.

1. pybind11 wrap of CGAL 5.0 Optimal Transport to simplify sketch to minimum edges.
* Optimal Transport 2d shape simplification included https://doc.cgal.org/latest/Optimal_transportation_reconstruction_2/index.html

**TODO** replace py::array with py::buffer to deal with pytorch tensors direction

2. Pytorch Canny edge finding filter.

## Prerequisites
* CMake >= 3.5

C++14 enabled compiler
* tested on linux with 7.4.0
* VS 2015 on Windows. Untested

## Installation

CGAL has multiple requirements including MPFR (https://www.mpfr.org/) Boost, Eigen.
To install all dependencies one can install libcgal-dev from repository.
``` 
sudo apt-get install libcgal-dev
```
Current package on ubuntu is cgal (4.7-4). This code requires cgal 5.0. So this project clones and builds it.
*TODO include boost and mpfr installation*

Conda install example
```bash
conda create --name test_evn python # latest python 3 is recommended, but should work with 2.7
conda activate test_evn
```

Clone environment with recursive flag to include cgal and pybind11 submodules
```bash
git clone https://github.com/xvdp/edges.git --recursive
cd edges
```

**pip installation**
```bash
../install.sh
```

**conda installation**
*TODO: conda installation currently faulty*

```bash
conda install conda-build
conda create --name test_evn
conda activate test_evn
conda build conda.recipe
```

**docker**
*TODO: untested*

```bash
cd pycgal/docs
make html
```

## Licenses

Pybind11: BSD
CGAL Optimal Transport: GPL

## Test / Example
Test is executed on install
```bash
python tests/test.py
```


