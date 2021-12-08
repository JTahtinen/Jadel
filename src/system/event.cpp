#include "event.h"
#include <SDL2/SDL.h>

namespace jadel
{    
    static SDL_Event inputEventArray[MAX_EVENTS];
    static SDL_Event windowEventArray[MAX_EVENTS];
    void* inputEvents;
    void* windowEvents;
    int numInputEvents;
    int numWindowEvents;

    void updateEvents()
    {
        numInputEvents = 0;
        numWindowEvents = 0;
        SDL_Event ev;

        while (SDL_PollEvent(&ev))
        {
            switch (ev.type)
            {
                case SDL_KEYDOWN:
                case SDL_KEYUP:
                case SDL_MOUSEBUTTONDOWN:
                case SDL_MOUSEBUTTONUP:
                case SDL_MOUSEMOTION:
                case SDL_MOUSEWHEEL:
                {
                    if (numInputEvents < MAX_EVENTS)
                    {
                        inputEventArray[numInputEvents++] = ev;
                    }
                    break;
                }
                case SDL_WINDOWEVENT:
                {
                    if (numWindowEvents < MAX_EVENTS)
                    {
                        windowEventArray[numWindowEvents++] = ev;
                    }
                }
            }
        }
    }

    void initEvents()
    {
        inputEvents = inputEventArray;
        windowEvents = windowEventArray;
    }
}
