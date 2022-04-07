//
// Created by aleksander on 23.12.2021.
//

#ifndef ZADANIE4_GENERATORS_H
#define ZADANIE4_GENERATORS_H

#include "ParticleGenerator.h"

#include <iostream>
#include <glm/gtc/random.hpp>

class CubePositionGenerator : public ParticleGenerator
{
public:
    glm::vec3 pos;
    glm::vec3 maxStartPosOffset;
    float particleRadius;
public:
    CubePositionGenerator(const glm::vec3 &newPos, const glm::vec3 &newOffset, const float &newParticleRadius) :
            pos(newPos.x, newPos.y, newPos.z),
            maxStartPosOffset(newOffset.x,
                              newOffset.y,
                              newOffset.z),
                              particleRadius(newParticleRadius)
    {};

    void generate(double dt, ParticleDataContainer &p, size_t startId, size_t endId) override;
};

class SpherePositionGenerator : public ParticleGenerator
{
public:
    glm::vec3 pos;
    float radius;
    float particleRadius;
    const glm::vec3 minPos = {-1, -1, -1};
    const glm::vec3 maxPos = {1, 1, 1};

    SpherePositionGenerator(const glm::vec3 &newPos, const float &newRadius,const float &newParticleRadius) :
            pos(newPos.x, newPos.y, newPos.z),
            radius(newRadius),
            particleRadius(newParticleRadius)
    {};

    void generate(double dt, ParticleDataContainer &p, size_t startId, size_t endId) override;

};

class VelocityGenerator : public ParticleGenerator
{
public:
    glm::vec3 minVelocity;
    glm::vec3 maxVelocity;
public:
    VelocityGenerator(const glm::vec3 &minVel, const glm::vec3 &maxVel) :
            minVelocity(minVel.x, minVel.y, minVel.z),
            maxVelocity(maxVel.x,
                        maxVel.y,
                        maxVel.z)
    {};

    void generate(double dt, ParticleDataContainer &p, size_t startId, size_t endId) override;
};

class OneColorGenerator : public ParticleGenerator
{
public:
    glm::vec4 color;
public:
    OneColorGenerator(const glm::vec4 &newColor) : color(newColor.r, newColor.g, newColor.b, newColor.a)
    {};

    void generate(double dt, ParticleDataContainer &p, size_t startId, size_t endId) override;
};

class TimeGenerator : public ParticleGenerator
{
public:
    float minTime;
    float maxTime;
public:
    TimeGenerator(float newMinTime, float newMaxTime) : minTime(newMinTime), maxTime(newMaxTime)
    {};

    void generate(double dt, ParticleDataContainer &p, size_t startId, size_t endId) override;


};


#endif //ZADANIE4_GENERATORS_H
