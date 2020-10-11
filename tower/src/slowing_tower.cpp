#include "slowing_tower.h"

SlowingTower::SlowingTower(Vector2 position, const ResourceManager& RM)
: Tower(position)
{
    m_life = Life(40);
    m_damage = 2.5f;
    m_cooldown = m_fire_rate = 0.75f;
    m_range = 500;
    m_texture = RM.get_texture(TextureType::TOWER_IDLE);
}

void SlowingTower::update(float delta_time)
{
    m_cooldown -= delta_time;
}