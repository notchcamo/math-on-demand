# soo

[![Deploy Document](https://github.com/notchcamo/soo/actions/workflows/deploy_doxygen.yml/badge.svg)](https://github.com/notchcamo/soo/actions/workflows/deploy_doxygen.yml)  
[![Unit Test (Windows, MSVC)](https://github.com/notchcamo/soo/actions/workflows/unit_test_windows_msvc.yml/badge.svg)](https://github.com/notchcamo/soo/actions/workflows/unit_test_windows_msvc.yml)  
[![Unit Test (macOS, AppleClang)](https://github.com/notchcamo/soo/actions/workflows/unit_test_macos_apple_clang.yml/badge.svg)](https://github.com/notchcamo/soo/actions/workflows/unit_test_macos_apple_clang.yml)
[![Unit Test (macOS, clang)](https://github.com/notchcamo/soo/actions/workflows/unit_test_macos_clang.yml/badge.svg)](https://github.com/notchcamo/soo/actions/workflows/unit_test_macos_clang.yml)  


**soo** is a simple 3D math library that provides essential features for game programming.  

## Features  
* 3D Vector
```c++
soo::Vector3<double> vec1{1.0, 2.0, 3.0};
soo::Vector3d vec2{3.0, 4.0, 5.0}; // Vector3d is the type alias for Vector3<double>.

double dotProduct = vec1.dot(vec2);
soo::Vector3d crossProduct = vec1.cross(vec2);

vec1.normalize();
```
* Arbitrary-size Matrix
```c++
// 2 X 3 Matrix
soo::Matrix<double, 2, 3> mat1{
    {1, 2, 3},
    {4, 5, 6}
};

soo::Matrix<double, 3, 2> mat2{
    {7, 8},
    {9, 10},
    {11, 12}
};

auto mult = mat1 * mat2; // mult is a 2 X 2 matrix.

auto transposed = mat1.transpose(); // transposed is a 3 X 2 matrix.

// Vector multiplication is only available in 4 X 4 matrix (Affine transformation)
soo::Vector3d vec1{1, 2, 3};
soo::Matrix4d mat3{ // Matrix4d is the type alias for Matrix<double, 4, 4>.
    {0, -1, 0, 10},
    {1, 0, 0, 20},
    {0, 0, 1, 30},
    {0, 0, 0, 1}
};

auto transformed = mat3 * vec1;
```

## Usage  
1. Copy `include/soo` directory to your project, then add its path to the include path.
2. include header as below:  
```c++
#include "soo/soo.h"
```

Refer [documentation](https://notchcamo.github.io/soo/) for the implementation details.