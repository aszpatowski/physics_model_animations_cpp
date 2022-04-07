//
// Created by aleksander on 13.12.2021.
//

#ifndef ZADANIE4_PARTICLESYSTEM_H
#define ZADANIE4_PARTICLESYSTEM_H

#include "ParticleDataContainer.h"
#include "ParticleEmitter.h"
#include "ParticleUpdater.h"
#include "ParticleGenerator.h"
#include <vector>

class ParticleSystem
{
public:
    ParticleDataContainer particles;
    ParticleDataContainer aliveParticles;

    size_t count;

    std::vector<std::shared_ptr<ParticleEmitter>> emitters;
    std::vector<std::shared_ptr<ParticleUpdater>> updaters;
public:
    ParticleSystem(){};
    virtual ~ParticleSystem() = default;

    void setup(size_t maxCount);

    virtual void update(double dt);

    virtual void reset();

    virtual size_t numAllParticles() const;

    virtual size_t numAliveParticles() const;

    void addEmitter(std::shared_ptr<ParticleEmitter> emitter);

    void addUpdater(std::shared_ptr<ParticleUpdater> updater);


};


#endif //ZADANIE4_PARTICLESYSTEM_H
