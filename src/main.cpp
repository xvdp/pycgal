
#include <pybind11/pybind11.h>
#include "optimal_transport.h"


PYBIND11_MODULE(pycgal, m) {
    m.doc() = R"pbdoc(
        Pybind11 example plugin
        -----------------------

        .. currentmodule:: cmake_example

        .. autosummary::
           :toctree: _generate

           add
           subtract
    )pbdoc";

    py::class_<OptimalTransport>(m, "OptimalTransport")
        .def(py::init<py::array_t<float>, const float &, const int &>(), py::arg("x"), py::arg("wtol")=0.005, py::arg("iters")=0)
        .def("simplify", py::overload_cast<>(&OptimalTransport::simplify))
        .def("simplify", py::overload_cast<const int &>(&OptimalTransport::simplify))
        .def("simplify", py::overload_cast<const float &>(&OptimalTransport::simplify))
        .def("simplify", py::overload_cast<const float &, const int &>(&OptimalTransport::simplify), R"pbdoc(OptimalTransport.simplify;
    Simplifies scattered points to segments utilizing Optimal Transport class from CGAL
    :: todo cite paper
    Args: optional
        wtol    (float [0.005]) wasserstein tolerance higher gives rougher results
        iters   (int [0]) if > 0, dissables wasserstein tolerance and simplifies for 'iters' number of cycles 
        )pbdoc"
        )

        .def("add_data", &OptimalTransport::add_data, py::arg("x"), "add new array for processing")

        .def_readonly("x",     &OptimalTransport::m_x, "input point scatter, array of doubles: shape (num_points, 2), dtype: float64")
        .def_readonly("points",     &OptimalTransport::m_points, "output point position array of doubles: shape (num_points, 2), dtype: float64")
        .def_readonly("segments",   &OptimalTransport::m_segments, "output segments position array of doubles: shape (num_segments, 4), dtype: float64")
        .def_readonly("edges",      &OptimalTransport::m_edges, "output index array of points that compose segments: shape (num of segments, 2), dtype: int64");


#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}
