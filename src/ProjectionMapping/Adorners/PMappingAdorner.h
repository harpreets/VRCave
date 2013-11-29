/*
 * PMappingAdorner.h
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

#ifndef HolographicAR_PMappingAdorner_h
#define HolographicAR_PMappingAdorner_h

#include "DraggingAdorners.h"

enum ADORNER_QUAD_CORNER {TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT };

class QuadAdorner{
    public:
        ofxQuad* parentQuad;
        ADORNER_QUAD_CORNER corner;
};

class PMappingAdorner : public DraggingAdorner, public QuadAdorner{
    public:
        PMappingAdorner(ofxQuad* parentQuad, size_t pointIndex, float x, float y, ADORNER_QUAD_CORNER adcorner, float width = DRAGGING_ADORNER_WIDTH, float height = DRAGGING_ADORNER_HEIGHT)
        : DraggingAdorner(x, y, width, height), index(pointIndex)
        {
            QuadAdorner::parentQuad = parentQuad;
            setAdornerQuadPosition(adcorner);
        }
    
        PMappingAdorner(ofxQuad* parentQuad, size_t pointIndex, ofPoint adornerPosition, ADORNER_QUAD_CORNER adcorner, float width = DRAGGING_ADORNER_WIDTH, float height = DRAGGING_ADORNER_HEIGHT)
        : DraggingAdorner(adornerPosition.x, adornerPosition.y, width, height), index(pointIndex)
        {
            QuadAdorner::parentQuad = parentQuad;
            setAdornerQuadPosition(adcorner);
        }
    
        size_t index;
    private:
        void setAdornerQuadPosition(ADORNER_QUAD_CORNER corner){
            switch (corner) {
                case TOP_LEFT:
                    break;
                case TOP_RIGHT:
                    DraggingAdorner::setPosition(DraggingAdorner::x - DraggingAdorner::width, DraggingAdorner::y);
                    break;
                case BOTTOM_LEFT:
                    DraggingAdorner::setPosition(DraggingAdorner::x, DraggingAdorner::y - DraggingAdorner::height);
                    break;
                case BOTTOM_RIGHT:
                    DraggingAdorner::setPosition(DraggingAdorner::x - DraggingAdorner::width, DraggingAdorner::y - DraggingAdorner::height);
                    break;
                default:
                    break;
            }
        }
};

#endif
