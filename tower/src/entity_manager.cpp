#include <fstream>

#include "resource_manager.h"
#include "entity_manager.h"
#include "game.h"

#include "bullet.h"
#include "tower.h"
#include "strong_enemy.h"
#include "healer_enemy.h"
#include "weak_enemy.h"

EntityManager::EntityManager(const ResourceManager& RM, GPLib* gp)
: m_resourceManager(RM), m_gp(gp)
{
    m_spawnCooldown = m_spawnRate;

    std::ifstream  stream("media/spawn_pattern.txt");

    for (std::string line; getline(stream, line); m_waveCount++)
        m_spawnPattern += line + "\n";
}

EntityManager::~EntityManager()
{
    for (Enemy* enemy : m_enemies)
        delete enemy;

    for (Tower* tower : m_towers)
        delete tower;
        
    for (Bullet* bullet : m_bullets)
        delete bullet;
}

void    EntityManager::update(float deltaTime)
{
    m_spawnCooldown -= deltaTime;

    if (m_spawnCooldown < 0 && m_waveIndex <= m_waveCount)
        spawnEnemies();

    for (Enemy* enemy : m_enemies)
    {
        if (enemy)
            enemy->update(deltaTime);
    }

    for (Bullet* bullet : m_bullets)
    {
        if (bullet)
            bullet->update(deltaTime);
    }

    for (Tower* tower : m_towers)
    {
        if (tower)
            tower->update(deltaTime, m_gp);
    }

    // Destroy entities that should be destroyed
    clear();
}

void    EntityManager::draw() const
{
    for (Bullet* bullet : m_bullets)
    {
        if (bullet)
            bullet->draw(m_gp);
    }

    for (Tower* tower : m_towers)
    {
        if (tower)
            tower->draw(m_gp);        
    }

    for (Enemy* enemy : m_enemies)
    {
        if (enemy)
            enemy->draw(m_gp);
    }
}

void EntityManager::clear()
{
    for (int i = 0; i < m_enemies.size(); ++i)
        destroyEnemy(i);

    for (int i = 0; i < m_bullets.size(); ++i)
        destroyBullet(i);

    for (int i = 0; i < m_towers.size(); ++i)
        destroyTower(i);
}

void    EntityManager::spawnEnemies()
{
    m_isInWave = true;
    m_spawnCooldown = m_spawnRate;

    switch (m_spawnPattern[m_spawnIndex++])
    {
        case 'W':
            createEnemy(new WeakEnemy(Enemy::m_waypoints[0], m_resourceManager));
            break;
        
        case 'H':
            createEnemy(new HealerEnemy(Enemy::m_waypoints[0], m_resourceManager));
            break;

        case 'S':
            createEnemy(new StrongEnemy(Enemy::m_waypoints[0], m_resourceManager));
            break;
        
        case ' ':
            m_spawnCooldown = 2.5f;
            break;

        case '\n':
            if (m_enemies.size() == 0 && m_waveIndex < m_waveCount)
            {
                Game::m_money = clamp(Game::m_money, 5, Game::m_money);
                m_waveIndex++;
                m_spawnCooldown = (m_waveTimer * m_waveIndex);
                m_isInWave = false;
            }
            else
                m_spawnIndex--;
            break;

        default:
            m_spawnCooldown = m_spawnRate;
    }
}

#pragma region Entity creators
void    EntityManager::createTower(Tower* tower)
{
    m_towers.push_back(tower);
    tower->m_entityManager = this;
}

void    EntityManager::createEnemy(Enemy* enemy)
{
    m_enemies.push_back(enemy);
    enemy->m_entityManager = this;
}

void    EntityManager::createBullet(Bullet* bullet)
{
    m_bullets.push_back(bullet);
    bullet->m_entityManager = this;
}
#pragma endregion

#pragma region Entity destroyers 
void    EntityManager::destroyTower(int index)
{
    Tower* tower = m_towers[index];
    if (!tower || tower->m_shouldDestroy)
    {
        m_towers[index] = m_towers.back();
        m_towers.pop_back();
        delete tower;
    }
}

void    EntityManager::destroyEnemy(int index)
{
    Enemy* enemy = m_enemies[index];
    if (!enemy || enemy->m_shouldDestroy)
    {
        m_enemies[index] = m_enemies.back();
        m_enemies.pop_back();
        delete enemy;
    }
}

void    EntityManager::destroyBullet(int index)
{
    Bullet* bullet = m_bullets[index];
    if (!bullet ||  bullet->m_shouldDestroy)
    {
        m_bullets[index] = m_bullets.back();
        m_bullets.pop_back();
        delete bullet;
    }
}
#pragma endregion

#pragma region Accessers
const int     EntityManager::getTimer() const
{
    return m_spawnCooldown < 0 || m_isInWave ? 0 : m_spawnCooldown;
}

const int   EntityManager::getWaveIndex() const
{
    return m_waveIndex;
}

const int   EntityManager::getWaveCount() const
{
    return m_waveCount;
}

const unsigned int    EntityManager::getEnemyCount() const
{
    return m_enemies.size();
}
#pragma endregion