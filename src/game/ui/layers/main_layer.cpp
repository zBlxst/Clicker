#include "ui/layers/main_layer.hpp"

#include "ui/button.hpp"
#include "ui/buttons/building_button.hpp"
#include "building.hpp"


MainLayer::MainLayer(WindowManager& window_manager) :
    Layer(window_manager) {
    std::shared_ptr<Button> click_button = std::make_shared<Button>(300, 300, 400, 400, window_manager);
    m_all_buttons.push_back(click_button);

    for (int i = 0; i < Building::N_BUILDINGS; i++) {
        std::shared_ptr<BuildingButton> building_button = std::make_shared<BuildingButton>(i, window_manager);
        m_all_buttons.push_back(building_button);
    }
}
