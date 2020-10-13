#include <fstream>
#include <string>

#include "resource_manager.h"
#include "entity_manager.h"

#include "bullet.h"
#include "tower.h"
#include "strong_enemy.h"
#include "healer_enemy.h"
#include "weak_enemy.h"

#include "button.h"

EntityManager::EntityManager(const ResourceManager& RM)
: m_ResourceManager(RM)
{
    m_spawn_cooldown = m_spawn_rate;

    std::ifstream  stream("media/spawn_pattern.txt");

    for (std::string line; getline(stream, line);)
        m_spawn_pattern += line + "\n";
}

EntityManager::~EntityManager()
{
    for (Enemy* enemy : m_enemies)
        destroyEnemy(enemy);

    for (Tower* tower : m_towers)
        destroyTower(tower);

    for (Bullet* bullet : m_bullets)
        destroyBullet(bullet);

    for (Button* button : m_buttons)
        destroyButton(button);
}

void    EntityManager::update(float delta_time)
{
    m_spawn_cooldown -= delta_time;

    if (m_spawn_cooldown < 0)
        spawn_enemies();
}

void    EntityManager::spawn_enemies()
{
    m_spawn_cooldown = m_spawn_rate;

    switch (m_spawn_pattern[m_spawn_index++])
    {
        case 'W':
            createEnemy(new WeakEnemy(Enemy::m_waypoints[0], m_ResourceManager));
            break;
        
        case 'H':
            createEnemy(new HealerEnemy(Enemy::m_waypoints[0], m_ResourceManager));
            break;

        case 'S':
            createEnemy(new StrongEnemy(Enemy::m_waypoints[0], m_ResourceManager));
            break;
        
        case ' ':
            m_spawn_cooldown = 2.5f;
            break;

        case '\n':
            m_spawn_cooldown = (m_wave_timer * m_spawn_index);
            break;

        default:
            m_spawn_cooldown = m_spawn_rate;
    }
}

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
    if (m_towers.size() == 0)
         return;

    *tower = *m_towers.back();
    delete m_towers.back();
    m_towers.pop_back();
}
void    EntityManager::destroyEnemy(Enemy* enemy)
{
    if (m_enemies.size() == 0)
         return;

    *enemy = *m_enemies.back();
    delete m_enemies.back();
    m_enemies.pop_back();
}
void    EntityManager::destroyBullet(Bullet* bullet)
{
     if (m_bullets.size() == 0)
         return;

    *bullet = *m_bullets.back();
    delete m_bullets.back();
    m_bullets.pop_back();
}

void    EntityManager::destroyButton(Button* button)
{
    if (m_buttons.size() == 0)
         return;

    *button = *m_buttons.back();
    delete m_buttons.back();
    m_buttons.pop_back();
}