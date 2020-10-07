#include "standard_tower.h"

StandardTower::StandardTower(Vector2 position, const RessourceManager& RM) : Tower(position)
{
    m_life = Life(25);
    m_damage = 5;
    m_cooldown = m_fire_rate = 10;
    m_range = 75;
    m_texture = RM.get_texture((unsigned int)TextureType::TOWER_IDLE);
}

void StandardTower::update()
{
    m_cooldown -= delta_time * 100;
}