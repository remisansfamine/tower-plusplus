#include "button_manager.h"

#include "button.h"

#include "map.h"

ButtonManager::~ButtonManager()
{
    for (Button* button : m_buttons)
        destroyButton(button);
}

void    ButtonManager::createButton(Button* button)
{
    m_buttons.push_back(button);
    button->m_ButtonManager = this;
}

void    ButtonManager::destroyButton(Button* button)
{
    if (m_buttons.size() == 0)
         return;

    *button = *m_buttons.back();
    delete m_buttons.back();
    m_buttons.pop_back();
}

void    ButtonManager::draw(GPLib* gp) const
{
    for (Button* button : m_buttons)
    {
        if (button)
            button->draw(gp);
    }
}

void    ButtonManager::update()
{
    for (Button* button : m_buttons)
    {
        if (button)
            button->update();
    }
}