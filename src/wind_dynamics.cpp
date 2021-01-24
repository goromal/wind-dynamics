#include "wind-dynamics/dryden_model.h"
#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>
#include <sstream>

using namespace Eigen;
namespace py = pybind11;

PYBIND11_MODULE(wind_dynamics, m)
{
    m.doc() = "Python binding module for the dryden wind modeling classes.";

    py::class_<dryden_model::DrydenWind>(m, "DrydenWind")
        .def(py::init())
        .def("initialize", &dryden_model::DrydenWind::initialize)
        .def("getWind", &dryden_model::DrydenWind::getWind);
}