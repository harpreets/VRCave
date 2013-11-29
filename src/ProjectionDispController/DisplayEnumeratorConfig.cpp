/*
 * DisplayEnumeratorConfig.cpp
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

#include "DisplayEnumeratorConfig.h"

DisplayEnumerator::DisplayEnumerator(string configFileName){
    if(_displaySettingsConfig.loadFile(configFileName)){
        _dispTypeMap = initMap();
        readDisplayPositions();
    }else{
        cout<<"Unable to load the config file."<<"\n";
    }
}

DisplayEnumerator::~DisplayEnumerator(){
    for(int i=0;i<_displayScreens.size();++i){
        delete _displayScreens[i];
    }
}

vector<DisplayScreen*> DisplayEnumerator::outputDisplays()const{
    return _displayScreens;
}

//Private Methods
void DisplayEnumerator::readDisplayPositions(){
    _displaySettingsConfig.pushTag("DisplayScreens");
        int numDisplays = _displaySettingsConfig.getNumTags("Screen");
        for(int i=0;i<numDisplays;++i){
            DISP_SHAPE dispType = _dispTypeMap[_displaySettingsConfig.getAttribute("Screen", "type", "quad", i)];
            _displaySettingsConfig.pushTag("Screen", i);
            _displaySettingsConfig.pushTag("Corners");
            switch (dispType) {
                case QUAD:
                {
                    vector<string> parsedCorner;
                    ofVec3f topLeft, topRight, bottomLeft, bottomRight;
                    
                    parsedCorner = ofSplitString(_displaySettingsConfig.getValue("TopLeft", "BAD_FORMED_STRING"), ",");
                    topLeft.x = atof(parsedCorner.at(0).c_str()); topLeft.y = atof(parsedCorner.at(1).c_str()); topLeft.z = atof(parsedCorner.at(2).c_str());
                    
                    parsedCorner.clear();
                    parsedCorner = ofSplitString(_displaySettingsConfig.getValue("TopRight", "BAD_FORMED_STRING"), ",");
                    topRight.x = atof(parsedCorner.at(0).c_str()); topRight.y = atof(parsedCorner.at(1).c_str()); topRight.z = atof(parsedCorner.at(2).c_str());
                    
                    parsedCorner.clear();
                    parsedCorner= ofSplitString(_displaySettingsConfig.getValue("BottomLeft", "BAD_FORMED_STRING"), ",");
                    bottomLeft.x = atof(parsedCorner.at(0).c_str()); bottomLeft.y = atof(parsedCorner.at(1).c_str()); bottomLeft.z = atof(parsedCorner.at(2).c_str());
                    
                    parsedCorner.clear();
                    parsedCorner = ofSplitString(_displaySettingsConfig.getValue("BottomRight", "BAD_FORMED_STRING"), ",");
                    bottomRight.x = atof(parsedCorner.at(0).c_str()); bottomRight.y = atof(parsedCorner.at(1).c_str()); bottomRight.z = atof(parsedCorner.at(2).c_str());
                    
                    _displayScreens.push_back(new QuadDisplayScreen(topLeft, topRight, bottomLeft,bottomRight));
                    cout<<"-- New quad screen initialised --"<<"\n"
                        <<"Top Left: "<<ofToString(topLeft)<<" Top Right: "<<ofToString(topRight)<<"\n"
                        <<"Bottom Left: "<<ofToString(bottomLeft)<<" Bottom Right: "<<ofToString(bottomRight)<<"\n";
                }
                    break;
                case HEX:
                    break;
                default:
                    break;
            }
            _displaySettingsConfig.popTag();
            _displaySettingsConfig.popTag();
        }
    _displaySettingsConfig.popTag();
}

map<string, DISP_SHAPE> DisplayEnumerator::initMap(){
    map<string, DISP_SHAPE> dispShapeTypeMap;
    dispShapeTypeMap["quad"] = QUAD;
    dispShapeTypeMap["pentagon"] = PENTAGON;
    dispShapeTypeMap["hexagon"] = HEX;
    return dispShapeTypeMap;
}