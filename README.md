# Math
A tiny math library with custom vector, matrix and other template classes that I use in other small projects as well.

So far it includes:
* 2D Vector
* 3D Vector
* 4D Vector
* 3D Point
* 2x2 Matrix
* 3x3 Matrix
* 4x4 Matrix
* Ray

Building and Running the tests
------------------------------
```bash
cmake -B build -DENABLE_TESTING=ON
cd build
make
ctest
```