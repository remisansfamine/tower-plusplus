#include "button.h"

#include "tower.h"

class ShopButton : public Button
{
    private:
        TowerType   m_type;
        int         m_price;

    public:
        ShopButton(GPLib*, Vector2, const ResourceManager&, TowerType);

        void update() override;
};