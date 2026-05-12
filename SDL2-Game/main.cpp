#include <SDL.h>
#undef main         
#include "Game.h"

int main(int argc, char* argv[])  // argc/argv not used but professor said to keep
{
    std::cout << "=== ZERO WING REMAKE ===" << std::endl;

    Game myGame;


    if (!myGame.SetupGame())
    {
        std::cout << "ERROR: game failed to start!" << std::endl;
        return -1; // error code -1 = something went wrong

    }

    myGame.MainLoop();
    myGame.Cleanup();

    std::cout << "GOODBYE!" << std::endl;

    return 0; // 0 = all good
}