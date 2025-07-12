#pragma once

#include <memory>
#include <vector>

#include "ui/layer.hpp"

class AchievementButton;

class AchievementLayer : public Layer {
private:
    static constexpr int X = 100;
    static constexpr int Y = 100;
    static constexpr int WIDTH = 800;
    static constexpr int HEIGHT = 800;

    std::vector<std::shared_ptr<AchievementButton>> m_all_achievement_buttons;
public:
    AchievementLayer(WindowManager& window_manager);
};