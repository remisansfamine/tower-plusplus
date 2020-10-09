#include "tower_slot.h"

TowerSlot::TowerSlot(Vector2 position) : m_position(position)
{
    m_collision = {position, 50, 50};
}

const Rectangle TowerSlot::get_collision() const
{
    return m_collision;
}

const Vector2   TowerSlot::get_position() const
{
    return m_position;
}
