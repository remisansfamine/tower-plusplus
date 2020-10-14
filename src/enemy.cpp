#include "enemy.h"
#include <iostream>

#include "game.h"

std::array<Vector2, 26> Enemy::m_waypoints;
int Enemy::m_waypoints_count = 0;

Enemy::Enemy(Vector2 position) : Entity(position) { }

void Enemy::move(float delta_time)
{
    m_stun_cooldown -= delta_time;

    if (m_current_waypoint == m_waypoints_count)
        return;
        
    m_direction = (m_waypoints[m_current_waypoint] - m_position).normalize();

    if (m_position.get_distance(m_waypoints[m_current_waypoint]) <= 16)
        m_current_waypoint++;

    m_position += m_direction * delta_time * m_speed / (m_stun_cooldown > 0 ? 2 : 1);
}

int Enemy::get_reward() const
{
    return m_reward;
}

Rectangle   Enemy::get_rect() const
{
    return Rectangle{m_position, m_rect.halfwidth, m_rect.halfheight};
}


float  Enemy::get_halfsize() const
{
    return m_rect.halfheight;
}

int     Enemy::get_lifebar_offert() const
{
    return m_libebar_offset;
}

void    Enemy::update(float delta_time)
{
    move(delta_time);

    if (m_life.m_life <= 0)
    {
        Game::m_money += get_reward();
        m_should_destroy = true;
    }
}

void    Enemy::stun(float cooldown)
{
    m_stun_cooldown = cooldown;
}
