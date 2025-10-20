#pragma once
#include <vector>
#include <unordered_map>
#include <cmath>
#include "NeighbourHoodSearch.h"

struct Int3 {
    int x, y, z;

    bool operator==(const Int3 &other) const {
        return x == other.x && y == other.y && z == other.z;
    }
};

struct Int3Hash {
    std::size_t operator()(const Int3 &k) const noexcept {
        std::size_t h1 = std::hash<int>{}(k.x);
        std::size_t h2 = std::hash<int>{}(k.y);
        std::size_t h3 = std::hash<int>{}(k.z);
        return h1 ^ (h2 << 1) ^ (h3 << 2);
    }
};

class UniformGridSearch final : public NeighbourHoodSearch {
public:
    explicit UniformGridSearch(const std::vector<Particle> &particles, double cell_size);

    std::vector<Particle> find_neighbours(Particle particle) override;

    void update_particles(const std::vector<Particle> &new_particles);

private:
    double cell_size;
    std::unordered_map<Int3, std::vector<int>, Int3Hash> grid;

    void build_grid();

    Int3 cell_index(const Vector3 &pos) const;
};
