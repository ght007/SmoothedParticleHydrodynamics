//
// Created by pc on 10/20/2025.
//

#ifndef UNTITLED1_FORCES_H
#define UNTITLED1_FORCES_H

#include "../Simulation.h"

class Forces {
public:
    explicit Forces(Simulation simulation);

    void compute_densities();

    void compute_non_pressure_forces();

    void compute_pressure_forces();

    void compute_pressure_gradient();

    void compute_velocity_laplacian();

private:
    Kernel *kernel;

    std::vector<Particle> *particles;
};


#endif //UNTITLED1_FORCES_H
