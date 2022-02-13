#pragma once
#include "SDL.h"
#include "Global.h"

class Menu
{
public:
    Menu(SDL_Renderer *renderer);
    ~Menu();

    void render();
    void update();
    void reset();
    void setMousePosition();

private:
    Vector2 MousePosition;

    SDL_Renderer *renderer;
    SDL_Texture *menuTexture;
};
