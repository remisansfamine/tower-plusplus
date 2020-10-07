#pragma once

#include <gp/gp.h>
#include <vector>

//#include "maths.h"

class Renderer
{
    public:
        GPTexture texture;
        GPVector2 m_position;
        GPVector2 m_dimension;
};

class RendererManager
{
    private:
        std::vector<Renderer*> renderers;

    public:

};