#ifndef COLLISION_H
#define COLLISION_H

#include <array>
#include <math.h>
#include <stdio.h>

#include "Global.h"

// Проверка на коллизию
unsigned char checkCollision(bool isFood, bool isBuff, bool useDoor, int i_x, int i_y, std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& map);

#endif
