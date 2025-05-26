#include "ui/layers/main_layer/main_layer.hpp"
#include "ui/layers/main_layer/click_button.hpp"

#include "ui/layers/main_layer/building_button.hpp"
#include "building.hpp"


MainLayer::MainLayer(WindowManager& window_manager) :
    Layer(window_manager) {
    std::shared_ptr<ClickButton> click_button = std::make_shared<ClickButton>(window_manager);
    m_all_buttons.push_back(click_button);

    for (int i = 0; i < Building::N_BUILDINGS; i++) {
        std::shared_ptr<BuildingButton> building_button = std::make_shared<BuildingButton>(i, window_manager);
        m_all_buttons.push_back(building_button);
    }
}
