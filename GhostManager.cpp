#include "GhostManager.h"

GhostManager::GhostManager(SDL_Renderer* ren) :
                ghosts({Ghost(0, ren),
                Ghost(1, ren),
                Ghost(2, ren),
                Ghost(3, ren)})
{
    renderer = ren;
    currentWave = 0;
    waveTimer = SECOND_SCATTER_TIME;
}

GhostManager::~GhostManager()
{

}


void GhostManager::render(bool isVanishing)
{
    // Рисует каждого призрака
    for (Ghost& ghost : ghosts)
    {
        ghost.render(isVanishing);
    }
}

void GhostManager::reset(unsigned char level, const std::array<Vector2, 4> &m_GhostPosition)
{
    currentWave = 0;

    // Изначально призраки находятся в состоянии исследования
    waveTimer = static_cast<unsigned short> (SECOND_SCATTER_TIME / pow(2, level));

    // Установить первоначальные позиции
    for (unsigned char i = 0; i < 4; i++)
    {
        ghosts[i].setPosition(m_GhostPosition[i].x, m_GhostPosition[i].y);
    }

    // Обновить всех призраков до первоначального состояния
    for (Ghost& ghost : ghosts)
    {
        ghost.reset(ghosts[2].getPosition(), ghosts[0].getPosition());
    }
}

void GhostManager::update(unsigned char level, std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map, Pacman &pacman)
{
    // Если Пакман не находится под бафом
    if (pacman.getPowerTimer() == 0)
    {
        if (waveTimer == 0)
        {
            if (currentWave < 7)
            {
                currentWave++;

                // Меняет каждому призраку его состояние
                for (Ghost& ghost : ghosts)
                {
                    ghost.switchMode();
                }
            }
            // Меняет таймер волн в зависимости остатка от деления
            if (currentWave % 2 == 1)
            {
                waveTimer = CHASE_TIME;
            }

            // Если это вторая волна
            else if (currentWave == 2)
            {
                // Запишет в таймер самое большое время спокойствия призраков
                waveTimer = static_cast<unsigned short>(SECOND_SCATTER_TIME / pow(2, level));
            }

            else
            {
                // В другом случае запишет самый маленький период спокойствия призраков
                waveTimer = static_cast<unsigned short>(FIRST_SCATTER_TIME / pow(2, level));
            }
        }
        else
        {
            // Уменьшает таймер до тех пор, пока он снова не будет равен 0
            waveTimer--;
        }
    }


    // Обновляет всех призраков
    for (Ghost& ghost: ghosts)
    {
        ghost.update(level, i_map, ghosts[0], pacman);
    }

}
