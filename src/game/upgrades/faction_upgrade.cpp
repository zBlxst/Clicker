#include "upgrades/faction_upgrade.hpp"

#include "game_manager.hpp"
#include <iostream>
#include <format>

FactionUpgrade::FactionUpgrade(Faction::MORALITY morality, Faction::FACTION faction, unsigned int index_in_gm, GameManager& game_manager) :
    UpgradeFactionCoins(index_in_gm, Faction::get_faction_coins_per_faction(faction), game_manager),
    m_morality(morality),
    m_faction(faction) {}


double FactionUpgrade::get_cost() {
    return UPGRADE_COSTS[m_faction];
}

void FactionUpgrade::buy_callback() {
    m_game_manager.set_faction(m_faction);
}

std::vector<std::string> FactionUpgrade::get_base_text_to_display() {
    std::vector<std::string> res = {
        std::format("Faction : {}", Faction::FACTIONS_NAMES[m_faction])
    };
    return res;
}

bool FactionUpgrade::is_available() {
    return UpgradeFactionCoins::is_available() && m_game_manager.get_morality() == m_morality && m_game_manager.get_faction() == Faction::NO_FACTION;
}

double FactionUpgrade::get_buff() {
    return 0;
}