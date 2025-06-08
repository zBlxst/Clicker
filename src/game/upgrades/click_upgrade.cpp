#include "upgrades/click_upgrade.hpp"

#include "game_manager.hpp"

#include <format>

ClickUpgrade::ClickUpgrade(int index, unsigned int index_in_gm, GameManager& game_manager) :
    m_index(index),
    Upgrade(index_in_gm, game_manager) {}

std::vector<std::string> ClickUpgrade::get_base_text_to_display() {
    std::vector<std::string> res = {
        std::format("Click")
    };
    return res;
}

double ClickUpgrade::get_cost() {
    return UPGRADE_COSTS[m_index];
}
double ClickUpgrade::get_buff() {
    return UPGRADE_BUFFS[m_index];
}
bool ClickUpgrade::is_available() {
    return Upgrade::is_available() && m_game_manager.get_stat_tracker().m_clicks >= UPGRADE_REQS[m_index];
}
void ClickUpgrade::buy_callback() {
    m_game_manager.add_click_additive_upgrade(get_buff());
}