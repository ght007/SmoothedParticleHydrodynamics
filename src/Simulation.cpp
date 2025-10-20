//
// Created by pc on 10/20/2025.
//

#include "Simulation.h"

#include "math/UniformGridSearch.h"

Simulation::Simulation(std::vector<Particle*> *particles, TimeIntegrator *time_integrator, Kernel *kernel,
                       NeighbourHoodSearch *neighbourhood_search) {
    this->particles = particles;
    this->time_integrator = time_integrator;
    this->kernel = kernel;
    this->neighbourhood_search = neighbourhood_search;
    this->forces = new Forces{*this};
}


void Simulation::simulation_step(double dt) const {
    if (auto *grid = dynamic_cast<UniformGridSearch *>(neighbourhood_search)) {
        grid->update_particles(particles);
    }
    forces->compute_forces();
    time_integrator->integrate(dt);
}
