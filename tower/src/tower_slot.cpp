#include "tower_slot.h"

TowerSlot::TowerSlot(Vector2 position) : Entity(position)
{
    collision = {position, 50, 50};
}

const Rectangle TowerSlot::get_collision() const
{
    return collision;
}