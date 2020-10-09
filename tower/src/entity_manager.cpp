#include "entity_manager.h"

#include "bullet.h"
#include "tower.h"
#include "enemy.h"
#include "button.h"

void    EntityManager::createTower(Tower* tower)
{
    m_towers.push_back(tower);
}

void    EntityManager::createEnemy(Enemy* enemy)
{
    m_enemies.push_back(enemy);
}

void    EntityManager::createBullet(Bullet* bullet)
{
    m_bullets.push_back(bullet);
}

void    EntityManager::createButton(Button* button)
{
    m_buttons.push_back(button);
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

    //if (m_enemies.size() > 1)
    //    delete m_enemies.back(); // Do segfault
}
void    EntityManager::destroyBullet(Bullet* bullet)
{
    *bullet = *m_bullets.back();
    m_bullets.pop_back();

    // if (m_bullets.size() > 1)
    //     delete m_bullets.back(); // Do segfault
}

void    EntityManager::destroyButton(Button* button)
{
    *button = *m_buttons.back();
    m_buttons.pop_back();

    // if (m_bullets.size() > 1)
    //     delete m_bullets.back(); // Do segfault
}