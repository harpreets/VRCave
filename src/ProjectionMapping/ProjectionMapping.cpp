/*
 * ProjectionMapping.cpp
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

#include "ProjectionMapping.h"

ProjectionMapping::ProjectionMapping(bool enableAdorners){
    setMarkers(enableAdorners);
//    currentIndex = -1;
    initAdornerCornerTypeMap();
//    enableEvents();
}

ProjectionMapping::~ProjectionMapping(){
    disbaleEvents();
    for(size_t i=0;i<_inputIndexOutputMappedQuadCollection.size();++i){
        delete _inputIndexOutputMappedQuadCollection.at(i);
    }
    for(size_t i=0;i<_pMappingAdorners.size();++i){
        ofRemoveListener(_pMappingAdorners.at(i)->objectDragged, this, &ProjectionMapping::adornerDragged);
        delete _pMappingAdorners.at(i);
    }
}

void ProjectionMapping::enableEvents(){
//    ofAddListener(ofEvents().draw, this, &ProjectionMapping::draw);
}

void ProjectionMapping::disbaleEvents(){
//    ofRemoveListener(ofEvents().draw, this, &ProjectionMapping::draw);
}

void ProjectionMapping::setMarkers(bool enable){
    if(enable == _adornersEnabled) return;
    _adornersEnabled = enable;
    
    for(size_t i=0;i<_pMappingAdorners.size();++i){
        _pMappingAdorners.at(i)->enableAdorner(_adornersEnabled);
    }
}

void ProjectionMapping::draw(){
    if(_adornersEnabled){
        for(size_t i=0;i<_pMappingAdorners.size();++i){
            _pMappingAdorners.at(i)->draw();
        }
    }
}

void ProjectionMapping::addQuadMapping(int inputIndex, ofRectangle inputRectangle, QuadContainer mappedOutputQuad){
    ofxQuad* quad = new ofxQuad();
    
    size_t someIndex = 0;
    setCorrepondingPointsMapping(someIndex, quad, inputRectangle.getTopLeft(), mappedOutputQuad.getTopLeft(), "topLeft"); ++someIndex;
    setCorrepondingPointsMapping(someIndex, quad, inputRectangle.getTopRight(), mappedOutputQuad.getTopRight(), "topRight"); ++someIndex;
    setCorrepondingPointsMapping(someIndex, quad, inputRectangle.getBottomRight(), mappedOutputQuad.getBottomRight(), "bottomRight"); ++someIndex;
    setCorrepondingPointsMapping(someIndex, quad, inputRectangle.getBottomLeft(), mappedOutputQuad.getBottomLeft(), "bottomLeft"); ++someIndex;

    _inputIndexOutputMappedQuadCollection[inputIndex] = quad;
}

ofxQuad* ProjectionMapping::mappedQuadToInputIndex(int inputIndex){
    ofxQuad* test = _inputIndexOutputMappedQuadCollection[inputIndex];
    return _inputIndexOutputMappedQuadCollection[inputIndex];
}

void ProjectionMapping::setCorrepondingPointsMapping(size_t& currentIndex, ofxQuad* quad, ofPoint inputPoint, ofPoint outputPoint, string outputCorner){
    quad->setInputPoint(currentIndex, inputPoint.x, inputPoint.y);
    quad->setOutputPoint(currentIndex, outputPoint.x, outputPoint.y);
    setOutputAdorner(currentIndex, outputPoint, outputCorner, quad);
}

void ProjectionMapping::setOutputAdorner(size_t currentIndex, ofPoint& ouputPoint, string outputCorner, ofxQuad* correspondingQuad){
    if(!_adornersEnabled) return;
    //cout<<"Key: "<<outputCorner<<" : "<<_adornerCornerTypeMap[outputCorner]<<"\n";
    PMappingAdorner *dragAdorner = new PMappingAdorner(correspondingQuad, currentIndex, ouputPoint, _adornerCornerTypeMap[outputCorner]);
    _pMappingAdorners.push_back(dragAdorner);
    ofAddListener(dragAdorner->objectDragged, this, &ProjectionMapping::adornerDragged);
}

void ProjectionMapping::adornerDragged(const void* sender, DragEventArgs& e){
    PMappingAdorner* currentAdorner = static_cast<PMappingAdorner*>(const_cast<void*>(sender));
    ofxQuad* correspondingQuad =  currentAdorner->parentQuad;
    correspondingQuad->setOutputPoint(currentAdorner->index, e.draggedToPosition.x, e.draggedToPosition.y);
}

void ProjectionMapping::initAdornerCornerTypeMap(){
    _adornerCornerTypeMap["topLeft"] = TOP_LEFT;
    _adornerCornerTypeMap["topRight"] = TOP_RIGHT;
    _adornerCornerTypeMap["bottomLeft"] = BOTTOM_LEFT;
    _adornerCornerTypeMap["bottomRight"] = BOTTOM_RIGHT;
}


//Non-const lValue reference to Type 'ofPoint' cannot bind to a temporary of type ofPoint





