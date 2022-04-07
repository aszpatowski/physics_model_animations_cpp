//
// Created by aleksander on 13.12.2021.
//

#ifndef ZADANIE4_PARTICLEDATACONTAINER_H
#define ZADANIE4_PARTICLEDATACONTAINER_H

#include <vector>
#include <glm/glm.hpp>

class ParticleDataContainer
{
public:
    std::vector<glm::vec3> position;
    std::vector<glm::vec3> velocity;
    std::vector<glm::vec3> acceleration;
    std::vector<glm::vec4> color;
    std::vector<glm::vec4> start_color;
    std::vector<glm::vec4> end_color;
    std::vector<glm::vec4> time;

    std::vector<float> radius;
    std::vector<bool> alive;

    size_t count = 0;
    size_t countAlive = 0;

public:
    ParticleDataContainer();

    void generate(size_t maxSize);

    void kill(size_t id);

    void wake(size_t id);

    void swapData(size_t a, size_t b);


};

#endif //ZADANIE4_PARTICLEDATACONTAINER_H
