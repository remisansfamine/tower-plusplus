#include "healer_enemy.h"

HealerEnemy::HealerEnemy(Vector2 position, const ResourceManager& RM) : Enemy(position)
{
    m_life = Life(25);
    m_reward = 5;
    m_damage = 5;
    m_speed = 200;
    m_texture = RM.get_texture(TextureType::HEALER_ENEMY_IDLE);
}

void HealerEnemy::update(float delta_time)
{
    Enemy::update(delta_time);
}