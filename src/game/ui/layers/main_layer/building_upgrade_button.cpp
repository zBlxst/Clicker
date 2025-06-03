#include "ui/layers/main_layer/building_upgrade_button.hpp"

#include <format>

#include "game_manager.hpp"
#include "building_upgrade.hpp"

BuildingUpgradeButton::BuildingUpgradeButton(int index, WindowManager& window_manager) :
    Button( BASE_POS_X + (index % N_COLS)*(WIDTH+H_SPACING), BASE_POS_Y + (index / N_COLS)*(HEIGHT+V_SPACING), 
            WIDTH, HEIGHT, window_manager),
    m_building_index(index / BuildingUpgrade::N_UPGRADES),
    m_upgrade_index(index % BuildingUpgrade::N_UPGRADES),
    m_ui_index(index),
    m_upgrade(m_building_index, m_upgrade_index, m_window_manager.get_game_manager()) {}

void BuildingUpgradeButton::callback() {
    if (m_upgrade.is_available()) {
        m_upgrade.buy();
    }
}

void BuildingUpgradeButton::display() {
    if (m_upgrade.is_available()) {
        Button::display();
        std::vector<std::string> to_write = {   
                                                std::format("Building : {}", std::round(m_building_index)),
                                                std::format("Buff : {}", std::round(m_upgrade.get_buff())),
                                                std::format("Cost : {}", std::round(m_upgrade.get_upgrade_cost()))
                                            }; 
        m_window_manager.draw_text(to_write, m_x, m_y, 15, WindowManager::BLACK);
    }
}

void BuildingUpgradeButton::update_ui_index(int index) {
    m_ui_index = index;
    m_x = BASE_POS_X + (m_ui_index % N_COLS)*(WIDTH+H_SPACING);
    m_y = BASE_POS_Y + (m_ui_index / N_COLS)*(HEIGHT+V_SPACING);
}

bool BuildingUpgradeButton::should_catch_click() {
    return m_upgrade.is_available();
}
