#include "explosive_tower.h"
#include "explosive_bullet.h"
#include "entity_manager.h"

ExplosiveTower::ExplosiveTower(TowerSlot* slot, const ResourceManager& RM)
: Tower(slot)
{
    m_life = m_max_life = 15;
    m_damage = 10;
    m_cooldown = m_fire_rate = 2.5f;
    m_range = 250;
    m_texture = RM.get_texture(TextureType::EXPLOSIVE_IDLE);
}

void ExplosiveTower::create_bullet()
{
    m_EntityManager->createBullet(new ExplosiveBullet(get_position(),
                                                 m_target,
                                                 m_EntityManager->m_ResourceManager));
}