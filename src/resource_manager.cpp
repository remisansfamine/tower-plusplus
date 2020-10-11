#include "resource_manager.h"

ResourceManager::ResourceManager(GPLib* gp) : gp(gp)
{
    textures[(unsigned int)TextureType::TOWER_IDLE] = GPTexture(gpTextureLoadFromFile(gp, "media/tower.png"));
    textures[(unsigned int)TextureType::TOWER_SLOT] = GPTexture(gpTextureLoadFromFile(gp, "media/tower_slot.png"));

    textures[(unsigned int)TextureType::ENEMY_IDLE] = GPTexture(gpTextureLoadFromFile(gp, "media/enemy.png"));
    textures[(unsigned int)TextureType::BULLET] = GPTexture(gpTextureLoadFromFile(gp, "media/bullet.png"));

    textures[(unsigned int)TextureType::GRASS] = GPTexture(gpTextureLoadFromFile(gp, "media/grass1.png"));

    textures[(unsigned int)TextureType::PATH_EAST] = GPTexture(gpTextureLoadFromFile(gp, "media/pathEast.png"));
    textures[(unsigned int)TextureType::PATH_NORTH] = GPTexture(gpTextureLoadFromFile(gp, "media/pathNorth.png"));
    textures[(unsigned int)TextureType::PATH_C_LL] = GPTexture(gpTextureLoadFromFile(gp, "media/pathCornerLL.png"));
    textures[(unsigned int)TextureType::PATH_C_LR] = GPTexture(gpTextureLoadFromFile(gp, "media/pathCornerLR.png"));
    textures[(unsigned int)TextureType::PATH_C_UL] = GPTexture(gpTextureLoadFromFile(gp, "media/pathCornerUL.png"));
    textures[(unsigned int)TextureType::PATH_C_UR] = GPTexture(gpTextureLoadFromFile(gp, "media/pathCornerUR.png"));
    textures[(unsigned int)TextureType::PATH_C_ULRB] = GPTexture(gpTextureLoadFromFile(gp, "media/pathCornerULRB.png"));

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