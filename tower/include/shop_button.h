#include "button.h"

#include "tower.h"

class ShopButton : public Button
{
    private:
        TowerType   m_type;
        int         m_price;

        void isPressed() override;

    public:
        ShopButton(GPLib*, Vector2, const ResourceManager&, TowerType);

        void update() override;

        void isUndragged() override;

        int getPrice() const;

        TowerType getType() const;
};