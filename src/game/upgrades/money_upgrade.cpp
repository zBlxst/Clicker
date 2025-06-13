#include "upgrades/money_upgrade.hpp"

#include "game_manager.hpp"

#include <format>

MoneyUpgrade::MoneyUpgrade(int index, unsigned int index_in_gm, GameManager& game_manager) :
    m_index(index),
    Upgrade(index_in_gm, game_manager) {}

std::vector<std::string> MoneyUpgrade::get_base_text_to_display() {
    std::vector<std::string> res = {
        std::format("Money")
    };
    return res;
}

double MoneyUpgrade::get_cost() {
    return UPGRADE_COSTS[m_index];
}
double MoneyUpgrade::get_buff() {
    return UPGRADE_BUFFS[m_index];
}
bool MoneyUpgrade::is_available() {
    return Upgrade::is_available() && m_game_manager.get_stat_tracker().m_click_gain >= UPGRADE_REQS[m_index];
}
void MoneyUpgrade::buy_callback() {
    m_game_manager.add_click_multiplicative_upgrade(get_buff());
    m_game_manager.add_money_multiplicative_upgrade(get_buff());
}