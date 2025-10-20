//
// Created by pc on 10/20/2025.
//

#ifndef UNTITLED1_NEIGHBOURHOODSEARCH_H
#define UNTITLED1_NEIGHBOURHOODSEARCH_H
#include <vector>

#include "../particles/Particle.h"

class NeighbourHoodSearch {
public:
    explicit NeighbourHoodSearch(const std::vector<Particle *> * particles) {
        this->particles = particles;
    };

    virtual std::vector<Particle *> find_neighbours(const Particle *particle) = 0;

    virtual ~NeighbourHoodSearch() = default;

protected:
    const std::vector<Particle *> *particles;
};

#endif //UNTITLED1_NEIGHBOURHOODSEARCH_H
