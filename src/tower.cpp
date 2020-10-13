#include "tower.h"

std::vector<TowerSlot> Tower::m_tower_slots;

Tower::Tower(Vector2 position) : Entity(position) { }

void Tower::update(float delta_time)
{
    m_cooldown -= delta_time;
}