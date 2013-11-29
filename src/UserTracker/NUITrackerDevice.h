/*
 * NUITrackerDevice.h
 *
 * Copyright 2013 (c) Harpreet Sareen [harpreets] http://github.com/harpreets
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */


//Deployment and Source Dependency : OpenNI/NITE installation on OS

#ifndef __HolographicAR__NUITrackerDevice__
#define __HolographicAR__NUITrackerDevice__

#include <iostream>
#include "ofxOpenNI.h"
#include "ofMain.h"

#define MAX_DEVICES 2
#define MAX_SKELETON_USERS 1
#define TRACK_USER_NUM 0
#define MAX_TRACKED_USERS 4

#define DEBUG_WIDTH 250
#define DEBUG_HEIGHT 300

typedef map<string, Joint> JointsMap;
typedef map<int, string> ErrorMap;

class KinectTrackerDevice {
public:
    KinectTrackerDevice(bool generateImages = true, bool generateDepth = true, bool generateUser = true, bool mirrorFlag = true, bool registerFlag = true, bool verbose = false);
    ~KinectTrackerDevice();
    void update(ofEventArgs&);
    void draw(ofEventArgs&);
    void exit(ofEventArgs&);
        
    //Setter methods
    void setDeviceAngle(int motorPivotAngle);
    void setMaxTrackUsers(int maxNumUsers = MAX_SKELETON_USERS);
    void setImageGenerator(bool);
    void setUserGenerator(bool);
    void setDepthGenerator(bool);
    void setRegister(bool);
    void setMirror(bool);
    //Debug methods
    void drawDebugDepth(bool);
    void drawDebugImage(bool);
    void drawDebugSkeleton(bool);

    //Getter methods
    ofVec3f getJointWorldPosition(string jointName)const;
    ofVec3f getJointScreenPosition(string jointName)const;
    bool isUserTracked()const;
    bool isImageGeneratorRunning()const;
    bool isDepthGeneratorRunning()const;
    bool isUserGeneratorRunning()const;
    bool isMirroredOutput()const;
    bool isRegisterOutput()const;
    bool isDeviceRunning()const;
private:
    //Kinect device flags
    bool _imageGeneratorFlag, _depthGeneratorFlag, _userGeneratorFlag, _mirrorFlag, _registerFlag, _verbose;
    bool _isUserTracked, _isDeviceRunning;
    bool _drawDepth, _drawSkeleton, _drawImage;
    int _numUserBeingTracked;
    
    ofxOpenNI _openNIDevice;
    ofxOpenNIUser* _trackedUser;
    ofxOpenNIJoint _trackedJoint;
    
    static ErrorMap _errorMap;
    static JointsMap _userJointPositionsMap;
    
    static ErrorMap initErrorCodesMap();
    static JointsMap initUserJointsMap();
    
    void setupDevice();
    void enableEvents();
    void disableEvents();
};

#endif /* defined(__HolographicAR__NUITrackerDevice__) */
