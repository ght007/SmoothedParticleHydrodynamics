//
// Created by pc on 10/20/2025.
//

#ifndef UNTITLED1_SIMULATION_H
#define UNTITLED1_SIMULATION_H
#include "math/TimeIntegrator.h"
#include "sph/Kernel.h"


class Simulation {
public:
    static double constexpr PARTICLE_MASS = 1;

    static double constexpr PARTICLE_RADIUS = 0.05;

    static double constexpr SMOOTHING_LENGTH = 0.1;

    static double constexpr GRAVITY = 9.81;

    std::vector<Particle> *particles;

    TimeIntegrator *time_integrator;

    Kernel* kernel;

    Simulation(std::vector<Particle> *particles, TimeIntegrator *time_integrator, Kernel *kernel) {
        this->particles = particles;
        this->time_integrator = time_integrator;
        this->kernel = kernel;
    };

    void simulation_loop() const;

};


#endif //UNTITLED1_SIMULATION_H