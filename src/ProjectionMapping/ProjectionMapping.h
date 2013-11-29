/*
 * ProjectionMapping.h
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


#ifndef __HolographicAR__ProjectionMapping__
#define __HolographicAR__ProjectionMapping__

#include "ofMain.h"
#include "ofxQuad.h"
#include "PMappingAdorner.h"
#include "GeometricalContainer.h"

//TODO : Make method prototypes pass variables by reference to prevent large mem copying

class ProjectionMapping{
    public:
        ProjectionMapping(bool enableAdorners = true);
        virtual ~ProjectionMapping();
        void setMarkers(bool enable);
        void addQuadMapping(int inputQuadIndex, ofRectangle inputRectangle, QuadContainer mappedQuad);
    
        ofxQuad* mappedQuadToInputIndex(int inputIndex);
    
        void draw();
    
        void saveMappedPoints(string mappedPointsXml);
    private:
    
        bool _adornersEnabled;
    
        map<int, ofxQuad*> _inputIndexOutputMappedQuadCollection;
        vector<PMappingAdorner*> _pMappingAdorners;
        map<string, ADORNER_QUAD_CORNER> _adornerCornerTypeMap;
    
        void enableEvents();
        void disbaleEvents();
        void adornerDragged(const void* sender, DragEventArgs& e);
        void initProjectionMapping();
        void initAdornerCornerTypeMap();
        void setCorrepondingPointsMapping(size_t& currentIndex, ofxQuad* quad, ofPoint inputPoint, ofPoint outputPoint, string outputCorner);
        void setOutputAdorner(size_t currentIndex, ofPoint& ouputPoint, string outputCorner, ofxQuad* correspondingQuad);

};

#endif /* defined(__HolographicAR__ProjectionMapping__) */
