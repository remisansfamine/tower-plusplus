#pragma once

#include <vector>

class ShopButton;
class Button;

class ButtonManager
{
    public:
        ButtonManager::ButtonManager();

        ShopButton* m_current = nullptr;

        std::vector<Button*> m_buttons;

        void    createButton(Button*);

        void    destroyButton(Button*);
};