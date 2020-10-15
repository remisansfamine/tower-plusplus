#include "entity.h"

Entity::Entity(Vector2 position)
: m_position(position) { }

#pragma region Accessers
float Entity::X() const
{
    return m_position.x;
}
float Entity::Y() const
{
    return m_position.y;
}
Vector2 Entity::get_position() const
{
    return m_position;
}
void Entity::get_angle(Vector2 target)
{
    Vector2 vect = target - m_position;

    m_angle = atan2(vect.y, vect.x);
}
#pragma endregion