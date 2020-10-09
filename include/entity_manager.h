#pragma once

#include <vector>

class Enemy;
class Tower;
class Bullet;

class EntityManager
{
    public:
        std::vector<Enemy*>     m_enemies;
        std::vector<Tower*>     m_towers;
        std::vector<Bullet*>    m_bullets;

        void    createTower(Tower*);
        void    createEnemy(Enemy*);
        void    createBullet(Bullet*);

        void    destroyTower(Tower*);
        void    destroyEnemy(Enemy*);
        void    destroyBullet(Bullet*);
};