#pragma once

#include "Vec2.h"

template <typename T, typename = typename std::enable_if<std::is_same<T, int>::value || std::is_same<T, float>::value || std::is_same<T, double>::value>::type>
class Vec3 : public Vec2<T> {
public:
    T z;

    Vec3(T xOff = 0, T yOff = 0, T zOff = 0) : Vec2<T>(xOff, yOff), z(zOff) {};
    Vec3(const Vec3& other) : Vec2<T>(other.x, other.y), z(other.z) {};

    Vec3 operator+(T offset) const {
        return Vec3(this->x + offset, this->y + offset, z + offset);
    };

    Vec3 operator+(const Vec3& other) const {
        return Vec3(this->x + other.x, this->y + other.y, z + other.z);
    };

    Vec3 operator-(T offset) const {
        return Vec3(this->x - offset, this->y - offset, z - offset);
    };

    Vec3 operator-(const Vec3& other) const {
        return Vec3(this->x - other.x, this->y - other.y, z - other.z);
    };

    Vec3 operator*(T offset) const {
        return Vec3(this->x * offset, this->y * offset, z * offset);
    };

    Vec3 operator*(const Vec3& other) const {
        return Vec3(this->x * other.x, this->y * other.y, z * other.z);
    };

    Vec3 operator/(T offset) const {
        return Vec3(this->x / offset, this->y / offset, z / offset);
    };

    Vec3 operator/(const Vec3& other) const {
        return Vec3(this->x / other.x, this->y / other.y, z / other.z);
    };

    T* get() const {
        return &this->x;
    };
};

template <typename T>
Vec3(T, T, T) -> Vec3<T>;