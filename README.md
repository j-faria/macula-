# macula-cpp
A C++ interface to David Kipping's macula code

This repository contains a simple C++ caller for the `macula` code written by David Kipping. 
The original Fortran 90 source can be obtained [here](https://www.cfa.harvard.edu/~dkipping/macula.html).
The file `caller.cpp` is a basic wrapper containing a port of the `maculacall.f90` program.


### compilation

    gfortran -c macula.f90
    g++ -c caller.cpp -std=c++0x
    g++ -o caller caller.o macula.o -l gfortran -lstdc++


