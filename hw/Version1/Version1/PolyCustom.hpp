//
//  PolyCustom.hpp
//  Version1
//
//  Created by Michael Felix on 9/28/23.
//

#ifndef PolyCustom_hpp
#define PolyCustom_hpp

#include "PolyShape.hpp"
#include <stdio.h>

bool loadPolyShape(const char* filename);
bool initPolyShape(const char* coordFile);

class PolyCustom: public PolyShape {
    friend bool loadPolyShape(const char* filename);
private:
    // shape points loaded from file shapeCoords.txt in loadShape()
    const char* _myLoadedFilepath;
    static int _numLoadedPnts;
    static const int _maxLoadedPnts; // stop loading from the file after this limit is reached
    static float** _loadedShapePnts; // Nx2 float
    
public:
    PolyCustom(const char* filepath, float centerX, float centerY, float angle, float scaleX, float scaleY, float r, float g, float b);
    ~PolyCustom();
    
    void draw() const override;
    
    //disabled constructors & operators
    PolyCustom() = delete;
    PolyCustom(const PolyCustom& obj) = delete;    // copy
    PolyCustom(PolyCustom&& obj) = delete;        // move
    PolyCustom& operator = (const PolyCustom& obj) = delete;    // copy operator
    PolyCustom& operator = (PolyCustom&& obj) = delete;        // move operator
};

#endif /* PolyCustom_hpp */
