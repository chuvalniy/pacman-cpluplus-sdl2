#pragma once
#include "Ghost.h"
#include "Pacman.h"
#include <array>
#include "SDL.h"
#include "Global.h"

class GhostManager
{
public:
    GhostManager(SDL_Renderer* ren);
    ~GhostManager();

    void render(bool isVanishing);
    // Обновление всех призраков
    void reset(unsigned char level, const std::array<Vector2, 4>& m_GhostPosition);
    // Обновляет состояние призраков ( преследовать/бродить )
    void update(unsigned char level, std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map, Pacman& pacman);

private:
    unsigned char currentWave;
    unsigned short waveTimer;

    SDL_Renderer *renderer;
    std::array<Ghost, 4> ghosts;
};
