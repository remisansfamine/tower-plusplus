#include "enemy.h"

#include "game.h"

std::vector<Vector2> Enemy::m_waypoints(26);

Enemy::Enemy(Vector2 position) : Entity(position) { }

void    Enemy::move(float delta_time)
{
    m_stunCooldown -= delta_time;

    if (m_position.getDistance(m_waypoints[m_currentWaypoint]) <= 16)
    {   
        if (++m_currentWaypoint == Enemy::m_waypoints.size())
            reachCastle();
    }

    m_direction = (m_waypoints[m_currentWaypoint] - m_position).normalize();

    m_position += m_direction * delta_time * m_speed / (m_stunCooldown > 0 ? 2 : 1);
}

int     Enemy::getReward() const
{
    return m_reward;
}

Rectangle   Enemy::getRect() const
{
    return Rectangle{m_position, m_rect.halfwidth, m_rect.halfheight};
}

float  Enemy::getHalfsize() const
{
    return m_rect.halfheight;
}

void    Enemy::update(float deltaTime)
{
    move(deltaTime);

    setAngle(m_waypoints[m_currentWaypoint]);

    if (m_life <= 0)
    {
        Game::m_money += getReward();
        m_shouldDestroy = true;
    }
}

void    Enemy::stun(float cooldown)
{
    m_stunCooldown = cooldown;
}

void    Enemy::draw(GPLib* gp)
{
    gpDrawTextureEx(gp, m_texture, {TILE_SIZE, TILE_SIZE}, m_position, m_angle, {1, 1}, nullptr, GP_CWHITE);
        
    if (m_life >= m_max_life || m_life <= 0)
        return;

    drawLifebar(gp);
}

void    Enemy::drawLifebar(GPLib* gp) const
{
    GPRect lifebar = {m_position.x - TILE_SIZE / 2, m_position.y + TILE_SIZE / 2 + m_libebarOffset, TILE_SIZE, TILE_SIZE / 8};
    gpDrawRectFilled(gp, lifebar, GP_CWHITE);

    lifebar.w *= m_life / m_max_life;
    gpDrawRectFilled(gp, lifebar, GPColor{1, 0, 0, 1});

    lifebar.w /= m_life / m_max_life;
    gpDrawRect(gp, lifebar, GP_CBLACK);
}

void    Enemy::reachCastle()
{
    m_shouldDestroy = true;

    Game::m_money = clamp(Game::m_money - getReward() * 1.25f, 0, getReward() * 1.25f);

    m_entityManager->m_castle.m_life -= m_damage;

    if (m_entityManager->m_castle.m_life <= 0)
        m_entityManager->m_gameState = GameState::LOSE;
}