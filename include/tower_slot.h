#pragma once

#include "maths.h"

class TowerSlot
{
    private:
        Vector2     m_position;
        Rectangle   m_collision;

    public:
        bool        m_is_occuped = false;
        
        TowerSlot(Vector2 position);

        const Rectangle get_collision() const;

        const Vector2   get_position() const;
};