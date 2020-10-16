#include "tower_slot.h"

TowerSlot::TowerSlot(Vector2 position) : m_position(position)
{
    m_collision = {position, 50, 50};
}

const Rectangle TowerSlot::getCollision() const
{
    return m_collision;
}

const Vector2   TowerSlot::getPosition() const
{
    return m_position;
}
