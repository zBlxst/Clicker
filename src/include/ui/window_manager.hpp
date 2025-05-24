#pragma once

#include <SFML/Graphics.hpp>

class GameManager;
class Layer;

class WindowManager {
private:
    sf::RenderWindow m_window;
    GameManager& m_game_manager;

    sf::Font m_font;
    sf::Text m_money_text;
    
    void display_gold();

public:
    WindowManager(unsigned int width, unsigned int height, GameManager& game_manager);
    void start();
    void draw_rect(unsigned int x, unsigned int y, unsigned int width, unsigned int height);
    GameManager& get_game_manager() const;
    
};