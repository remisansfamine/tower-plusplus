#include "strong_enemy.h"

StrongEnemy::StrongEnemy(Vector2 position, const ResourceManager& RM) : Enemy(position)
{
    m_life = m_max_life = 50;
    m_reward = 8;
    m_damage = 25;
    m_speed = 50;
    m_texture = RM.get_texture(TextureType::STRONG_ENEMY_IDLE);
}

void StrongEnemy::update(float delta_time)
{
    Enemy::update(delta_time);
}