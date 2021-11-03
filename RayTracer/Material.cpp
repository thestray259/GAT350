#include "Material.h"

bool Lambertian::Scatter(const ray_t& ray, const raycastHit_t& hit, glm::vec3& attenuation, ray_t& scattered) const
{
    //glm::vec3 target = hit.point + hit.normal + randomInUnitSphere();
    //glm::vec3 direction = glm::normalize(target - hit.point);
    glm::vec3 direction = glm::normalize(hit.normal + randomInUnitSphere()); 

    scattered = { hit.point, direction };
    attenuation = albedo->value(hit.uv, hit.point);

    return true;
}

bool Metal::Scatter(const ray_t& ray, const raycastHit_t& hit, glm::vec3& attenuation, ray_t& scattered) const
{
    glm::vec3 reflected = reflect(glm::normalize(ray.direction), hit.normal);

    scattered = ray_t{ hit.point, reflected + (randomInUnitSphere() * fuzz) }; 
    scattered.origin = hit.point;
    scattered.direction = reflected + (randomInUnitSphere() * fuzz);
    attenuation = albedo->value(hit.uv, hit.point);

    return (glm::dot(scattered.direction, hit.normal) > 0);
}

bool Dielectric::Scatter(const ray_t& ray, const raycastHit_t& hit, glm::vec3& attenuation, ray_t& scattered) const
{
    attenuation = albedo->value(hit.uv, hit.point);

    glm::vec3 refracted;
    glm::vec3 normal;
    float cosine;
    float refractionRatio;

    // check if ray is hitting the inside of the surface or from the outside, adjust values
    if (glm::dot(ray.direction, hit.normal) > 0)
    {
        // ray hits inside of surface
        normal = -hit.normal;
        refractionRatio = refractionIndex;
        cosine = refractionIndex * glm::dot(ray.direction, hit.normal) / ray.direction.length();
    }
    else
    {
        // ray hits outside of surface
        normal = hit.normal;
        refractionRatio = 1.0f / refractionIndex;
        cosine = -glm::dot(ray.direction, hit.normal) / ray.direction.length();
    }

    float reflectProbability = 1.0f;
    if (refract(ray.direction, normal, refractionRatio, refracted))
    {
        reflectProbability = schlick(cosine, refractionIndex);
    }

    glm::vec3 reflected = reflect(glm::normalize(ray.direction), hit.normal);

    scattered = (random01() < reflectProbability) ? ray_t{ hit.point, reflected } : ray_t{ hit.point, refracted };

    return true;
}
