#pragma once

#include <functional>
#include <memory>
#include <vector>

class GameManager;

class Achievement {

public:
    static std::vector<std::shared_ptr<Achievement>> get_all_achievements(GameManager& game_manager);

protected:
    bool m_obtained;
    GameManager& m_game_manager;

public:
    Achievement(GameManager& game_manager, std::function<bool(GameManager&)> check_function);
    void update();
    bool is_obtained();
    std::function<bool(GameManager&)> check_if_obtained;
};

bool money1(GameManager& game_manager);