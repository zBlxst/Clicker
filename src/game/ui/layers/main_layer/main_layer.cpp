#include "ui/layers/main_layer/main_layer.hpp"
#include "ui/layers/main_layer/click_button.hpp"
#include "ui/layers/main_layer/upgrade_button.hpp"
#include "ui/layers/main_layer/building_button.hpp"

#include "building.hpp"
#include "building_upgrade.hpp"
#include "game_manager.hpp"


MainLayer::MainLayer(WindowManager& window_manager) :
    Layer(window_manager),
    m_all_upgrade_buttons() {
    
    for (int i = 0; i < Upgrade::TYPES::N_ITEMS; i++) {
        m_all_upgrade_buttons.push_back(std::vector<std::shared_ptr<UpgradeButton>>());
    }
    std::shared_ptr<ClickButton> click_button = std::make_shared<ClickButton>(window_manager);
    m_all_buttons.push_back(click_button);

    for (int i = 0; i < Building::N_BUILDINGS; i++) {
        std::shared_ptr<BuildingButton> building_button = std::make_shared<BuildingButton>(i, window_manager);
        m_all_buttons.push_back(building_button);
    }

    for (std::shared_ptr<Upgrade> b_up: m_window_manager.get_game_manager().get_all_upgrades()[Upgrade::TYPES::BUILDING]) {
        std::shared_ptr<UpgradeButton> building_upgrade_button = std::make_shared<UpgradeButton>(b_up, window_manager);
        m_all_buttons.push_back(building_upgrade_button);
        m_all_upgrade_buttons[Upgrade::TYPES::BUILDING].push_back(building_upgrade_button);
    }
}

void MainLayer::display() {
    int available_building_upgrades = 0;
    for (int i = 0; i < Upgrade::TYPES::N_ITEMS; i++) {
        for (std::shared_ptr<UpgradeButton> b_up_button: m_all_upgrade_buttons[i]) {
            if (b_up_button->m_upgrade->is_available()) {
                b_up_button->update_ui_index(available_building_upgrades++);
            }
        }
    }
    Layer::display();
}