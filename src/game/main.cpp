#include <SFML/Graphics.hpp>
#include <iostream>

#include "ui/window_manager.hpp"
#include "game_manager.hpp"
#include "save_manager.hpp"

int main()
{
    GameManager gm = GameManager();
    SaveManager sm = SaveManager(gm);
    
    std::cout << "Starting the game" << std::endl;
    sm.load_save(); 
    WindowManager window_manager = WindowManager(1000, 1000, gm);    
    window_manager.start();
    
    
    std::cout << "Ending the game" << std::endl;
    sm.store_save();
}
