//
// Created by aleksander on 13.12.2021.
//

#include "ParticleDataContainer.h"

ParticleDataContainer::ParticleDataContainer()
{}

void ParticleDataContainer::generate(size_t maxSize)
{

    count = maxSize;
    countAlive = 0;

    position.clear(); position.reserve(count);
    velocity.clear(); velocity.reserve(count);
    acceleration.clear(); acceleration.reserve(count);
    color.clear(); color.reserve(count);
    start_color.clear(); start_color.reserve(count);
    end_color.clear(); end_color.reserve(count);
    time.clear(); time.reserve(count);
    alive.clear(); alive.reserve(count);
    radius.clear(); radius.reserve(count);
}

void ParticleDataContainer::kill(size_t id)
{

    if (countAlive > 0)
    {
        alive[id] = false;
        swapData(id, countAlive - 1);
        countAlive--;
    }

}

void ParticleDataContainer::wake(size_t id)
{

    if (countAlive < count)
    {
        alive[id] = true;
        countAlive++;
    }
}
void ParticleDataContainer::swapData(size_t a, size_t b)
{
    std::swap(position[a], position[b]);
    std::swap(velocity[a], velocity[b]);
    std::swap(acceleration[a], acceleration[b]);
    std::swap(color[a], color[b]);
    std::swap(start_color[a], start_color[b]);
    std::swap(end_color[a], end_color[b]);
    std::swap(time[a], time[b]);
    std::swap(alive[a], alive[b]);
    std::swap(radius[a], radius[b]);
}
