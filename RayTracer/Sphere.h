#pragma once
#include "Geometry.h"

class Sphere : public Geometry
{
public:
    Sphere() = default;
    Sphere(const glm::vec3& center, float radius) :
        center(center),
        radius(radius) {}

    bool Hit(const ray_t& r, float tMin, float tMax, raycastHit_t& hit) override;

public:
    glm::vec3 center;
    float radius = 0;
};