#include "ofApp.h"

const float dt = 1 / 60.0;
size_t sumOfParticles = 0;

//--------------------------------------------------------------
void ofApp::setup()
{
    mySound.load("Jingle_Punks_Deck_the_Halls.wav");
    mySound.play();

    font.load(OF_TTF_SANS, 11, true, true);

    background.load("background.jpg");
    ofBackground(0, 50, 0);
    floor.set(2560, 1, 1600);
    floor.setPosition(0, -2.5, (1600 / 2) - 300);

    cam.setGlobalPosition(0, 6, 10);
    cam.setTarget(glm::vec3(0, 3, 0));
    cam.setDistance(800);

    currentCameraPosition = {0,232,766};
    minCameraPosition = {-360,100,499};
    maxCameraPosition = {424,300,777};
    directionCamera = {(minCameraPosition[0]-maxCameraPosition[0])/360.0f,(maxCameraPosition[1]-minCameraPosition[1])/360.0f,(minCameraPosition[2]-maxCameraPosition[2])/360.0f};

    systems.emplace_back();
    systems.emplace_back();
    systems[0].setup(10000);
    systems[1].setup(10000);

    spheres.push_back(SphereObject(glm::vec3(0, 80, 0), 120, glm::vec4(255, 255, 255, 255)));

    spheres.push_back(SphereObject(glm::vec3(0, 250, 0), 80, glm::vec4(255, 255, 255, 255)));

    spheres.push_back(SphereObject(glm::vec3(0, 340, 0), 50, glm::vec4(255, 255, 255, 255)));

    spheres.push_back(SphereObject(glm::vec3(-15, 360, 45), 6, glm::vec4(10, 10, 10, 255)));
    spheres.push_back(SphereObject(glm::vec3(15, 360, 45), 6, glm::vec4(10, 10, 10, 255)));

    spheres.push_back(SphereObject(glm::vec3(0, 340, 49), 4, glm::vec4(255, 165, 0, 255)));


    std::shared_ptr<ParticleEmitter> emitter = std::make_shared<ParticleEmitter>();
    emitter->emitRate = 380;
    emitter->addGenerator(std::make_shared<CubePositionGenerator>(glm::vec3(0, 600, 50), glm::vec3(800, 10, 250), 1.5));
    emitter->addGenerator(std::make_shared<VelocityGenerator>(glm::vec3(-10, -10, -9), glm::vec3(10, 9, 9)));
    emitter->addGenerator(std::make_shared<OneColorGenerator>(glm::vec4(255.0f, 255.0f, 255.0f, 255.0f)));
    emitter->addGenerator(std::make_shared<TimeGenerator>(3, 15));
    systems[0].addEmitter(emitter);

    std::shared_ptr<ParticleEmitter> emitter2 = std::make_shared<ParticleEmitter>();
    emitter2->emitRate = 160;
    emitter2->addGenerator(std::make_shared<SpherePositionGenerator>(glm::vec3(-300, 100, 0), 30, 1.5));
    emitter2->addGenerator(std::make_shared<VelocityGenerator>(glm::vec3(70, 90, -20), glm::vec3(180, 180, 20)));
    emitter2->addGenerator(std::make_shared<OneColorGenerator>(glm::vec4(255.0f, 255.0f, 255.0f, 255.0f)));
    emitter2->addGenerator(std::make_shared<TimeGenerator>(3, 10));
    systems[0].addEmitter(emitter2);

    std::shared_ptr<ParticleEmitter> emitter3 = std::make_shared<ParticleEmitter>();
    emitter3->emitRate = 160;
    emitter3->addGenerator(std::make_shared<SpherePositionGenerator>(glm::vec3(300, 100, 0), 30, 1.5));
    emitter3->addGenerator(std::make_shared<VelocityGenerator>(glm::vec3(-180, 90, -20), glm::vec3(-70, 180, 20)));
    emitter3->addGenerator(std::make_shared<OneColorGenerator>(glm::vec4(255.0f, 255.0f, 255.0f, 255.0f)));
    emitter3->addGenerator(std::make_shared<TimeGenerator>(3, 10));
    systems[0].addEmitter(emitter3);

    snowCannon1.set(45,180);
    snowCannon2.set(45,180);

    snowCannon1.setPosition(-340,30,0);
    snowCannon2.setPosition(340,30,0);

    snowCannon1.rotateDeg(-37,0,0,1);
    snowCannon2.rotateDeg(37,0,0,1);



    std::shared_ptr<EulerUpdater> eulerUpdater = std::make_shared<EulerUpdater>();
    std::shared_ptr<TimeUpdater> timeUpdater = std::make_shared<TimeUpdater>();
    std::shared_ptr<FloorCollisionUpdater> floorCollisionUpdater = std::make_shared<FloorCollisionUpdater>(0, 0.1);
    std::shared_ptr<CollisionObjectsUpdater> collisionObjectsUpdater = std::make_shared<CollisionObjectsUpdater>(
            spheres);
    std::shared_ptr<GravityUpdater> gravityUpdater = std::make_shared<GravityUpdater>(glm::vec3(0, -25, 0));
    std::shared_ptr<SimpleResistanceUpdater> simpleResistanceUpdater = std::make_shared<SimpleResistanceUpdater>(0.01);

    systems[0].addUpdater(gravityUpdater);
    systems[0].addUpdater(simpleResistanceUpdater);
    systems[0].addUpdater(eulerUpdater);
    systems[0].addUpdater(floorCollisionUpdater);
    systems[0].addUpdater(collisionObjectsUpdater);
    systems[0].addUpdater(timeUpdater);


    light.setPosition(glm::vec3(-160, 100, 40));
    light.setScale(glm::vec3(200, 10, 100));


    light3.setPosition(glm::vec3(0, 400, 50));
    light3.setScale(glm::vec3(200, 100, 200));


    std::shared_ptr<ParticleEmitter> emitter4 = std::make_shared<ParticleEmitter>();
    emitter4->emitRate = 130;
    emitter4->addGenerator(std::make_shared<SpherePositionGenerator>(glm::vec3(-250, 10, 300), 10, 1.7));
    emitter4->addGenerator(std::make_shared<VelocityGenerator>(glm::vec3(-4, 50, -5), glm::vec3(4, 100, 5)));
    emitter4->addGenerator(std::make_shared<OneColorGenerator>(glm::vec4(255.0f, 0.0f, 0.0f, 255.0f)));
    emitter4->addGenerator(std::make_shared<TimeGenerator>(1, 2));
    systems[1].addEmitter(emitter4);

    std::shared_ptr<ParticleEmitter> emitter6 = std::make_shared<ParticleEmitter>();
    emitter6->emitRate = 250;
    emitter6->addGenerator(std::make_shared<SpherePositionGenerator>(glm::vec3(-250, 10, 300), 25, 1.3));
    emitter6->addGenerator(std::make_shared<VelocityGenerator>(glm::vec3(-4, 50, -5), glm::vec3(4, 100, 5)));
    emitter6->addGenerator(std::make_shared<OneColorGenerator>(glm::vec4(255.0f, 255.0f, 0.0f, 255.0f)));
    emitter6->addGenerator(std::make_shared<TimeGenerator>(1, 1.5));
    systems[1].addEmitter(emitter6);

    std::shared_ptr<ParticleEmitter> emitter8 = std::make_shared<ParticleEmitter>();
    emitter8->emitRate = 290;
    emitter8->addGenerator(std::make_shared<SpherePositionGenerator>(glm::vec3(-250, 100, 300), 20, 0.8f));
    emitter8->addGenerator(std::make_shared<VelocityGenerator>(glm::vec3(-14, 50, -15), glm::vec3(14, 100, 15)));
    emitter8->addGenerator(std::make_shared<OneColorGenerator>(glm::vec4(30, 30, 30, 255.0f)));
    emitter8->addGenerator(std::make_shared<TimeGenerator>(1, 4));
    systems[1].addEmitter(emitter8);


    std::shared_ptr<ParticleEmitter> emitter5 = std::make_shared<ParticleEmitter>();
    emitter5->emitRate = 130;
    emitter5->addGenerator(std::make_shared<SpherePositionGenerator>(glm::vec3(250, 10, 300), 10, 1.7));
    emitter5->addGenerator(std::make_shared<VelocityGenerator>(glm::vec3(-4, 50, -5), glm::vec3(4, 100, 5)));
    emitter5->addGenerator(std::make_shared<OneColorGenerator>(glm::vec4(255.0f, 0.0f, 0.0f, 255.0f)));
    emitter5->addGenerator(std::make_shared<TimeGenerator>(1, 2));
    systems[1].addEmitter(emitter5);

    std::shared_ptr<ParticleEmitter> emitter7 = std::make_shared<ParticleEmitter>();
    emitter7->emitRate = 250;
    emitter7->addGenerator(std::make_shared<SpherePositionGenerator>(glm::vec3(250, 10, 300), 25, 1.3));
    emitter7->addGenerator(std::make_shared<VelocityGenerator>(glm::vec3(-4, 50, -5), glm::vec3(4, 100, 5)));
    emitter7->addGenerator(std::make_shared<OneColorGenerator>(glm::vec4(255.0f, 255.0f, 0.0f, 255.0f)));
    emitter7->addGenerator(std::make_shared<TimeGenerator>(1, 1.5));
    systems[1].addEmitter(emitter7);

    std::shared_ptr<ParticleEmitter> emitter9 = std::make_shared<ParticleEmitter>();
    emitter9->emitRate = 290;
    emitter9->addGenerator(std::make_shared<SpherePositionGenerator>(glm::vec3(250, 100, 300), 20, 0.8f));
    emitter9->addGenerator(std::make_shared<VelocityGenerator>(glm::vec3(-14, 50, -15), glm::vec3(14, 100, 15)));
    emitter9->addGenerator(std::make_shared<OneColorGenerator>(glm::vec4(30, 30, 30, 255.0f)));
    emitter9->addGenerator(std::make_shared<TimeGenerator>(1, 4));
    systems[1].addEmitter(emitter9);

    std::shared_ptr<EulerUpdater> eulerUpdater1 = std::make_shared<EulerUpdater>();
    std::shared_ptr<TimeUpdater> timeUpdater1 = std::make_shared<TimeUpdater>();

    systems[1].addUpdater(eulerUpdater1);
    systems[1].addUpdater(timeUpdater1);


    campFireWood1.set(20,100);
    campFireWood2.set(20,100);

    campFireWood3.set(20,100);
    campFireWood4.set(20,100);

    campFireWood1.setPosition(-250,2.2,300);
    campFireWood2.setPosition(-250,2,300);

    campFireWood3.setPosition(250,2.2,300);
    campFireWood4.setPosition(250,2,300);

    campFireWood1.rotateDeg(90,1,0,0);
    campFireWood2.rotateDeg(87,1,0,0);
    campFireWood3.rotateDeg(90,1,0,0);
    campFireWood4.rotateDeg(87,1,0,0);

    campFireWood1.rotateDeg(45,0,1,0);
    campFireWood2.rotateDeg(-45,0,1,0);
    campFireWood3.rotateDeg(45,0,1,0);
    campFireWood4.rotateDeg(-45,0,1,0);

    light4.setPosition(glm::vec3(-250, 20, 300));
    light4.setPointLight();

    light5.setPosition(glm::vec3(250, 20, 300));
    light5.setPointLight();

    ofEnableDepthTest();
    ofEnableAlphaBlending();
    ofEnableSmoothing();

    //light.enable();
    light3.enable();
    light4.enable();
    light5.enable();
}

//--------------------------------------------------------------
void ofApp::update()
{
    sumOfParticles = 0;
    for (auto &system: systems)
    {
        system.update(dt);
        sumOfParticles += system.numAliveParticles();
    }
    std::stringstream windowTitleString;
    windowTitleString.clear();
    windowTitleString << "fps: " << ofGetFrameRate() << "\tNumber of Particles:" << sumOfParticles;
    ofSetWindowTitle(windowTitleString.str());
    //std::cout<< cam.getGlobalPosition().x <<"\t"<<cam.getGlobalPosition().y<<"\t"<<cam.getGlobalPosition().z<<std::endl;

}

//--------------------------------------------------------------
void ofApp::draw()
{
    animCamera();
    cam.begin();
    ofSetColor(0, 100, 0, 255);
    floor.draw();
    ofSetColor(255, 255, 255, 255);
    background.draw(-background.getWidth() / 2, 0, -300);
    ofSetColor(30, 30, 30, 255);
    snowCannon1.draw();
    snowCannon2.draw();
    ofSetColor(43, 29, 14, 255);
    campFireWood1.draw();
    campFireWood2.draw();
    campFireWood3.draw();
    campFireWood4.draw();

    for (auto &system: systems)
    {
        for (size_t i = 0; i < system.numAliveParticles(); ++i)
        {

            ofSetColor((int) system.particles.color[i].r, (int) system.particles.color[i].g,
                       (int) system.particles.color[i].b, (int) system.particles.color[i].a);
            ofDrawSphere(system.particles.position[i], system.particles.radius[i]);

        }
    }
    for (size_t i = 0; i < spheres.size(); ++i)
    {
        ofSetColor((int) spheres[i].color.r, (int) spheres[i].color.g, (int) spheres[i].color.b,
                   (int) spheres[i].color.a);
        ofDrawSphere(spheres[i].getPosition(), spheres[i].getRadius());
    }
    cam.end();
    ofSetColor(255, 255, 255);
    font.drawString("Autor: Aleksander Szpatowski",ofGetWidth() -230,ofGetHeight() -10);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{

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

void ofApp::animCamera()
{
    currentCameraPosition[0] += directionCamera[0];
    currentCameraPosition[1] += directionCamera[1];
    currentCameraPosition[2] += directionCamera[2];
    cam.setGlobalPosition(currentCameraPosition[0],currentCameraPosition[1],currentCameraPosition[2]);
    cam.setTarget(glm::vec3(0, 30, 0));
    cam.setDistance(700);
    if(currentCameraPosition[0]>maxCameraPosition[0]) directionCamera[0]*=-1;
    if(currentCameraPosition[1]>maxCameraPosition[1]) directionCamera[1]*=-1;
    if(currentCameraPosition[2]>maxCameraPosition[2]) directionCamera[2]*=-1;

    if(currentCameraPosition[0]<minCameraPosition[0]) directionCamera[0]*=-1;
    if(currentCameraPosition[1]<minCameraPosition[1]) directionCamera[1]*=-1;
    if(currentCameraPosition[2]<minCameraPosition[2]) directionCamera[2]*=-1;
}
