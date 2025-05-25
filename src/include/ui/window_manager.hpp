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
    // sf::Color WHITE = sf::Color::White;
    // sf::Color WHITE = sf::Color::White;

private:
    sf::RenderWindow m_window;
    GameManager& m_game_manager;

    std::vector<std::shared_ptr<Layer>> m_all_layers;

    sf::Font m_font;
    sf::Text m_text;
    
public:
    WindowManager(unsigned int width, unsigned int height, GameManager& game_manager);
    void start();
    void draw_rect(unsigned int x, unsigned int y, unsigned int width, unsigned int height);
    void draw_text(std::string text, unsigned int x, unsigned int y, unsigned int size, sf::Color color);
    void draw_text(std::vector<std::string> text, unsigned int x, unsigned int y, unsigned int size, sf::Color color);
    GameManager& get_game_manager() const;
    
};