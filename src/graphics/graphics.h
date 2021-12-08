#pragma once
#include "../defs.h"
#include "../math/math.h"

namespace jadel
{    
    struct Surface
    {
        uint32* pixels;
        int width;
        int height;
    };

    void drawPixelFast(int x, int y, uint32 color);
    void drawPixel(int x, int y, uint32 color);    
    void clearTargetSurface();
//    void setTargetSurface(Surface* surface);
    void pushTargetSurface(Surface* surface);
    void popTargetSurface();
    void setClearColor(uint32 color);
    void blitSurface(const Surface* surface, bool fitToSurface);
    void blitSurface(const Surface* surface, iRect pos);
    uint32 getPixel(int x, int y, const Surface* surface);
    int createSurface(int width, int height, Surface* surface);
    void freeSurface(Surface* surface);
}
