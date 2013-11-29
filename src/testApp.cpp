#include "testApp.h"

void drawWalls();

//--------------------------------------------------------------
void testApp::setup(){
    ofBackground(0);
    
    //Kinect Init Stuff
    kinect.drawDebugSkeleton(true);
    
    //On screen cameras, displays and scene renders objects (for off-screen rendering)
    setupViewports();
    setupCameras();
    setupCameraSceneRenders();
    
    //Projection Mapping
    #ifdef ENABLE_PROJECTION_MAPPING
        initProjectionMapping();
        enableMappingMarkers = true;
    #endif
    
    xPos = -182; yPos = 0; zPos = 2000;
    ofEnableSmoothing();
    ofEnableNormalizedTexCoords();
    someImage.loadImage("stad_2.png");
}

//--------------------------------------------------------------
void testApp::setupViewports(){
    size_t numViewports = worldScreenEnumerator.outputDisplays().size();
    float windowWidth = ofGetWindowWidth(), windowHeight = ofGetWindowHeight();

    float discreteViewportWidth = (float)windowWidth/numViewports, discreteViewportHeight = (float)discreteViewportWidth/ASPECT_RATIO; //TODO : Aspect Ratio assumed > 1 for wide angle displays for now
    
    for(size_t i=0;i<numViewports;++i){
        ofRectangle viewport;
        viewport.set(i * discreteViewportWidth, 0, discreteViewportWidth, discreteViewportHeight);
        viewPorts.push_back(viewport);
    }
}

//--------------------------------------------------------------
void testApp::setupCameras(){
    size_t numViewports = worldScreenEnumerator.outputDisplays().size();
    for(size_t i=0;i<numViewports;++i){
        if(worldScreenEnumerator.outputDisplays().at(i)->shape == QUAD){
            UserPerspectiveCam camera;
            camera.setNearClip(CAM_NEAR);
            camera.setFarClip(CAM_FAR * 10);
            camera.setViewPortalWindow(((QuadDisplayScreen*)worldScreenEnumerator.outputDisplays().at(i))->getTopLeft(),
                                       ((QuadDisplayScreen*)worldScreenEnumerator.outputDisplays().at(i))->getTopRight(),
                                       ((QuadDisplayScreen*)worldScreenEnumerator.outputDisplays().at(i))->getBottomLeft(),
                                       ((QuadDisplayScreen*)worldScreenEnumerator.outputDisplays().at(i))->getBottomRight());
            cameras.push_back(camera);
        }
    }
}

//--------------------------------------------------------------
void testApp::setupCameraSceneRenders(){
    size_t numViewports = worldScreenEnumerator.outputDisplays().size();
    ofRectangle currViewport = ofGetWindowRect();
    for(size_t i=0;i<numViewports;++i){
        ofFbo camSceneFbo; ofFbo::Settings camSceneFboSettings;
        camSceneFboSettings.width = currViewport.width; camSceneFboSettings.height = currViewport.height; camSceneFboSettings.internalformat = GL_RGBA;
        camSceneFbo.allocate(camSceneFboSettings);
        
        //Clear all FBOs to avoid artefacts
        camSceneFbo.begin();
            ofClear(0, 0, 0, 0);
        camSceneFbo.end();
        
        cameraRenders.push_back(camSceneFbo);
    }
}

//--------------------------------------------------------------
void testApp::initProjectionMapping(){
    size_t numDisplays = worldScreenEnumerator.outputDisplays().size();
    for(size_t i=0;i<numDisplays;++i){
        if(worldScreenEnumerator.outputDisplays().at(i)->shape == QUAD){
            QuadContainer initialOutputQuad(viewPorts[i]);
            projectionMapping.addQuadMapping(i, viewPorts[i], initialOutputQuad);
        }
    }
}

//--------------------------------------------------------------
void testApp::update(){
    if(kinect.isUserTracked()){
        for(size_t i=0;i<cameras.size();++i){
            cameras.at(i).setUserPosition(kinect.getJointWorldPosition("head"));
        }
    }
    drawCamSceneRenderFbos();
}

//--------------------------------------------------------------
void testApp::drawCamSceneRenderFbos(){
    for(size_t i=0;i<cameras.size();++i){
        cameraRenders.at(i).begin();
            ofClear(0, 0, 0, 0);
            cameras.at(i).begin();
                drawWalls();
        someImage.bind();
        ofFill();
                ofBox(0, 0, -50, 100);
        someImage.unbind();
//        someImage.bind();
//        ofFill();
//        ofBox(0, 0, -50, 100);
//        someImage.unbind();
//        someImage.bind();
//        ofFill();
//        ofBox(-1000, 0, -50, 500);
//        someImage.unbind();
//        someImage.bind();
//        ofFill();
//                ofBox(1000, 0, -100, 400);
//        someImage.unbind();
//        someImage.bind();
//        ofFill();
//                ofBox(-600, -500, -50, 300);
//        someImage.unbind();
//        someImage.bind();
//        ofFill();
//                ofBox(800, 800, -200, 400);
//        someImage.unbind();        
            cameras.at(i).end();
        cameraRenders.at(i).end();
    }
}

//--------------------------------------------------------------
void testApp::draw(){
//    for(size_t i=0;i<cameras.size();++i){
        #ifdef ENABLE_PROJECTION_MAPPING
            projectionMapping.draw();
//            ofxQuad* test = projectionMapping.mappedQuadToInputIndex(0);
            projectionMapping.mappedQuadToInputIndex(0)->beginDraw();
                cameraRenders.at(0).draw(viewPorts[0].x, viewPorts[0].y, viewPorts[0].width, viewPorts[0].height);
            projectionMapping.mappedQuadToInputIndex(0)->endDraw();
    
    
            projectionMapping.mappedQuadToInputIndex(1);
            projectionMapping.mappedQuadToInputIndex(1)->beginDraw();
                cameraRenders.at(1).draw(viewPorts[1].x, viewPorts[1].y, viewPorts[1].width, viewPorts[1].height);
            projectionMapping.mappedQuadToInputIndex(1)->endDraw();

            ofxQuad* test = projectionMapping.mappedQuadToInputIndex(2);
            projectionMapping.mappedQuadToInputIndex(2)->beginDraw();
                cameraRenders.at(2).draw(viewPorts[2].x, viewPorts[2].y, viewPorts[2].width, viewPorts[2].height);
            projectionMapping.mappedQuadToInputIndex(2)->endDraw();
        #endif
                /*****Draw here*****/
    
//        for(size_t i=0;i<cameras.size();++i){
//                cameraRenders.at(i).draw(viewPorts[i].x, viewPorts[i].y, viewPorts[i].width, viewPorts[i].height);
//        }
    
    
    
//            cameras.at(i).begin(viewPorts[i]);
//                drawWalls();
//            cameras.at(i).end();

                /*******************/
//        #ifdef ENABLE_PROJECTION_MAPPING
//            projectionMapping.mappedQuadToInputIndex(i)->endDraw();
//        #endif
//    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    switch (key){
        case 'e':
            #ifdef ENABLE_PROJECTION_MAPPING
                enableMappingMarkers = !enableMappingMarkers;
                projectionMapping.setMarkers(enableMappingMarkers);
            #endif
            break;
        case 'a':
            xPos-=500;
            cameras.at(0).setUserPosition(ofVec3f(xPos, yPos, zPos));
            cameras.at(1).setUserPosition(ofVec3f(xPos, yPos, zPos));
            cameras.at(2).setUserPosition(ofVec3f(xPos, yPos, zPos));
            break;
        case 'd':
            xPos+=500;
            cameras.at(0).setUserPosition(ofVec3f(xPos, yPos, zPos));
            cameras.at(1).setUserPosition(ofVec3f(xPos, yPos, zPos));
            cameras.at(2).setUserPosition(ofVec3f(xPos, yPos, zPos));
            break;
        case 'w':
            yPos +=500;
            cameras.at(0).setUserPosition(ofVec3f(xPos, yPos, zPos));
            cameras.at(1).setUserPosition(ofVec3f(xPos, yPos, zPos));
            cameras.at(2).setUserPosition(ofVec3f(xPos, yPos, zPos));
            break;
        case 's':
            yPos -=500;
            cameras.at(0).setUserPosition(ofVec3f(xPos, yPos, zPos));
            cameras.at(1).setUserPosition(ofVec3f(xPos, yPos, zPos));
            cameras.at(2).setUserPosition(ofVec3f(xPos, yPos, zPos));
            break;
        case OF_KEY_UP:
            zPos += 50;
            cameras.at(0).setUserPosition(ofVec3f(xPos, yPos, zPos));
            cameras.at(1).setUserPosition(ofVec3f(xPos, yPos, zPos));
            cameras.at(2).setUserPosition(ofVec3f(xPos, yPos, zPos));
            break;
        case OF_KEY_DOWN:
            zPos -=50;
            cameras.at(0).setUserPosition(ofVec3f(xPos, yPos, zPos));
            cameras.at(1).setUserPosition(ofVec3f(xPos, yPos, zPos));
            cameras.at(2).setUserPosition(ofVec3f(xPos, yPos, zPos));
            break;
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------
void testApp::exit(){
}

void drawWalls(){
    ofPushStyle();
    //Left wall
    ofSetColor(213, 207, 207);
    glBegin(GL_QUADS);
    glVertex3f(1890, 1010, 0);
    glVertex3f(1890, 1010, -200);
    glVertex3f(1890, -1450, -200);
    glVertex3f(1890, -1450, 0);
    glEnd();
    
    //Right wall
    glBegin(GL_QUADS);
    glVertex3f(-2255, 1010, 0);
    glVertex3f(-2255, 1010, -200);
    glVertex3f(-2255, -1450, -200);
    glVertex3f(-2255, -1450, 0);
    glEnd();
    ofPopStyle();
    
    ofPushStyle();
    ofSetColor(137, 129, 129);
    //Top wall
    glBegin(GL_QUADS);
    glVertex3f(1890, 1010, 0);
    glVertex3f(-2255, 1010, 0);
    glVertex3f(-2255, 1010, -200);
    glVertex3f(1890, 1010, -200);
    glEnd();
    
    glBegin(GL_QUADS);
    glVertex3f(1890, -1450, 0);
    glVertex3f(-2255, -1450, 0);
    glVertex3f(-2255, -1450, -200);
    glVertex3f(1890, -1450, -200);
    glEnd();
    ofPopStyle();
}