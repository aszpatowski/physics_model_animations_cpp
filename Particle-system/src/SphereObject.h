//
// Created by aleksander on 04.01.2022.
//

#ifndef ZADANIE4_SPHEREOBJECT_H
#define ZADANIE4_SPHEREOBJECT_H

#include <glm/glm.hpp>

class SphereObject
{
public:
    glm::vec3 position;
    float radius;
    glm::vec4 color;
public:
    SphereObject(const glm::vec3 &newPosition, float newRadius, const glm::vec4 &newColor) : position(newPosition),
                                                                                             radius(newRadius),
                                                                                             color(newColor)
    {};

    const glm::vec3 &getPosition() const;

    void setPosition(const glm::vec3 &position);

    float getRadius() const;

    void setRadius(float radius);

    const glm::vec4 &getColor() const;

    void setColor(const glm::vec4 &color);

};


#endif //ZADANIE4_SPHEREOBJECT_H
