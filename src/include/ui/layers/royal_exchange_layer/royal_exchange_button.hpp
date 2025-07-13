#pragma once

#include "ui/buttons/button.hpp"
#include "faction.hpp"

#include <memory>

class WindowManager;

class RoyalExchangeButton : public Button {

public:
    static constexpr int BASE_POS_X = 200;
    static constexpr int BASE_POS_Y = 20;
    static constexpr int WIDTH = 400;
    static constexpr int HEIGHT = 100;
    static constexpr int V_SPACING = 10;
    static constexpr int N_COLS = 7;

private:
    int m_ui_index;
    
    double get_cost();
    
public:
    const Faction::FACTION_COINS m_faction_coins;
    
    RoyalExchangeButton(Faction::FACTION_COINS faction_coins, WindowManager& window_manager);
    void callback();
    void display();
    void update_ui_index(int index);
    sf::Color get_background_color();
};