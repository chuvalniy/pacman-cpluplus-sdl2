#include "SpriteLoader.h"

SDL_Texture* SpriteLoader::loadTexture(std::string spritePath, SDL_Renderer* renderer)
{
    SDL_Texture *newTexture = NULL;

    SDL_Surface *loadedSurface = IMG_Load(spritePath.c_str());
    if (loadedSurface == NULL)
    {
        printf( "Unable to load image %s! SDL Error: %s\n", spritePath.c_str(), IMG_GetError() );
    }
    else
    {
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == NULL)
        {
            printf( "Unable to optimize image %s! SDL Error: %s\n", spritePath.c_str(), SDL_GetError() );
        }

        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
}


void SpriteLoader::applyTexture(int x, int y, SDL_Renderer* renderer, SDL_Texture *texture, SDL_Rect *srcRect)
{
    SDL_Rect destRect = { x, y, CELL_SIZE, CELL_SIZE};
    SDL_RenderCopy(renderer, texture, srcRect, &destRect);
}
