#include "weak_enemy.h"

WeakEnemy::WeakEnemy(Vector2 position, const ResourceManager& RM) : Enemy(position)
{
    m_life = m_max_life = 25;
    m_reward = 3;
    m_damage = 10;
    m_speed = 125;
    m_texture = RM.getTexture(TextureType::WEAK_ENEMY_IDLE);
    m_direction = Vector2(5, 3, true);
}

void WeakEnemy::update(float delta_time)
{
    Enemy::update(delta_time);
}