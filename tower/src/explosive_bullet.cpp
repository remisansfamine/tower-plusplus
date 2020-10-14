#include "explosive_bullet.h"

#include "collisions.h"

ExplosiveBullet::ExplosiveBullet(Vector2 position, Enemy* enemy, float damage, const ResourceManager& RM)
: Bullet(position, enemy, damage, RM)
{
    
}

bool ExplosiveBullet::collision_check(const Enemy& enemy) const
{
    return c_circle_box(Circle{m_range, get_position()}, enemy.get_rect());
}