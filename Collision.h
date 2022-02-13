#pragma once

#include <array>
#include <math.h>
#include "Global.h"

bool checkCollision(bool isFood, bool isBuff, bool useDoor, int i_x, int i_y, std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& map);
