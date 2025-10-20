//
// Created by pc on 10/20/2025.
//

#ifndef UNTITLED1_FORCES_H
#define UNTITLED1_FORCES_H

#include "../Simulation.h"

class Forces {
public:
    explicit Forces(Simulation simulation);

private:
    Kernel *kernel;

    std::vector<Particle> *particles;
};


#endif //UNTITLED1_FORCES_H
