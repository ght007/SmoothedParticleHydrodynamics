//
// Created by pc on 10/20/2025.
//

#include "Simulation.h"

void Simulation::simulation_loop() const {
    for (int i = 0; i < 1000; i++) {
        time_integrator->integrate(0.01);
    }
}
