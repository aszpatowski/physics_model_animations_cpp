//
// Created by aleksander on 13.12.2021.
//

#ifndef ZADANIE4_PARTICLEGENERATOR_H
#define ZADANIE4_PARTICLEGENERATOR_H
#include "ParticleDataContainer.h"
#include <glm/glm.hpp>
class ParticleGenerator
{
public:
    ParticleGenerator(){};
    virtual ~ParticleGenerator(){};
    virtual void generate(double dt, ParticleDataContainer &p, size_t startId, size_t endId){};
};


#endif //ZADANIE4_PARTICLEGENERATOR_H
