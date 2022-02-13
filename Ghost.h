#pragma once
#include "Unit.h"
#include "Pacman.h"

class Ghost : public Unit
{
public:
    Ghost(unsigned char m_ghostId, SDL_Renderer *ren);
    ~Ghost();

    bool pacmanCollision(const Vector2 &pacman);
    void updateTarget(unsigned char moveDir, const Vector2 &m_ghost, const Vector2 &pacman);
    float getTargetDistance(unsigned char m_moveDir);
    void reset(const Vector2 &m_Home, const Vector2 &m_HomeExit);
    void switchMode();
    void update(unsigned char level, std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map, Ghost& ghost, Pacman& pacman);
    void render(bool isVanishing);

private:
    // Цель призраков, когда они были задеты Пакманом под баффом
    Vector2 Home;
    // Vector2 выхода из двери
    Vector2 HomeExit;
    // Текущая цель призрака
    Vector2 Target;

    bool moveState;
    bool openDoor;

    unsigned char ghostId;


    unsigned char debuffState;
    unsigned char debuffStateTimer;

    SDL_Texture *debuffGhost;
    SDL_Texture *yellowGhost;
    SDL_Texture *redGhost;
    SDL_Texture *blueGhost;
    SDL_Texture *pinkGhost;


};
