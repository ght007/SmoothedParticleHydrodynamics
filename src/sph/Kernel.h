//
// Created by pc on 10/20/2025.
//

#ifndef UNTITLED1_KERNEL_H
#define UNTITLED1_KERNEL_H
#include "../math/Vector3.h"

class Kernel {
public:
    explicit Kernel(double smoothing_length) {
        this->smoothing_length = smoothing_length;
    }

    virtual double W(const Vector3 &p_i, const Vector3 &p_j) = 0;

    virtual Vector3 grad_W(const Vector3 &p_i, const Vector3 &p_j) = 0;

    virtual ~Kernel() = default;

protected:
    double smoothing_length;
};

#endif //UNTITLED1_KERNEL_H
