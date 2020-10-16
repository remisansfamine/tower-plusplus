#include "bullet.h"

#include "entity_manager.h"
#include "collisions.h"

Bullet::Bullet(Vector2 position, Enemy* enemy)
: Entity(position), m_target(enemy) { }

void Bullet::update(float deltaTime) 
{
    move(deltaTime);

    setAngle(m_target->getPosition());

    for (Enemy* enemy : m_entityManager->m_enemies)
    {
        if (enemy && c_point_box(getPosition(), enemy->getRect()))
            hit(*enemy);
    }

    if (!m_target || m_target->m_shouldDestroy)
        m_shouldDestroy = true;
}

void Bullet::move(float delta_time)
{
    m_direction = (m_target->getPosition() - m_position).normalize();
    m_position += m_direction * m_speed * delta_time;
}

void Bullet::hit(Enemy& enemy)
{
    enemy.m_life -= m_damage;
    m_shouldDestroy = true;
}

void Bullet::draw(GPLib* gp)
{
    gpDrawTextureEx(gp, m_texture, {64, 64}, m_position, m_angle,
                   {1, 1}, nullptr, GP_CWHITE);
}