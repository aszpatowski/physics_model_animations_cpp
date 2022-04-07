#pragma once
#include "ofMain.h"

class AttrForce
{
    private:
    glm::vec2 pos;
    glm::vec2 horizontal1;
    glm::vec2 horizontal2;
    glm::vec2 vertical1;
    glm::vec2 vertical2;
    float g = 300000;
    float size = 8;
    float epsilon = 0.9;
    ofColor color = {255,255,255};
    public:
    void create(float x, float y);
    void draw();
    glm::vec2 getAttr(glm::vec2 posDisk);
};