//
// Created by pc on 10/20/2025.
//
#include "UniformGridSearch.h"

UniformGridSearch::UniformGridSearch(const std::vector<Particle> &particles, double cell_size)
    : NeighbourHoodSearch(particles), cell_size(cell_size) {
    build_grid();
}

void UniformGridSearch::update_particles(const std::vector<Particle> &new_particles) {
    this->particles = new_particles;
    build_grid();
}

std::vector<Particle> UniformGridSearch::find_neighbours(Particle particle) {
    std::vector<Particle> neighbours;
    auto [x, y, z] = cell_index(particle.position);

    // Search the particle's cell and the 26 surrounding ones
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            for (int dz = -1; dz <= 1; ++dz) {
                Int3 neighbor_cell{x + dx, y + dy, z + dz};
                auto it = grid.find(neighbor_cell);
                if (it == grid.end()) continue;

                for (const int idx : it->second) {
                    const Particle &p2 = particles[idx];
                    if (&p2 == &particle) continue;

                    double dist2 = particle.position.distance(p2.position) * particle.position.distance(p2.position); // TODO fix distance squared method
                    if (dist2 < cell_size * cell_size && dist2 > 0.0) {
                        neighbours.push_back(p2);
                    }
                }
            }
        }
    }

    return neighbours;
}

void UniformGridSearch::build_grid() {
    grid.clear();
    for (size_t i = 0; i < particles.size(); ++i) {
        Int3 cell = cell_index(particles[i].position);
        grid[cell].push_back(static_cast<int>(i));
    }
}

Int3 UniformGridSearch::cell_index(const Vector3 &pos) const {
    return {
        static_cast<int>(std::floor(pos.x / cell_size)),
        static_cast<int>(std::floor(pos.y / cell_size)),
        static_cast<int>(std::floor(pos.z / cell_size))
    };
}
