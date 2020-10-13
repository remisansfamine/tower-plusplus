#include "weak_enemy.h"

WeakEnemy::WeakEnemy(Vector2 position, const ResourceManager& RM) : Enemy(position)
{
    m_life = Life(25);
    m_reward = 3;
    m_damage = 10;
    m_speed = 250;
    m_texture = RM.get_texture(TextureType::WEAK_ENEMY_IDLE);
    m_direction = Vector2(5, 3, true);
}

void WeakEnemy::update(float delta_time)
{
    move(delta_time);
}