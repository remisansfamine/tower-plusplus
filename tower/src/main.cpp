#include <iostream>
#include "define.h"

#include <gp/gp.h>

#include "game.h"

int main(int argc, char* argv[])
{
    GPLib* gp = gpInit(SCREEN_WIDTH, SCREEN_HEIGHT, "Tower++", GP_VSYNC_ON);
    std::cout << std::endl; // Force flush stdout

    Game game(gp);

    while (gpWindowShouldClose(gp) == false)
    {
        gpEventsPoll(gp);

        game.update();

        gpDrawBegin(gp);
        gpDrawClearBackground(gp, GP_CBLACK);

        game.display();
        
        gpDrawEnd(gp);
    }

    gpShutdown(gp);
    return 0;
}
