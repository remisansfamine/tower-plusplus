#include "render_manager.h"

#include <iostream>

void RendererManager::draw(GPLib* gp) const
{
    for (Renderer* renderer : renderers)
    {
        gpDrawTexture(gp, renderer->m_texture, renderer->m_position, true, GPColor{1, 1, 1, 1});
    }
}