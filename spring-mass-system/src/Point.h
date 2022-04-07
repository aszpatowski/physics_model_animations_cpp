//
// Created by aleksander on 31.01.2022.
//
#pragma once
#ifndef SPRING_MASS_SYSTEM_POINT_H
#define SPRING_MASS_SYSTEM_POINT_H

#include "ofMain.h"


class Point
{
public:
    Point(const glm::vec2 &_pos, const glm::vec2 &_force, float _mass,const glm::vec3 &_color, float dt);
    void appendForce(glm::vec2 _force);
    void absorbForce(float factor);
    void setPos(glm::vec2 newPos);
    void update(float dt);
    void resetForce();

    glm::vec2 previousPos;
    glm::vec2 pos;
    glm::vec2 tempPos;
    glm::vec2 force;
    glm::vec3 color;
    float mass;
};


#endif //SPRING_MASS_SYSTEM_POINT_H
