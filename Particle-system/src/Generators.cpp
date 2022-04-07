//
// Created by aleksander on 23.12.2021.
//

#include "Generators.h"
#include <glm/gtc/random.hpp>
void CubePositionGenerator::generate(double dt, ParticleDataContainer &p, size_t startId, size_t endId)
{
    glm::vec3 posMin{ pos.x - maxStartPosOffset.x, pos.y - maxStartPosOffset.y, pos.z - maxStartPosOffset.z};
    glm::vec3 posMax{ pos.x + maxStartPosOffset.x, pos.y + maxStartPosOffset.y, pos.z + maxStartPosOffset.z};

    for (size_t i = startId; i < endId; ++i)
    {
        p.position[i] = glm::linearRand(posMin, posMax);
        p.radius[i]= particleRadius;
    }
}

void SpherePositionGenerator::generate(double dt, ParticleDataContainer &p, size_t startId, size_t endId)
{
    // Inspiration  https://datagenetics.com/blog/january32020/index.html
    glm::vec3 tempPos;
    for (size_t i=startId;i<endId;++i)
    {
        do
        {
            tempPos = glm::linearRand(minPos, maxPos);
        } while (glm::length(tempPos) > 1.0);
        p.position[i]  = glm::vec3(tempPos.x*radius+pos.x,tempPos.y*radius+pos.y,tempPos.z*radius+pos.z);
        p.radius[i]= particleRadius;
    }
}

void VelocityGenerator::generate(double dt, ParticleDataContainer &p, size_t startId, size_t endId)
{
    for (size_t i = startId; i < endId; ++i)
    {
        p.velocity[i] = glm::linearRand(minVelocity, maxVelocity);
    }
}
void OneColorGenerator::generate(double dt, ParticleDataContainer &p, size_t startId, size_t endId)
{
    for (size_t i = startId; i < endId; ++i)
    {
        p.color[i] = color;
    }
}

void TimeGenerator::generate(double dt, ParticleDataContainer &p, size_t startId, size_t endId)
{
    for (size_t i = startId; i < endId; ++i)
    {
        p.time[i].x = p.time[i].y = glm::linearRand(minTime, maxTime);
        p.time[i].z = (float)0.0;
        p.time[i].w = (float)1.0 / p.time[i].x;
    }
}
