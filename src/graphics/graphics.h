#pragma once
#include "../defs.h"
#include "../math/math.h"

namespace jadel
{    
    struct Surface
    {
        char name[40];
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
    void blitSurface(const Surface* surface, iRect sourceRect, iRect targetRect);
    void blitSurface(const Surface* surface, iRect pos);
    uint32 getPixel(int x, int y, const Surface* surface);
    int createSurface(int width, int height, Surface* surface, const char* name);
    void freeSurface(Surface* surface);
    void flipVertically(Surface* surface);
    void flipHorizontally(Surface* surface);
    Vec4 blendColors(Vec4 color0, Vec4 color1, float alpha);
    Vec4 createColor(uint32 color);
    uint32 createColor(Vec4 color);
    bool copySurface(const Surface* source, Surface* target, const char* name);
}
