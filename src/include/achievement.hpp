#pragma once

#include <functional>
#include <memory>
#include <vector>

class GameManager;

class Achievement {
    
public:
    static constexpr int N_MONEY_ACHIEVEMENTS = 20;
    static constexpr int N_MONEY_CLICK_ACHIEVEMENTS = 19;
    static constexpr int N_CLICK_ACHIEVEMENTS = 9;
    static constexpr int N_BUILDING_ACHIEVEMENTS = 22;
    static std::vector<std::shared_ptr<Achievement>> get_all_achievements(GameManager& game_manager);

private:
    static constexpr double MONEY_ACHIEVEMENTS[N_MONEY_ACHIEVEMENTS] = {1e3, 1e6, 1e9, 1e12, 1e15, 1e18, 1e21, 1e24, 1e27, 1e30, 1e33, 1e36, 1e66, 1e78, 1e93, 1e108, 1e123, 1e153, 1e201, 1e243};
    static constexpr double MONEY_CLICK_ACHIEVEMENTS[N_MONEY_CLICK_ACHIEVEMENTS] = {100, 1000, 1e6, 1e9, 1e12, 1e15, 1e18, 1e21, 1e24, 1e36, 1e45, 1e54, 1e66, 1e78, 1e93, 1e108, 1e123, 1e153, 1e201};
    static constexpr double CLICK_ACHIEVEMENTS[N_CLICK_ACHIEVEMENTS] = {100, 500, 1000, 2500, 5000, 10000, 50000, 100000};
    static constexpr double BUILDING_ACHIEVEMENTS[N_BUILDING_ACHIEVEMENTS] = {1, 50, 100, 150, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1500, 2000, 2500, 3000, 3500, 5000, 75000, 12000, 20000};


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
std::function<bool(GameManager&)> money_click_achievements(double amount);
std::function<bool(GameManager&)> click_achievements(double amount);
std::function<bool(GameManager&)> building_achievements(int building_index, double amount);