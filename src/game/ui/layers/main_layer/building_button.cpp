#include "ui/layers/main_layer/building_button.hpp"

#include <format>
#include <math.h>

#include "game_manager.hpp"
#include "building.hpp"
#include "utils.hpp"

BuildingButton::BuildingButton(int index, WindowManager& window_manager) :
    Button( BASE_POS_X, BASE_POS_Y + index*(HEIGHT+V_SPACING), 
            WIDTH, HEIGHT, window_manager),
    m_game_manager(window_manager.get_game_manager()),
    m_index(index) {}

void BuildingButton::callback() {
    m_game_manager.get_all_buildings()[m_index]->level_up();
}

bool BuildingButton::should_catch_click() {
    return m_game_manager.get_all_buildings()[m_index]->is_available();
}

void BuildingButton::display() {
    if(!m_game_manager.get_all_buildings()[m_index]->is_available()) {
        return;
    }
    Button::display();
    std::vector<std::string> to_write = {   std::format("Level : {}", m_game_manager.get_all_buildings()[m_index]->get_level()),
                                            std::format("Cost : {}", double_to_string(m_game_manager.get_all_buildings()[m_index]->get_cost())),
                                            std::format("Gain : {}/s", double_to_string(m_game_manager.m_production_buff.get_buffed_value(m_game_manager.get_all_buildings()[m_index]->get_gain()))),
                                        }; 
    m_window_manager.draw_text(to_write, m_x, m_y, 15, WindowManager::BLACK);
}

sf::Color BuildingButton::get_background_color() {
    switch (m_game_manager.get_all_buildings()[m_index]->m_morality)
    {
    case Faction::MORALITY::GOOD:
        return sf::Color::Cyan;
    case Faction::MORALITY::BAD:
        return sf::Color(0xff8000ff);
    }
    return sf::Color::White;
}