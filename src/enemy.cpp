#include "enemy.h"

//std::vector<Vector2> Enemy::m_waypoints;
std::array<Vector2, 9> Enemy::m_waypoints;

Enemy::Enemy(Vector2 position) : Entity(position) { }

void Enemy::move(float delta_time)
{
    if (m_current_waypoint == m_waypoints.size())
        return;
        
    m_direction = (m_waypoints[m_current_waypoint] - m_position).normalize();
    if (m_position.get_distance(m_waypoints[m_current_waypoint]) <= 10)
        m_current_waypoint++;

    m_position += m_direction * m_speed * delta_time;
}