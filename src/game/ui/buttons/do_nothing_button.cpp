#include "ui/buttons/do_nothing_button.hpp"

#include <format>

#include "game_manager.hpp"
#include "building.hpp"

DoNothingButton::DoNothingButton(unsigned int x, unsigned int y, unsigned int width, unsigned int height, WindowManager& window_manager):
    Button( x, y, 
            width, height, window_manager) {}

void DoNothingButton::callback() {}

void DoNothingButton::display() {}