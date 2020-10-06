#include <iostream>

#include <gp/gp.h>

#include "game.h"

int main(int argc, char* argv[])
{
    GPLib* gp = gpInit(800, 600, "Tower++", GP_VSYNC_ON);
    std::cout << std::endl; // Force flush stdout

    Game game(gp);

    while (gpWindowShouldClose(gp) == false)
    {
        // Poll events (mouse, keyboards, etc...)
        gpEventsPoll(gp);

        game.update();

        if (gpMouseButtonIsPressed(gp, GP_MOUSE_BUTTON_1))
        {
            GPVector2 mousePos = gpMousePosition(gp);
            std::cout << "Mouse pressed at { " << mousePos.x << ", " << mousePos.y << " }" << std::endl;
        }

        gpDrawBegin(gp);
        gpDrawClearBackground(gp, GP_CBLACK);

        game.display();
        
        gpDrawEnd(gp);
    }

    gpShutdown(gp);
    return 0;
}
