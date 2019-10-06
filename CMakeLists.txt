cmake_minimum_required (VERSION 2.8.11)
project (wind-dynamics)

set(CMAKE_CXX_STANDARD 17)

find_package(Eigen3 REQUIRED)

if (NOT TARGET utils)
  include_directories(lib/utils/include)
  add_subdirectory(lib/utils)
endif()

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
