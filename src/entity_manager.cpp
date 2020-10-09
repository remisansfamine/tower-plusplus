#include "entity_manager.h"

#include "bullet.h"
#include "tower.h"
#include "enemy.h"

void    EntityManager::createTower(Tower*)
{

}

void    EntityManager::createEnemy(Enemy*)
{

}

void    EntityManager::createBullet(Bullet*)
{

}

void    EntityManager::destroyTower(Tower* tower)
{
    *tower = *m_towers.back();
    m_towers.pop_back();

    // if (m_towers.size() > 1)
    //     delete m_towers.back(); // Do segfault
}
void    EntityManager::destroyEnemy(Enemy* enemy)
{
    *enemy = *m_enemies.back();
    m_enemies.pop_back();
}
void    EntityManager::destroyBullet(Bullet* bullet)
{
    *bullet = *m_bullets.back();
    m_bullets.pop_back();
}