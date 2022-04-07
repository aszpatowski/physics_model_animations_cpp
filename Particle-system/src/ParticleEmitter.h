//
// Created by aleksander on 13.12.2021.
//

#ifndef ZADANIE4_PARTICLEEMITTER_H
#define ZADANIE4_PARTICLEEMITTER_H

#include <vector>
#include <memory>
#include "ParticleGenerator.h"
#include "ParticleDataContainer.h"
#include <iostream>
class ParticleEmitter
{
protected:
    std::vector<std::shared_ptr<ParticleGenerator>> generators;

public:
    float emitRate = 300;
public:
    ParticleEmitter()
    {};

    virtual ~ParticleEmitter()
    {};

    void emit(double dt, ParticleDataContainer &p);

    void addGenerator(std::shared_ptr<ParticleGenerator> generator);
};


#endif //ZADANIE4_PARTICLEEMITTER_H
