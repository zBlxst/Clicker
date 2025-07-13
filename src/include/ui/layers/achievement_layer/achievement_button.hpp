#pragma once

#include "ui/button.hpp"
#include <memory>

class WindowManager;
class Achievement;

class AchievementButton : public Button {

public:
    static constexpr int BASE_POS_X = 20;
    static constexpr int BASE_POS_Y = 20;
    static constexpr int WIDTH = 100;
    static constexpr int HEIGHT = 100;
    static constexpr int V_SPACING = 10;
    static constexpr int H_SPACING = 10;
    static constexpr int N_COLS = 7;

private:
    int m_ui_index;
    
    bool should_catch_click();
    
public:
    const std::shared_ptr<Achievement> m_achievement;
    
    AchievementButton(std::shared_ptr<Achievement> achievement, WindowManager& window_manager);
    void callback();
    void display();
    void update_ui_index(int index);
    sf::Color get_background_color();
};