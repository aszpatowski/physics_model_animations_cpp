#pragma once
#include "ofMain.h"

class Disk
{
private:
    glm::vec2 pos;
    glm::vec2 previousPos;
    glm::vec2 vel;
    glm::vec2 acc;
    ofColor color;
    float radius;
    float mass;
    static float defaultDt;
    ofColor setColor();
    glm::vec2 setVel();
    glm::vec2 setPos(int x, int y);
    //For optimization
    //Thanks that we don't have to add every time radius to our position when we check collision with wall
    void setCollision();

    glm::vec2 xCollision;
    glm::vec2 yCollision;

public:
    void create(int x = 0, int y = 0);
    void update(float waterLevel, float viscosity, float dt = defaultDt);
    void draw();
    glm::vec2 getPos();
    glm::vec2 getVel();
    glm::vec2 getAcc();
    glm::vec2 getNextPos();
    void resetAcc();
    void updateAcc(glm::vec2 deltaAcc);
    ofColor getColor();
    float getRadius();
    float getMass();
    void setVelCollision(glm::vec2 vel2, float mass2);
    void setPreviousPos();
    void addGravity(int gravity);
    void setPos(glm::vec2 newPos);
};