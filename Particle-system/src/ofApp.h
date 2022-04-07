#pragma once

#include "ofMain.h"
#include "ofVbo.h"
#include "ofGraphics.h"
#include "ParticleDataContainer.h"
#include "ParticleGenerator.h"
#include "ParticleEmitter.h"
#include "ParticleSystem.h"
#include "ParticleUpdater.h"
#include "Updaters.h"
#include "Generators.h"
#include "SphereObject.h"
#include <string>
class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        void animCamera();
private:

    std::vector<ParticleSystem> systems;
    ofEasyCam cam;
    ofLight light;
    ofLight light3;
    std::vector<SphereObject> spheres;

    ofSoundPlayer mySound;
    ofImage background;
    ofBoxPrimitive floor;

    //camera movement
    std::vector<float> directionCamera;
    std::vector<float> currentCameraPosition;
    std::vector<float> minCameraPosition;
    std::vector<float> maxCameraPosition;

    ofCylinderPrimitive snowCannon1;
    ofCylinderPrimitive snowCannon2;

    ofCylinderPrimitive campFireWood1;
    ofCylinderPrimitive campFireWood2;
    ofCylinderPrimitive campFireWood3;
    ofCylinderPrimitive campFireWood4;

    ofLight light4;
    ofLight light5;

    ofTrueTypeFont font;

		
};
