#pragma once

#include <functional>
#include <memory>
#include <vector>

class GameManager;

class Achievement {
    
public:
    static constexpr int N_MONEY_ACHIEVEMENTS = 12;
    static std::vector<std::shared_ptr<Achievement>> get_all_achievements(GameManager& game_manager);

private:
static constexpr double MONEY_ACHIEVEMENTS[N_MONEY_ACHIEVEMENTS] = {1e3, 1e6, 1e9, 1e12, 1e15, 1e18, 1e21, 1e24, 1e27, 1e30, 1e33, 1e36};


protected:
    bool m_obtained;
    GameManager& m_game_manager;

public:
    Achievement(GameManager& game_manager, std::function<bool(GameManager&)> check_function);
    void update();
    bool is_obtained();
    std::function<bool(GameManager&)> check_if_obtained;
};

std::function<bool(GameManager&)> money_achievements(double amount);