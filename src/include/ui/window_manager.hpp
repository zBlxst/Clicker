#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

class GameManager;
class Layer;
class MainLayer;
class AchievementLayer;
class RoyalExchangeLayer;

class WindowManager {
public:
    static constexpr sf::Color WHITE = sf::Color::White;
    static constexpr sf::Color BLACK = sf::Color::Black;

    const int m_width;
    const int m_height;
    
    static inline sf::Font sf_font = sf::Font("assets/arial.ttf");
    static inline sf::Text sf_text = sf::Text(sf_font);
private:
    sf::RenderWindow m_window;
    GameManager& m_game_manager;

    std::vector<std::shared_ptr<Layer>> m_all_layers;
    std::shared_ptr<Layer> m_current_drawing_layer;

    std::shared_ptr<MainLayer> m_main_layer;
    std::shared_ptr<AchievementLayer> m_achievement_layer;
    std::shared_ptr<RoyalExchangeLayer> m_royal_exchange_layer;
    
public:
    WindowManager(unsigned int width, unsigned int height, GameManager& game_manager);
    void start();
    
    void pop_layer();
    void push_layer(std::shared_ptr<Layer> layer);
    
    void draw_rect(int x, int y, int width, int height, sf::Color color);
    void draw_text(std::string text, int x, int y, int size, sf::Color color);
    void draw_text(std::vector<std::string> text, int x, int y, int size, sf::Color color);
    
    void render_texture(sf::RenderTexture& texture, int x, int y);

    GameManager& get_game_manager() const;
    
};