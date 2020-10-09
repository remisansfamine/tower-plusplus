#include "entity.h"

Entity::Entity(Vector2 position) : m_position(position) {}

GPTexture Entity::get_texture() const
{
    return m_texture;
}

#pragma region Accessers
float Entity::get_damage() const
{
    return m_damage;
}
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