#include "explosive_bullet.h"

#include "entity_manager.h"
#include "collisions.h"

ExplosiveBullet::ExplosiveBullet(Vector2 position, Enemy* enemy,
                                 const ResourceManager& RM)
: Bullet(position, enemy)
{
    m_speed = 300;
    m_texture = RM.getTexture(TextureType::EXPLOSIVE_BULLET);
    m_damage = 10.f;
}


void    ExplosiveBullet::hit(Enemy& enemy)
{
    for (Enemy* enemy : m_entityManager->m_enemies)
    {
        if (enemy && c_circle_box(Circle{m_range, getPosition()}, enemy->getRect()))
            Bullet::hit(*enemy);
    }
}

void    ExplosiveBullet::draw(GPLib* gp)
{
    Bullet::draw(gp);
    gpDrawCircleFilled(gp, m_position, m_range, GPColor{1.f, 0.f, 0.f, 0.1f});
}
