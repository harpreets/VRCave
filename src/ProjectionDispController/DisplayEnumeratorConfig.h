/*
 * DisplayEnumeratorConfig.h
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

#ifndef __HolographicAR__DisplayEnumeratorConfig__
#define __HolographicAR__DisplayEnumeratorConfig__

#include "ofMain.h"
#include "DisplayScreen.h"
#include "Quad.h"
#include "ofxXmlSettings.h"

class DisplayEnumerator{
    public:
        DisplayEnumerator(string configFileName);
        virtual ~DisplayEnumerator();
        vector<DisplayScreen*> outputDisplays()const;
    private:
        ofxXmlSettings _displaySettingsConfig;
        map<string, DISP_SHAPE> _dispTypeMap;
        vector<DisplayScreen*> _displayScreens;
    
        map<string, DISP_SHAPE> initMap();
        void readDisplayPositions();
};

#endif /* defined(__HolographicAR__DisplayEnumeratorConfig__) */
