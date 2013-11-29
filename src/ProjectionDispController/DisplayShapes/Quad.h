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


#ifndef HolographicAR_Quad_h
#define HolographicAR_Quad_h

#include "DisplayScreen.h"

class QuadScreen : public DisplayScreen{
public:
    QuadScreen(){
        DisplayScreen::shape = QUAD;
    }
    
    virtual ofVec3f getTopLeft()const{
        return _topLeft;
    }
    virtual ofVec3f getTopRight()const{
        return _topRight;
    }
    virtual ofVec3f getBottomLeft()const{
        return _bottomLeft;
    }
    virtual ofVec3f getBottomRight()const{
        return _bottomRight;
    }
    
protected:
    ofVec3f _topLeft, _topRight, _bottomLeft, _bottomRight;
};

class QuadDisplayScreen : public QuadScreen{
public:
    QuadDisplayScreen(ofVec3f topLeft, ofVec3f topRight, ofVec3f bottomLeft, ofVec3f bottomRight)
    {
        QuadScreen::_topLeft = topLeft; QuadScreen::_topRight = topRight;
        QuadScreen::_bottomLeft = bottomLeft; QuadScreen::_bottomRight = bottomRight;
    }
    
    vector<ofVec3f> screenCorners(){
        vector<ofVec3f> screenCorners;
        screenCorners.push_back(_topLeft);
        screenCorners.push_back(_topRight);
        screenCorners.push_back(_bottomLeft);
        screenCorners.push_back(_bottomRight);
        return screenCorners;
    }
};

// Quad Screen inheritance sample
//class RectangularQuadScreen : public QuadScreen{
//    public:
//    RectangularQuadScreen(ofVec3f topLeft, ofVec3f topRight, ofVec3f bottomLeft, ofVec3f bottomRight)
//    {
//        QuadScreen::_topLeft = topLeft; QuadScreen::_topRight = topRight;
//        QuadScreen::_bottomLeft = bottomLeft; QuadScreen::_bottomRight = bottomRight;
//    }
//    private:
//};

#endif
