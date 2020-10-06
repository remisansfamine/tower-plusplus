#pragma once

#include <string>

#include <gp/gp.h>

class Entity
{
    protected:
        std::string name;

        float   life;
        float   m_damage;
        float   x, y;
        GPTexture texture;

    public:

        Entity(float x, float y, float life) : x(x), y(y), life(life) {}

        GPTexture get_texture() const
        { return texture; }

        const float X() const { return x; }
        const float Y() const { return y; }

        //virtual void update();
};