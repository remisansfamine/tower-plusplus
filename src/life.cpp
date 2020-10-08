#include "life.h"

Life::Life(float max_life) :  m_max_life(max_life), m_life(max_life) {}

float Life::get_max_life() const
{
    return m_max_life;
}