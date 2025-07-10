#include "upgrades/faction_upgrades/faction_picker.hpp"

#include "game_manager.hpp"
#include "building.hpp"
#include <iostream>
#include <format>

FactionPicker::FactionPicker(Faction::MORALITY morality, Faction::FACTION faction, int index_in_gm, GameManager& game_manager) :
    UpgradeFactionCoins(index_in_gm, Faction::get_faction_coins_per_faction(faction), game_manager),
    m_morality(morality),
    m_faction(faction) {}


double FactionPicker::get_cost() {
    return UPGRADE_COSTS[m_faction];
}

void FactionPicker::buy_callback() {
    m_game_manager.set_faction(m_faction);
}

std::vector<std::string> FactionPicker::get_base_text_to_display() {
    std::vector<std::string> res = {
        std::format("Faction : {}", Faction::FACTIONS_NAMES[m_faction])
    };
    return res;
}

bool FactionPicker::is_available() {
    return UpgradeFactionCoins::is_available() && m_game_manager.get_morality() == m_morality && m_game_manager.get_faction() == Faction::NO_FACTION;
}

double FactionPicker::get_buff() {
    return 0;
}