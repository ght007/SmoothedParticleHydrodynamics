cmake_minimum_required(VERSION 4.0)
project(untitled1)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled1 main.cpp
        src/Simulation.cpp
        src/Simulation.h
        src/math/Vector3.h
        src/particles/Particle.h
        src/math/TimeIntegrator.h
        src/math/SemiImplicitEuler.cpp
        src/math/SemiImplicitEuler.h
        src/sph/Forces.cpp
        src/sph/Forces.h
        src/sph/Kernel.h
        src/sph/CubicSplineKernel.h
        src/math/NeighbourHoodSearch.h
        src/math/UniformGridSearch.cpp
        src/math/UniformGridSearch.h
)
