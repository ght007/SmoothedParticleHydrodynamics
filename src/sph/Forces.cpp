//
// Created by pc on 10/20/2025.
//

#include "Forces.h"

#include <iostream>
#include <ostream>

Forces::Forces(const Simulation &simulation) {
    this->kernel = simulation.kernel;
    this->neighbourhood_search = simulation.neighbourhood_search;
    this->particles = simulation.particles;
}


void Forces::compute_densities(const std::vector<std::vector<Particle *> > &neighbours) const {
    for (int i = 0; i < particles->size(); i++) {
        Particle &p_i = *particles->at(i);
        if (p_i.is_boundary) continue;
        double density = 0;
        for (const Particle *p_j: neighbours[i]) {
            density += p_j->mass * kernel->W(p_i.position, p_j->position);
        }
        if (density < 1e-5f) {
            p_i.density = 1e-5f;
        }
        p_i.density = density;
    }
}

void Forces::compute_pressures() const {
    constexpr double gamma = 7.0;
    constexpr double rho0 = Simulation::REST_DENSITY; // or particles->at(0).rest_density, depending on your setup
    constexpr double c0 = Simulation::SPEED_OF_SOUND; // should be defined in your simulation parameters
    constexpr double B = (c0 * c0 * rho0) / gamma;

    for (auto &p: *particles) {
        if (p->is_boundary) continue;
        p->pressure = B * (pow(p->density / rho0, gamma) - 1.0);
    }
}


void Forces::compute_forces() const {
    std::vector<std::vector<Particle *> > neighbours;

    for (const auto &p_i: *particles) {
        neighbours.push_back(neighbourhood_search->find_neighbours(p_i));
    }

    compute_densities(neighbours);
    compute_pressures();
    compute_forces(neighbours);
}

void Forces::compute_forces(const std::vector<std::vector<Particle *> > &neighbours) const {
    compute_non_pressure_forces(neighbours);
    compute_pressure_forces(neighbours);
}


void Forces::compute_non_pressure_forces(const std::vector<std::vector<Particle *> > &neighbours) const {
    for (int i = 0; i < particles->size(); i++) {
        Particle &p_i = *particles->at(i);
        if (p_i.is_boundary) continue;
        Vector3 force{
            0, 0, 0
        };
        force.y = p_i.mass * Simulation::GRAVITY;
        force = force + p_i.mass * Simulation::MU / p_i.density * compute_velocity_laplacian(p_i, neighbours[i]);

        p_i.force = force;

        // TODO chatgpt code
        Vector3 boundary_force{0, 0, 0};
        for (const Particle *p_j: neighbours[i]) {
            if (!p_j->is_boundary) continue;
            double dist = (p_i.position - p_j->position).norm();
            if (dist < Simulation::PARTICLE_RADIUS) {
                // simple linear repulsion
                boundary_force = boundary_force + (Simulation::PARTICLE_RADIUS - dist) * 50.0 * (
                                     p_i.position - p_j->position).normalize();
            }
        }
        p_i.force = p_i.force + boundary_force;
    }
}

void Forces::compute_pressure_forces(const std::vector<std::vector<Particle *> > &neighbours) const {
    for (int i = 0; i < particles->size(); i++) {
        Particle &p_i = *particles->at(i);
        if (p_i.is_boundary) continue;
        Vector3 force = p_i.force;

        force = force + -1 / p_i.density * compute_pressure_gradient(p_i, neighbours[i]);

        p_i.force = force;
    }
}

Vector3 Forces::compute_pressure_gradient(const Particle &p_i, const std::vector<Particle *> &neighbours) const {
    auto pressure_gradient = Vector3{0, 0, 0};

    for (const Particle *p_j: neighbours) {
        const double symmetric_part = p_i.pressure / (p_i.density * p_i.density) + p_j->pressure / (
                                          p_j->density * p_j->density);
        pressure_gradient = pressure_gradient + p_j->mass * symmetric_part * (kernel->
                                grad_W(p_i.position, p_j->position));
    }

    return p_i.density * pressure_gradient;
}

Vector3 Forces::compute_velocity_laplacian(const Particle &p_i, const std::vector<Particle *> &neighbours) const {
    auto velocity_laplacian = Vector3{0, 0, 0};

    for (const Particle *p_j: neighbours) {
        Vector3 v_ij = p_i.velocity - p_j->velocity;
        const double grad_W_ij_norm = (kernel->grad_W(p_i.position, p_j->position).norm());
        const double r_ij_norm = (p_i.position - p_j->position).norm();
        velocity_laplacian = velocity_laplacian + p_j->mass / p_j->density * 2 * grad_W_ij_norm / r_ij_norm * v_ij;
    }

    return -1 * velocity_laplacian;
}
