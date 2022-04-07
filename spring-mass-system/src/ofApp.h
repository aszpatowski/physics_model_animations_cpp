#pragma once

#include <vector>
#include <iostream>
#include "ofMain.h"
#include "Point.h"
#include "Spring.h"

class ofApp : public ofBaseApp
{

public:
    void setup();

    void update();

    void draw();

    void keyPressed(int key);

    void keyReleased(int key);

    void mouseMoved(int x, int y);

    void mouseDragged(int x, int y, int button);

    void mousePressed(int x, int y, int button);

    void mouseReleased(int x, int y, int button);

    void mouseEntered(int x, int y);

    void mouseExited(int x, int y);

    void windowResized(int w, int h);

    void dragEvent(ofDragInfo dragInfo);

    void gotMessage(ofMessage msg);

    const float g = 9.8;
    const float dt = 1.0f/60.0f;

    const float WIDTH = 1024, HEIGHT = 768;

    std::vector<Spring> springs;
    std::vector<std::vector<Point>> points;
    std::vector<std::vector<Point>> points_backup;

    ofImage background;
    ofImage pan;
    ofImage panRotated;


    ofImage bacon;

    glm::vec2 mousePos;
    bool clicked = false;
    bool modeBacon = true;

    std::vector <glm::vec2> panCollision;
    std::vector <glm::vec2> panCollisionRotated;

    ofImage basket;
    ofImage table;
    ofImage chair;

    glm::vec2 basketPos;
    glm::vec2 tablePos;
    glm::vec2 chairPos;

    std::vector <glm::vec2> basketCollision;
    std::vector <glm::vec2> tableCollision;
    std::vector <glm::vec2> chairCollision;

    float pointRadius;
    float panCollisionRadius;

    int currentLevel;

    ofTrueTypeFont font;


};
