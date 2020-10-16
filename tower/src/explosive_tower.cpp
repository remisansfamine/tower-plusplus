#include "explosive_tower.h"

#include "explosive_bullet.h"
#include "entity_manager.h"

ExplosiveTower::ExplosiveTower(TowerSlot* slot, const ResourceManager& RM)
: Tower(slot)
{
    m_price = 10;
    m_life = m_max_life = 60;
    m_damage = 10;
    m_cooldown = m_fireRate = 2.5f;
    m_range = 250;
    m_texture = RM.getTexture(TextureType::EXPLOSIVE_IDLE);
}

void ExplosiveTower::createBullet()
{
    m_entityManager->createBullet(new ExplosiveBullet(getPosition(),
                                                 m_target,
                                                 m_entityManager->m_resourceManager));
}