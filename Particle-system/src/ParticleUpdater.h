//
// Created by aleksander on 13.12.2021.
//

#ifndef ZADANIE4_PARTICLEUPDATER_H
#define ZADANIE4_PARTICLEUPDATER_H

#include "ParticleDataContainer.h"

class ParticleUpdater
{
public:
    ParticleUpdater()
    { };
    virtual ~ParticleUpdater()
    {  };

    virtual void update(float dt, ParticleDataContainer& p){};
};


#endif //ZADANIE4_PARTICLEUPDATER_H
