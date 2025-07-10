#include "upgrades/faction_upgrades/morality_picker.hpp"

#include "game_manager.hpp"
#include "building.hpp"

#include <iostream>
#include <format>

MoralityPicker::MoralityPicker(Faction::MORALITY morality, int index_in_gm, GameManager &game_manager) :
    Upgrade(index_in_gm, game_manager),
    m_morality(morality) {}


double MoralityPicker::get_cost() {
    return UPGRADE_COSTS[m_morality];
}

void MoralityPicker::buy_callback() {
    m_game_manager.set_morality(m_morality);
    for (int i = 3; i < 10; i++) {
        m_game_manager.get_all_buildings()[i]->m_morality = m_morality;
    }
}

std::vector<std::string> MoralityPicker::get_base_text_to_display() {
    std::vector<std::string> res = {
        std::format("Morality : {}", Faction::MORALITIES_NAMES[m_morality])
    };
    return res;
}

bool MoralityPicker::is_available() {
    return Upgrade::is_available() && m_game_manager.get_morality() == Faction::NO_MORALITY;
}

double MoralityPicker::get_buff() {
    return 0;
}