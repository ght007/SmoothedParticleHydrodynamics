//
// Created by pc on 10/20/2025.
//

#ifndef UNTITLED1_CUBICSPLINEKERNEL_H
#define UNTITLED1_CUBICSPLINEKERNEL_H
#include <numbers>

#include "Kernel.h"


class CubicSplineKernel final : public Kernel {
public:
    explicit CubicSplineKernel(const double smoothing_length) : Kernel(smoothing_length) {
    }

    double W(const Vector3 &p_i, const Vector3 &p_j) override {
        const Vector3 r = p_i - p_j;
        const double q = r.norm() / smoothing_length;

        if (2 < q) {
            return 0;
        }
        if (0 <= q && q <= 2) {
            const double h3 = smoothing_length * smoothing_length * smoothing_length;
            const double normalisation_factor = 21 / (16 * h3 * std::numbers::pi);
            return normalisation_factor * std::pow(1 - q / 2, 4) * (1 + 2 * q);
        }
        return 0;
    }

    Vector3 grad_W(const Vector3 &p_i, const Vector3 &p_j) override {
        const Vector3 r = p_i - p_j;
        const double q = r.norm() / smoothing_length;

        if (2 < q) {
            return Vector3{0, 0, 0};
        }
        if (0 <= q && q <= 2) {
            const double h3 = smoothing_length * smoothing_length * smoothing_length;
            const double normalisation_factor = 21 / (16 * h3 * std::numbers::pi) / smoothing_length;
            return normalisation_factor * -5 * q * std::pow(1 - q / 2, 3) / smoothing_length * r;
        }
        return Vector3{0, 0, 0};
    }
};


#endif //UNTITLED1_CUBICSPLINEKERNEL_H
