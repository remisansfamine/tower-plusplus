#include "bullet.h"

#include "entity_manager.h"

#include "collisions.h"

Bullet::Bullet(Vector2 position, Enemy* enemy, float damage, const ResourceManager& RM)
: Entity(position), m_target(enemy)
{
    m_texture = RM.get_texture(TextureType::BULLET);
    m_speed = 600;
    m_damage = damage;
}

void Bullet::update(float delta_time) 
{
    move(delta_time);

    Vector2 vect = m_target->get_position() - get_position();

    m_angle = atan2(vect.y, vect.x);

    for (Enemy* enemy : m_EntityManager->m_enemies)
    {
        if (!enemy)
            continue;

        if (collision_check(*enemy))
            hit(*enemy);
    }

    if (!m_target || m_target->m_should_destroy)
        m_should_destroy = true;
}

void Bullet::move(float delta_time)
{
    m_direction = (m_target->get_position() - m_position).normalize();
    m_position += m_direction * m_speed * delta_time;
}

void Bullet::hit(Enemy& enemy)
{
    enemy.m_life.m_life -= get_damage();
    m_should_destroy = true;
}

bool Bullet::collision_check(const Enemy& enemy) const
{
    return c_point_box(get_position(), Rectangle{enemy.get_position(), enemy.get_halfsize(), enemy.get_halfsize()});
}
