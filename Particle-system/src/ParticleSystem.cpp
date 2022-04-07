//
// Created by aleksander on 13.12.2021.
//

#include "ParticleSystem.h"
#include <iostream>

void ParticleSystem::setup(size_t maxCount)
{
    count = maxCount;
    particles.generate(maxCount);
    aliveParticles.generate(maxCount);
    for (size_t i = 0; i < maxCount; ++i)
    {
        particles.alive[i]= false;
    }
}

void ParticleSystem::update(double dt)
{
    for(auto &emitter:emitters)
    {
        emitter->emit(dt,particles);
    }
    for(size_t i =0 ;i<count; i++)
    {
        particles.acceleration[i] = glm::vec3(0.0f);
    }
    for(auto &updater: updaters)
    {
        updater->update(dt,particles);
    }
}

void ParticleSystem::reset()
{

}


size_t ParticleSystem::numAllParticles() const
{
    return particles.count;
}

size_t ParticleSystem::numAliveParticles() const
{
    return particles.countAlive;
}

void ParticleSystem::addEmitter(std::shared_ptr<ParticleEmitter> emitter)
{
    emitters.push_back(emitter);
}

void ParticleSystem::addUpdater(std::shared_ptr<ParticleUpdater> updater)
{
    updaters.push_back(updater);
}
