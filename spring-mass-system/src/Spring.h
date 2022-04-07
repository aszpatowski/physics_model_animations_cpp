//
// Created by aleksander on 01.02.2022.
//
#pragma once
#ifndef SPRING_MASS_SYSTEM_SPRING_H
#define SPRING_MASS_SYSTEM_SPRING_H

#include "ofMain.h"
#include <utility>
#include <vector>

struct Spring
{
    Spring(std::vector<std::vector<size_t>> _idPoints, float _d0, float _k,float _min, float _max) : idPoints(std::move(_idPoints)), d0(_d0), k(_k),min(_min),max(_max)
    {
    };
    std::vector<std::vector<size_t>> idPoints;
    float d0; //rest length
    float k;
    float min;
    float max;
};

#endif //SPRING_MASS_SYSTEM_SPRING_H
