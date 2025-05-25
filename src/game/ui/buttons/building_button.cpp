#include "ui/buttons/building_button.hpp"

#include <format>

#include "game_manager.hpp"
#include "building.hpp"

BuildingButton::BuildingButton(int index, WindowManager& window_manager) :
    Button( BASE_POS_X, BASE_POS_Y + index*(HEIGHT+V_SPACING), 
            WIDTH, HEIGHT, window_manager),
    m_game_manager(window_manager.get_game_manager()),
    m_index(index) {}

void BuildingButton::callback() {
    m_game_manager.get_all_buildings()[m_index]->level_up();
}

void BuildingButton::display() {
    Button::display();
    std::vector<std::string> to_write = {   std::format("Level : {}", std::round(m_game_manager.get_all_buildings()[m_index]->get_level())),
                                            std::format("Cost : {}", std::round(m_game_manager.get_all_buildings()[m_index]->get_cost()))
                                        }; 
    m_window_manager.draw_text(to_write, m_x, m_y, 15, WindowManager::BLACK);
}