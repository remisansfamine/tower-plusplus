#include "slowing_tower.h"

SlowingTower::SlowingTower(Vector2 position, const RessourceManager& RM) : Tower(position)
{
    m_life = Life(40);
    m_damage = 2.5f;
    m_cooldown = m_fire_rate = 25;
    m_range = 135;
    m_texture = RM.get_texture((unsigned int)TextureType::TOWER_IDLE);
}

void SlowingTower::update()
{
    m_cooldown -= delta_time * 100;
}