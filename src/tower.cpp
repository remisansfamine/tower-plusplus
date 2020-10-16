#include "tower.h"

#include "game.h"
#include "entity_manager.h"
#include "enemy.h"
#include "collisions.h"

std::vector<TowerSlot> Tower::m_towerSlots;

Tower::Tower(TowerSlot* slot) : Entity(slot->getPosition()), m_slot(slot) { }

Tower::~Tower()
{
    Game::m_money += (m_life / m_max_life) * m_price / 2;

    if (m_slot)
        m_slot->m_isAvailable = true;
}

void    Tower::update(float delta_time, GPLib* m_gp)
{
    Vector2 mousePos = gpMousePosition(m_gp);

    if (c_point_box(mousePos, getRect()))
    {
        if (gpMouseButtonIsPressed(m_gp, GP_MOUSE_BUTTON_2))
            m_shouldDestroy = true;

        if (gpMouseButtonIsPressed(m_gp, GP_MOUSE_BUTTON_1) && Game::m_money >= m_price * 1.5f)
            upgrade();
    }

    if (m_entityManager->getEnemyCount() != 0)
        m_life -= delta_time;

    m_cooldown -= delta_time;

    if (m_target)
    {
        if (c_circle_box({m_range, m_position}, m_target->getRect()) &&
        !m_target->m_shouldDestroy)
        {
            setAngle(m_target->getPosition());

            shoot();
        }
        else
            m_target = nullptr;
    }
    else
        getTarget();

    if (m_life <= 0)
        m_shouldDestroy = true;
}

void    Tower::getTarget()
{
    for (Enemy* enemy : m_entityManager->m_enemies)
    {
        if (enemy && !enemy->m_shouldDestroy &&
        c_circle_point(getCircle(), enemy->getPosition()))
        {
            m_target = enemy;
            break;
        }
    }
}

void    Tower::shoot()
{
    if (m_cooldown <= 0)
    {
        createBullet();

        m_cooldown = m_fireRate;
    }
}

void    Tower::upgrade()
{
    m_price *= 1.5f;
    Game::m_money -= m_price;

    m_max_life *= 1.1f;
    m_life = m_max_life;
    m_fireRate *= 1.1f;
    m_range *= 1.1f;

    m_level++;
}

void    Tower::draw(GPLib* gp)
{
    drawLifebar(gp);

    gpDrawTextureEx(gp, m_texture, {TILE_SIZE, TILE_SIZE}, m_position, m_angle, {1, 1}, nullptr, GP_CWHITE);
}

void    Tower::drawLifebar(GPLib* gp) const
{
    GPRect lifebar = {m_position.x - TILE_SIZE / 2, m_position.y + TILE_SIZE / 2 + 5, TILE_SIZE, TILE_SIZE / 8};
    gpDrawRectFilled(gp, lifebar, GP_CWHITE);

    lifebar.w *= m_life / m_max_life;
    gpDrawRectFilled(gp, lifebar, GPColor{0, 0.75, 0.5, 1});

    lifebar.w /= m_life / m_max_life;
    gpDrawRect(gp, lifebar, GP_CBLACK);
}

Circle Tower::getCircle() const
{
    return Circle{m_range, m_position};
}

Rectangle Tower::getRect() const
{
    return Rectangle{getPosition(), TILE_SIZE / 2, TILE_SIZE / 2};
}