/*
 * TrackerScreenFoRCalibration.h
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


//TODO Class - Calibration of the screen coordinates automatically with user movement

#ifndef __HolographicAR__TrackerScreenFoRCalibration__
#define __HolographicAR__TrackerScreenFoRCalibration__

#include <iostream>
#include "ofMain.h"

#define TOLERABLE_ERROR 0.5

//FOR - Frame of Reference
enum ScreenCorners {
    TOP_LEFT,
    TOP_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_RIGHT
};

class TrackerScreenFORCalibration{
    public:
        TrackerScreenFORCalibration();
        ~TrackerScreenFORCalibration();
        void start();
        void current();
        void stop();
    
        //Getters
        bool isTopLeftCaptured()const;
        bool isTopRightCaptured()const;
        bool isBottomLeftCaptured()const;
        bool isBottomRightCaptured()const;
    
        //Fire events when screen coordinates are captured and send the information about which type of corners were tracked
        static ofEvent<ScreenCorners> screenVertexTracked;
        static ofEvent<bool> calibrationCompleted;
    
        //Asyncronously send progress via threads when each vertex is tracked
    private:
        void update(ofEventArgs&);
        void enableEvents();
        void disableEvents();
    
        //Sides captured in Tracker-Screen Frame of Reference
        bool _topLeftLocked, _topRightLocked, _bottomLeftLocked, _bottomRightLocked;
    
        //Quad sides
        ofPoint _topLeft, _topRight, _bottomLeft, _bottomRight;
};

#endif /* defined(__HolographicAR__TrackerScreenFoRCalibration__) */
