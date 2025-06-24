#include "ui/window_manager.hpp"

#include "ui/layers/main_layer/main_layer.hpp"
#include "ui/button.hpp"
#include "game_manager.hpp"
#include "building.hpp"

#include <iostream>
#include <format>

WindowManager::WindowManager(unsigned int width, unsigned int height, GameManager& game_manager) : 
    m_width(width),
    m_height(height),
    m_window(sf::VideoMode({width, height}), "mygame"),
    m_game_manager(game_manager),
    m_all_layers(),
    m_font("assets/arial.ttf"),
    m_text(m_font) {
        std::shared_ptr<MainLayer> main_layer = std::make_shared<MainLayer>(std::ref(*this));
        m_all_layers.push_back(main_layer);
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

        m_window.clear();
        m_all_layers.back()->display();
        std::string money_text = std::format("Money {}", (int)m_game_manager.get_money());
        std::string gain_text = std::format("Gain {}/s", (int)m_game_manager.get_prod());
        std::string total_clicks_text = std::format("Total clicks {}", (int)m_game_manager.get_stat_tracker().m_clicks);
        std::string click_gain_text = std::format("Click gain {}", (int)m_game_manager.get_click_gain());
        std::string assistants_text = std::format("Assistants {}", (int)m_game_manager.get_assistants());
        std::string mana_text = std::format("Mana {} / {}", (int)m_game_manager.get_mana(), (int)m_game_manager.get_mana_max());
        std::vector<std::string> to_print = {money_text, gain_text, total_clicks_text, click_gain_text, assistants_text, mana_text};
        draw_text(to_print, 0, 0, 15, WHITE);
        m_window.display();
    }
}

void WindowManager::pop_layer() {
    m_all_layers.pop_back();
}

void WindowManager::draw_rect(  unsigned int x, unsigned int y, 
                                unsigned int width, unsigned int height) {
    sf::RectangleShape rect;
    rect.setPosition(sf::Vector2f(x, y));
    rect.setSize(sf::Vector2f(width, height));
    m_window.draw(rect);
}

void WindowManager::draw_text(  std::string text, unsigned int x, unsigned int y, 
                                unsigned int size, sf::Color color) {
    m_text.setPosition(sf::Vector2f(x, y));
    m_text.setString(text);
    m_text.setCharacterSize(size);
    m_text.setFillColor(color);
    m_window.draw(m_text);
}

void WindowManager::draw_text(  std::vector<std::string> text, unsigned int x, unsigned int y, 
                                unsigned int size, sf::Color color) {
    unsigned int height = y;
    for (std::string str: text) {
        draw_text(str, x, height, size, color);
        height += m_text.getGlobalBounds().size.y*1.5;
    }
}


GameManager& WindowManager::get_game_manager() const {
    return m_game_manager;
}
