#include "Pacman.h"


Pacman::Pacman(SDL_Renderer *ren)
{
    renderer = ren;
}

Pacman::~Pacman()
{
    cleanUp();
}

void Pacman::reset()
{
    texture = SpriteLoader::loadTexture("pacman.png",  renderer);
    deathTexture = SpriteLoader::loadTexture("pacman_death.png", renderer);

    moveDir = 0;

    srcRect = { 0, 0, 16, 16 };
    Position = { 0, 0 };

    totalScore = 0;
    isDead = 0;

    powerTimer = 0;

    animationTimer = 0;
    animationOver = 0;
}


void Pacman::update(unsigned char level, std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map)
{
    walls[0] = checkCollision(0, 0, 0, 1 + Position.x, Position.y, i_map);
    walls[1] = checkCollision(0, 0, 0, Position.x, Position.y - 1, i_map);
    walls[2] = checkCollision(0, 0, 0, Position.x - 1, Position.y, i_map);
    walls[3] = checkCollision(0, 0, 0, Position.x, 1 + Position.y, i_map);

    if (walls[directions.back()] == 0)
    {
        // Поменяй текущее направление на направление в последнем элементе списка
        moveDir = directions.back();
    }
    if (walls[moveDir] == 0 && directions.size() > 0)
    {
        switch(moveDir)
        {
            case 0: Position.x += PACMAN_SPEED; break;
            case 1: Position.y -= PACMAN_SPEED; break;
            case 2: Position.x -= PACMAN_SPEED; break;
            case 3: Position.y += PACMAN_SPEED; break;
        }
    }
    // Если персонаж выходит за карту по X координате, то поменяй его позицию по X на противоположную
    if (-CELL_SIZE >= Position.x)
    {
        Position.x = CELL_SIZE * MAP_WIDTH - PACMAN_SPEED;
    }

    else if (CELL_SIZE * MAP_WIDTH <= Position.x)
    {
        Position.x = PACMAN_SPEED - CELL_SIZE;
    }

    if (checkCollision(0, 1, 0, Position.x, Position.y, i_map) == 1)
    {
        totalScore += 200;
        powerTimer = static_cast<unsigned short>(POWER_TIME / pow(2, level));
    }

    else
    {
        powerTimer = std::max(0, powerTimer - 1);
    }

    // Если Пакман собрал монетки (еду), то начисли ему 100 очков за каждую собранную единицу
    if (checkCollision(1, 0, 0, Position.x, Position.y, i_map) == 1)
    {
        totalScore += 100;
    }


}

void Pacman::render(bool isVictory)
{
    // Текущий кадр анимации
    unsigned char frame = static_cast<unsigned char>(floor(animationTimer / static_cast<float>(PACMAN_ANIMATION_SPEED)));

    // Отдельная анимация поражения/победы
    if (isDead == 1 || isVictory == 1)
    {
        if (animationTimer < PACMAN_DEATH_FRAMES * PACMAN_ANIMATION_SPEED)
        {
            animationTimer++;

            srcRect.x = CELL_SIZE * frame;
            srcRect.y = 0;
            srcRect.h = CELL_SIZE;
            srcRect.w = CELL_SIZE;

            SpriteLoader::applyTexture(Position.x, Position.y, renderer, deathTexture, &srcRect);
        }
        else
        {
            // Конец анимации победы/поражения
            animationOver = 1;
        }
    }
    // Обычная игровая анимация передвижения
    else
    {
        srcRect.x = CELL_SIZE * frame;
        srcRect.y = CELL_SIZE * moveDir;
        srcRect.h = CELL_SIZE;
        srcRect.w = CELL_SIZE;

        SpriteLoader::applyTexture(Position.x, Position.y, renderer, texture, &srcRect);
        animationTimer = (1 + animationTimer) % (PACMAN_ANIMATION_FRAMES * PACMAN_ANIMATION_SPEED);
    }


}

void Pacman::moveRight()
{
    // Если список с направлениями пустой
    if (directions.size() == 0)
    {
        // Если нет коллизии справа
        if (walls[0] == 0)
        {
            // Добавь направление в список
            directions.push_front(0);
        }
    }

    // Если список содержит один элемент
    else if(directions.size() == 1)
    {
        // Добавь направление в конец
        directions.push_back(0);
    }

    // Если в списке два элемента
    else if(directions.size() == 2)
    {
        // Убери последний элемент списка
        directions.pop_back();
        // Добавь вместо него новый
        directions.push_back(0);
    }
}

void Pacman::moveUp()
{
    if (directions.size() == 0)
    {
        if (walls[1] == 0)
        {
            directions.push_front(1);
        }
    }
    else if(directions.size() == 1)
    {
        directions.push_back(1);
    }

    else if(directions.size() == 2)
    {
        directions.pop_back();
        directions.push_back(1);
    }
}

void Pacman::moveLeft()
{
    if (directions.size() == 0)
    {
        if (walls[2] == 0)
        {
            directions.push_front(2);
        }
    }
    else if(directions.size() == 1)
    {
        directions.push_back(2);
    }

    else if(directions.size() == 2)
    {
        directions.pop_back();
        directions.push_back(2);
    }
}

void Pacman::moveDown()
{
    if (directions.size() == 0)
    {
        if (walls[3] == 0)
        {
            directions.push_front(3);
        }
    }
    else if(directions.size() == 1)
    {
        directions.push_back(3);
    }

    else if(directions.size() == 2)
    {
        directions.pop_back();
        directions.push_back(3);
    }
}


unsigned short Pacman::getPowerTimer()
{
    return powerTimer;
}

unsigned short Pacman::getDirection()
{
    return moveDir;
}

unsigned short Pacman::getTotalScore()
{
    return totalScore;
}

bool Pacman::getDead()
{
    return isDead;
}

void Pacman::setDead(bool m_isDead)
{
    isDead = m_isDead;
}

void Pacman::cleanUp()
{

}


