//
// Created by aleksander on 04.01.2022.
//

#include "SphereObject.h"

const glm::vec3 &SphereObject::getPosition() const
{
    return position;
}

void SphereObject::setPosition(const glm::vec3 &position)
{
    SphereObject::position = position;
}

float SphereObject::getRadius() const
{
    return radius;
}

void SphereObject::setRadius(float radius)
{
    SphereObject::radius = radius;
}

const glm::vec4 &SphereObject::getColor() const
{
    return color;
}

void SphereObject::setColor(const glm::vec4 &color)
{
    SphereObject::color = color;
}

