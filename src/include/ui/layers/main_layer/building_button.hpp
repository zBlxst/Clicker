#pragma once

#include "ui/button.hpp"

class WindowManager;

class BuildingButton : public Button {
    static constexpr int BASE_POS_X = 840;
    static constexpr int BASE_POS_Y = 10;
    static constexpr int WIDTH = 150;
    static constexpr int HEIGHT = 80;
    static constexpr int V_SPACING = 10;
    

private:
    GameManager& m_game_manager;

    int m_index;
public:
    BuildingButton(int index, WindowManager& window_manager);
    void callback();
    bool should_catch_click();
    void display();

    sf::Color get_background_color();
};