#include "ui/buttons/close_layer_button.hpp"

#include <format>

#include "game_manager.hpp"
#include "building.hpp"

CloseLayerButton::CloseLayerButton(WindowManager& window_manager) :
    Button( BASE_POS_X, BASE_POS_Y, 
            window_manager.m_width, window_manager.m_height, window_manager),
    m_game_manager(window_manager.get_game_manager()) {}

void CloseLayerButton::callback() {
    m_window_manager.pop_layer();
}

void CloseLayerButton::display() {}