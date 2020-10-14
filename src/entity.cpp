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
#pragma endregion