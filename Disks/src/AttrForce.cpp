#include "AttrForce.h"

glm::vec2 AttrForce::getAttr(glm::vec2 posDisk) {
    
    glm::vec2 distXY = pos - posDisk;
    return ((glm::normalize(distXY)*g)/((glm::length(distXY)+epsilon)*(glm::length(distXY)+epsilon))); // sqrt(x*x + y*y)**2 = r^2
};

void AttrForce::create(float x, float y) {
    pos = glm::vec2(x,y);;
    horizontal1 = pos - glm::vec2(size,0);
    horizontal2 = pos + glm::vec2(size,0);
    vertical1 = pos - glm::vec2(0,size);
    vertical2 = pos + glm::vec2(0,size);
}

void AttrForce::draw() {
    ofSetColor(color);
    ofDrawLine(horizontal1,horizontal2);
    ofDrawLine(vertical1,vertical2);
    ofNoFill();
    ofDrawCircle(pos, size);
}
