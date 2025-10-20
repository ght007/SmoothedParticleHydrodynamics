//
// Created by pc on 10/20/2025.
//
#pragma once

#include "../math/Vector3.h"

class Particle {
public:
    Vector3 position{};

    Vector3 velocity{};

    Vector3 forces{};

    double mass = 0;

    double radius = 0;

    bool isBoundary = false;

    explicit Particle(const double mass, const double radius, const bool isBoundary=false) {
        this->mass = mass;
        this->radius = radius;
        this->isBoundary = isBoundary;
    }
};
