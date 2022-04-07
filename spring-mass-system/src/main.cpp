#include "ofMain.h"
#include "ofApp.h"
// Materials
// https://youtu.be/tkeznE2TLAo
// https://youtu.be/bCy1_Jh4kKA
// https://www.youtube.com/watch?v=kyQP4t_wOGI


//========================================================================
int main( ){
	ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
