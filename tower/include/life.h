#pragma once

class Life
{
    private:
        float m_max_life;

    public:
        float m_life;
        
        Life() = default;
        Life(float max_life) :  m_max_life(max_life), m_life(max_life) {}

        float get_max_life() const { return m_max_life; }
};