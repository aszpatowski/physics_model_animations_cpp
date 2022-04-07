#include <Disk.h>
constexpr float minRadius = 6;
constexpr float maxRadius = 20;
constexpr float maxVel = 100;

float Disk::defaultDt = 1.0/60;

void Disk::create(int x, int y) {
    radius = ofRandom(minRadius,maxRadius);
    color = setColor();
    pos = setPos(x, y);
    vel = setVel();
    acc = glm::vec2(0,0);
    mass = PI*radius*radius*1; // density = 1
    setCollision();

}
void Disk::setCollision() {
    xCollision.x = 0.0 + radius;
    xCollision.y = ofGetWidth() - radius;

    yCollision.x = 0.0 + radius;
    yCollision.y = ofGetHeight() - radius;
}
void Disk::update(float waterLevel, float viscosity, float dt) {
    if(pos.y>waterLevel)
    {
        acc+= (-6.0*PI*vel*viscosity*getRadius())/mass;
    }

    vel += acc*dt;
    previousPos = pos;
    pos += vel*dt;

    if(pos.x < xCollision.x || pos.x>=xCollision.y)
    {
        setPreviousPos();
        vel.x*=-1;
    }
    if(pos.y < yCollision.x || pos.y>=yCollision.y)
    {
        setPreviousPos();
        vel.y*=-1;
    }
}

void Disk::draw() {
    ofSetColor(color);
    ofFill();
    ofDrawCircle(pos.x,pos.y,radius);
}

glm::vec2 Disk::getPos() {
    return pos;
}

glm::vec2 Disk::getVel() {
    return vel;
}

glm::vec2 Disk::getAcc() {
    return acc;
}

ofColor Disk::getColor() {
    return color;
}

float Disk::getRadius() {
    return radius;
}
float Disk::getMass() {
    return mass;
}
ofColor Disk::setColor() {
    return ofColor(ofRandom(0,255),ofRandom(0,255),ofRandom(0,255));
}

glm::vec2 Disk::setPos(int x, int y) {
    if (x==0 || y == 0)
        return glm::vec2(ofRandom(0+radius,ofGetWidth()-radius), ofRandom(0+radius,ofGetHeight()-radius));
    else
        return glm::vec2(float(x), float(y));
}

glm::vec2 Disk::setVel() {
    return glm::vec2(ofRandom(-maxVel,maxVel),ofRandom(-maxVel,maxVel));
}
void Disk::resetAcc()
{
    acc *= 0;
}
void Disk::updateAcc(glm::vec2 newAcc)
{
    acc+=newAcc;
    
}
void Disk::setVelCollision(glm::vec2 vel2,float mass2)
{
    //https://en.wikipedia.org/wiki/Elastic_collision
    vel = ((mass - mass2)/(mass + mass2))*vel + ((2*mass2)/(mass + mass2))*vel2;
};
void Disk::setPreviousPos()
{
    pos = previousPos;
}

void Disk::addGravity(int gravity) {
    acc.y+=gravity*defaultDt;
}

glm::vec2 Disk::getNextPos() {
    return pos+vel*defaultDt;
}

void Disk::setPos(glm::vec2 newPos) {
    pos = newPos;
}
