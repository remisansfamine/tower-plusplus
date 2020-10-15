#include "slowing_tower.h"

#include "slowing_bullet.h"
#include "entity_manager.h"


SlowingTower::SlowingTower(TowerSlot* slot, const ResourceManager& RM)
: Tower(slot)
{
    m_life = m_max_life = 70;
    m_damage = 2.5f;
    m_cooldown = m_fire_rate = 0.25f;
    m_range = 175;
    m_texture = RM.get_texture(TextureType::SLOWING_IDLE);
}

void SlowingTower::create_bullet()
{
    m_EntityManager->createBullet(new SlowingBullet(get_position(),
                                                 m_target,
                                                 m_EntityManager->m_ResourceManager));
}