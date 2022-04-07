#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    gui.setup();
    gui.add(fluidLevel.setup("Fluid level", (2 * ofGetHeight()) / 3, 0, ofGetHeight()));
    gui.add(viscosity.setup("Viscosity", 0.934, 0, 20));
    gui.add(gravity.setup("Gravity", 0, 0, 10000));
    font.load(OF_TTF_SANS, 9, true, true);
    fluidWidth = ofGetWidth();
    int numberOfDisks = 100;

    myDisks.assign(numberOfDisks, Disk());

    createDisks();
}

void ofApp::createDisks() {
    for (size_t i = 0; i < myDisks.size(); i++) {
        myDisks[i].create();
    }
}

//--------------------------------------------------------------
void ofApp::update() {
    for (auto &pair: willCollide) {
        float dt = 0.0;
        for (float i = 1.0 / 600; i < 1.0 / 60; i += 1.0 / 7200) {
            if (glm::length(myDisks[pair[0]].getPos() + myDisks[pair[0]].getVel() * i - myDisks[pair[1]].getPos() +
                            myDisks[pair[1]].getVel() * i) >
                (myDisks[pair[0]].getRadius() + myDisks[pair[1]].getRadius())) {
                dt = i;
            } else {
                break;
            }
        }
        //https://www.wolframalpha.com/input/?i=%28a%2Bb*d%2Bc%2Be*d%29%5E2+%2B+%28f%2Bg*d%2Bh%2Bi*d%29%5E2%3D%28r%2Bl%29%5E2%2C+find+d
        //std::cout<<"he"<<std::endl;
        myDisks[pair[0]].update(getFluidLevel(), getViscosity(), dt);
        myDisks[pair[1]].update(getFluidLevel(), getViscosity(), dt);
        glm::vec2 oldVel1 = myDisks[pair[0]].getVel();
        myDisks[pair[0]].setVelCollision(myDisks[pair[1]].getVel(), myDisks[pair[1]].getMass());
        myDisks[pair[1]].setVelCollision(oldVel1, myDisks[pair[0]].getMass());
        myDisks[pair[0]].update(getFluidLevel(), getViscosity(), 1.0 / 60 - dt);
        myDisks[pair[1]].update(getFluidLevel(), getViscosity(), 1.0 / 60 - dt);
        disksToSkip.push_back(pair[0]);
        disksToSkip.push_back(pair[1]);
    }
    willCollide.clear();
    for (size_t i = 0; i < myDisks.size(); i++) {
        myDisks[i].resetAcc();
        myDisks[i].addGravity(gravity);
        for (size_t j = 0; j < myAttrForces.size(); j++) {
            myDisks[i].updateAcc(myAttrForces[j].getAttr(myDisks[i].getPos()));
        }

        if (std::find(disksToSkip.begin(), disksToSkip.end(), int(i)) == disksToSkip.end()) {
            myDisks[i].update(getFluidLevel(), getViscosity());
        } else{
            std::cout<<"cze"<<std::endl;
        }
        myDisks[i].resetAcc();
        myDisks[i].addGravity(gravity);

        //podpunkt 5 kolizja

        for (size_t j = i; j <= myDisks.size(); j++) {
           if (glm::length(myDisks[i].getPos() - myDisks[j].getPos()) <
                (myDisks[i].getRadius() + myDisks[j].getRadius())) {
                myDisks[i].setPreviousPos();
                myDisks[j].setPreviousPos();
                glm::vec2 oldVel1 = myDisks[i].getVel();
                myDisks[i].setVelCollision(myDisks[j].getVel(), myDisks[j].getMass());
                myDisks[j].setVelCollision(oldVel1, myDisks[i].getMass());
            }
            if (glm::length(myDisks[i].getNextPos() - myDisks[j].getNextPos()) <=
                myDisks[i].getRadius() + myDisks[j].getRadius()) {
                willCollide.push_back(vector<int>{int(i), int(j)});
                /*
                glm::vec2 oldVel1 = myDisks[i].getVel();
                myDisks[i].setVelCollision(myDisks[j].getVel(), myDisks[j].getMass());
                myDisks[j].setVelCollision(oldVel1, myDisks[i].getMass());*/

            }
        }
        //https://www.wolframalpha.com/input/?i=%28p%2Bv*d%2Bq%2Bw*d%29%5E2%3D%28r%2Bl%29%5E2%2C+find+d

    }
    disksToSkip.clear();
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofBackgroundGradient(ofColor(270, 60, 60), ofColor(10, 10, 10));

    for (size_t i = 0; i < myAttrForces.size(); i++) {
        myAttrForces[i].draw();
    }
    for (size_t i = 0; i < myDisks.size(); i++) {
        myDisks[i].draw();
    }
    ofSetColor(0, 0, 128, 64);
    ofFill();
    ofDrawRectangle(0, getFluidLevel(), fluidWidth, ofGetWidth() - getFluidLevel());
    gui.draw();
    ofSetColor(255, 255, 255);
    font.drawString("Number of disks: " + ofToString(myDisks.size()) + " (Press 'D' to reset)", ofGetWidth() - 300, 20);
    font.drawString("Number of attraction forces : " + ofToString(myAttrForces.size()) + " (Press 'A' to reset)",
                    ofGetWidth() - 300, 40);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    // D = 100, A = 97
    if (key == 100) {
        myDisks.clear();
    } else if (key == 97) {
        myAttrForces.clear();
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
    if (button == 0) {
        myDisks.push_back(Disk());
        myDisks[myDisks.size() - 1].create(x, y);
    } else if (button == 2) {
        myAttrForces.push_back(AttrForce());
        myAttrForces[myAttrForces.size() - 1].create(x, y);
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}


float ofApp::getFluidLevel() {
    return fluidLevel;
}

float ofApp::getViscosity() {
    return viscosity;
}
