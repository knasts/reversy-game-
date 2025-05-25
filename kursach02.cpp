#include <iostream>
#include "Game.h"
#include "MainMenu.h"
#include "Board.h"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Network.hpp"

using namespace sf;

int WinMain()
{
    Game game;

    while (game.window_is_open())
    {
        game.update();

        game.render();
    }

    return 0;
}

