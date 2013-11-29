/*
 * Hex.h
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


#ifndef HolographicAR_Hex_h
#define HolographicAR_Hex_h

#include "DisplayScreen.h"

class HexScreen : public DisplayScreen{
public:
    HexScreen(){
        DisplayScreen::shape = HEX;
    }
protected:
    ofVec3f _corner1, _corner2, _corner3, _corner4, _corner5, _corner6;
};

class HexDisplayScreen : public HexScreen{
public:
    HexDisplayScreen(ofVec3f corner1, ofVec3f corner2, ofVec3f corner3, ofVec3f corner4, ofVec3f corner5, ofVec3f corner6)
    {
        HexScreen::_corner1 = corner1; HexScreen::_corner2 = corner2;
        HexScreen::_corner3 = corner3; HexScreen::_corner4 = corner4;
        HexScreen::_corner5 = corner5; HexScreen::_corner6 = corner6;
    }
    
    vector<ofVec3f> screenCorners(){
        vector<ofVec3f> screenCorners;
        screenCorners.push_back(_corner1);
        screenCorners.push_back(_corner2);
        screenCorners.push_back(_corner3);
        screenCorners.push_back(_corner4);
        screenCorners.push_back(_corner5);
        return screenCorners;
    }
};


#endif
