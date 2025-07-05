#include "achievement.hpp"

#include <iostream>

#include "game_manager.hpp"

Achievement::Achievement(GameManager& game_manager, std::function<bool(GameManager&)> check_function) :
    m_obtained(false),
    m_game_manager(game_manager),
    check_if_obtained(check_function) {}

std::vector<std::shared_ptr<Achievement>> Achievement::get_all_achievements(GameManager& game_manager) {
    std::vector<std::shared_ptr<Achievement>> res = {};
    for (int i = 0; i < Achievement::N_MONEY_ACHIEVEMENTS; i++) {
        res.push_back(std::make_shared<Achievement>(game_manager, money_achievements(Achievement::MONEY_ACHIEVEMENTS[i])));
    }
    return res;
}


void Achievement::update() {
    if (!m_obtained && check_if_obtained(m_game_manager)) {
        std::cout << "Obtained" << std::endl;
        m_game_manager.get_stat_tracker().m_n_achievements++;
        m_obtained = true;
    }
}

bool Achievement::is_obtained() {
    return m_obtained;
}

// Achievement functions
std::function<bool(GameManager&)> money_achievements(double amount) {
    return [amount](GameManager& game_manager) { return game_manager.get_money() >= amount; };
}
