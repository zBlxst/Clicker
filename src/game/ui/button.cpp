#include "ui/button.hpp"

#include "ui/window_manager.hpp"
#include "game_manager.hpp"


Button::Button( unsigned int x, unsigned int y, 
                unsigned int width, unsigned int height,
                WindowManager& window_manager) : 
    m_x(x), m_y(y),
    m_width(width), m_height(height),
    m_window_manager(window_manager) {}

bool Button::catched_click(unsigned int x, unsigned int y) {
    if (   (m_x < x && x < m_x + m_width)
        && (m_y < y && y < m_y + m_height)
        && should_catch_click()) {
            callback();
            return true;
        }
    return false;
}

void Button::callback() {
    m_window_manager.get_game_manager().click();
}

void Button::display() {
    m_window_manager.draw_rect(m_x, m_y, m_width, m_height);
}

bool Button::should_catch_click() {
    return true;
}


