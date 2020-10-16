#pragma once

#include <vector>

#include <gp/gp.h>

class ShopButton;
class Button;

class ButtonManager
{
    private:
        void    destroyButton(Button*);

    public:
        ButtonManager::~ButtonManager();

        ShopButton* m_current = nullptr;

        std::vector<Button*> m_buttons;

        void    createButton(Button*);

        void    draw(GPLib* gp) const;

        void    update();
};