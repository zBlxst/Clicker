#pragma once

#include "ui/button.hpp"

class WindowManager;

class BuildingButton : public Button {
    static constexpr unsigned int BASE_POS_X = 840;
    static constexpr unsigned int BASE_POS_Y = 10;
    static constexpr unsigned int WIDTH = 150;
    static constexpr unsigned int HEIGHT = 80;
    static constexpr unsigned int V_SPACING = 10;
    

private:
    GameManager& m_game_manager;

    unsigned int m_index;
public:
    BuildingButton(int index, WindowManager& window_manager);
    void callback();
    bool should_catch_click();
    void display();
};