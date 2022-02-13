#pragma once

#include <array>
#include <string>
#include <SDL.h>
#include "Pacman.h"
#include "Ghost.h"
#include "SpriteLoader.h"
#include "Global.h"


class Map
{
public:

    Map(std::string spritePath, SDL_Renderer* ren);
    ~Map();

    std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> loadMap(const std::array<std::string, MAP_HEIGHT>& m_mapSketch, Pacman *pacman, std::array<Vector2, 4> &ghostPosition);

    void drawMap(const std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& mapLoader);

//    std::array<Vector2, 4> getGhostPosition();

    SDL_Renderer* renderer;
    SDL_Texture* texture;


private:


};
