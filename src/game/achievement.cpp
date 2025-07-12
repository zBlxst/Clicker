#include "achievement.hpp"

#include <iostream>

#include "game_manager.hpp"
#include "building.hpp"

Achievement::Achievement(GameManager& game_manager, std::function<bool(GameManager&)> check_function) :
    m_obtained(false),
    m_game_manager(game_manager),
    check_if_obtained(check_function) {}

std::vector<std::shared_ptr<Achievement>> Achievement::get_all_achievements(GameManager& game_manager) {
    std::vector<std::shared_ptr<Achievement>> res = {};

    // Money achievements
    for (int i = 0; i < Achievement::N_MONEY_ACHIEVEMENTS; i++) {
        res.push_back(std::make_shared<Achievement>(game_manager, money_achievements(Achievement::MONEY_ACHIEVEMENTS[i])));
    }

    // Money click achievements
    for (int i = 0; i < Achievement::N_MONEY_CLICK_ACHIEVEMENTS; i++) {
        res.push_back(std::make_shared<Achievement>(game_manager, money_click_achievements(Achievement::MONEY_CLICK_ACHIEVEMENTS[i])));
    }

    // Click achievements
    for (int i = 0; i < Achievement::N_CLICK_ACHIEVEMENTS; i++) {
        res.push_back(std::make_shared<Achievement>(game_manager, click_achievements(Achievement::CLICK_ACHIEVEMENTS[i])));
    }

    // Building achievements
    for (int i = 0; i < Building::N_BUILDINGS; i++) {
        for (int j = 0; j < Achievement::N_BUILDING_ACHIEVEMENTS; j++) {
            res.push_back(std::make_shared<Achievement>(game_manager, building_achievements(i, Achievement::MONEY_ACHIEVEMENTS[j])));
        }
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
    return [amount](GameManager& game_manager) { return game_manager.get_stat_tracker().m_total_gain >= amount; };
}

std::function<bool(GameManager&)> money_click_achievements(double amount) {
    return [amount](GameManager& game_manager) { return game_manager.get_stat_tracker().m_click_gain >= amount; };
}

std::function<bool(GameManager&)> click_achievements(double amount) {
    return [amount](GameManager& game_manager) { return game_manager.get_stat_tracker().m_clicks >= amount; };
}


std::function<bool(GameManager&)> building_achievements(int building_index, double amount) {
    return [building_index, amount](GameManager& game_manager) { return game_manager.get_all_buildings()[building_index]->get_level() >= amount; };
}