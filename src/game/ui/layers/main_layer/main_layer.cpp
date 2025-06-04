#include "ui/layers/main_layer/main_layer.hpp"
#include "ui/layers/main_layer/click_button.hpp"
#include "ui/layers/main_layer/building_upgrade_button.hpp"
#include "ui/layers/main_layer/building_button.hpp"

#include "building.hpp"
#include "building_upgrade.hpp"
#include "game_manager.hpp"


MainLayer::MainLayer(WindowManager& window_manager) :
    Layer(window_manager),
    m_all_building_upgrade_buttons() {
    std::shared_ptr<ClickButton> click_button = std::make_shared<ClickButton>(window_manager);
    m_all_buttons.push_back(click_button);

    for (int i = 0; i < Building::N_BUILDINGS; i++) {
        std::shared_ptr<BuildingButton> building_button = std::make_shared<BuildingButton>(i, window_manager);
        m_all_buttons.push_back(building_button);
    }

    for (std::shared_ptr<BuildingUpgrade> b_up: m_window_manager.get_game_manager().get_all_upgrades()) {
        std::shared_ptr<BuildingUpgradeButton> building_upgrade_button = std::make_shared<BuildingUpgradeButton>(b_up, window_manager);
        m_all_buttons.push_back(building_upgrade_button);
        m_all_building_upgrade_buttons.push_back(building_upgrade_button);
    }
}

void MainLayer::display() {
    int available_building_upgrades = 0;
    for (std::shared_ptr<BuildingUpgradeButton> b_up_button: m_all_building_upgrade_buttons) {
        if (b_up_button->m_upgrade->is_available()) {
            b_up_button->update_ui_index(available_building_upgrades++);
        }
    }
    Layer::display();
}