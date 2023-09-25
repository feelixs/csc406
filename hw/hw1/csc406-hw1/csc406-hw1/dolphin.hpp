//
//  dolphin.hpp
//  csc406-hw1
//
//  Created by Michael Felix on 9/20/23.
//

#ifndef dolphin_hpp
#define dolphin_hpp

#include <stdio.h>

void loadShape(const char* filename); // returns the amount of vertices in the loaded file

class Dolphin
{
    friend int loadShape();
    
    private:
        float centerX_, centerY_, scaleX_, scaleY_, angle_;
        float red_, green_, blue_;
            
        static const int numShapePnts_;
        static float** shapePnts_;


    public:
        Dolphin(float centerX, float centerY, float angle, float scaleX, float scaleY, float r, float g, float b);
        ~Dolphin();
        
        void draw() const;

        //disabled constructors & operators
        Dolphin() = delete;
        Dolphin(const Dolphin& obj) = delete;    // copy
        Dolphin(Dolphin&& obj) = delete;        // move
        Dolphin& operator = (const Dolphin& obj) = delete;    // copy operator
        Dolphin& operator = (Dolphin&& obj) = delete;        // move operator
};

#endif /* dolphin_hpp */
