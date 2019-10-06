# Wind Dynamics

Algorithms for simulating wind in C++.

To use in your project, add the following lines to your *CMakeLists.txt* file:

```cmake
if (NOT TARGET wind-dynamics)
  include_directories(path/to/wind-dynamics/include)
  add_subdirectory(path/to/lib/wind-dynamics)
endif()
```

## Usage

The class *DrydenWind* must be initialized with wind velocity-defining parameters before it is used:

```c++
#include "wind-dynamics/dryden_model.h"

...

dryden_model::DrydenWind wind;
wind.initialize(double wx_nominal, double wy_nominal, double wz_nominal,
                double wx_gust_bound, double wy_gust_bound, double wz_gust_bound);
```

The variables *w[axis]\_nominal* define the nominal wind velocity in meters/second, and the variables *w[axis]\_gust\_bound* define a loose bound on the additional gust velocity in that direction.

To get the current wind velocity, call the following:

```c++
Eigen::Vector3d wind_velocity = wind.getWind(double dt);
```

Where the variable *dt* is the amount of elapsed time in seconds since *getWind()* was last called. The *dt* variable is for the internal propagation of the Dryden gust dynamic model.
