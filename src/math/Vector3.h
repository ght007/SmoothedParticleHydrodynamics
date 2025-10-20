//
// Created by pc on 10/20/2025.
//

#ifndef UNTITLED1_VECTOR3_H
#define UNTITLED1_VECTOR3_H
#include <cmath>

class Vector3 {
public:
    double x = 0;
    double y = 0;
    double z = 0;

    Vector3() = default;

    Vector3(const double x, const double y, const double z) {
        this->x = x;
        this->y = y;
        this->z = z;
    };

    [[nodiscard]] double norm() const {
        return sqrt(x * x + y * y + z * z);
    }

    [[nodiscard]] double norm2() const {
        return sqrt(x * x + y * y + z * z);
    }

    [[nodiscard]] Vector3 normalize() const {
        return {x / norm(), y / norm(), z / norm()};
    }

    [[nodiscard]] double dot(const Vector3& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    [[nodiscard]] double distance(const Vector3& other) const {
        return (*this - other).norm();
    }

    bool operator==(const Vector3 &other) const {
        return x == other.x && y == other.y && z == other.z;
    }

    bool operator!=(const Vector3& other) const {
        return !(*this == other);
    }

    Vector3 operator+(const Vector3& other) const {
        return {x + other.x, y + other.y, z + other.z};
    }

    Vector3 operator-(const Vector3& other) const {
        return {x - other.x, y - other.y, z - other.z};
    }

    Vector3 operator*(const Vector3& other) const {
        return {x * other.x, y * other.y, z * other.z};
    }

    friend Vector3 operator*(double scale, const Vector3& vector) {
        return {scale * vector.x, scale * vector.y, scale * vector.z};
    }

    Vector3 operator/(const Vector3& other) const {
        return {x / other.x, y / other.y, z / other.z};
    }

    friend Vector3 operator/(double scale, const Vector3& vector) {
        return {scale / vector.x, scale / vector.y, scale / vector.z};
    }
};


#endif //UNTITLED1_VECTOR3_H
