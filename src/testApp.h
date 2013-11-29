#pragma once

#include "ofMain.h"
#include "VRCave.h"


class testApp : public ofBaseApp{

	public:
        testApp() : worldScreenEnumerator(displaysConfig){} //Initialization list for display config parser
		void setup();
		void update();
		void draw();
        void exit();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

        KinectTrackerDevice kinect;

        //Displays, Cameras, Viewports
        DisplayEnumerator worldScreenEnumerator;
        vector<UserPerspectiveCam> cameras;
        vector<ofRectangle> viewPorts;
        vector<ofFbo> cameraRenders;
    
        //Projection Mapping
        ProjectionMapping projectionMapping;
        bool enableMappingMarkers;
    private:
    
        void setupViewports();
        void setupCameras();
        void setupCameraSceneRenders();
    
        void initProjectionMapping();
    
        void drawCamSceneRenderFbos();
    
    int xPos, yPos, zPos;
    ofImage someImage;
};