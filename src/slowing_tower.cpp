#include "slowing_tower.h"

#include "slowing_bullet.h"
#include "entity_manager.h"

SlowingTower::SlowingTower(TowerSlot* slot, const ResourceManager& RM)
: Tower(slot)
{
    m_price = 7;
    m_life = m_max_life = 70;
    m_damage = 2.5f;
    m_cooldown = m_fireRate = 0.25f;
    m_range = 175;
    m_texture = RM.getTexture(TextureType::SLOWING_IDLE);
}

void SlowingTower::createBullet()
{
    m_entityManager->createBullet(new SlowingBullet(getPosition(),
                                                    m_target,
                                                    m_entityManager->m_resourceManager));
}