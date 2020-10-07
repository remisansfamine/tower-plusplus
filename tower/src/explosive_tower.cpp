#include "explosive_tower.h"

ExplosiveTower::ExplosiveTower(Vector2 position, const RessourceManager& RM) : Tower(position)
{
    m_life = Life(15);
    m_damage = 10;
    m_cooldown = m_fire_rate = 2.5f;
    m_range = 250;
    m_texture = RM.get_texture((unsigned int)TextureType::TOWER_IDLE);
}

void ExplosiveTower::update()
{
    m_cooldown -= delta_time;   
}