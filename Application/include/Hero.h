#ifndef HERO_H
#define HERO_H
#include "Global.h"
#include <SDL.h>
#include "SDL_Handler.h"
#include "Collision.h"
#include <iostream>
#include <array>
#include <list>

class Hero
{
private:

    // Конец игры
    bool isDead;

    // Конец анимации
    bool animationOver;

    // Направление персонажа
    unsigned char moveDir;

    // Частота смены анимации
    unsigned short animationTimer;

    // Длительности баффа персонажа
    unsigned short powerTimer;

    // Количество очков
    unsigned short totalScore;

    // Массив, содержащий доступные направления персонажа
    std::array<bool, 4> walls {};
    // Список, содержащий направления персонажа
    std::list<unsigned char> directions;

    // Позиция персонажа
    Vector2 mainHero;

    SDL_Handler handler;

    // Переменные для изображения персонажа на целевую поверхнотсь
    SDL_Surface *texture;
    SDL_Surface *death_texture;
    SDL_Rect clip;

public:

    Hero();

    // Обновления координат персонажа
    void Update(unsigned char level, std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map);

    // Направления движения персонажа
    void MoveUp();
    void MoveDown();
    void MoveLeft();
    void MoveRight();

    // Отрисовка персонажа
    void Draw(bool isVictory);

    // Обновление персонажа
    void Reset();

    // Установка состояния персонажа
    void SetDead(bool m_isDead);
    // Установка позиции персонажа
    void SetPosition(short x, short y);
    // Установка таймера анимации
    void SetAnimationTimer(unsigned short m_animationTimer);

    // Возвращает таймер до конца баффа
    unsigned short GetPowerTimer();
    // Получить текущее количество очков
    unsigned short GetTotalScore();
    // Возвращает направление персонажа
    unsigned short GetDirection();
    // Получить координаты персонажа
    Vector2 GetPosition();
    // Получить состояние анимации
    bool GetAnimationOver();
    // Получить состояние персонажа
    bool GetDead();

    // Удаление всех текстур (поверхностей) персонажа
    void CleanUp();


};

#endif
