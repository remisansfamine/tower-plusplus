#include "standard_bullet.h"
#include "entity_manager.h"
#include "collisions.h"

StandardBullet::StandardBullet(Vector2 position, Enemy* enemy, const ResourceManager& RM)
: Bullet(position, enemy)
{
    m_speed = 600;
    m_texture = RM.getTexture(TextureType::STANDARD_BULLET);
    m_damage = 5.f;
}