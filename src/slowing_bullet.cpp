#include "slowing_bullet.h"

SlowingBullet::SlowingBullet(Vector2 position, Enemy* enemy, float damage, const ResourceManager& RM)
: Bullet(position, enemy, damage, RM)
{
    
}

void SlowingBullet::hit(Enemy& enemy)
{
    Bullet::hit(enemy);
    enemy.stun(2.5f);
}
