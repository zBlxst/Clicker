#include "ui/layers/royal_exchange_layer/royal_exchange_button.hpp"

#include <format>
#include <math.h>

#include "game_manager.hpp"
#include "window_manager.hpp"
#include "achievement.hpp"

#include <iostream>
#include <format>
#include <cmath>

RoyalExchangeButton::RoyalExchangeButton(   Faction::FACTION_COINS faction_coins, 
                                            WindowManager& window_manager) :
    Button( 0, 0, 
            WIDTH, HEIGHT, window_manager),
    m_faction_coins(faction_coins),
    m_ui_index(0) {}


void RoyalExchangeButton::callback() {
    if (m_window_manager.get_game_manager().buy_faction_coins(get_cost(), { m_faction_coins })) {
        m_window_manager.get_game_manager().add_royal_exchange(m_faction_coins, 1);
    }
}

void RoyalExchangeButton::display() {
    Button::display();
    std::vector<std::string> to_write = { 
        std::format("Faction coin : {}", Faction::get_faction_coins_name(m_faction_coins)),
        std::format("Cost : {}", get_cost()),
    };
    m_window_manager.draw_text(to_write, m_x, m_y, 15, WindowManager::BLACK);
}

double RoyalExchangeButton::get_cost() {
    return 20*pow(1.1, m_window_manager.get_game_manager().get_royal_exchange(m_faction_coins));
}

void RoyalExchangeButton::update_ui_index(int index) {
    m_ui_index = index;
    m_x = BASE_POS_X;
    m_y = BASE_POS_Y + m_ui_index*(HEIGHT+V_SPACING);
}

sf::Color RoyalExchangeButton::get_background_color() {
    // if (m_achievement->is_obtained()) {
    //     return sf::Color::White;
    // }
    return sf::Color(0xffffff80);
}