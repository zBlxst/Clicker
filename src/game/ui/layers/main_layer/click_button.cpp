#include "ui/layers/main_layer/click_button.hpp"

#include <format>

#include "game_manager.hpp"
#include "building.hpp"

ClickButton::ClickButton(WindowManager& window_manager) :
    Button( BASE_POS_X, BASE_POS_Y, 
            window_manager.m_width, window_manager.m_height, window_manager),
    m_game_manager(window_manager.get_game_manager()) {}

void ClickButton::callback() {
    m_game_manager.click(true);
}

void ClickButton::display() {}