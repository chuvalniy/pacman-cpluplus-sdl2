#include "Map.h"


Map::Map(std::string spritePath, SDL_Renderer* ren)
{
    renderer = ren;
    texture = SpriteLoader::loadTexture(spritePath, ren);
}

Map::~Map()
{

}

std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> Map::loadMap(const std::array<std::string, MAP_HEIGHT>& m_mapSketch, Pacman *pacman, std::array<Vector2, 4> &ghostPosition)
{
// Итоговая "мнимая" карта (заполняется клетками)
    std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> outputMap {};



    for (unsigned char i = 0; i < MAP_HEIGHT; i++)
    {
        for (unsigned char j = 0; j < MAP_WIDTH; j++)
        {
            outputMap[j][i] = Cell::Empty;

            // В зависимости от символа устанавливает определенный тип клетки
            switch (m_mapSketch[i][j])
            {
                case '#': // Стена
                    {
                        outputMap[j][i] = Cell::Wall;
                        break;
                    }
                case '=': // Дверь
                    {
                        outputMap[j][i] = Cell::Door;
                        break;
                    }
                case '.': // Еда
                    {
                        outputMap[j][i] = Cell::Food;
                        break;
                    }
                case 'o': // Бафф
                    {
                        outputMap[j][i] = Cell::Buff;
                        break;
                    }
                case 'P': // Пакман
                    {
                        pacman->setPosition(CELL_SIZE * j, CELL_SIZE * i);
                        break;
                    }
                case '0': // Призраки
                    {
                        ghostPosition[0].x = CELL_SIZE * j;
                        ghostPosition[0].y = CELL_SIZE * i;
                        break;
                    }
                case '1':
                    {
                        ghostPosition[1].x = CELL_SIZE * j;
                        ghostPosition[1].y = CELL_SIZE * i;

                        break;
                    }
                case '2':
                    {
                        ghostPosition[2].x = CELL_SIZE * j;
                        ghostPosition[2].y = CELL_SIZE * i;
                        break;
                    }
                case '3':
                    {
                        ghostPosition[3].x = CELL_SIZE * j;
                        ghostPosition[3].y = CELL_SIZE * i;
                        break;
                    }
            }
        }
    }
    return outputMap;
}

void Map::drawMap(const std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& mapLoader)
{
    SDL_Rect rect; // Позиция где отрисовывать поверхности
    SDL_Rect clip; // Выбор определенных координат поверхности

    for (unsigned char i = 0; i < MAP_WIDTH; i++)
    {
        for (unsigned char j = 0; j < MAP_HEIGHT; j++)
        {
            clip = { CELL_SIZE, CELL_SIZE, CELL_SIZE, CELL_SIZE };
            rect = { i*CELL_SIZE, j*CELL_SIZE, CELL_SIZE, CELL_SIZE };

            switch (mapLoader[i][j])
            {
                case Cell::Food:
                {
                    clip.x = 0;
                    SDL_RenderCopy(renderer, texture, &clip, &rect);
                    break;
                }
                case Cell::Door:
                {
                    clip.x = 2 * CELL_SIZE;
                    SDL_RenderCopy(renderer, texture, &clip, &rect);
                    break;
                }
                case Cell::Buff:
                {
                    SDL_RenderCopy(renderer, texture, &clip, &rect);
                    break;
                }
                case Cell::Wall:
                {
                    // Разные текстуры для стен
                    bool down = 0;
                    bool left = 0;
                    bool right = 0;
                    bool up = 0;

                    if (j < MAP_HEIGHT - 1)
                    {
                        if (Cell::Wall == mapLoader[i][j + 1])
                        {
                            down = 1;
                        }
                    }

                    if (i > 0)
                    {
                        if (Cell::Wall == mapLoader[i - 1][j])
                        {
                            left = 1;
                        }
                    }
                    else
                    {
                        left = 1;
                    }

                    if (i < MAP_WIDTH - 1)
                    {
                        if (Cell::Wall == mapLoader[i + 1][j])
                        {
                            right = 1;
                        }
                    }
                    else
                    {
                        right = 1;
                    }

                    if (j > 0)
                    {
                        if (Cell::Wall == mapLoader[i][j - 1])
                        {
                            up = 1;
                        }
                    }

                    clip.x = CELL_SIZE * (down + 2 * (left + 2 * (right + 2 * up)));
                    clip.y = 0;

                    SDL_RenderCopy(renderer, texture, &clip, &rect);
                    break;
                }
            }
        }
    }
}

//
//std::array<Vector2, 4> Map::getGhostPosition()
//{
//    return ghostPosition;
//}
