#include "achievements/money_achievement.hpp"

#include "game_manager.hpp"

MoneyAchievement::MoneyAchievement(double requirement, GameManager& game_manager) : 
    Achievement(game_manager),
    m_requirement(requirement) {}

void MoneyAchievement::check_if_obtained() {
    if (!m_obtained && m_game_manager.get_money() >= m_requirement) {
        obtain();
    }
}