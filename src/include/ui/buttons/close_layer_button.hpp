#pragma once

#include "ui/button.hpp"

class WindowManager;

class CloseLayerButton : public Button {
    static constexpr unsigned int BASE_POS_X = 0;
    static constexpr unsigned int BASE_POS_Y = 0;
    

private:
    GameManager& m_game_manager;

public:
    CloseLayerButton(WindowManager& window_manager);
    void callback();
    void display();
};