#include "slowing_bullet.h"

SlowingBullet::SlowingBullet(Vector2 position, Enemy* enemy, const ResourceManager& RM)
: Bullet(position, enemy)
{
    m_speed = 800;
    m_texture = RM.get_texture(TextureType::SLOWING_BULLET);
    m_damage = 2.5f;
}

void SlowingBullet::hit(Enemy& enemy)
{
    Bullet::hit(enemy);
    enemy.stun(2.5f);
}