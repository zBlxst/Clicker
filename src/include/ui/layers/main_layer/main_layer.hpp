#pragma once

#include <memory>
#include <vector>

#include <ui/layer.hpp>

class BuildingUpgradeButton;

class MainLayer : public Layer {
private:
    std::vector<std::shared_ptr<BuildingUpgradeButton>> m_all_building_upgrade_buttons;
public:
    MainLayer(WindowManager& window_manager);

    void display();
};