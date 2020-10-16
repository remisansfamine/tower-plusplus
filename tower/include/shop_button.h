#include "button.h"

#include "tower.h"
#include "entity_manager.h"

class ShopButton : public Button
{
    private:
        GPFont m_font;
        TowerType   m_type;
        int         m_price;
        EntityManager* m_entityManager;
        void isPressed() override;
        void buyTower();

    public:
        ShopButton(GPLib*, Vector2, const ResourceManager&, TowerType, EntityManager*);

        void update() override;

        void draw(GPLib* gp) const override;

        void isUndragged() override;
};