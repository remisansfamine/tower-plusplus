#pragma once

#include "maths.h"

class TowerSlot
{
    private:
        Vector2     m_position;
        Rectangle   m_collision;

    public:
        bool        m_isOccuped = false;
        
        TowerSlot(Vector2 position);

        const Rectangle get_collision() const;
};