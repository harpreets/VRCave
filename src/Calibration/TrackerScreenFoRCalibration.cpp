/*
 * TrackerScreenFoRCalibration.cpp
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


#include "TrackerScreenFoRCalibration.h"

TrackerScreenFORCalibration::TrackerScreenFORCalibration(){
    
    this->_topLeftLocked = false; this->_topRightLocked = false;
    this->_bottomLeftLocked = false; this->_bottomRightLocked = false;
    
    this->_topLeft = ofPoint(0, 0);
    this->_topRight = ofPoint(ofGetWidth(), 0);
    this->_bottomLeft = ofPoint(0, ofGetHeight());
    this->_bottomRight = ofPoint(ofGetWidth(), ofGetHeight());
    
    enableEvents();
}

TrackerScreenFORCalibration::~TrackerScreenFORCalibration(){
    disableEvents();
}

void TrackerScreenFORCalibration::enableEvents(){
    ofAddListener(ofEvents().update, this, &TrackerScreenFORCalibration::update);
}

void TrackerScreenFORCalibration::disableEvents(){
    ofRemoveListener(ofEvents().update, this, &TrackerScreenFORCalibration::update);
}

void TrackerScreenFORCalibration::start(){
    
}

void TrackerScreenFORCalibration::stop(){
    
}

bool TrackerScreenFORCalibration::isBottomLeftCaptured()const{
    return _bottomLeftLocked;
}

bool TrackerScreenFORCalibration::isBottomRightCaptured()const{
    return _bottomRightLocked;
}

bool TrackerScreenFORCalibration::isTopLeftCaptured()const{
    return _topLeftLocked;
}

bool TrackerScreenFORCalibration::isTopRightCaptured()const{
    return _topRightLocked;
}