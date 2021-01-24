cmake_minimum_required (VERSION 2.8.11)
project (wind-dynamics)
option(PYTHON_BINDINGS "Build Python bindings." OFF)

set(CMAKE_CXX_STANDARD 17)

find_package(Eigen3 REQUIRED)

include_directories(
  include
  ${EIGEN3_INCLUDE_DIRS}
)

add_library(wind-dynamics INTERFACE)
target_include_directories(wind-dynamics
  INTERFACE
  include
  ${EIGEN3_INCLUDE_DIRS}
)

if (PYTHON_BINDINGS)
  add_subdirectory(lib/pybind11)
  pybind11_add_module(wind_dynamics src/wind_dynamics.cpp)
endif()
