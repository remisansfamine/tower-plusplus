#include "strong_enemy.h"

StrongEnemy::StrongEnemy(Vector2 position, const ResourceManager& RM) : Enemy(position)
{
    m_life = Life(50);
    m_damage = 25;
    m_speed = 100;
    m_texture = RM.get_texture((unsigned int)TextureType::ENEMY_IDLE);
}

void StrongEnemy::update()
{
    move();
}