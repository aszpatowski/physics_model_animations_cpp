//
// Created by aleksander on 23.12.2021.
//

#ifndef ZADANIE4_UPDATERS_H
#define ZADANIE4_UPDATERS_H

#include "ParticleUpdater.h"
#include "SphereObject.h"
#include <iostream>

class EulerUpdater : public ParticleUpdater
{
public:
    glm::vec3 globalAcceleration;
public:
    EulerUpdater() : globalAcceleration(0.0, 0.0, 0.0)
    {}

    virtual void update(float dt, ParticleDataContainer &p) override;
};

class TimeUpdater : public ParticleUpdater
{
public:
    virtual void update(float dt, ParticleDataContainer &p) override;
};

class CollisionObjectsUpdater : public ParticleUpdater
{
public:
    std::vector<SphereObject> sphereObjects;

    CollisionObjectsUpdater(std::vector<SphereObject> const &newSphereObjects) : sphereObjects(newSphereObjects)
    {};
public:
    virtual void update(float dt, ParticleDataContainer &p) override;

};

class FloorCollisionUpdater : public ParticleUpdater
{
public:
    float y;
    float bounce;

    FloorCollisionUpdater(float const &newY, float const &newBounce) : y(newY), bounce(newBounce)
    {};
public:
    virtual void update(float dt, ParticleDataContainer &p) override;
};

class AttractorUpdater : public ParticleUpdater
{
    std::vector<glm::vec3> attractorsPositions;
    std::vector<float> attractorsForce;
public:
    virtual void update(float dt, ParticleDataContainer &p) override;

    void add(const glm::vec3 &attrPos, const float &attrForce)
    {
        attractorsPositions.push_back(attrPos);
        attractorsForce.push_back(attrForce);
    }
};
class GravityUpdater : public ParticleUpdater
{
public:
    glm::vec3 gravityForce;
    GravityUpdater(glm::vec3 newGravityForce):gravityForce(newGravityForce){};
    virtual void update(float dt, ParticleDataContainer &p) override;
};
class SimpleResistanceUpdater : public ParticleUpdater
{
public:
    float resistanceForce;
    SimpleResistanceUpdater(float newResistanceForce): resistanceForce(newResistanceForce){};
    virtual void update(float dt, ParticleDataContainer &p) override;
};


#endif //ZADANIE4_UPDATERS_H
