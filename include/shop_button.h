#include "button.h"

#include "tower.h"

class ShopButton : public Button
{
    private:
        TowerType   m_type;
        int         m_price;
        Vector2     m_initial_position;

    public:
        ShopButton(GPLib*, Vector2, const ResourceManager&, TowerType);

        void update() override;

        void is_pressed(Vector2 mouse_pos) override;
        void is_undragged() override;

        int get_price() const;

        TowerType get_type() const;
};