#include "Sphere.h"

bool Sphere::Hit(const ray_t& r, float tMin, float tMax, raycastHit_t& hit)
{
    glm::vec3 oc = r.origin - center;
    float a = glm::dot(r.direction, r.direction);
    float b = 2 * glm::dot(r.direction, oc);
    float c = glm::dot(oc, oc) - (radius * radius);

    // b^2 - 4ac
    float discriminant = (b * b) - (4 * a * c);

    return (discriminant >= 0);
}