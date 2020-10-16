#include "standard_tower.h"

#include "entity_manager.h"
#include "standard_bullet.h"

StandardTower::StandardTower(TowerSlot* slot, const ResourceManager& RM)
: Tower(slot)
{
    m_price = 5;
    m_life = m_max_life = 120;
    m_damage = 5;
    m_cooldown = m_fireRate = 1.f;
    m_range = 150;
    m_texture = RM.getTexture(TextureType::STANDARD_IDLE);
}

void StandardTower::createBullet()
{
    m_entityManager->createBullet(new StandardBullet(getPosition(),
                                                     m_target, m_entityManager->m_resourceManager));
}