#include <fstream>
#include <string>

#include "resource_manager.h"
#include "entity_manager.h"

#include "bullet.h"
#include "tower.h"
#include "strong_enemy.h"
#include "healer_enemy.h"
#include "weak_enemy.h"

EntityManager::EntityManager(const ResourceManager& RM)
: m_ResourceManager(RM)
{
    m_spawn_cooldown = m_spawn_rate;

    std::ifstream  stream("media/spawn_pattern.txt");

    for (std::string line; getline(stream, line); m_wave_count++)
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
}

void    EntityManager::update(float delta_time)
{
    m_spawn_cooldown -= delta_time;

    if (m_spawn_cooldown < 0 && m_wave_index < m_wave_count)
        spawn_enemies();

    for (Enemy* enemy : m_enemies)
    {
        if (!enemy)
            continue;

        enemy->update(delta_time);
    }

    for (Bullet* bullet : m_bullets)
    {
        if (!bullet)
            continue;

        bullet->update(delta_time);
    }
}

void    EntityManager::draw(GPLib* gp) const
{
    for (Tower* tower : m_towers)
    {
        if (!tower)
            continue;

        tower->draw(gp);
    }

    for (Bullet* bullet : m_bullets)
    {
        if (!bullet)
            continue;

        bullet->draw(gp);
    }

    for (Enemy* enemy : m_enemies)
    {
        if (!enemy)
            continue;

        enemy->draw(gp);
    }
}

void EntityManager::clear()
{
    for (Tower* tower : m_towers)
    {
        if (tower && tower->m_should_destroy)
            destroyTower(tower);
    }

    for (Bullet* bullet : m_bullets)
    {
        if (bullet && bullet->m_should_destroy)
            destroyBullet(bullet);
    }

    for (Enemy* enemy : m_enemies)
    {
        if (enemy && enemy->m_should_destroy)
            destroyEnemy(enemy);
    }
}

void    EntityManager::spawn_enemies()
{
    is_in_wave = true;
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
            if (m_enemies.size() == 0)
            {
                m_spawn_cooldown = (m_wave_timer * m_wave_index++);
                is_in_wave = false;
            }
            else
                m_spawn_index--;
            break;

        default:
            m_spawn_cooldown = m_spawn_rate;
    }
}

void    EntityManager::createTower(Tower* tower)
{
    m_towers.push_back(tower);
    tower->m_EntityManager = this;
}

void    EntityManager::createEnemy(Enemy* enemy)
{
    m_enemies.push_back(enemy);
    enemy->m_EntityManager = this;
}

void    EntityManager::createBullet(Bullet* bullet)
{
    m_bullets.push_back(bullet);
    bullet->m_EntityManager = this;
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

const int     EntityManager::get_timer() const
{
    return m_spawn_cooldown < 0 || is_in_wave ? 0 : m_spawn_cooldown;
}

const int   EntityManager::get_wave_index() const
{
    return m_wave_index;
}

const int   EntityManager::get_wave_count() const
{
    return m_wave_count;
}
