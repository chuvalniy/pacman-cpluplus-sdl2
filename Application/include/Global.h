#pragma once

// Экран
const unsigned int MENU_SCREEN_WIDTH = 300;
const unsigned int MENU_SCREEN_HEIGHT = 600;
const unsigned int GAME_SCREEN_WIDTH = 336;
const unsigned int GAME_SCREEN_HEIGHT = 380;
const unsigned int SCREEN_BPP = 32;
const unsigned int FPS = 70;

// Размер клетки, размер карты
const unsigned char CELL_SIZE = 16;
const unsigned char MAP_HEIGHT = 21;
const unsigned char MAP_WIDTH = 21;

// Скорость персонажей
const unsigned char HERO_SPEED = 1;
const unsigned char GHOST_SPEED = 1;
const unsigned char FEAR_SPEED = 1;

//
const unsigned char GHOST_1_CHASE = 2;
const unsigned char GHOST_2_CHASE = 1;
const unsigned char GHOST_3_CHASE = 4;

// Длительность состояний персонажей (в кадрах)
const unsigned short BUFF_TIME = 512;
const unsigned short CHASE_TIME = 1024;
const unsigned short FIRST_SCATTER_TIME = 512;
const unsigned short SECOND_SCATTER_TIME = 1024;

// Скорость анимации Пакмана
const unsigned char PACMAN_ANIMATION_FRAMES = 6;
const unsigned char PACMAN_ANIMATION_SPEED = 4;
const unsigned char PACMAN_DEATH_FRAMES = 12;

// Скорость анимации призраков
const unsigned char GHOST_ANIMATION_FRAMES = 6;
const unsigned char GHOST_ANIMATION_SPEED = 3;
const unsigned char GHOST_VANISH_START = 64;

//
struct Vector2
{
    short x;
    short y;

    bool operator==(const Vector2& Position)
    {
        return this->x == Position.x && this->y == Position.y;
    }
};

// Виды предметов на карте
enum Cell : unsigned char
{
    Empty = 0,
    Door = 1,
    Buff = 2,
    Food = 3,
    Wall = 4
};

// Состояние игры
enum GameState : unsigned char
{
     MainMenu = 0,
     InGame = 1,
     GameOver = 2,
     Victory = 3,
     ChangeLevel = 4,
     Leaderboard = 5,
     Help = 6,
     Exit = 7
};

