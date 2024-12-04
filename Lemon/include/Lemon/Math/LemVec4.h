#pragma once
#include <Lemon/LemPrerequisites.h>

class LemVec4
{
public:
    LemVec4()
    {
        
    }
    LemVec4(f32 x, f32 y, f32 z, f32 w) : x(x), y(y), z(z), w(w)
    {
        
    }
    ~LemVec4()
    {
        
    }

    f32 x, y, z, w = 0;
};