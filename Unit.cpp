#include "Unit.h"


Unit::Unit()
{

}

Unit::~Unit()
{

}

void Unit::setPosition(short m_x, short m_y)
{
    Position = { m_x, m_y };
}

Vector2 Unit::getPosition()
{
    return Position;
}
