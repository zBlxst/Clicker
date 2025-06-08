#pragma once

#include <memory>
#include <vector>

#include "ui/layer.hpp"

class UpgradeButton;

class MainLayer : public Layer {
private:
    std::vector<std::vector<std::shared_ptr<UpgradeButton>>> m_all_upgrade_buttons;
public:
    MainLayer(WindowManager& window_manager);

    void display();
};