#include "enemy.h"

//std::vector<Vector2> Enemy::m_waypoints;
std::array<Vector2, 26> Enemy::m_waypoints;
int Enemy::m_waypoints_count = 0;


Enemy::Enemy(Vector2 position) : Entity(position)
{
    m_rect = {position, 32, 32};
}

void Enemy::move(float delta_time)
{
    if (m_current_waypoint == m_waypoints_count)
        return;
        
    m_direction = (m_waypoints[m_current_waypoint] - m_position).normalize();
    if (m_position.get_distance(m_waypoints[m_current_waypoint]) <= 10)
        m_current_waypoint++;

    m_position += m_direction * m_speed * delta_time;
}

int Enemy::get_reward() const
{
    return m_reward;
}

float  Enemy::get_halfsize() const
{
    return m_rect.halfheight;
}
