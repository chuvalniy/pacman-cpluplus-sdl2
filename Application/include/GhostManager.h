#ifndef GHOSTMANAGER_H
#define GHOSTMANAGER_H
#include "Enemy.h"
#include "Global.h"
#include <SDL.h>
#include "Hero.h"
#include <array>


class GhostManager // Вспомогательный класс к Enemy
{
private:

    // Призраки нападают волнами
    unsigned char current_wave;
    // Таймер для отслеживания времени между волнами
    unsigned short wave_timer;

    // Массив с типом Enemy, содержащий 4 призрака
    std::array<Enemy, 4> Ghosts;

public:

    GhostManager();

    void CleanUp();
    // Отрисовка всех призраков
    void Draw(bool isVanishing);
    // Обновление всех призраков
    void Reset(unsigned char level, const std::array<Vector2, 4>& m_GhostPosition);
    // Обновляет состояние призраков ( преследовать/бродить )
    void Update(unsigned char level, std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map, Hero& Pacman);
};

#endif // GHOSTMANAGER_H
