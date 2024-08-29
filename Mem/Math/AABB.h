#pragma once

#include "Vec3.h"

class AABB {
public:
    Vec3<float> lower, upper;

    AABB(Vec3<float> lPoint = Vec3<float>(), Vec3<float> uPoint = Vec3<float>()) : lower(lPoint), upper(uPoint) {};

    bool intersects(const Vec3<float>& point) {
        return 
            (point.x >= lower.x && point.x <= upper.x) &&
            (point.y >= lower.y && point.y <= upper.y) &&
            (point.z >= lower.z && point.z <= upper.z);
    };
};