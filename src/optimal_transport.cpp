#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Optimal_transportation_reconstruction_2.h>
#include <fstream>
#include <iostream>
#include <string>
#include <iterator>
#include <vector>

#include "optimal_transport.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::FT                                               FT;
typedef K::Point_2                                          Point;
typedef K::Segment_2 Segment;
typedef CGAL::Optimal_transportation_reconstruction_2<K>    Otr_2;

namespace py = pybind11;

OptimalTransport::OptimalTransport(py::array_t<float> x, const float &wtol, const int &iters)
{
    m_x = x;
    m_wtol = wtol;
    m_iters = iters;
}

void OptimalTransport::add_data(py::array_t<float> x)
{
    m_x = x;
}

void OptimalTransport::simplify(){

    assert(int(m_x.ndim()) == int(2));

    // Vars
        // CGAL input
        std::vector<Point> points;
        // CGAL outputs
        std::vector<Point> out_points_isolated;
        std::vector<Segment> out_segments;
        std::vector<Point> out_points;
        std::vector<std::size_t> out_isolated_vertices;
        std::vector<std::pair<std::size_t,std::size_t> > out_edges;
        // Temp
        ssize_t i=0;
    
    // CGAL -> get inputs
    for (i=0; i < m_x.shape(0); i++)
        points.push_back({m_x.mutable_at(i, 0), m_x.mutable_at(i, 1)});

    // CGAL -> process optimal transport
    Otr_2 otr2(points);
    otr2.run_under_wasserstein_tolerance(m_wtol);

    // CGAL -> extract outputs
    otr2.list_output(std::back_inserter(out_points_isolated), std::back_inserter(out_segments));
    otr2.indexed_output(std::back_inserter(out_points), std::back_inserter(out_isolated_vertices), std::back_inserter(out_edges));

    // Outputs
    py::array_t<float> temp_segments({int(out_segments.size()), 2, 2});
    py::array_t<float> temp_points({int(out_points.size()), 2});
    py::array_t<int64_t> temp_edges({int(out_edges.size()), 2});
    auto _segments = temp_segments.mutable_unchecked<3>();
    auto _points = temp_points.mutable_unchecked<2>();
    auto _edges = temp_edges.mutable_unchecked<2>();
    
    // outputs -> fill segment array
    i = 0;
    std::vector<Segment>::iterator sit;
    for (sit = out_segments.begin(); sit != out_segments.end(); sit++) {
        _segments(i, 0, 0) = float((*sit).source()[0]);
        _segments(i, 0, 1) = float((*sit).source()[1]);
        _segments(i, 1, 0) = float((*sit).target()[0]);
        _segments(i, 1, 1) = float((*sit).target()[1]);
        i++;
    }
    m_segments = temp_segments;

    //fill points array
    i = 0;
    std::vector<Point>::iterator pit;
    for (pit = out_points.begin(); pit != out_points.end(); pit++) {
        _points(i, 0) = float((*pit)[0]);
        _points(i, 1) = float((*pit)[1]);
        i++;
    }
    m_points = temp_points;

    //fill edges array
    i = 0;
    std::vector<std::pair<std::size_t, std::size_t> >::iterator eit;
    for (eit = out_edges.begin(); eit != out_edges.end(); eit++){
        _edges(i, 0) = int64_t((*eit).first);
        _edges(i, 1) = int64_t((*eit).second);
        i++;
    }
    m_edges = temp_edges;
}   

void OptimalTransport::simplify(const float &wtol, const int &iters){
    m_wtol = wtol;
    m_iters = iters;
}
void OptimalTransport::simplify(const int &iters){
    m_iters = iters;
}
void OptimalTransport::simplify(const float &wtol){
    m_wtol = wtol;
    simplify();
}
 
