#include "jadel.h"
#include <SDL2/SDL.h>

namespace jadel
{
    int initJadel()
    {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0) return 0;
        initEvents();
        initInput();
        return 1;
    }

    void updateJadel()
    {
        updateEvents();
        updateInput();
    }

    int quitJadel()
    {
        SDL_Quit();
        return 0;
    }
}
