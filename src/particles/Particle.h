//
// Created by pc on 10/20/2025.
//
#pragma once

#include "../math/Vector3.h"

class Particle {
public:
    Vector3 position{};

    Vector3 velocity{};

    Vector3 force{};

    double mass = 0;

    double density = 0;

    double pressure = 0;

    double radius = 0;

    bool is_boundary = false;

    explicit Particle(const double mass, const double radius, const bool isBoundary=false) {
        this->mass = mass;
        this->radius = radius;
        this->is_boundary = isBoundary;
    }
};
