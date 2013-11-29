/*
 * DraggingAdorners.h
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

#ifndef HolographicAR_DraggingAdorners_h
#define HolographicAR_DraggingAdorners_h

#include "ofxDraggable.h"
#define DRAGGING_ADORNER_WIDTH 20
#define DRAGGING_ADORNER_HEIGHT 20

class DraggingAdorner  : public ofxDraggable {
    public:
        DraggingAdorner(float x, float y, float width = DRAGGING_ADORNER_WIDTH, float height = DRAGGING_ADORNER_HEIGHT) : _x(x), _y(y), _width(width), _height(height)
        {
            ofxMSAInteractiveObject::x = _x;
            ofxMSAInteractiveObject::y = _y;
            init(width, height);
            _enabled = true; //adorners drawing enabled
        }
    
        DraggingAdorner(ofPoint point, float width = DRAGGING_ADORNER_WIDTH, float height = DRAGGING_ADORNER_HEIGHT){
            ofxMSAInteractiveObject::x = point.x;
            ofxMSAInteractiveObject::y = point.y;
            init(width, height);
        }
    
        void setPosition(float x, float y){
            ofxMSAInteractiveObject::x = _x = x;
            ofxMSAInteractiveObject::y = _y = y;
        }
    
        void enableAdorner(bool enable){
            if(enable == _enabled) return; //to not enable events if already enabled
            _enabled = enable;
            if(_enabled){
                ofxMSAInteractiveObject::enableMouseEvents();
            }else{
                ofxMSAInteractiveObject::disableMouseEvents();
            }
        }
    
        void draw(){
            if(_enabled){
                ofRect(ofxMSAInteractiveObject::x, ofxMSAInteractiveObject::y, _width, _height);
                if (ofxMSAInteractiveObject::isMousePressed()) {
                    ofPushStyle();
                    ofNoFill();
                    ofSetColor(DRAG_BORDER_HEX);
                    ofSetColor(ofColor::red);
                    ofRect(x, y, width, height);
                    ofPopStyle();
                } else if (ofxMSAInteractiveObject::isMouseOver()){
                    ofPushStyle();
                    ofNoFill();
                    ofSetColor(OVER_BORDER_HEX);
                    ofSetColor(ofColor::red);
                    ofRect(x, y, width, height);
                    ofPopStyle();
                }
            }
        }
    private:
        float _x, _y, _width, _height, _enabled;
        void init(float width, float height)
        {
            ofxMSAInteractiveObject::width = width;
            ofxMSAInteractiveObject::height = height;
        }
};

#endif
