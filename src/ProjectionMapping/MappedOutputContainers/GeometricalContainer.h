/*
 * GeometricalContainer.h
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

#ifndef HolographicAR_GeometricalContainer_h
#define HolographicAR_GeometricalContainer_h

class GeometricContainer{};

//Similar to ofRectange but for irregular Quads as well
class QuadContainer : public GeometricContainer {
public:
    explicit QuadContainer(ofRectangle& quad)
    : _topLeft(quad.getTopLeft()), _topRight(quad.getTopRight()), _bottomLeft(quad.getBottomLeft()), _bottomRight(quad.getBottomRight())
    {}
    QuadContainer(ofPoint& topLeft, ofPoint& topRight, ofPoint& bottomLeft, ofPoint& bottomRight)
    : _topLeft(topLeft), _topRight(topRight), _bottomLeft(bottomLeft), _bottomRight(bottomRight)
    {}
    virtual ofPoint& getTopLeft(){
        return _topLeft;
    }
    virtual ofPoint& getTopRight(){
        return _topRight;
    }
    virtual ofPoint& getBottomLeft(){
        return _bottomLeft;
    }
    virtual ofPoint& getBottomRight(){
        return _bottomRight;
    }
private:
    ofPoint _topLeft, _topRight, _bottomLeft, _bottomRight;
};

class HexContainer : public GeometricContainer{
    public:
        HexContainer(ofPoint& corner1, ofPoint& corner2, ofPoint& corner3, ofPoint& corner4, ofPoint& corner5, ofPoint& corner6)
        :_corner1(corner1), _corner2(corner2), _corner3(corner3), _corner4(corner4), _corner5(corner5), _corner6(corner6)
        {}
    private:
        ofVec3f _corner1, _corner2, _corner3, _corner4, _corner5, _corner6;
};

#endif
