#pragma once

#include <memory>
#include <vector>

#include "ui/layer.hpp"
#include "achievement_layer/achievement_button.hpp"
#include "achievement.hpp"

// class AchievementButton;

class AchievementLayer : public Layer {
private:
    static constexpr int X = 100;
    static constexpr int Y = 100;
    static constexpr int WIDTH = 800;
    static constexpr int HEIGHT = 800;

    static constexpr int N_LINES = (Achievement::N_ACHIEVEMENTS + AchievementButton::N_COLS) / AchievementButton::N_COLS;
    static constexpr int MAX_SCROLL = N_LINES * AchievementButton::HEIGHT 
                                    + (N_LINES - 1) * AchievementButton::V_SPACING
                                    - HEIGHT
                                    + AchievementButton::BASE_POS_X * 2; 

    std::vector<std::shared_ptr<AchievementButton>> m_all_achievement_buttons;
public:
    AchievementLayer(WindowManager& window_manager);
    void recv_scroll(int delta);
};