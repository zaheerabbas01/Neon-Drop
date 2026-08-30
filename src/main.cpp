#include "Game.h"
#include <iostream>

int main()
{
    std::srand(static_cast<unsigned>(time(NULL)));
    Game game;

    while (game.running())
    {
        // game update
        game.update();

        // game render
        game.render();
    }
    

    return 0;
}