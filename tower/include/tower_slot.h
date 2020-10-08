#pragma once

#include "entity.h"
#include "maths.h"

class TowerSlot
{
    private:
        Vector2     m_position;
        Rectangle   m_collision;

    public:
        bool        m_isOccuped = false;
        
        TowerSlot(Vector2 position) : m_position(position)
        {
            m_collision = {position, 50, 50};
        }
        const Rectangle get_collision() const
        {
            return m_collision;
        }
};