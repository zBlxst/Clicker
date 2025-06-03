#pragma once

#include "ui/button.hpp"
#include "building_upgrade.hpp"

class WindowManager;

class BuildingUpgradeButton : public Button {

private:
    static constexpr unsigned int BASE_POS_X = 10;
    static constexpr unsigned int BASE_POS_Y = 50;
    static constexpr unsigned int WIDTH = 100;
    static constexpr unsigned int HEIGHT = 100;
    static constexpr unsigned int V_SPACING = 10;
    static constexpr unsigned int H_SPACING = 10;
    static constexpr unsigned int N_COLS = 5;
    
    int m_building_index;
    int m_upgrade_index;
    int m_ui_index;
    
    BuildingUpgrade m_upgrade;
    bool should_catch_click();

public:
    BuildingUpgradeButton(int index, WindowManager& m_window_manager);
    void callback();
    void display();
    void update_ui_index(int index);
};