#include <iostream>
#include <pybind11/pybind11.h>
#include <pybind11/iostream.h>
#include <pybind11/numpy.h>


namespace py = pybind11;

class OptimalTransport{
    public:
        OptimalTransport(py::array_t<float> x, const float &wtol=0.005, const int &iters=0);
        
        py::array_t<float> m_x;
        py::array_t<float> m_points;
        py::array_t<float> m_segments;
        py::array_t<int64_t> m_edges;

        void simplify(const float &wtol, const int &iters);
        void simplify(const float &wtol);
        void simplify(const int &iters);
        void simplify();
        void add_data(py::array_t<float> x);
    
    private:
        
        float m_wtol;
        int m_iters;

};
