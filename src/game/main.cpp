#include <SFML/Graphics.hpp>
#include <iostream>

#include "ui/window_manager.hpp"
#include "game_manager.hpp"

int main()
{
    GameManager gm = GameManager();

    WindowManager window_manager = WindowManager(1000, 1000, gm);    
    window_manager.start();

    
}
