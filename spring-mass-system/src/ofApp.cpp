#include "ofApp.h"


//--------------------------------------------------------------



void ofApp::setup()
{
    font.load(OF_TTF_SANS, 14, true, true);
    currentLevel = 1;

    ofBackground(0, 0, 0);
    background.load("background.jpg");
    background.resize(WIDTH, HEIGHT);

    pan.load("Pan.png");
    pan.resize(WIDTH / 4, HEIGHT / 14);

    panRotated.load("Pan_13degrees.png");
    panRotated.resize(WIDTH / 4, HEIGHT / 8);

    bacon.load("bacon.png");

    basket.load("basket.png");
    basket.resize(WIDTH/4, HEIGHT/4);

    table.load("table.png");
    table.resize(WIDTH/4, HEIGHT/4);

    chair.load("chair.png");
    chair.resize(WIDTH/4, HEIGHT/4);

    pointRadius = 2;
    panCollisionRadius = 10;

    size_t widthObject = 15, heightObject = 3;
    float distanceBetweenPoints = 6;
    glm::vec2 beginPoint = {200, -50};

    bacon.resize(distanceBetweenPoints + 1, heightObject * distanceBetweenPoints);

    // Generate points
    std::vector<Point> tempPoints; // Row by row...
    for (size_t i = 0; i < heightObject; ++i)
    {
        for (size_t j = 0; j < widthObject; ++j)
        {
            tempPoints.emplace_back(Point(glm::vec2(beginPoint.x + distanceBetweenPoints * j,
                                                    beginPoint.y + distanceBetweenPoints * i), glm::vec2(-15.0, 0.0),
                                          2.0f, glm::vec3(255, 0, 0), dt
            ));
        }
        points.push_back(tempPoints);
        tempPoints.clear();
    }
    points_backup = points;

    // Connect points with springs (with scheme: right, down, right down diagonally and left down diagonally. If this is possible)

    for (size_t i = 0; i < heightObject; i++)
    {
        for (size_t j = 0; j < widthObject; j++)
        {
            if (j + 1 < widthObject) //right
                springs.push_back(Spring({{i, j},
                                          {i, j + 1}}, distanceBetweenPoints, 1, distanceBetweenPoints - 5,
                                         distanceBetweenPoints + 5));
            if (i + 1 < heightObject) //down
                springs.push_back(Spring({{i,     j},
                                          {i + 1, j}}, distanceBetweenPoints, 1, distanceBetweenPoints - 5,
                                         distanceBetweenPoints + 5));

            if (j + 1 < widthObject && i + 1 < heightObject) //right down diagonally
            {
                springs.push_back(Spring({{i,     j},
                                          {i + 1, j + 1}}, distanceBetweenPoints * sqrt(2), 1,
                                         distanceBetweenPoints - 5, distanceBetweenPoints + 5));
            }
            if (int(j) - 1 >= 0 && i + 1 < heightObject) //left down diagonally
            {
                springs.push_back(Spring({{i,     j},
                                          {i + 1, j - 1}}, distanceBetweenPoints * sqrt(2), 1,
                                         distanceBetweenPoints - 5, distanceBetweenPoints + 5));
            }
        }
    }

    panCollision = {glm::vec2(110, 40),
                    glm::vec2(120, 40),
                    glm::vec2(130, 40),
                    glm::vec2(140, 40),
                    glm::vec2(150, 40),
                    glm::vec2(160, 40),
                    glm::vec2(170, 40),
                    glm::vec2(180, 40),
                    glm::vec2(190, 40),
                    glm::vec2(200, 40),
                    glm::vec2(210, 40),
                    glm::vec2(220, 40),
                    glm::vec2(230, 40),
                    glm::vec2(240, 40)};
    panCollisionRotated = {
            glm::vec2(109, 59),
            glm::vec2(119, 61),
            glm::vec2(129, 63),
            glm::vec2(139, 65),
            glm::vec2(149, 67),
            glm::vec2(159, 69),
            glm::vec2(169, 71),
            glm::vec2(179, 73),
            glm::vec2(189, 75),
            glm::vec2(199, 77),
            glm::vec2(209, 79),
            glm::vec2(219, 81),
            glm::vec2(229, 83),
            glm::vec2(239, 85)
    };

    basketPos = {(3*WIDTH)/4.0 - 80,(3*HEIGHT)/4.0};

    basketCollision = {glm::vec2(35, 28),
            glm::vec2(25, 30),
                       glm::vec2(27, 40),
                       glm::vec2(29, 50),
                       glm::vec2(31, 60),
                       glm::vec2(33, 70),
                       glm::vec2(35, 80),
                       glm::vec2(37, 90),
                       glm::vec2(39, 100),
                       glm::vec2(40, 110),
                       glm::vec2(41, 120),
                       glm::vec2(42, 130),
                       glm::vec2(44, 140),
                       glm::vec2(45, 150),
                       glm::vec2(47, 160),
                       glm::vec2(48, 170),
                       glm::vec2(64, 168),
                       glm::vec2(79, 166),
                       glm::vec2(94, 164),
                       glm::vec2(109, 162),
                       glm::vec2(124, 160),
                       glm::vec2(139, 162),
                       glm::vec2(154, 164),
                       glm::vec2(169, 166),
                       glm::vec2(184, 168),
                       glm::vec2(199, 170),
                       glm::vec2(212, 28),
                       glm::vec2(222, 30),
                       glm::vec2(220, 40),
                       glm::vec2(218, 50),
                       glm::vec2(217, 60),
                       glm::vec2(215, 70),
                       glm::vec2(214, 80),
                       glm::vec2(212, 90),
                       glm::vec2(211, 100),
                       glm::vec2(209, 110),
                       glm::vec2(208, 120),
                       glm::vec2(206, 130),
                       glm::vec2(205, 140),
                       glm::vec2(203, 150),
                       glm::vec2(202, 160),
                       glm::vec2(200, 170),
    };

}

//--------------------------------------------------------------
void ofApp::update()
{
    for (size_t i = 0; i < points.size(); ++i)
    {
        for (size_t j = 0; j < points[0].size(); ++j)
        {
            points[i][j].resetForce();
            points[i][j].appendForce({0, g * 20});
        }
    }
    float dist;
    float dx;
    float F;
    glm::vec2 normal;
    bool shouldStabilize;
    for (size_t index = 0; index < springs.size(); ++index)
    {
        shouldStabilize = false;
        dist = glm::distance(points[springs[index].idPoints[0][0]][springs[index].idPoints[0][1]].pos,
                             points[springs[index].idPoints[1][0]][springs[index].idPoints[1][1]].pos);

        dx = dist - springs[index].d0;
        F = -springs[index].k * dx;
        normal = (points[springs[index].idPoints[0][0]][springs[index].idPoints[0][1]].pos -
                  points[springs[index].idPoints[1][0]][springs[index].idPoints[1][1]].pos) / dist;

        if (dist > springs[index].max)
        {
            shouldStabilize = true;
            dist = dist -  springs[index].max;
        }
        if (dist < springs[index].min)
        {
            shouldStabilize = true;
            dist = springs[index].min -  dist;
        }
        if(shouldStabilize)
        {
            points[springs[index].idPoints[0][0]][springs[index].idPoints[0][1]].setPos((-dist/2)*normal);
            points[springs[index].idPoints[1][0]][springs[index].idPoints[1][1]].setPos((dist/2)*normal);
        }
        points[springs[index].idPoints[0][0]][springs[index].idPoints[0][1]].appendForce(normal * F);
        points[springs[index].idPoints[1][0]][springs[index].idPoints[1][1]].appendForce(-normal * F);
    }

    if (clicked)
    {
        for (size_t i = 0; i < points.size(); ++i)
        {
            for (size_t j = 0; j < points[0].size(); ++j)
            {
                for (size_t panId = 0; panId < panCollision.size(); ++panId)
                {
                    normal = points[i][j].pos - (mousePos + panCollision[panId]);
                    dist = glm::length(normal);
                    if (dist < (pointRadius + panCollisionRadius))
                    {

                        points[i][j].absorbForce(0.9);
                        points[i][j].appendForce((normal / dist) * 15000);
                    }

                }
            }
        }
    } else
    {
        for (size_t i = 0; i < points.size(); ++i)
        {
            for (size_t j = 0; j < points[0].size(); ++j)
            {
                for (size_t panId = 0; panId < panCollisionRotated.size(); ++panId)
                {
                    normal = points[i][j].pos - (mousePos + panCollisionRotated[panId]);
                    dist = glm::length(normal);
                    if (dist < (pointRadius + panCollisionRadius))
                    {
                        points[i][j].absorbForce(0.9);
                        points[i][j].appendForce((normal / dist) * 15000);
                    }
                }
            }
        }
    }

    switch (currentLevel)
    {
        case 1:

            for (size_t i = 0; i < points.size(); ++i)
            {
                for (size_t j = 0; j < points[0].size(); ++j)
                {
                    for (size_t colId = 0; colId < basketCollision.size(); ++colId)
                    {
                        normal = points[i][j].pos - (basketPos + basketCollision[colId]);
                        dist = glm::length(normal);
                        if (dist < (pointRadius + panCollisionRadius))
                        {
                            points[i][j].absorbForce(0.8);
                            points[i][j].appendForce((normal / dist) * 16000);
                        }
                    }
                }
            }

            break;
        case 2:
            break;
        case 3:
            break;
    }



    for (size_t i = 0; i < points.size(); ++i)
    {
        for (size_t j = 0; j < points[0].size(); ++j)
        {
            points[i][j].update(dt);

        }
    }



    // if out of the screen reset.
    if (points[0][0].pos.x > WIDTH +200 || points[0][0].pos.x < -200 || points[0][0].pos.y > HEIGHT+200 ||
        points[0][0].pos.y < -400)
    {
        points.clear();
        points = points_backup;
    }

}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofSetColor(255, 255, 255);
    background.draw(0, 0);
    if (modeBacon)
    {
        for (size_t j = 0; j < points[0].size(); ++j)
        {
            ofSetColor(255, 255, 255);
            bacon.draw(points[0][j].pos);
        }
    } else
    {
        for (size_t index = 0; index < springs.size(); ++index)
        {
            ofSetColor(0, 255, 0);
            ofDrawLine(points[springs[index].idPoints[0][0]][springs[index].idPoints[0][1]].pos,
                       points[springs[index].idPoints[1][0]][springs[index].idPoints[1][1]].pos);
        }

        for (size_t i = 0; i < points.size(); ++i)
        {
            for (size_t j = 0; j < points[0].size(); ++j)
            {
                ofSetColor(255, 0, 0);
                ofDrawCircle(points[i][j].pos, pointRadius);
            }
        }
    }
    if (clicked)
    {
        pan.draw(mousePos);
        if (!modeBacon)
        {
            ofSetColor(255, 0, 255);
            for (size_t i = 0; i < panCollision.size(); ++i)
            {
                ofDrawCircle(mousePos + panCollision[i], panCollisionRadius);
            }
        }

    } else
    {
        panRotated.draw(mousePos);
        if (!modeBacon)
        {
            ofSetColor(255, 0, 255);
            for (size_t i = 0; i < panCollisionRotated.size(); ++i)
            {
                ofDrawCircle(mousePos + panCollisionRotated[i], panCollisionRadius);
            }
        }
    }
    ofSetColor(255, 255, 255);
    switch (currentLevel)
    {
        case 1:
            basket.draw(basketPos);
            if(!modeBacon){
                ofSetColor(255, 0, 255);
                for (size_t i = 0; i < basketCollision.size(); ++i)
                {
                    ofDrawCircle(basketPos + basketCollision[i], panCollisionRadius);
                }
            }
            break;
        case 2:

            if(!modeBacon){

            }
            break;
        case 3:

            if(!modeBacon){

            }
            break;
    }


    ofSetColor(255, 255, 255);
    ofDrawLine(glm::vec2(WIDTH/3 + WIDTH / 4,0),glm::vec2(WIDTH/3 + WIDTH / 4,HEIGHT));

    font.drawString("Current Level: " + ofToString(currentLevel), ofGetWidth() - 200, 40);
    font.drawString("Left CTRL to change the view.", ofGetWidth() - 300, 60);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    if (key == 3682) //Left control
    {
        if (modeBacon == true)
        { modeBacon = false; }
        else
        {
            modeBacon = true;
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
    if(x>WIDTH/3)
        x = WIDTH/3;
    mousePos = {x, y};
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
    if(x>WIDTH/3)
        x = WIDTH/3;
    mousePos = {x, y};
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
    if(x>WIDTH/3)
        x = WIDTH/3;
    mousePos = {x, y};
    clicked = true;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
    if(x>WIDTH/3)
        x = WIDTH/3;
    mousePos = {x, y};
    clicked = false;
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{
    if(x>WIDTH/3)
        x = WIDTH/3;
    mousePos = {x, y};
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
{

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{

}


