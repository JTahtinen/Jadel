#pragma once
#include <stdint.h>
#include "../graphics/graphics.h"
#include "../defs.h"
struct SDL_Window;

namespace jadel
{
    struct Window
    {
        SDL_Window* win;
        Surface surface;
    };
    
    bool createWindow(const char* title, int width, int height, Window* window);
    void destroyWindow(Window* window);
    uint32* getPixels(Window* window);
    void updateWindow(Window* window);
    void applySurface(Surface* surface, bool fitToWindow, Window* target);
}


