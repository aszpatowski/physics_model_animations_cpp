#pragma once

#include "ofMain.h"
#include "Disk.h"
#include "AttrForce.h"
#include "ofxGui.h"

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
		void createDisks();

		float getFluidLevel();
		float getViscosity();
	private:

		vector <Disk> myDisks;
		vector <AttrForce>  myAttrForces;
        vector <vector<int>> willCollide;
        vector <int> disksToSkip;

		ofxFloatSlider fluidLevel;
		float fluidWidth;
		float fluidHeight;
		ofxFloatSlider  viscosity;
        ofxIntSlider gravity;
		ofxPanel gui;

		ofTrueTypeFont font;
		
};
