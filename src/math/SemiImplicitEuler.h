//
// Created by pc on 10/20/2025.
//

#ifndef UNTITLED1_SEMIIMPLICITEULER_H
#define UNTITLED1_SEMIIMPLICITEULER_H
#include "TimeIntegrator.h"


class SemiImplicitEuler final : public TimeIntegrator {
public:
    explicit SemiImplicitEuler(std::vector<Particle *> *particles) : TimeIntegrator(particles) {
    }

    void integrate(const double dt) override {
        for (Particle *p: *particles) {
            p->velocity = p->velocity + dt / p->mass * p->force;
            p->position = p->position + dt * p->velocity;
        }
    }
};


#endif //UNTITLED1_SEMIIMPLICITEULER_H
