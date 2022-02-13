#include "Hero.h"

Hero::Hero() :
    isDead(0),
    powerTimer(0),
    mainHero({0, 0}),
    animationOver(0),
    directions({0}),
    moveDir(0),
    totalScore(0)
{
}

void Hero::Reset()
{
    texture = handler.loadImage("pacman.png");
    death_texture = handler.loadImage("pacman_death.png");

    animationOver = 0;
    animationTimer = 0;

    totalScore = 0;

    isDead = 0;
    powerTimer = 0;
    moveDir = 0;
}

void Hero::SetPosition(short x, short y)
{
    mainHero = {x, y};
}

void Hero::SetDead(bool m_isDead)
{
    isDead = m_isDead;
}

void Hero::SetAnimationTimer(unsigned short m_animationTimer)
{
    animationTimer = m_animationTimer;
}

void Hero::Update(unsigned char level, std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map)
{
    // Проверка коллизии на все 4 направления персонажа
    walls[0] = checkCollision(0, 0, 0, 1 + mainHero.x, mainHero.y, i_map);
    walls[1] = checkCollision(0, 0, 0, mainHero.x, mainHero.y - 1, i_map);
    walls[2] = checkCollision(0, 0, 0, mainHero.x - 1, mainHero.y, i_map);
    walls[3] = checkCollision(0, 0, 0, mainHero.x, 1 + mainHero.y, i_map);

    // Если нет коллизии со стенками в последнем элемента списка с направлением персонажа
    if (walls[directions.back()] == 0)
    {
        // Поменяй текущее направление на направление в последнем элементе списка
        moveDir = directions.back();
    }

    if (walls[moveDir] == 0)
    {
        // Задает персонажу новые координаты в зависимости от направления и скорости
        switch (moveDir)
        {
            case 0: mainHero.x += HERO_SPEED; break; // Направо
            case 1: mainHero.y -= HERO_SPEED; break; // Вверх
            case 2: mainHero.x -= HERO_SPEED; break; // Налево
            case 3: mainHero.y += HERO_SPEED; break; // Вниз
        }
    }

    // Если персонаж выходит за карту по X координате, то поменяй его позицию по X на противоположную
    if (-CELL_SIZE >= mainHero.x)
    {
        mainHero.x = CELL_SIZE * MAP_WIDTH - HERO_SPEED;
    }

    else if (CELL_SIZE * MAP_WIDTH <= mainHero.x)
    {
        mainHero.x = HERO_SPEED - CELL_SIZE;
    }

    // Если Пакман собрал бафф, то добавь ему очки и обнови таймер баффа
    if (checkCollision(0, 1, 0, mainHero.x, mainHero.y, i_map) == 1)
    {
        totalScore += 200;
        powerTimer = static_cast<unsigned short>(BUFF_TIME / pow(2, level));
    }

    else
    {
        powerTimer = std::max(0, powerTimer - 1);
    }

    // Если Пакман собрал монетки (еду), то начисли ему 100 очков за каждую собранную единицу
    if (checkCollision(1, 0, 0, mainHero.x, mainHero.y, i_map) == 1)
    {
        totalScore += 100;
    }
}

void Hero::Draw(bool isVictory)
{
    // Текущий кадр анимации
    unsigned char frame = static_cast<unsigned char>(floor(animationTimer / static_cast<float>(PACMAN_ANIMATION_SPEED)));

    // Отдельная анимация поражения/победы
    if (isDead == 1 || isVictory == 1)
    {
        if (animationTimer < PACMAN_DEATH_FRAMES * PACMAN_ANIMATION_SPEED)
        {
            animationTimer++;

            clip.x = CELL_SIZE * frame;
            clip.y = 0;
            clip.h = CELL_SIZE;
            clip.w = CELL_SIZE;

            handler.applySurface(mainHero.x, mainHero.y, death_texture, handler.screen, &clip);
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
        clip.x = CELL_SIZE * frame;
        clip.y = CELL_SIZE * moveDir;
        clip.h = CELL_SIZE;
        clip.w = CELL_SIZE;

        handler.applySurface(mainHero.x, mainHero.y, texture, handler.screen, &clip);
        animationTimer = (1 + animationTimer) % (PACMAN_ANIMATION_FRAMES * PACMAN_ANIMATION_SPEED);
    }


}

void Hero::MoveRight()
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

void Hero::MoveUp()
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

void Hero::MoveLeft()
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

void Hero::MoveDown()
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

unsigned short Hero::GetDirection()
{
    return moveDir;
}

unsigned short Hero::GetPowerTimer()
{
    return powerTimer;
}

bool Hero::GetDead()
{
    return isDead;
}

bool Hero::GetAnimationOver()
{
    return animationOver;
}

Vector2 Hero::GetPosition()
{
    return mainHero;
}

unsigned short Hero::GetTotalScore()
{
    return totalScore;
}

void Hero::CleanUp()
{
    SDL_FreeSurface(texture);
    SDL_FreeSurface(death_texture);
}

