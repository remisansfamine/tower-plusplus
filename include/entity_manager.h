#pragma once

#include <vector>

class Enemy;
class Tower;
class Bullet;
class Button;

class EntityManager
{
    public:
        std::vector<Enemy*>     m_enemies;
        std::vector<Tower*>     m_towers;
        std::vector<Bullet*>    m_bullets;
        std::vector<Button*>    m_buttons;

        void    createTower(Tower*);
        void    createEnemy(Enemy*);
        void    createBullet(Bullet*);
        void    createButton(Button*);

        void    destroyTower(Tower*);
        void    destroyEnemy(Enemy*);
        void    destroyBullet(Bullet*);
        void    destroyButton(Button*);
};