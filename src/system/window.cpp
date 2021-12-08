#include "window.h"
#include <SDL2/SDL.h>

namespace jadel
{
    bool createWindow(const char* title, int width, int height, Window* window)
    {
        SDL_Window* win;
        win = SDL_CreateWindow(title,
                         SDL_WINDOWPOS_CENTERED,
                         SDL_WINDOWPOS_CENTERED,
                         width,
                         height,
                         SDL_WINDOW_SHOWN);
        if (!win) return false;
        
        window->win = win;
        window->surface.width = width;
        window->surface.height = height;
        window->surface.pixels = getPixels(window);
        return true;
    }

    void destroyWindow(Window* window)
    {
        SDL_DestroyWindow(window->win);
    }

    uint32* getPixels(Window* window)
    {
        SDL_Surface* winSurface = SDL_GetWindowSurface(window->win);
        uint32* pixels = (uint32*)winSurface->pixels;
        return pixels;
    }

    void updateWindow(Window* window)
    {
        SDL_UpdateWindowSurface(window->win);
    }

    void applySurface(Surface* surface, bool fitToWindow, Window* target)
    {       
        if (!surface || !target) return;
        pushTargetSurface(&target->surface);
        blitSurface(surface, fitToWindow);
        popTargetSurface();
    }
}
