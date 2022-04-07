//
// Created by aleksander on 23.12.2021.
//

#include "Updaters.h"

void EulerUpdater::update(float dt, ParticleDataContainer &p)
{
    const glm::vec3 globalA{globalAcceleration.x, globalAcceleration.y, globalAcceleration.z};

    for (size_t i = 0; i < p.countAlive; ++i)
        p.acceleration[i] += globalA;

    for (size_t i = 0; i < p.countAlive; ++i)
        p.velocity[i] += dt * p.acceleration[i];

    for (size_t i = 0; i < p.countAlive; ++i)
        p.position[i] += dt * p.velocity[i];
}

void TimeUpdater::update(float dt, ParticleDataContainer &p)
{
    size_t endId = p.countAlive;
    if (endId == 0) return;

    for (size_t i = 0; i < p.countAlive; ++i)
    {
        p.time[i].x -= dt;
        p.time[i].z = 1.0f - (p.time[i].x * p.time[i].w);
        p.color[i].a = 255.0f - 255.0f / (p.time[i].x + 1); // I added '+1' in denominator,
        // thanks that particles become transparent more smoothly

        if (p.time[i].x < 0.0f)
        {
            p.kill(i);
            endId = p.countAlive < p.count ? p.countAlive : p.count;
        }

    }

}

void CollisionObjectsUpdater::update(float dt, ParticleDataContainer &p)
{
    for (size_t i = 0; i < p.countAlive; ++i)
    {
        for(size_t s = 0; s < sphereObjects.size(); ++s)
        {
            if(glm::length(p.position[i]-sphereObjects[s].getPosition())<sphereObjects[s].getRadius())
            {
                p.velocity[i] = glm::normalize(p.position[i]-sphereObjects[s].getPosition())*0.3f*glm::length(p.velocity[i]);
                p.position[i] += dt * p.velocity[i];
            }
        }
    }
}

void FloorCollisionUpdater::update(float dt, ParticleDataContainer &p)
{
    for (size_t i = 0; i < p.countAlive; ++i)
    {
        if (p.position[i].y < y)
        {
            glm::vec3 force = p.acceleration[i];
            float normalFactor = glm::dot(force, glm::vec3(0.0f, 1.0f, 0.0f));
            if (normalFactor < 0.0f)
            {
                force -= glm::vec3(0.0f, 1.0f, 0.0f) * normalFactor;
            }
            float velocityFactor = glm::dot(p.velocity[i], glm::vec3(0.0f, 1.0f, 0.0f));
            p.velocity[i] -= glm::vec3(0.0f, 1.0f, 0.0f) * (1.0f + bounce) * velocityFactor;
            p.acceleration[i] = force;
            p.position[i] += dt * p.velocity[i];
        }

    }
}

void AttractorUpdater::update(float dt, ParticleDataContainer &p)
{
    glm::vec3 distXYZ;
    for (size_t i = 0; i < p.countAlive; ++i)
    {
        for(size_t a = 0; a < attractorsPositions.size(); ++a)
        {
            distXYZ = attractorsPositions[a] - p.position[i];
            p.acceleration[i] += ((glm::normalize(distXYZ)*attractorsForce[a])/((glm::length(distXYZ)+0.8f)*(glm::length(distXYZ)+0.8f))); //0.1f is epsilon
        }

    }
}
void GravityUpdater::update(float dt, ParticleDataContainer &p)
{
    for (size_t i = 0; i < p.countAlive; ++i)
    {
        p.acceleration[i] += gravityForce;
    }
}
void SimpleResistanceUpdater::update(float dt, ParticleDataContainer &p)
{
    for (size_t i = 0; i < p.countAlive; ++i)
    {
        p.acceleration[i] += -resistanceForce*p.velocity[i]; // I know that real formula is different and depends on the mass and radius.
    }
}