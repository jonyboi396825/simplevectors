# Simplevectors

Simple vector implementations in C++.

**NOTE**: C++11 or higher is needed for this library.

**NOTE**: This is mostly tested on MacOS 12.6 with C++11, clang 13.0.0, CMake 3.22.2, and GNU make 3.81


## Installation

The simplest way is to download the single-header `simplevectors.hpp` file from the releases page. To include the file, simply put the path to the header file.

```cpp
#include "path/to/simplevectors.hpp"
```

### CMake

Alternatively, you can use CMake to install the library:

```cmake
cmake_minimum_required(VERSION 3.16.3)
project(MyProject LANGUAGES CXX)

find_package(simplevectors REQUIRED)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE simplevectors::simplevectors)
```

If you do this, the include path will be slightly different:

```cpp
#include <simplevectors/vectors.hpp>
```

## Usage

This section covers basic usage of vectors. For more details, read the docstrings in the source code files.

Everything is under the namespace `svector`.

All of the examples below (except for initialization, printing, and exceptions specifically noted) show the methods of each vector. For each method, there is also a function under the `svector` namespace that takes in a vector object and the arguments for the corresponding method. For example:

```cpp
svector::Vector2D v2d(2, 4);
double xval = v2d.x() + 1;
v2d.x(xval);
```

is equivalent to:

```cpp
svector::Vector2D v2d(2, 4);
double xval = svector::x(v2d) + 1;
svector::x(v2d, xval);
```

### Initialization

```cpp
svector::Vector2D zero2d; // <0, 0>
svector::Vector3D zero3d; // <0, 0, 0>

svector::Vector2D v2d(2, 4);    // <2, 4>
svector::Vector3D v3d(2, 4, 5); // <2, 4, 5>
```

### Printing

Both `Vector2D` and `Vector3D` have `toString()` methods for printing.

```cpp
#include <iostream>

std::cout << zero2d.toString() << std::endl; // "<0.000, 0.000>"
std::cout << v3d.toString() << std::endl; // "<2.000, 4.000, 5.000>"
```

### Properties

```cpp
// components of the vector
std::cout << v2d.x() << " " // 2.000
          << v2d.y() << " " // 4.000
          << std::endl;

std::cout << v3d.x() << " " // 2.000
          << v3d.y() << " " // 4.000
          << v3d.z() << " " // 5.000
          << std::endl;

// 2D magnitude and angle from horizontal, in radians
// Angle ranges from (-π, π]
std::cout << v2d.magn() << std::endl;  // 4.472
std::cout << v2d.angle() << std::endl; // 1.107

// 3D magnitude and angle from x-axis (ALPHA), y-axis (BETA),
// and z-axis (GAMMA) in radians
// Angles range from [0, π]
std::cout << v3d.magn() << std::endl;                  // 6.708
std::cout << v3d.angle<svector::ALPHA>() << std::endl; // 1.268
std::cout << v3d.angle<svector::BETA>() << std::endl;  // 0.932
std::cout << v3d.angle<svector::GAMMA>() << std::endl; // 0.730

// set component values
v2d.x(4); // v2d is now <4, 4>
v3d.y(5);
v3d.z(3); // v3d is now <2, 5, 3>

std::cout << v2d.toString() << std::endl; // "<4.000, 4.000>"
std::cout << v3d.toString() << std::endl; // "<2.000, 5.000, 3.000>"
```

Note that the functional equivalent for getting the angles of a 3D vector is slightly different:

```cpp
std::cout << svector::alpha(v3d) << std::endl; // alpha angle
std::cout << svector::beta(v3d) << std::endl;  // beta angle
std::cout << svector::gamma(v3d) << std::endl; // gamma angle
```

### Operations

These are operations that can be done on both 2D and 3D vectors. For simplicity, examples will be shown with only 2D vectors.

```cpp
svector::Vector2D lhs(2, 5);
svector::Vector2D rhs(3, -4);

svector::Vector2D sum = lhs + rhs;        // <5, 1>
svector::Vector2D difference = lhs - rhs; // <-1, 9>
svector::Vector2D product = lhs * 3;      // <6, 15>
svector::Vector2D quotient = lhs / 3;     // <0.667, 1.667>
double dot_product = lhs.dot(rhs);        // -14
svector::Vector2D neg = -lhs;             // <-2, -5>
```

Cross products only work on 3D vectors.

```cpp
svector::Vector3D lhs3d(2, 5, -3);
svector::Vector3D rhs3d(6, 5, 9);

svector::Vector3D cross = lhs3d.cross(rhs3d); // <60, -36, -20>
```

Vectors can be added, subtracted, multiplied, or divided in place.
```cpp
svector::Vector2D inplacev(2, 5);
inplacev += svector::Vector2D(3, 6);
inplacev -= svector::Vector2D(2, 3);
inplacev *= 5;
inplacev /= 7;

std::cout << inplacev.toString() << std::endl; // <2.143, 5.714>
```

### Equality

Works for both 2D and 3D vectors.

```cpp
svector::Vector2D lhs1(2, 5);
svector::Vector2D rhs1(3, -4);
svector::Vector2D lhs2(2, 5);
svector::Vector2D rhs2(2, 5);

bool equal1 = lhs1 == rhs1;  // false
bool equal2 = lhs1 != rhs1;  // true
bool equal3 = lhs2 == rhs2;  // true
bool equal4 = lhs2 != rhs2;  // false
```

### Normalization

```cpp
svector::Vector2D unnorm2D(3, 4);
svector::Vector3D unnorm3D(3, 4, 5);

svector::Vector2D norm2D = unnorm2D.normalize(); // <0.6, 0.8>
svector::Vector3D norm3D = unnorm3D.normalize(); // <0.424, 0.566, 0.707>
```

### Rotation 2D

For 2D vectors, the `rotate` method requires one argument, `ang`, which is the angle to rotate in radians. A positive angle indicates counterclockwise rotation, and a negative angle indicates clockwise rotation. The method returns a new vector.

```cpp
svector::Vector2D v1(1, 0);
svector::Vector2D v2(1, 0);

svector::Vector2D v1ccw = v1.rotate(M_PI_4);  // <0.707, 0.707>
svector::Vector2D v2cw = v1.rotate(-M_PI_4);  // <0.707, -0.707>
```

### Rotation 3D

For 3D vectors, the `rotate` method only works for one axis at a time. It requires a template argument indicating the axis to rotate around: `ALPHA` for the x-axis, `BETA` for the y-axis, and `GAMMA` for the z-axis.

```cpp
svector::Vector3D v1_3D(1, 0, 1);

svector::Vector3D v1_xRotation =
    v1_3D.rotate<svector::ALPHA>(M_PI_2); // <1, -1, 0>
svector::Vector3D v1_yRotation =
    v1_3D.rotate<svector::BETA>(M_PI_2); // <1, 0, -1>
svector::Vector3D v1_zRotation =
    v1_3D.rotate<svector::GAMMA>(M_PI_2); // <0, 1, 1>
```

Rotations can also be chained:

```cpp
svector::Vector3D v1_chained =
    v1_3D.rotate<svector::ALPHA>(M_PI_2)
        .rotate<svector::BETA>(M_PI_2)
        .rotate<svector::GAMMA>(M_PI_2); // <1, 0, -1>
```

Note that the functional equivalent of rotation around a certain axis is slightly different:

```cpp
svector::Vector3D v1_xRotation = svector::rotateAlpha(v1_3D, M_PI_2);
svector::Vector3D v1_yRotation = svector::rotateBeta(v1_3D, M_PI_2);
svector::Vector3D v1_zRotation = svector::rotateGamma(v1_3D, M_PI_2);
```

### Looping

The `Vector` class and the classes that extend it (namely `Vector2D` and `Vector3D`) are container-like in the sense that they have iterators and `begin()`, `end()`, `rbegin()`, and `rend()` methods. This means that they can be looped through like any other STL container.

```cpp
svector::Vector<5> vector_loop{1, 6, 4, 3, 9};

for (const auto& i: vector_loop) {
  std::cout << i << std::endl;
} // 1, 6, 4, 3, 9
```

This can be helpful for calculating sums.

## Extending

To go beyond only 2D and 3D, you can extend the `Vector` base class (the 2D and 3D vector classes extend this base class as well). `Vector` is a template class, where the template takes in the number of dimensions the vector has:

```cpp
class Quaternion : public svector::Vector<4> {};
```

The `Vector` base class provides a protected variable, `m_components`, an `std::array` of each component of the vector. It also provides these methods, **which are not virtual**:

- `operator+()`: adds two vectors
- `operator-()`: subtracts two vectors, or flips the direction of a vector if used as a unary operator
- `operator*()`: scalar multiplication
- `operator/()`: scalar division
- `operator==()`: equality (by comparing each component)
- `operator!=()`: inequality
- `operator+=()`: adds in place
- `operator-=()`: subtracts in place
- `operator*=()`: multiplies in place
- `operator/=()`: divides in place
- `dot()`: finds the dot product of two vectors
- `magn()`: finds the magnitude of a vector
- `normalize()`: normalizes a vector
- `numDimensions()`: determines the number of dimensions in a vector
- `operator[](index)`: returns dimension `index`'s component of a vector

Note that the binary operations with another vector require vectors **that have the same dimension**.

The base class provides these constructors:

- `Vector()`: initializes a 0 vector (or a vector with 0s in every dimension)
- `Vector(std::initializer_list<double> args)`: initializes a vector, with each component given in the initializer list
- `Vector(const Vector<dimensions>& other)`: copy constructor

You can inherit them using `using svector::Vector<D>::Vector` or write your own constructors.

These methods are virtual and could be overridden:

- `std::string toString()`: converts vector to a string format

To make the operators work, you must include a constructor that takes in a base class:

```cpp
class Quaternion : public svector::Vector<4> {
  Quaternion(const svector::Vector<4>& other){
    this->m_components[0] = other[0]; 
    this->m_components[1] = other[1]; 
    this->m_components[2] = other[2]; 
    this->m_components[3] = other[3]; 
  };
};
```

After this, you can make your own methods interacting with the components of the vectors.

## Embedding (2D and 3D vectors only)

For adding vectors to an embedded device, there is a file called `embed.hpp`, located in `include/simplevectors`, which contains a minimized version of the 2D and 3D vector objects above, named `Vec2D` and `Vec3D`, respectively. They include every feature mentioned except for looping and extending.

Differences from `Vector2D` and `Vector3D`:

- Names are `Vec2D` and `Vec3D` rather than `Vector2D` and `Vector3D`
- Uses `.x`, `.y`, and `.z` rather than `.x()`, `.y()`, and `.z()` to access x, y, and z values.
- There are no methods in the minimized objects (e.g. `.dot()`, `.cross()`, etc), so you must use the functional equivalents (e.g. `dot(vec)`, `cross(vec)`) mentioned above.
- Embedded devices only support 2D and 3D vectors.
- This file is not included within `simplevectors/vectors.hpp` because it is meant to be a standalone file, so it must be included explicitly.

```cpp
#include <simplevectors/embed.hpp>

// ...

svector::Vec2D embv2(2, 4);
svector::Vec3D embv3(2, 4, 5);

svector::toString(embv2); // <2.000, 4.000>
svector::toString(embv3); // <2.000, 4.000, 5.000>

std::cout << embv2.x << std::endl; // 2
std::cout << embv3.y << std::endl; // 4
std::cout << embv3.z << std::endl; // 5

// all operators work the same

svector::Vec2D emblhs(2, 5);
svector::Vec2D embrhs(3, -4);
double embdot = svector::dot(emblhs, embrhs); // -14
```

### Embedded devices without access to the STL

For embedded devices without access to the C++ STL, such as on an Arduino, there is another file named `embed.h`. It is the same as `embed.hpp`, except that it does not contain a `svector` or `std` namespace and there is no `toString()` function.


## License

MIT License (© 2022 Jonathan Liu)
