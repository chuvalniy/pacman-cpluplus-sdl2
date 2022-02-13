#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "string"
#include "Global.h"
#include "stdio.h"

class SpriteLoader {

public:

    static SDL_Texture *loadTexture(std::string spritePath, SDL_Renderer* renderer);
    static void applyTexture(int x, int y, SDL_Renderer* renderer, SDL_Texture *texture, SDL_Rect *srcRect);
};




