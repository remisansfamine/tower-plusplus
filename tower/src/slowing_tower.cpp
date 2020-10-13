#include "slowing_tower.h"

SlowingTower::SlowingTower(Vector2 position, const ResourceManager& RM)
: Tower(position)
{
    m_life = Life(40);
    m_damage = 2.5f;
    m_cooldown = m_fire_rate = 0.25f;
    m_range = 175;
    m_texture = RM.get_texture(TextureType::SLOWING_IDLE);
}

void SlowingTower::update(float delta_time)
{
    Tower::update(delta_time);
}