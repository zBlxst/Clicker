#include "ui/window_manager.hpp"

#include "ui/layer.hpp"
#include "ui/button.hpp"
#include "game_manager.hpp"


#include <iostream>
#include <format>

WindowManager::WindowManager(unsigned int width, unsigned int height, GameManager& game_manager) : 
    m_window(sf::VideoMode({width, height}), "mygame"),
    m_game_manager(game_manager),
    m_font("assets/arial.ttf"),
    m_money_text(m_font) {}

void WindowManager::start() {
    
    Layer layer = Layer(std::ref(*this));


    while (m_window.isOpen())
    {
        while (const std::optional event = m_window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                m_window.close();
            if (const sf::Event::MouseButtonReleased* buttonPressed = event->getIf<sf::Event::MouseButtonReleased>()) {
                if (buttonPressed->button == sf::Mouse::Button::Left) {
                    layer.recv_click(buttonPressed->position.x, buttonPressed->position.y);
                    // m_game_manager.click();
                }
                    
            }

        }

        m_window.clear();
        layer.display();
        display_gold();
        m_window.display();
    }
}

void WindowManager::display_gold() {
    m_money_text.setString(std::format("Money : {}", m_game_manager.get_money()));
    m_money_text.setCharacterSize(15);
    m_money_text.setFillColor(sf::Color::White);
    m_window.draw(m_money_text);
}

void WindowManager::draw_rect(  unsigned int x, unsigned int y, 
                                unsigned int width, unsigned int height) {
    sf::RectangleShape rect;
    rect.setPosition(sf::Vector2f(x, y));
    rect.setSize(sf::Vector2f(width, height));
    m_window.draw(rect);
}

GameManager& WindowManager::get_game_manager() const {
    return m_game_manager;
}
