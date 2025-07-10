#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

class GameManager;
class Layer;

class WindowManager {
public:
    static constexpr sf::Color WHITE = sf::Color::White;
    static constexpr sf::Color BLACK = sf::Color::Black;

    const int m_width;
    const int m_height;
private:
    sf::RenderWindow m_window;
    GameManager& m_game_manager;

    std::vector<std::shared_ptr<Layer>> m_all_layers;

    sf::Font m_font;
    sf::Text m_text;
    
public:
    WindowManager(unsigned int width, unsigned int height, GameManager& game_manager);
    void start();
    
    void pop_layer();
    
    void draw_rect(int x, int y, int width, int height, sf::Color color);
    void draw_text(std::string text, int x, int y, int size, sf::Color color);
    void draw_text(std::vector<std::string> text, int x, int y, int size, sf::Color color);
    
    GameManager& get_game_manager() const;
    
};