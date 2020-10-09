#include "resource_manager.h"

ResourceManager::ResourceManager(GPLib* gp) : gp(gp)
{
    textures[(unsigned int)TextureType::TOWER_IDLE] = GPTexture(gpTextureLoadFromFile(gp, "media/tower.png"));
    textures[(unsigned int)TextureType::TOWER_SLOT] = GPTexture(gpTextureLoadFromFile(gp, "media/tower_slot.png"));
    textures[(unsigned int)TextureType::ENEMY_IDLE] = GPTexture(gpTextureLoadFromFile(gp, "media/enemy.png"));
    textures[(unsigned int)TextureType::BULLET] = GPTexture(gpTextureLoadFromFile(gp, "media/bullet.png"));
    textures[(unsigned int)TextureType::PATH] = GPTexture(gpTextureLoadFromFile(gp, "media/path.png"));
    textures[(unsigned int)TextureType::GRASS] = GPTexture(gpTextureLoadFromFile(gp, "media/grass.png"));

    textures[(unsigned int)TextureType::BUTTON] = GPTexture(gpTextureLoadFromFile(gp, "media/button.png"));
    
    textures[(unsigned int)TextureType::ERROR] = GPTexture(gpTextureLoadFromFile(gp, "media/error.png"));
}

ResourceManager::~ResourceManager()
{
    for (GPTexture texture : textures)
        gpTextureUnload(gp, texture);
}

const GPTexture ResourceManager::get_texture(TextureType type) const
{
    return textures[(unsigned int)type];
}