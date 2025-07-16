#include "ui/layers/main_layer/upgrade_button.hpp"

#include <format>
#include <math.h>

#include "game_manager.hpp"
#include "upgrades/upgrade.hpp"
#include "utils.hpp"

UpgradeButton::UpgradeButton(   std::shared_ptr<Upgrade> upgrade, 
                                WindowManager& window_manager) :
    Button( 0, 0, 
            WIDTH, HEIGHT, window_manager),
    m_upgrade(upgrade),
    m_ui_index(0) {}


void UpgradeButton::callback() {
    if (m_upgrade->is_available()) {
        m_upgrade->buy();
    }
}

void UpgradeButton::display() {
    if (m_upgrade->is_available()) {
        Button::display();
        std::vector<std::string> to_write = m_upgrade->get_base_text_to_display();
        to_write.push_back(std::format("Buff : {}", double_to_string(m_upgrade->get_buff())));
        to_write.push_back(std::format("Cost : {}", double_to_string(m_upgrade->get_cost()))); 
        m_window_manager.draw_text(to_write, m_x, m_y, 15, WindowManager::BLACK);
    }
}

void UpgradeButton::update_ui_index(int index) {
    m_ui_index = index;
    m_x = BASE_POS_X + (m_ui_index % N_COLS)*(WIDTH+H_SPACING);
    m_y = BASE_POS_Y + (m_ui_index / N_COLS)*(HEIGHT+V_SPACING);
}

bool UpgradeButton::should_catch_click() {
    return m_upgrade->is_available();
}
