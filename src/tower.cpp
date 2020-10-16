#include "tower.h"

#include "map.h"

#include "game.h"

#include "resource_manager.h"
#include "entity_manager.h"
#include "enemy.h"

#include "bullet.h"

#include "collisions.h"

std::vector<TowerSlot> Tower::m_towerSlots;

Tower::Tower(TowerSlot* slot) : Entity(slot->getPosition()), m_slot(slot) { }

Tower::~Tower()
{
    if (m_slot)
        m_slot->m_isAvailable = true;
}

void Tower::update(float delta_time, GPLib* m_gp)
{
    Vector2 mouse_pos = gpMousePosition(m_gp);

    if (gpMouseButtonIsPressed(m_gp, GP_MOUSE_BUTTON_2))
    {
        if (c_point_box(getPosition(), Rectangle{mouse_pos, 32, 32}))
        {
            m_shouldDestroy = true;
            Game::m_money += (m_life / m_max_life) * m_price / 2;
        }
    }

    if (m_entityManager->getEnemyCount() != 0)
        m_life -= delta_time;

    m_cooldown -= delta_time;

    if (m_target)
    {
        if (c_circle_box({m_range, getPosition()}, m_target->getRect()) &&
        !m_target->m_shouldDestroy)
        {
            get_angle(m_target->getPosition());

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

void Tower::getTarget()
{
    for (Enemy* enemy : m_entityManager->m_enemies)
    {
        if (enemy && !enemy->m_shouldDestroy &&
        c_circle_point({m_range, getPosition()}, enemy->getPosition()))
        {
            m_target = enemy;
            break;
        }
    }
}

void Tower::shoot()
{
    if (m_cooldown <= 0)
    {
        createBullet();

        m_cooldown = m_fireRate;
    }
}

void Tower::draw(GPLib* gp)
{
    GPRect lifebar = {m_position.x - TILE_SIZE / 2, m_position.y + TILE_SIZE / 2 + 5, TILE_SIZE, TILE_SIZE / 8};
    gpDrawRectFilled(gp, lifebar, GP_CWHITE);

    lifebar.w *= m_life / m_max_life;
    gpDrawRectFilled(gp, lifebar, GPColor{0, 0.75, 0.5, 1});

    lifebar.w /= m_life / m_max_life;
    gpDrawRect(gp, lifebar, GP_CBLACK);

    gpDrawTextureEx(gp, m_texture, {64, 64}, m_position, m_angle, {1, 1}, nullptr, GP_CWHITE);

    gpDrawCircle(gp, m_position, m_range, GPColor{1, 0, 0, 1});
}