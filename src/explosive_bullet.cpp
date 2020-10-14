#include "explosive_bullet.h"
#include "entity_manager.h"
#include "collisions.h"

ExplosiveBullet::ExplosiveBullet(Vector2 position, Enemy* enemy, const ResourceManager& RM)
: Bullet(position, enemy)
{
    m_texture = RM.get_texture(TextureType::EXPLOSIVE_BULLET);
    m_damage = 10.f;
}


void ExplosiveBullet::hit(Enemy& enemy)
{
    for (Enemy* enemy : m_EntityManager->m_enemies)
    {
        if (enemy && c_circle_box(Circle{m_range, get_position()}, enemy->get_rect()))
            Bullet::hit(*enemy);
    }
}

void ExplosiveBullet::draw(GPLib* gp)
{
    Bullet::draw(gp);
    gpDrawCircleFilled(gp, m_position, m_range, GPColor{1.f, 0.f, 0.f, 0.1f});
}
