#include "upgrades/building_upgrade.hpp"

#include "game_manager.hpp"
#include <iostream>
#include <format>

BuildingUpgrade::BuildingUpgrade(int building_index, int upgrade_index, int index_in_gm, GameManager &game_manager) :
    Upgrade(index_in_gm, game_manager),
    m_building_index(building_index),
    m_upgrade_index(upgrade_index) {}

int BuildingUpgrade::get_req() {
    return UPGRADE_REQS[m_upgrade_index];
}

double BuildingUpgrade::get_buff() {
    return UPGRADE_BUFFS[m_upgrade_index];
}

double BuildingUpgrade::get_cost() {
    return UPGRADE_COSTS[m_building_index][m_upgrade_index];
}

void BuildingUpgrade::buy_callback() {
    m_game_manager.get_all_buildings()[m_building_index]->m_buff.m_multiplicative_buff *= get_buff();
    if (m_upgrade_index < 2 && m_building_index <= 10) {
        m_game_manager.add_assistants(1);
    }
}

std::vector<std::string> BuildingUpgrade::get_base_text_to_display() {
    std::vector<std::string> res = {
        std::format("Building : {}", m_building_index)
    };
    return res;
}

bool BuildingUpgrade::is_available() {
    return Upgrade::is_available() && m_game_manager.get_all_buildings()[m_building_index]->get_level() >= get_req();
}