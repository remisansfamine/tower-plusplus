#include "resource_manager.h"

ResourceManager::ResourceManager(GPLib* gp) : m_gp(gp)
{
    m_font = gpFontLoad(m_gp, "media/unique.ttf", 30);

    m_textures[(unsigned int)TextureType::STANDARD_IDLE] = gpTextureLoadFromFile(gp, "media/standard_tower.png");
    m_textures[(unsigned int)TextureType::SLOWING_IDLE] = gpTextureLoadFromFile(gp, "media/slowing_tower.png");
    m_textures[(unsigned int)TextureType::EXPLOSIVE_IDLE] = gpTextureLoadFromFile(gp, "media/explosive_tower.png");

    m_textures[(unsigned int)TextureType::TOWER_SLOT] = gpTextureLoadFromFile(gp, "media/tower_slot.png");

    m_textures[(unsigned int)TextureType::WEAK_ENEMY_IDLE] = gpTextureLoadFromFile(gp, "media/weak_enemy.png");
    m_textures[(unsigned int)TextureType::HEALER_ENEMY_IDLE] = gpTextureLoadFromFile(gp, "media/healer_enemy.png");
    m_textures[(unsigned int)TextureType::STRONG_ENEMY_IDLE] = gpTextureLoadFromFile(gp, "media/strong_enemy.png");

    m_textures[(unsigned int)TextureType::STANDARD_BULLET] = gpTextureLoadFromFile(gp, "media/standard_bullet.png");
    m_textures[(unsigned int)TextureType::SLOWING_BULLET] = gpTextureLoadFromFile(gp, "media/slowing_bullet.png");
    m_textures[(unsigned int)TextureType::EXPLOSIVE_BULLET] = gpTextureLoadFromFile(gp, "media/explosive_bullet.png");

    m_textures[(unsigned int)TextureType::GRASS] = gpTextureLoadFromFile(gp, "media/grass1.png");

    m_textures[(unsigned int)TextureType::PATH_EAST] = gpTextureLoadFromFile(gp, "media/pathEast.png");
    m_textures[(unsigned int)TextureType::PATH_NORTH] = gpTextureLoadFromFile(gp, "media/pathNorth.png");
    m_textures[(unsigned int)TextureType::PATH_C_LB] = gpTextureLoadFromFile(gp, "media/pathCornerLB.png");
    m_textures[(unsigned int)TextureType::PATH_C_RB] = gpTextureLoadFromFile(gp, "media/pathCornerRB.png");
    m_textures[(unsigned int)TextureType::PATH_C_UL] = gpTextureLoadFromFile(gp, "media/pathCornerUL.png");
    m_textures[(unsigned int)TextureType::PATH_C_UR] = gpTextureLoadFromFile(gp, "media/pathCornerUR.png");
    m_textures[(unsigned int)TextureType::PATH_C_ULRB] = gpTextureLoadFromFile(gp, "media/pathCornerULRB.png");

    m_textures[(unsigned int)TextureType::CASTLE] = GPTexture(gpTextureLoadFromFile(gp, "media/castle.png"));
    
    m_textures[(unsigned int)TextureType::ERROR] = GPTexture(gpTextureLoadFromFile(gp, "media/error.png"));
}

ResourceManager::~ResourceManager()
{
    for (GPTexture texture : m_textures)
        gpTextureUnload(m_gp, texture);

    //gpFontUnload(m_gp, m_font);
}

const GPTexture ResourceManager::getTexture(TextureType type) const
{
    return m_textures[(unsigned int)type];
}

const GPFont ResourceManager::getFont() const
{
    return m_font;
}