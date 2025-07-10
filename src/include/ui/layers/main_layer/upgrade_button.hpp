#pragma once

#include "ui/button.hpp"
#include <memory>

class WindowManager;
class Upgrade;

class UpgradeButton : public Button {

private:
    static constexpr int BASE_POS_X = 10;
    static constexpr int BASE_POS_Y = 200;
    static constexpr int WIDTH = 100;
    static constexpr int HEIGHT = 100;
    static constexpr int V_SPACING = 10;
    static constexpr int H_SPACING = 10;
    static constexpr int N_COLS = 5;

    
    int m_ui_index;
    
    bool should_catch_click();
    
public:
    const std::shared_ptr<Upgrade> m_upgrade;
    
    UpgradeButton(std::shared_ptr<Upgrade> upgrade, WindowManager& window_manager);
    void callback();
    void display();
    void update_ui_index(int index);
};