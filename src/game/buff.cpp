#include "buff.hpp"

#include <cmath>

Buff::Buff(GameManager& game_manager) :
    m_game_manager(game_manager),
    m_additive_buff(0),
    m_multiplicative_buff(1),
    m_exponential_buff(1),
    m_additive_buff_callbacks({}),
    m_multiplicative_buff_callbacks({}),
    m_exponential_buff_callbacks({}) {}

double Buff::get_buffed_value(double value) {
    value += m_additive_buff;
    for (std::shared_ptr<std::function<double(GameManager&)>> func : m_additive_buff_callbacks) {
        value += func->operator()(m_game_manager);
    }
    value *= m_multiplicative_buff;
    for (std::shared_ptr<std::function<double(GameManager&)>> func : m_multiplicative_buff_callbacks) {
        value *= func->operator()(m_game_manager);
    }
    value = pow(value, m_exponential_buff);
    for (std::shared_ptr<std::function<double(GameManager&)>> func : m_exponential_buff_callbacks) {
        value = pow(value, func->operator()(m_game_manager));
    }
    return value;
}

void Buff::remove_callback(std::shared_ptr<std::function<double(GameManager&)>> func_pointer) {
    std::erase(m_additive_buff_callbacks, func_pointer);
    std::erase(m_multiplicative_buff_callbacks, func_pointer);
    std::erase(m_exponential_buff_callbacks, func_pointer);
    std::erase(m_misc_callbacks, func_pointer);
}

void Buff::call_misc_callbacks() {
    for (std::shared_ptr<std::function<double(GameManager&)>> func : m_misc_callbacks) {
        func->operator()(m_game_manager);
    }
}