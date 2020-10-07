#include "ressource_manager.h"

RessourceManager::RessourceManager(GPLib* gp) : gp(gp)
{
    textures[(int)TextureType::TOWER_IDLE] = GPTexture(gpTextureLoadFromFile(gp, "media/tower.jpg"));
    textures[(int)TextureType::ENEMY_IDLE] = GPTexture(gpTextureLoadFromFile(gp, "media/enemy.png"));
    textures[(int)TextureType::BULLET] = GPTexture(gpTextureLoadFromFile(gp, "media/bullet.jpg"));
}

RessourceManager::~RessourceManager()
{
    for (GPTexture texture : textures)
        gpTextureUnload(gp, texture);
}

const GPTexture RessourceManager::get_texture(unsigned int index) const
{
    return textures[index]; 
}