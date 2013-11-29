#include "ofMain.h"
#include "testApp.h"
#include "ofAppGlutWindow.h"

#define SCREEN_RES_WIDTH 800
#define SCREEN_RES_HEIGHT 600

//========================================================================
int main( ){

    ofAppGlutWindow window;
    #ifdef ENABLE_PROJECTION_MAPPINGsys
    	window.setGlutDisplayString("rgb double depth alpha");
    #endif
	ofSetupOpenGL(&window, SCREEN_RES_WIDTH, SCREEN_RES_HEIGHT, OF_FULLSCREEN);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new testApp());

}
