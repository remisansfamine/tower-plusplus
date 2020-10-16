#pragma once

#include "maths.h"

class TowerSlot
{
    private:
        Vector2     m_position;
        Rectangle   m_collision;

    public:
        bool        m_isAvailable = true;
        
        TowerSlot(Vector2 position);

        const Rectangle getCollision() const;

        const Vector2   getPosition() const;
};