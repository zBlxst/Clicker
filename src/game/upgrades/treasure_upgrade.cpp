#include "upgrades/treasure_upgrade.hpp"

#include "game_manager.hpp"

#include <format>

TreasureUpgrade::TreasureUpgrade(int index, int index_in_gm, GameManager& game_manager) :
    m_index(index),
    Upgrade(index_in_gm, game_manager) {}

std::vector<std::string> TreasureUpgrade::get_base_text_to_display() {
    std::vector<std::string> res = {
        std::format("Treasure")
    };
    return res;
}

double TreasureUpgrade::get_cost() {
    return UPGRADE_COSTS[m_index];
}
double TreasureUpgrade::get_buff() {
    return UPGRADE_BUFFS[m_index];
}
bool TreasureUpgrade::is_available() {
    return Upgrade::is_available() && m_game_manager.get_stat_tracker().m_total_gain >= UPGRADE_REQS[m_index];
}
void TreasureUpgrade::buy_callback() {
    double buff = get_buff();
    m_game_manager.m_click_buff.m_additive_buff_callbacks.push_back(
      std::make_shared<std::function<double(GameManager&)>>([buff](GameManager& game_manager) { return buff*game_manager.get_building_prod(); })
    );
}