#include "resource_manager.h"

ResourceManager::ResourceManager(GPLib* gp) : gp(gp)
{
    textures[(unsigned int)TextureType::STANDARD_IDLE] = GPTexture(gpTextureLoadFromFile(gp, "media/standard_tower.png"));
    textures[(unsigned int)TextureType::SLOWING_IDLE] = GPTexture(gpTextureLoadFromFile(gp, "media/slowing_tower.png"));
    textures[(unsigned int)TextureType::EXPLOSIVE_IDLE] = GPTexture(gpTextureLoadFromFile(gp, "media/explosive_tower.png"));

    textures[(unsigned int)TextureType::TOWER_SLOT] = GPTexture(gpTextureLoadFromFile(gp, "media/tower_slot.png"));

    textures[(unsigned int)TextureType::WEAK_ENEMY_IDLE] = GPTexture(gpTextureLoadFromFile(gp, "media/weak_enemy.png"));
    textures[(unsigned int)TextureType::HEALER_ENEMY_IDLE] = GPTexture(gpTextureLoadFromFile(gp, "media/healer_enemy.png"));
    textures[(unsigned int)TextureType::STRONG_ENEMY_IDLE] = GPTexture(gpTextureLoadFromFile(gp, "media/strong_enemy.png"));

    textures[(unsigned int)TextureType::BULLET] = GPTexture(gpTextureLoadFromFile(gp, "media/bullet.png"));

    textures[(unsigned int)TextureType::GRASS] = GPTexture(gpTextureLoadFromFile(gp, "media/grass1.png"));

    textures[(unsigned int)TextureType::PATH_EAST] = GPTexture(gpTextureLoadFromFile(gp, "media/pathEast.png"));
    textures[(unsigned int)TextureType::PATH_NORTH] = GPTexture(gpTextureLoadFromFile(gp, "media/pathNorth.png"));
    textures[(unsigned int)TextureType::PATH_C_LB] = GPTexture(gpTextureLoadFromFile(gp, "media/pathCornerLB.png"));
    textures[(unsigned int)TextureType::PATH_C_RB] = GPTexture(gpTextureLoadFromFile(gp, "media/pathCornerRB.png"));
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