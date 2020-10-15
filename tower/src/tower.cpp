#include "tower.h"

#include "map.h"

#include "resource_manager.h"
#include "entity_manager.h"
#include "enemy.h"

#include "bullet.h"

#include "collisions.h"

std::vector<TowerSlot> Tower::m_tower_slots;

Tower::Tower(TowerSlot* slot) : Entity(slot->get_position()), m_slot(slot) { }

void Tower::update(float delta_time)
{
    m_life -= delta_time;
    m_cooldown -= delta_time;

    if (m_target)
    {
        if (c_circle_box({m_range, get_position()}, m_target->get_rect()) &&
        !m_target->m_should_destroy)
        {
            get_angle(m_target->get_position());

            shoot();
        }
        else
            m_target = nullptr;
    }
    else
        get_target();

    if (m_life <= 0)
        m_should_destroy = true;
}

void Tower::get_target()
{
    for (Enemy* enemy : m_EntityManager->m_enemies)
    {
        if (enemy && !enemy->m_should_destroy && c_circle_point({m_range, get_position()}, enemy->get_position()))
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
        create_bullet();

        m_cooldown = m_fire_rate;
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