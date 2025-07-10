#pragma once

#include "ui/button.hpp"

class WindowManager;

class ClickButton : public Button {
    static constexpr int BASE_POS_X = 0;
    static constexpr int BASE_POS_Y = 0;
    

private:
    GameManager& m_game_manager;

public:
    ClickButton(WindowManager& window_manager);
    void callback();
    void display();
};