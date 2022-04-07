//
// Created by aleksander on 31.01.2022.
//

#include "Point.h"

Point::Point(const glm::vec2 &_pos, const glm::vec2 &_force, float _mass,const glm::vec3&_color, float dt= 0.01) : previousPos(_pos), force(_force),
                                                                                                 mass(_mass), color(_color)
{
    pos = previousPos + (dt*dt*force)/mass;
}

void Point::update(float dt)
{
    tempPos = pos;
    pos = 2*pos - previousPos + (dt*dt*force)/mass; //Verlet method
    previousPos = tempPos;
}

void Point::appendForce(glm::vec2 _force)
{
    force+=_force;
}

void Point::resetForce()
{
    force = {0.0,0.0};
}


void Point::setPos(glm::vec2 newPos)
{
    pos += newPos;
}

void Point::absorbForce(float factor)
{
    force*=factor;
}
