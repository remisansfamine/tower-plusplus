#include "weak_enemy.h"

WeakEnemy::WeakEnemy(Vector2 position, const ResourceManager& RM) : Enemy(position)
{
    m_life = Life(25);
    m_damage = 10;
    m_speed = 250;
    m_texture = RM.get_texture(TextureType::ENEMY_IDLE);
    m_direction = Vector2(5, 3, true);
}

void WeakEnemy::update()
{
    move();
}