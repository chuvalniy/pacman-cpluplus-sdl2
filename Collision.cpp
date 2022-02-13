#include "Collision.h"

bool checkCollision(bool isFood, bool isBuff, bool useDoor, int i_x, int i_y, std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& map)
{
    bool output = 0;

    // Получение точной позиции
    float cell_x = i_x / static_cast<float>(CELL_SIZE);
    float cell_y = i_y / static_cast<float>(CELL_SIZE);


    //
    for (unsigned char i = 0; i < 4; i++)
	{
		short x = 0;
		short y = 0;

		switch (i)
		{
			case 0: // Верхняя левая клетка
			{
				x = static_cast<short>(floor(cell_x));
				y = static_cast<short>(floor(cell_y));
				break;
			}
			case 1: // Верхняя правая клетка
			{
				x = static_cast<short>(ceil(cell_x));
				y = static_cast<short>(floor(cell_y));
				break;
			}
			case 2: // Нижняя левая клетка
			{
				x = static_cast<short>(floor(cell_x));
				y = static_cast<short>(ceil(cell_y));

				break;
			}
			case 3: // Нижняя правая клетка
			{
				x = static_cast<short>(ceil(cell_x));
				y = static_cast<short>(ceil(cell_y));
			}
		}

		// Если позиции персонажей внутри карты
        if (0 <= x && 0 <= y && MAP_HEIGHT > y && MAP_WIDTH > x)
		{
			if (isFood == 0 && isBuff == 0) // Проверка на коллизию ТОЛЬКО со стеной
			{
				if (Cell::Wall == map[x][y])
				{
					output = 1;
				}
				else if (useDoor == 0 && Cell::Door == map[x][y])
                {
                    output = 1;
                }
			}

			else if (isFood == 0 && isBuff == 1) // Проверка на коллизию ТОЛЬКО со баффом
            {
                if (Cell::Buff == map[x][y])
                {
                    output = 1;
                    map[x][y] = Cell::Empty;
                }
            }
            else if (isFood == 1 && isBuff == 0) // Проверка на коллизию ТОЛЬКО со едой
            {
                if (Cell::Food == map[x][y])
                {
                    output = 1;
                    map[x][y] = Cell::Empty;
                }
            }
		}
	}

	return output;
}
