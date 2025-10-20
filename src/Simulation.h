//
// Created by pc on 10/20/2025.
//

#ifndef UNTITLED1_SIMULATION_H
#define UNTITLED1_SIMULATION_H
#include "math/TimeIntegrator.h"
#include "sph/Forces.h"
#include "sph/Kernel.h"

class NeighbourHoodSearch;
class Forces;
class Simulation {
public:
    static double constexpr PARTICLE_MASS = 0.02; // kg, small particle mass
    static double constexpr PARTICLE_RADIUS = 0.02; // m, typical spacing between particles
    static double constexpr SMOOTHING_LENGTH = 0.35; // m, usually 2x particle radius
    static double constexpr GRAVITY = 9.81; // m/s^2, Earth gravity
    static double constexpr MU = 0.001; // Pa·s, viscosity for water (~1e-3)
    static double constexpr REST_DENSITY = 10.0; // kg/m^3, water density
    static double constexpr SPEED_OF_SOUND = 20.0; // m/s, artificial speed of sound for compressible SPH


    std::vector<Particle *> *particles;

    TimeIntegrator *time_integrator;

    Kernel *kernel;

    NeighbourHoodSearch *neighbourhood_search;

    Forces *forces;

    Simulation(std::vector<Particle *> *particles, TimeIntegrator *time_integrator, Kernel *kernel,
               NeighbourHoodSearch *neighbourhood_search);

    void simulation_step(double dt) const;
};


#endif //UNTITLED1_SIMULATION_H
