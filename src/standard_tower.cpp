#include "standard_tower.h"

#include "entity_manager.h"
#include "standard_bullet.h"

StandardTower::StandardTower(TowerSlot* slot, const ResourceManager& RM)
: Tower(slot)
{
    m_life = m_max_life = 120;
    m_damage = 5;
    m_cooldown = m_fire_rate = 1.f;
    m_range = 150;
    m_texture = RM.get_texture(TextureType::STANDARD_IDLE);
}

void StandardTower::create_bullet()
{
    m_EntityManager->createBullet(new StandardBullet(get_position(),
                                                     m_target, m_EntityManager->m_ResourceManager));
}