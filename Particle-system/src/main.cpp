#include "ofMain.h"
#include "ofApp.h"
// https://www.youtube.com/watch?v=MQLSOUenjbI
// https://www.youtube.com/watch?v=_qxXBkyyqkg

// https://www.cppstories.com/2014/03/three-particle-effects/
//========================================================================
int main( ){
	ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
