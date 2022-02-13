#ifndef GHOST_H
#define GHOST_H

#include <SDL.h>
#include <array>
#include "Global.h"
#include "SDL_Handler.h"
#include "Collision.h"
#include "Hero.h"

class Enemy
{
private:
    // Догонять пакмана/Гулять по карте
    bool Mode;
    // Открытие двери
    bool openDoor;

    // Текущее направление
    unsigned char MoveDir;
    // Идентификатор призраков (0, 1, 2, 3);
    unsigned char GhostID;
    // Состояние призраков (зависит от эффекта баффа Пакмана)
    unsigned char FearMode;
    // Длительность состояния (зависит от эффекта баффа Пакмана)
    unsigned char FearModeTimer;
    // Таймер для отображения анимаций
    unsigned char animationTimer;

    // Цель призраков, когда они были задеты Пакманом под баффом
    Vector2 Exit;
    // Координаты выхода из двери
    Vector2 ExitHome;
    // Текущая позиция призрака
    Vector2 Ghost;
    // Текущая цель призрака
    Vector2 Target;

    SDL_Handler handler;

    // Поверхности с изображениями призраков
    SDL_Surface *fear_ghost;
    SDL_Surface *yellow_ghost;
    SDL_Surface *red_ghost;
    SDL_Surface *blue_ghost;
    SDL_Surface *pink_ghost;

public:
    // Конструктор с параметров идентификатора призрака
    Enemy(unsigned char ghost_id);

    // Установка позиции призрака
    void SetPosition(short m_x, short m_y);

    // Проверка на коллизию с Пакманом
    bool PacmanCollision(const Vector2& Pacman);

    // Обновление цели призраков
    void UpdateTarget(unsigned char MoveDir, const Vector2& m_Ghost, const Vector2& Pacman);

    // Обновление позиции призраков
    void Update(unsigned char level, std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map, Enemy& m_Ghost, Hero& Pacman);

    // Получить текущее направление призраков
    float GetDirection(unsigned char MoveDir);

    // Обновить призрака
    void Reset(const Vector2 &m_Exit, const Vector2 &m_HomeExit);

    // Поменять состояние призрака (догонять Пакмна/ходить по карте)
    void SwitchMode();

    // Отрисовка призрака
    void Draw(bool isVanishing);

    // Получить позицию призрака
    Vector2 GetPosition();

    // Удалить все поверхности с призраками
    void CleanUp();
};

#endif // GHOST_H
