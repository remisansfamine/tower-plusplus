#include "explosive_tower.h"

ExplosiveTower::ExplosiveTower(Vector2 position, const ResourceManager& RM)
: Tower(position)
{
    m_life = Life(15);
    m_damage = 10;
    m_cooldown = m_fire_rate = 2.5f;
    m_range = 250;
    m_texture = RM.get_texture(TextureType::EXPLOSIVE_IDLE);
}

void ExplosiveTower::update(float delta_time)
{
    Tower::update(delta_time);
}