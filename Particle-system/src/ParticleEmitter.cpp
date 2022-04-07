//
// Created by aleksander on 13.12.2021.
//

#include "ParticleEmitter.h"

void ParticleEmitter::addGenerator(std::shared_ptr<ParticleGenerator> generator)
{
    generators.push_back(generator);
}

void ParticleEmitter::emit(double dt, ParticleDataContainer &p)
{
    size_t maxNewParticles = static_cast<size_t>(dt * emitRate);
    size_t startId = p.countAlive;
    size_t endId = std::min(startId + maxNewParticles, p.count - 1);
    for (size_t i =0; i<generators.size();++i)
    {
        generators[i]->generate(dt, p, startId, endId);
    }

    for (size_t i = startId; i < endId; i++)
    {
        p.wake(i);
    }
}
