#include "ui/layers/achievement_layer/achievement_button.hpp"

#include <format>
#include <math.h>

#include "game_manager.hpp"
#include "achievement.hpp"

#include <iostream>
#include <format>

AchievementButton::AchievementButton(   std::shared_ptr<Achievement> achievement, 
                                WindowManager& window_manager) :
    Button( 0, 0, 
            WIDTH, HEIGHT, window_manager),
    m_achievement(achievement),
    m_ui_index(0) {}


void AchievementButton::callback() {}

void AchievementButton::display() {
    Button::display();
    std::vector<std::string> to_write = m_achievement->get_base_text_to_display();
    m_window_manager.draw_text(to_write, m_x, m_y, 15, WindowManager::BLACK);
}

void AchievementButton::update_ui_index(int index) {
    m_ui_index = index;
    m_x = BASE_POS_X + (m_ui_index % N_COLS)*(WIDTH+H_SPACING);
    m_y = BASE_POS_Y + (m_ui_index / N_COLS)*(HEIGHT+V_SPACING);
}

bool AchievementButton::should_catch_click() {
    return false;
}

sf::Color AchievementButton::get_background_color() {
    if (m_achievement->is_obtained()) {
        return sf::Color::White;
    }
    return sf::Color(0xffffff80);
}