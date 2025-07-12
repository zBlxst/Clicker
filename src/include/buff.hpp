#pragma once

#include <vector>
#include <memory>
#include <functional>

class GameManager;

class Buff {

public:
    GameManager& m_game_manager;

    double m_additive_buff;
    double m_multiplicative_buff;
    double m_exponential_buff;

    std::vector<std::shared_ptr<std::function<double(GameManager&)>>> m_additive_buff_callbacks;
    std::vector<std::shared_ptr<std::function<double(GameManager&)>>> m_multiplicative_buff_callbacks;
    std::vector<std::shared_ptr<std::function<double(GameManager&)>>> m_exponential_buff_callbacks;
    std::vector<std::shared_ptr<std::function<double(GameManager&)>>> m_misc_callbacks;

    void remove_callback(std::shared_ptr<std::function<double(GameManager&)>>);

    Buff(GameManager& game_manager);
    double get_buffed_value(double value);
    void call_misc_callbacks();
};