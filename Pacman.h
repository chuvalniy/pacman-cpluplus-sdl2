#pragma once
#include "Unit.h"


class Pacman : public Unit
{
public:
    Pacman(SDL_Renderer *ren);
    ~Pacman();

    void reset();
    void render(bool isVictory);
    void update(unsigned char level, std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map);

    void moveRight();
    void moveUp();
    void moveLeft();
    void moveDown();

    void setDead(bool m_isDead);

    unsigned short getPowerTimer();
    unsigned short getTotalScore();
    unsigned short getDirection();
    bool getDead();

    void cleanUp();




private:
    std::list<unsigned char> directions {};

    bool isDead;
    bool animationOver;
    unsigned short powerTimer;
    unsigned short totalScore;

    SDL_Texture *deathTexture;


};
