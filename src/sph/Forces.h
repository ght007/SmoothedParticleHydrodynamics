//
// Created by pc on 10/20/2025.
//

#ifndef UNTITLED1_FORCES_H
#define UNTITLED1_FORCES_H

#include "../Simulation.h"
#include "../math/NeighbourHoodSearch.h"

class Simulation;
class Kernel;
class Forces {
public:
    explicit Forces(const Simulation &simulation);

    void compute_forces() const;

private:
    void compute_forces(const std::vector<std::vector<Particle *>> &neighbours) const;

    void compute_densities(const std::vector<std::vector<Particle *>> &neighbours) const;

    void compute_pressures() const;

    void compute_non_pressure_forces(const std::vector<std::vector<Particle *>> &neighbours) const;

    void compute_pressure_forces(const std::vector<std::vector<Particle *>> &neighbours) const;

    Vector3 compute_pressure_gradient(const Particle &p_i, const std::vector<Particle *> &neighbours) const;

    Vector3 compute_velocity_laplacian(const Particle &p_i, const std::vector<Particle *> &neighbours) const;

    Kernel *kernel;

    NeighbourHoodSearch *neighbourhood_search;

    std::vector<Particle *> *particles;
};


#endif //UNTITLED1_FORCES_H
