#include "healer_enemy.h"

HealerEnemy::HealerEnemy(Vector2 position, const RessourceManager& RM) : Enemy(position)
{
    m_life = Life(25);
    m_damage = 5;
    m_speed = 400;
    m_texture = RM.get_texture((unsigned int)TextureType::ENEMY_IDLE);
}

void HealerEnemy::update()
{
    move();
}