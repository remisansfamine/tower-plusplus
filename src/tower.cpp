#include "tower.h"

#include "resource_manager.h"
#include "entity_manager.h"
#include "enemy.h"
#include "bullet.h"

#include "collisions.h"

std::vector<TowerSlot> Tower::m_tower_slots;

Tower::Tower(Vector2 position) : Entity(position) { }

void Tower::update(float delta_time)
{
    m_cooldown -= delta_time;

    if (!m_target)
    {
        get_target();
    }
    else
    {
        if (c_circle_box({m_range, get_position()}, m_target->get_rect()) &&
        !m_target->m_should_destroy)
        {
            Vector2 vect = m_target->get_position() - get_position();

            m_angle = atan2(vect.y, vect.x) + M_PI / 2;

            shoot();
        }
        else
            m_target = nullptr;
    }
}

void Tower::get_target()
{
    for (Enemy* enemy : m_EntityManager->m_enemies)
    {
        if (!enemy)
            continue;

        if (c_circle_point({m_range, get_position()}, enemy->get_position()))
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

void Tower::create_bullet()
{
    m_EntityManager->createBullet(new Bullet(get_position(),
                                                 m_target, get_damage(),
                                                 m_EntityManager->m_ResourceManager));
}