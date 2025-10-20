#include "UniformGridSearch.h"

void UniformGridSearch::update_particles(const std::vector<Particle *> *new_particles) {
    particles = new_particles;
    build_grid();
}

void UniformGridSearch::build_grid() {
    grid.clear();

    for (size_t i = 0; i < particles->size(); ++i) {
        Particle* p = (*particles)[i];
        Int3 idx = cell_index(p->position);
        grid[idx].push_back(i);
    }
}

Int3 UniformGridSearch::cell_index(const Vector3 &pos) const {
    return Int3{
        static_cast<int>(std::floor(pos.x / cell_size)),
        static_cast<int>(std::floor(pos.y / cell_size)),
        static_cast<int>(std::floor(pos.z / cell_size))
    };
}


UniformGridSearch::UniformGridSearch(const std::vector<Particle *> *particles, double cell_size,
    double smoothing_length) : NeighbourHoodSearch(particles) {
    this->cell_size = cell_size;
    this->smoothing_length = smoothing_length;
    build_grid();
}

std::vector<Particle *> UniformGridSearch::find_neighbours(const Particle *particle) {
    std::vector<Particle*> neighbours;

    Int3 center = cell_index(particle->position);

    // Loop over neighboring cells (including the current cell)
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            for (int dz = -1; dz <= 1; ++dz) {
                Int3 neighbor_cell{center.x + dx, center.y + dy, center.z + dz};

                auto it = grid.find(neighbor_cell);
                if (it != grid.end()) {
                    for (int idx : it->second) {
                        Particle* p_j = (*particles)[idx];
                        if (p_j == particle) continue;

                        Vector3 diff = p_j->position - particle->position;
                        if (diff.norm() <= smoothing_length) {
                            neighbours.push_back(p_j);
                        }
                    }
                }
            }
        }
    }

    return neighbours;
}
