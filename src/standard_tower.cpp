#include "standard_tower.h"

StandardTower::StandardTower(Vector2 position, const ResourceManager& RM)
: Tower(position)
{
    m_life = Life(25);
    m_damage = 5;
    m_cooldown = m_fire_rate = 1.f;
    m_range = 500;
    m_texture = RM.get_texture(TextureType::STANDARD_IDLE);
}

void StandardTower::update(float delta_time)
{
    Tower::update(delta_time);
}