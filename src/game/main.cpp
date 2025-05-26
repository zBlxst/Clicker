#include <SFML/Graphics.hpp>
#include <iostream>

#include "ui/window_manager.hpp"
#include "game_manager.hpp"

int main()
{
    GameManager gm = GameManager();

    std::cout << "Starting the game" << std::endl;
    WindowManager window_manager = WindowManager(1000, 1000, gm);    
    window_manager.start();
    
    std::cout << "Ending the game" << std::endl;
    
}
