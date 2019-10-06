# Wind Dynamics

Algorithms for simulating wind in C++.

To use in your project, add the following lines to your *CMakeLists.txt* file:

```cmake
if (NOT TARGET wind-dynamics)
  include_directories(path/to/wind-dynamics/include)
  add_subdirectory(path/to/lib/wind-dynamics)
endif()
```
