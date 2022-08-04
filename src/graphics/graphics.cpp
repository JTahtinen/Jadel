#include "graphics.h"
#include "../math/math.h"
#include <stdlib.h>
#include <string.h>

namespace jadel
{
    #define TARGET_SURFACE_STACK_SIZE 20
    static Surface* targetSurfaceStack[TARGET_SURFACE_STACK_SIZE];
    static int numTargetSurfaces = 0;

    static Surface* targetSurface = NULL;
    static int halfTargetWidth = 0;
    static int halfTargetHeight = 0;
    static uint32 clearColor = 0;

    void drawPixelFast(int x, int y, uint32 color)
    {
        //targetSurface->pixels[(x + halfTargetWidth) + (y + halfTargetHeight) * targetSurface->width] = color;
        targetSurface->pixels[x + y * targetSurface->width] = color;
    }

    void drawPixel(int x, int y, uint32 color)
    {
        if (x >= 0 && x < targetSurface->width
            && y >= 0 && y < targetSurface->height)
        {
            drawPixelFast(x, y, color);
        }
    }

    void clearTargetSurface()
    {    
        for (int y = 0; y < targetSurface->height; ++y)
        {
            for (int x = 0; x < targetSurface->width; ++x)
            {
                drawPixelFast(x, y, clearColor);
            }
        }
    }

    void updateCurrentTargetSurface()
    {
        if (numTargetSurfaces == 0)
        {
            halfTargetWidth = 0;
            halfTargetHeight = 0;
            targetSurface = NULL;
        }
        else
        {
            targetSurface = targetSurfaceStack[numTargetSurfaces - 1];
            halfTargetWidth = targetSurface->width / 2;
            halfTargetHeight = targetSurface->height / 2;
        }
    }
    
    void pushTargetSurface(Surface* surface)
    {
        if (surface && numTargetSurfaces < TARGET_SURFACE_STACK_SIZE)
        {
            targetSurfaceStack[numTargetSurfaces++] = surface;
            updateCurrentTargetSurface();
        }
    }
    
    void popTargetSurface()
    {
        if (numTargetSurfaces > 0)
        {
            --numTargetSurfaces;
            updateCurrentTargetSurface();
        }
    }

/*
    void setTargetSurface(Surface* surface)
    {
        targetSurface = surface;
        if (!surface)
        {
            halfTargetWidth = 0;
            halfTargetHeight = 0;
            return;
        }
        halfTargetWidth = surface->width / 2;
        halfTargetHeight = surface->height / 2;
    }
*/

    void setClearColor(uint32 color)
    {
        clearColor = color;
    }
    
    void blitSurface(const Surface* surface, bool fitToSurface)
    {
        if (!surface || !targetSurface) return;

        //      uint32* targetPixels = targetSurface->pixels;
        uint32* surfacePixels = surface->pixels;
        if (fitToSurface)
        {
            float xStep = (float)surface->width / (float)targetSurface->width;
            float yStep = (float)surface->height / (float)targetSurface->height;

            for (int y = 0; y < targetSurface->height; ++y)
            {
                for (int x = 0; x < targetSurface->width; ++x)
                {
                    drawPixelFast(x, y, getPixel((int)((float)x * xStep), (int)((float)y * yStep), surface)); 
//                    targetPixels[x + y * targetSurface->width]
                    //= getPixel((int)((float)x * xStep), (int)((float)y * yStep), surface);
                }
            }
        }
        else
        {
            int xEnd;
            int yEnd;
            if (surface->width <= targetSurface->width) xEnd = surface->width;
            else xEnd = targetSurface->width;
            if (surface->height <= targetSurface->height) yEnd = surface->height;
            else yEnd = targetSurface->height;

            for (int y = 0; y < yEnd; ++y)
            {
                for (int x = 0; x < xEnd; ++x)
                {
                    uint32 sourcePixel = getPixel(x, y, surface);
                    Vec4 sourcePixelVec4 = createColor(sourcePixel);
                    if (sourcePixelVec4.a == 1.0f)
                    {
                        drawPixelFast(x, y, sourcePixel);
                    }
                    else
                    {
                        uint32 targetPixel = getPixel(x, y, targetSurface);
                        Vec4 targetPixelVec4 = createColor(targetPixel);
                        Vec4 finalPixel =
                            blendColors(sourcePixelVec4, targetPixelVec4, sourcePixelVec4.a);
                      
                        drawPixelFast(x, y, createColor(finalPixel));
                    }
                                  //targetPixels[x + y * targetSurface->width] = getPixel(x, y, surface);
                }
            }
        }
    }
    
    void blitSurface(const Surface* surface, iRect sourceRect, iRect targetRect)
    {
        int xStart = targetRect.x;
        int yStart = targetRect.y;
        int xEnd = targetRect.x + targetRect.w;
        int yEnd = targetRect.y + targetRect.h;

        int sourceXStart = sourceRect.x;
        int sourceYStart = sourceRect.y;
        int sourceXEnd = sourceRect.x + sourceRect.w;
        int sourceYEnd = sourceRect.y + sourceRect.h;

        if (xStart > xEnd)
        {
            int temp = xStart;
            xStart = xEnd;
            xEnd = temp;
        }
        
        if (yStart > yEnd)
        {
            int temp = yStart;
            yStart = yEnd;
            yEnd = temp;
        }

        if (sourceXStart > sourceXEnd)
        {
            int temp = sourceXStart;
            sourceXStart = sourceXEnd;
            sourceXEnd = temp;
        }
        
        if (sourceYStart > sourceYEnd)
        {
            int temp = sourceYStart;
            sourceYStart = sourceYEnd;
            sourceYEnd = temp;
        }

        
        if (xStart >= targetSurface->width) return;
        if (yStart >= targetSurface->height) return;
        if (xEnd <= 0) return;
        if (yEnd <= 0) return;
        if (xStart < 0) xStart = 0;       
        if (yStart < 0) yStart = 0;
        if (xEnd >= targetSurface->width) xEnd = targetSurface->width;
        if (yEnd >= targetSurface->height) yEnd = targetSurface->height;

        if (sourceXStart >= surface->width) return;
        if (sourceYStart >= surface->height) return;
        if (sourceXEnd <= 0) return;
        if (sourceYEnd <= 0) return;
        if (sourceXStart < 0) sourceXStart = 0;       
        if (sourceYStart < 0) sourceYStart = 0;
        if (sourceXEnd >= surface->width) sourceXEnd = surface->width;
        if (sourceYEnd >= surface->height) sourceYEnd = surface->height;

  
        float xStep = (float)(sourceXEnd - sourceXStart) / (float)(xEnd - xStart);
        float yStep = (float)(sourceYEnd - sourceYStart) / (float)(yEnd - yStart);
//        float xStep = (float)(targetRect.w) / (float)(sourceRect.w);
//        float yStep = (float)(targetRect.h) / (float)(sourceRect.h);
        for (int y = yStart; y < yEnd; ++y)
        {
            int sourceYIndex = sourceYStart + (int)(yStep * (float)(y - yStart));
            for (int x = xStart; x < xEnd; ++x)
            {
                int sourceXIndex = sourceXStart + (int)(xStep * (float)(x - xStart));
//                targetSurface->pixels[x + y * targetSurface->width]
//                    = getPixel(sourceXIndex, sourceYIndex, surface);
                uint32 sourcePixel = getPixel(sourceXIndex, sourceYIndex, surface);
                Vec4 sourcePixelVec4 = createColor(sourcePixel);

                if (sourcePixelVec4.a == 1.0f)
                {
                    drawPixelFast(x, y, getPixel(sourceXIndex, sourceYIndex, surface));
                }
                else
                {
                    uint32 targetPixel = getPixel(x, y, targetSurface);
                    Vec4 targetPixelVec4 = createColor(targetPixel);
                    Vec4 finalPixel = blendColors(targetPixelVec4, sourcePixelVec4, sourcePixelVec4.a);
                    drawPixelFast(x, y, createColor(finalPixel));
                }
            }
        }
    }

    void blitSurface(const Surface* surface, iRect targetRect)
    {
        if (!surface) return;
        iRect sourceRect = {.x = 0, .y = 0, .w = surface->width, .h = surface->height};
        blitSurface(surface, sourceRect, targetRect);
    }

    uint32 getPixel(int x, int y, const Surface* target)
    {
        uint32 result = target->pixels[x + y * target->width];
        return result;
    }

    int createSurface(int width, int height, Surface* surface, const char* name)
    {
        if (!surface) return 0;

        if (width == 0 || height == 0) return 0;
        
        surface->pixels = (uint32*)malloc(width * height * sizeof uint32);
        if (!surface->pixels) return 0;
        
        strncpy(surface->name, name, 39);
        surface->name[39] = 0;
        surface->width = width;
        surface->height = height;
        return 1;
    }
    
    void freeSurface(Surface* surface)
    {
        if (surface)
        {
            free(surface->pixels);
        }
    }

    uint32* workBuffer = (uint32*)malloc(2000 * 2000 * sizeof(uint32));

    void flipVertically(Surface* surface)
    {
        for (int y = 0; y < surface->height; ++y)
        {
            for (int x = 0; x < surface->width; ++x)
            {
                workBuffer[x + y * surface->width]
                    = surface->pixels[x + (surface->height - 1 - y) * surface->width];
            }
        }
        memcpy(surface->pixels, workBuffer, surface->width * surface->height * 4);
    }

    void flipHorizontally(Surface* surface)
    {
        for (int y = 0; y < surface->height; ++y)
        {
            for (int x = 0; x < surface->width; ++x)
            {
                workBuffer[x + y * surface->width]
                    = surface->pixels[(surface->width - 1 - x) + y * surface->width];
            }
        }
        memcpy(surface->pixels, workBuffer, surface->width * surface->height * 4);
    }


    Vec4 blendColors(Vec4 color0, Vec4 color1, float alpha)
    {
        float calpha = clampf(alpha, 0, 1.0f);    
        float da = color1.a - color0.a;
        float dr = color1.r - color0.r;
        float dg = color1.g - color0.g;
        float db = color1.b - color0.b;
        float finalA = color0.a + da * calpha;
        float finalR = color0.r + dr * calpha;
        float finalG = color0.g + dg * calpha;
        float finalB = color0.b + db * calpha;
        Vec4 result(finalA, finalR, finalG, finalB);
        return result;
    }

    Vec4 createColor(uint32 color)
    {
        Vec4 result;
        uint8 a = color >> 24;
        uint8 r = color >> 16;
        uint8 g = color >> 8;
        uint8 b = color;

        result.a = (float)a / 255.0f;
        result.r = (float)r / 255.0f;
        result.g = (float)g / 255.0f;
        result.b = (float)b / 255.0f;
        return result;
    }

    uint32 createColor(Vec4 color)
    {
        Vec4 clampedColor(clampf(0, 1, color.a),
                          clampf(0, 1, color.r),
                          clampf(0, 1, color.g),
                          clampf(0, 1, color.b)); 
        uint8 a = (uint8)(color.a * 255.0f);
        uint8 r = (uint8)(color.r * 255.0f);
        uint8 g = (uint8)(color.g * 255.0f);
        uint8 b = (uint8)(color.b * 255.0f);
        uint32 result = (a << 24 & 0xff000000)
            | (r << 16 & 0x00ff0000)
            | (g << 8 & 0x0000ff00)
            | (b & 0x000000ff);
        return result;
    }

    bool copySurface(const Surface* source, Surface* target, const char* name)
    {
        if (source->pixels && source->width + source->height > 0)
        {
            createSurface(source->width, source->height, target, name);
            memcpy(target->pixels, source->pixels, source->width * source->height * 4);
            return true;
        }
        return false;
    }

}

