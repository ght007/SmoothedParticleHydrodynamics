#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>

#include "src/Simulation.h"
#include "src/math/SemiImplicitEuler.h"
#include "src/math/UniformGridSearch.h"
#include "src/particles/Particle.h"
#include "src/sph/CubicSplineKernel.h"

int main() {
    auto* particles = new std::vector<Particle*>();

    const double cube_size = 0.5;
    const double radius = Simulation::PARTICLE_RADIUS;
    const double spacing = radius * 2.0;
    const double fluid_height_fraction = 0.8;

    int grid_res = static_cast<int>(std::round(cube_size / spacing));
    std::cout << "Grid resolution: " << grid_res << std::endl;

    // --- Boundary particles ---
    for (int x = 0; x <= grid_res; ++x) {
        for (int y = 0; y <= grid_res; ++y) {
            for (int z = 0; z <= grid_res; ++z) {
                bool is_boundary =
                    (x == 0 || x == grid_res ||
                     y == 0 || // bottom
                     z == 0 || z == grid_res);

                // Open top
                if (is_boundary) {
                    auto* p = new Particle(Simulation::PARTICLE_MASS, radius);
                    p->position = Vector3(
                        x * spacing,
                        y * spacing,
                        z * spacing
                    );
                    p->velocity = Vector3(0.0, 0.0, 0.0);
                    p->is_boundary = true; // 🔹 flag boundary
                    particles->push_back(p);
                }
            }
        }
    }

    // --- Fluid particles ---
    for (int x = 1; x < grid_res; ++x) {
        for (int y = 1; y < static_cast<int>(grid_res * fluid_height_fraction); ++y) {
            for (int z = 1; z < grid_res; ++z) {
                auto* p = new Particle(Simulation::PARTICLE_MASS, radius);
                p->position = Vector3(
                    x * spacing,
                    y * spacing,
                    z * spacing
                );
                p->velocity = Vector3(0.0, 0.0, 0.0);
                p->is_boundary = false; // 🔹 mark as fluid
                particles->push_back(p);
            }
        }
    }

    std::cout << "Total particles: " << particles->size() << std::endl;

    // --- Simulation setup ---
    Kernel* kernel = new CubicSplineKernel(Simulation::SMOOTHING_LENGTH);
    NeighbourHoodSearch* neighborhood_search =
        new UniformGridSearch(particles, Simulation::SMOOTHING_LENGTH, Simulation::SMOOTHING_LENGTH);
    TimeIntegrator* integrator = new SemiImplicitEuler(particles);
    const Simulation simulation(particles, integrator, kernel, neighborhood_search);

    // --- Output ---
    std::ofstream file(R"(C:\Users\pc\CLionProjects\untitled1\src\resources\particle_positions.txt)");
    if (!file.is_open()) {
        std::cerr << "Failed to open output file." << std::endl;
        return -1;
    }

    const int num_steps = 2;
    const double dt = 0.0001;

    for (int step = 0; step < num_steps; ++step) {
        simulation.simulation_step(dt);

        for (const auto& p : *particles) {
            file << p->position.x << " " << p->position.y << " " << p->position.z << " "
                 << (p->is_boundary ? 1 : 0) << " ";  // 🔹 write boundary flag
        }
        file << "\n";
    }

    file.close();

    // Cleanup
    delete kernel;
    delete neighborhood_search;
    delete integrator;
    for (auto p : *particles) delete p;
    delete particles;

    return 0;
}
