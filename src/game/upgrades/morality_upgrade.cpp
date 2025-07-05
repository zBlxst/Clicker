#include "upgrades/morality_upgrade.hpp"

#include "game_manager.hpp"
#include <iostream>
#include <format>

MoralityUpgrade::MoralityUpgrade(unsigned int index_in_gm, GameManager &game_manager) :
    Upgrade(index_in_gm, game_manager),
    m_morality((Faction::MORALITY)index_in_gm) {}


double MoralityUpgrade::get_cost() {
    return UPGRADE_COSTS[m_morality];
}

void MoralityUpgrade::buy_callback() {
    m_game_manager.set_morality(m_morality);
}

std::vector<std::string> MoralityUpgrade::get_base_text_to_display() {
    std::vector<std::string> res = {
        std::format("Morality : {}", Faction::MORALITIES_NAMES[m_morality], (int)m_morality)
    };
    return res;
}

bool MoralityUpgrade::is_available() {
    return Upgrade::is_available() && m_game_manager.get_morality() == Faction::NONE;
}

double MoralityUpgrade::get_buff() {
    return 0;
}