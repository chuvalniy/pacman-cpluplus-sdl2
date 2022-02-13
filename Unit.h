#pragma once
#include "Global.h"
#include "SDL.h"
#include "SpriteLoader.h"
#include <stdio.h>
#include <array>
#include <list>
#include "Collision.h"

class Unit
{
public:

    Unit();
    ~Unit();

    unsigned char moveDir;
    unsigned short animationTimer;


    void setPosition(short m_x, short m_y);

    void getX();
    void getY();
    Vector2 getPosition();

protected:

    SDL_Rect srcRect;

    Vector2 Position;

    SDL_Texture *texture;
    SDL_Renderer *renderer;

    std::array<bool, 4> walls {};

};
