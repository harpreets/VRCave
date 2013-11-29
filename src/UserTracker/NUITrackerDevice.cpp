//
//  NUITrackerDevice.cpp
//  HolographicAR
//
//  Created by Harpreet Sareen on 26/04/13.
//
//

#include "NUITrackerDevice.h"

//Build a map of String-Joints key value pairs
JointsMap KinectTrackerDevice::_userJointPositionsMap = initUserJointsMap();
//Build a map of ErrorCodes-String key value pairs
ErrorMap KinectTrackerDevice::_errorMap = initErrorCodesMap();

//Initialize the device
KinectTrackerDevice::KinectTrackerDevice(bool generateImages, bool generateDepth, bool generateUser, bool mirrorFlag, bool registerFlag, bool verbose)
{
    enableEvents();
    
    this->_verbose = verbose;
    this->_isUserTracked = false;
    drawDebugImage(false); drawDebugSkeleton(false); drawDebugDepth(false);
    
    _openNIDevice.setup();
        setDepthGenerator(generateDepth);
        setImageGenerator(generateImages);
        setUserGenerator(generateUser);
        setMirror(mirrorFlag);
        setRegister(registerFlag);
        setMaxTrackUsers(MAX_SKELETON_USERS);
    _openNIDevice.start();
    _openNIDevice.setUserSmoothing(0.1f);
}

void KinectTrackerDevice::enableEvents()
{
    ofAddListener(ofEvents().update, this, &KinectTrackerDevice::update);
    ofAddListener(ofEvents().draw, this, &KinectTrackerDevice::draw);
    ofAddListener(ofEvents().exit, this, &KinectTrackerDevice::exit);
}

void KinectTrackerDevice::disableEvents()
{
    ofRemoveListener(ofEvents().update, this, &KinectTrackerDevice::update);
    ofRemoveListener(ofEvents().draw, this, &KinectTrackerDevice::draw);
    ofRemoveListener(ofEvents().exit, this, &KinectTrackerDevice::exit);
}

KinectTrackerDevice::~KinectTrackerDevice(){
}

void KinectTrackerDevice::update(ofEventArgs& e)
{
    _openNIDevice.update();
    this->_numUserBeingTracked = _openNIDevice.getNumTrackedUsers();
    if(_numUserBeingTracked >=1 ){
        this->_isUserTracked = true;
        this->_trackedUser = &_openNIDevice.getTrackedUser(TRACK_USER_NUM);
    }else{
        if(_isUserTracked){
        this->_isUserTracked = false;
        }
    }
}

//Draw the skeleton, user mask or point cloud for the user
//Useful for drawing the skeleton to know that the user has been recognized and polyline skeleton confidence
//For eg: Drawing the skeleton will show which polyline joints is the device confident about and which ones are being predicted
void KinectTrackerDevice::draw(ofEventArgs& e)
{
    #ifdef DEBUG
    //Calculate how many draw bools are turned on and draw the debug regions accordingly
    if(_numUserBeingTracked >= MAX_SKELETON_USERS){
        if(_drawSkeleton){_openNIDevice.drawSkeletons(ofGetWidth() - DEBUG_WIDTH, ofGetHeight()- DEBUG_HEIGHT, DEBUG_WIDTH, DEBUG_HEIGHT);}
        if(_drawDepth) {_openNIDevice.drawDepth(ofGetWidth() - (2 * DEBUG_WIDTH), ofGetHeight() - DEBUG_HEIGHT, DEBUG_WIDTH, DEBUG_HEIGHT);}
        if(_drawImage) {_openNIDevice.drawImage(ofGetWidth() - (3 * DEBUG_WIDTH), ofGetHeight() - DEBUG_HEIGHT, DEBUG_WIDTH, DEBUG_HEIGHT);}
    }
    #endif
}

void KinectTrackerDevice::exit(ofEventArgs& e)
{
    disableEvents();
    _openNIDevice.stop();
    #ifdef DEBUG
        cout<<"Kinect Tracker Device - Exit called"<<"\n";
    #endif
}


bool KinectTrackerDevice::isUserTracked()const
{
    return _isUserTracked;
}

bool KinectTrackerDevice::isDeviceRunning()const
{
    return _isDeviceRunning;
}

ofVec3f KinectTrackerDevice::getJointWorldPosition(string jointName)const
{
    //check here is device has not started already
    if(_isUserTracked && _trackedUser!=NULL){
        return (_trackedUser->getJoint(_userJointPositionsMap[jointName]).getWorldPosition());
    }
}

ofVec3f KinectTrackerDevice::getJointScreenPosition(string jointName)const
{
    //check here is device has not started already
    if(_isUserTracked && _trackedUser!=NULL){
        return (_trackedUser->getJoint(_userJointPositionsMap[jointName]).getProjectivePosition());
    }    
}

void KinectTrackerDevice::drawDebugDepth(bool drawDepth){
    this->_drawDepth = drawDepth;
}

void KinectTrackerDevice::drawDebugImage(bool drawImage){
    this->_drawImage = drawImage;
}

void KinectTrackerDevice::drawDebugSkeleton(bool drawSkeleton){
    this->_drawSkeleton = drawSkeleton;
}

void KinectTrackerDevice::setMirror(bool mirrorFlag)
{
    //check here if device has not started already
    this->_mirrorFlag = mirrorFlag;
    if(mirrorFlag) {
        _openNIDevice.setMirror(mirrorFlag);
    }
    #ifdef DEBUG
        cout<<"Kinect Tracker Device Mirror set to " + ofToString(mirrorFlag)<<"\n";
    #endif
}

void KinectTrackerDevice::setRegister(bool registerFlag)
{
    //check here is device has not started already
    this->_registerFlag = registerFlag;
    if (registerFlag) {
        _openNIDevice.setRegister(registerFlag);
    }
    #ifdef DEBUG
        cout<<"Kinect Tracker Device Register set to " + ofToString(registerFlag)<<"\n";
    #endif
}

void KinectTrackerDevice::setImageGenerator(bool imageGenerator)
{
    //check here if device has not started already
    this->_imageGeneratorFlag = imageGenerator;
    if(imageGenerator) {
        _openNIDevice.addImageGenerator();
    }else{
        _openNIDevice.removeImageGenerator();
    }
    #ifdef DEBUG
        cout<<"Kinect Tracker Device Image Generator set to " + ofToString(imageGenerator)<<"\n";
    #endif
}

void KinectTrackerDevice::setDepthGenerator(bool depthGenerator)
{
    //check here if device has not started already
    this->_depthGeneratorFlag = depthGenerator;
    if(depthGenerator) {
        _openNIDevice.addDepthGenerator();
    }else{
        _openNIDevice.removeDepthGenerator();
    }
    #ifdef DEBUG
        cout<<"Kinect Tracker Device Depth Generator set to " + ofToString(depthGenerator)<<"\n";
    #endif
}

void KinectTrackerDevice::setUserGenerator(bool userGenerator)
{
    //check here if device has not started already
    this->_userGeneratorFlag = userGenerator;
    if(userGenerator) {
        _openNIDevice.addUserGenerator();
    }else{
        _openNIDevice.removeUserGenerator();
    }
    #ifdef DEBUG
        cout<<"Kinect Tracker Device User Generator set to " + ofToString(userGenerator)<<"\n";
    #endif
}

void KinectTrackerDevice::setMaxTrackUsers(int maxNumUsers){
    //check here if device has not started already
    _openNIDevice.setMaxNumUsers(((maxNumUsers >= MAX_TRACKED_USERS) ? MAX_TRACKED_USERS : maxNumUsers));
    cout<<"Maximum users to be tracked set as: "<<maxNumUsers<<"\n";
}

void KinectTrackerDevice::setDeviceAngle(int motorPivotAngle)
{
    //check here if device has not started already
    return 0;
}

//Boost.Assign make_list_of avoided to check the user of Boost for the library
//C++0x in XCode not used since Apple LVVM 4.2 compiler doesn't have the same by default
map<string, Joint> KinectTrackerDevice::initUserJointsMap(){
    map<string, Joint> userJointMap;
    //start at root joint
    userJointMap["torso"] = JOINT_TORSO;
    userJointMap["neck"] = JOINT_NECK;
    userJointMap["head"] = JOINT_HEAD;
    // left arm + shoulder
    userJointMap["leftShoulder"] = JOINT_LEFT_SHOULDER;
    userJointMap["leftElbow"] = JOINT_LEFT_ELBOW;
    userJointMap["leftHand"] = JOINT_LEFT_HAND;
    // right arm + shoulder
    userJointMap["rightShoulder"] = JOINT_RIGHT_SHOULDER;
    userJointMap["rightElbow"] = JOINT_RIGHT_ELBOW;
    userJointMap["rightHand"] = JOINT_RIGHT_HAND;
    //left leg
    userJointMap["leftHip"] = JOINT_LEFT_HIP;
    userJointMap["leftKnee"] = JOINT_LEFT_KNEE;
    userJointMap["leftFoot"] = JOINT_LEFT_FOOT;
    //right leg
    userJointMap["rightHip"] = JOINT_RIGHT_HIP;
    userJointMap["rightKnee"] = JOINT_RIGHT_KNEE;
    userJointMap["rightFoot"] = JOINT_RIGHT_FOOT;
    
    #ifdef DEBUG
        cout<<"Set up the String-Joint map for the Kinect Tracker Device\n";
    #endif
    return userJointMap;
}

//Boost.Assign make_list_of avoided to check the user of Boost for the library
//C++0x in XCode not used since Apple LVVM 4.2 compiler doesn't have the same by default
map<int, std::string> KinectTrackerDevice::initErrorCodesMap(){
    map<int, string> errorMap;
    errorMap[100] = "Error: Device not initialized.\n";
    errorMap[101] = "Error: Unable to initialize the device.\n";
    errorMap[103] = "Error: Lost the tracking device.\n";
    errorMap[202] = "Error: Bad Access. Trying to access without initializing device\n";
    errorMap[500] = "Fatal Error: Unknown error occured.\n";
    
    return errorMap;
}