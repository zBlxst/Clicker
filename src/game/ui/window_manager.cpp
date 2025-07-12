#include "ui/window_manager.hpp"

#include "ui/layers/main_layer/main_layer.hpp"
#include "ui/layers/achievement_layer/achievement_layer.hpp"
#include "ui/button.hpp"
#include "game_manager.hpp"
#include "building.hpp"
#include "ui/layer.hpp"

#include <iostream>
#include <format>

WindowManager::WindowManager(unsigned int width, unsigned int height, GameManager& game_manager) : 
    m_width(width),
    m_height(height),
    m_window(sf::VideoMode({width, height}), "mygame"),
    m_game_manager(game_manager),
    m_all_layers() {
        m_main_layer = std::make_shared<MainLayer>(std::ref(*this));
        m_all_layers.push_back(m_main_layer);

        m_achievement_layer = std::make_shared<AchievementLayer>(std::ref(*this));
        m_all_layers.push_back(m_achievement_layer);
    }

void WindowManager::start() {
    
    m_game_manager.start();
    
    
    while (m_window.isOpen())
    {
        while (const std::optional event = m_window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) {
                m_window.close();
                m_game_manager.stop();
            }
            if (const sf::Event::MouseButtonReleased* buttonPressed = event->getIf<sf::Event::MouseButtonReleased>()) {
                if (buttonPressed->button == sf::Mouse::Button::Left) {
                    m_all_layers.back()->recv_click(buttonPressed->position.x, buttonPressed->position.y);
                }
                    
            }

        }
    
        sf::RectangleShape transparency_rect;
        transparency_rect.setFillColor(sf::Color(0xffffff80));
        transparency_rect.setPosition(sf::Vector2f(0, 0));
        transparency_rect.setSize(sf::Vector2f(m_width, m_height));
    
        m_window.clear();
        for (std::shared_ptr<Layer> layer : m_all_layers) {
            m_window.draw(transparency_rect);
            m_current_drawing_layer = layer;
            layer->m_render_texture.clear();
            layer->display();
            m_window.draw(layer->get_sprite());
        }
        m_window.display();
    }
}

void WindowManager::pop_layer() {
    m_all_layers.pop_back();
}

void WindowManager::push_layer(std::shared_ptr<Layer> layer) {
    m_all_layers.push_back(layer);
}

void WindowManager::draw_rect(  int x, int y, 
                                int width, int height, sf::Color color) {
    sf::RenderTexture& target = m_current_drawing_layer->m_render_texture;
    sf::RectangleShape rect;
    rect.setFillColor(color);
    rect.setPosition(sf::Vector2f(x, y));
    rect.setSize(sf::Vector2f(width, height));
    target.draw(rect);
}

void WindowManager::draw_text(  std::string text, int x, int y, 
                                int size, sf::Color color) {
    sf::RenderTexture& target = m_current_drawing_layer->m_render_texture;
    sf_text.setPosition(sf::Vector2f(x, y));
    sf_text.setString(text);
    sf_text.setCharacterSize(size);
    sf_text.setFillColor(color);
    target.draw(sf_text);
}

void WindowManager::draw_text(  std::vector<std::string> text, int x, int y, 
                                int size, sf::Color color) {
    int height = y;
    for (std::string str: text) {
        draw_text(str, x, height, size, color);
        height += sf_text.getGlobalBounds().size.y*1.5;
    }
}

void WindowManager::render_texture(sf::RenderTexture& texture, int x, int y) {
    sf::Sprite sprite(texture.getTexture());
    sprite.setPosition(sf::Vector2f(x, y));
    m_window.draw(sprite);
}


GameManager& WindowManager::get_game_manager() const {
    return m_game_manager;
}
