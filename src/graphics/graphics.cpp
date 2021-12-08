#include "graphics.h"
#include "../math/math.h"
#include <stdlib.h>

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
        targetSurface->pixels[(x + halfTargetWidth) + (y + halfTargetHeight) * targetSurface->width] = color;
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
        for (int y = -halfTargetHeight; y < halfTargetHeight; ++y)
        {
            for (int x = -halfTargetWidth; x < halfTargetWidth; ++x)
            {
                drawPixel(x, y, clearColor);
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

        uint32* targetPixels = targetSurface->pixels;
        uint32* surfacePixels = surface->pixels;
        if (fitToSurface)
        {
            float xStep = (float)surface->width / (float)targetSurface->width;
            float yStep = (float)surface->height / (float)targetSurface->height;

            for (int y = 0; y < targetSurface->height; ++y)
            {
                for (int x = 0; x < targetSurface->width; ++x)
                {
                    targetPixels[x + y * targetSurface->width]
                        = getPixel((int)((float)x * xStep), (int)((float)y * yStep), surface);
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
                    targetPixels[x + y * targetSurface->width] = getPixel(x, y, surface);
                }
            }
        }
    }

    void blitSurface(const Surface* surface, iRect pos)
    {
        int xStart = pos.x;
        int yStart = pos.y;
        int xEnd = pos.x + pos.w;
        int yEnd = pos.y + pos.h;

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
        
        if (xStart >= targetSurface->width) return;
        if (yStart >= targetSurface->height) return;
        if (xEnd <= 0) return;
        if (yEnd <= 0) return;
        if (xStart < 0) xStart = 0;       
        if (yStart < 0) yStart = 0;
        if (xEnd >= targetSurface->width) xEnd = targetSurface->width;
        if (yEnd >= targetSurface->height) yEnd = targetSurface->height;

        float xStep = (float)surface->width / ((float)xEnd - (float)xStart);
        float yStep = (float)surface->height / ((float)yEnd - (float)yStart);

        for (int y = yStart; y < yEnd; ++y)
        {
            int sourceYIndex = (int)(yStep * (float)(yEnd - y));
            for (int x = xStart; x < xEnd; ++x)
            {
                int sourceXIndex = (int)(xStep * (float)(xEnd - x));
                targetSurface->pixels[x + y * targetSurface->width]
                    = getPixel(sourceXIndex, sourceYIndex, surface);
            }
        }
    }


    uint32 getPixel(int x, int y, const Surface* target)
    {
        uint32 result = target->pixels[x + y * target->width];
        return result;
    }

    int createSurface(int width, int height, Surface* surface)
    {
        if (!surface) return 0;

        if (width == 0 || height == 0) return 0;
        
        surface->pixels = (uint32*)malloc(width * height * sizeof uint32);
        if (!surface->pixels) return 0;

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
}
