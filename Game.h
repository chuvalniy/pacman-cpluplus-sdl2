#pragma once

#include <stdio.h>
#include <array>
#include "Pacman.h"
#include "SDL.h"
#include "Map.h"
#include "SDL_image.h"
#include "GhostManager.h"



class Game
{
public:
    Game();
    ~Game();

    void init();
    void update();
    void render();
    void reset();
    void handleEvents();
    bool running();
    void cleanUp();


private:
    bool isRunning;

    Pacman *pacman;
    Map *map;
    GhostManager *ghostManager;

    SDL_Window *window;
    SDL_Surface *screen;
    SDL_Renderer *renderer;
    SDL_Event event;

    std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> worldMap {};
    std::array<std::string, MAP_HEIGHT> mapLoader {};

    std::array<Vector2, 4> ghostPosition;

    bool isVictory;

};
