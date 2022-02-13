#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "Global.h"
#include <stdio.h>

class SDL_Handler
{
public:

    SDL_Handler();
    ~SDL_Handler();

    bool init();

    void cleanUp();

    SDL_Texture *loadSurface(std::string path);
};
