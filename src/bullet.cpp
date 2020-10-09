#include "bullet.h"

Bullet::Bullet(Vector2 position, Enemy* enemy, float damage, const ResourceManager& RM)
: Entity(position), m_target(enemy)
{
    m_texture = RM.get_texture(TextureType::BULLET);
    m_speed = 250;
    m_damage = damage;
}

void Bullet::update(float delta_time) 
{
    move(delta_time);
}

void Bullet::move(float delta_time)
{
    m_direction = (m_target->get_position() - m_position).normalize();
    m_position += m_direction * m_speed * delta_time;
}