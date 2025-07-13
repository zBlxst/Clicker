#include "ui/layers/achievement_layer/achievement_layer.hpp"

#include "ui/layers/achievement_layer/achievement_button.hpp"
#include "achievement.hpp"

#include "game_manager.hpp"
#include "window_manager.hpp"

AchievementLayer::AchievementLayer(WindowManager& window_manager) :
    Layer(X, Y, WIDTH, HEIGHT, window_manager),
    m_all_achievement_buttons() {
        int n_achievement = 0;
        for (std::shared_ptr<Achievement> achievement : window_manager.get_game_manager().get_all_achievements()) {
            std::shared_ptr<AchievementButton> achievement_button = std::make_shared<AchievementButton>(achievement, window_manager);
            m_all_achievement_buttons.push_back(achievement_button);
            m_all_buttons.push_back(achievement_button);
            achievement_button->update_ui_index(n_achievement++);
        }
    }

void AchievementLayer::recv_scroll(int delta) {
    m_y_offset += 30*delta;
    if (m_y_offset >= 0) {
        m_y_offset = 0;
    }
    if (m_y_offset <= -MAX_SCROLL) {
        m_y_offset = -MAX_SCROLL;
    } 
}