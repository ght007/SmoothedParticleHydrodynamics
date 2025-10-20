//
// Created by pc on 10/20/2025.
//

#ifndef UNTITLED1_TIMEINTEGRATOR_H
#define UNTITLED1_TIMEINTEGRATOR_H
#include <vector>
#include "../particles/Particle.h"

class TimeIntegrator {
public:
    explicit TimeIntegrator(const std::vector<Particle> &particles) {
        this->particles = particles;
    }

    virtual void integrate(double dt) = 0;

    virtual ~TimeIntegrator() = default;

protected:
    std::vector<Particle> particles;
};


#endif //UNTITLED1_TIMEINTEGRATOR_H
