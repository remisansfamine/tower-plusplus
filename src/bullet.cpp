#include "bullet.h"

#include "entity_manager.h"

#include "collisions.h"

Bullet::Bullet(Vector2 position, Enemy* enemy)
: Entity(position), m_target(enemy) { }

void Bullet::update(float delta_time) 
{
    move(delta_time);

    get_angle(m_target->get_position());

    for (Enemy* enemy : m_EntityManager->m_enemies)
    {
        if (!enemy)
            continue;

        if (c_point_box(get_position(), Rectangle{enemy->get_position(), enemy->get_halfsize(), enemy->get_halfsize()}))
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
    enemy.m_life -= m_damage;
    m_should_destroy = true;
}

void Bullet::draw(GPLib* gp)
{
    gpDrawTextureEx(gp, m_texture, {64, 64}, m_position, m_angle, {1, 1}, nullptr, GP_CWHITE);
}