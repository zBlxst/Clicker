#include <building_upgrade.hpp>

#include "game_manager.hpp"
#include <iostream>

BuildingUpgrade::BuildingUpgrade(unsigned int building_index, unsigned int upgrade_index, GameManager &game_manager) :
    m_game_manager(game_manager),
    m_building_index(building_index),
    m_upgrade_index(upgrade_index) {}

int BuildingUpgrade::get_req() {
    return UPGRADE_REQS[m_upgrade_index];
}

int BuildingUpgrade::get_buff() {
    return UPGRADE_BUFFS[m_upgrade_index];
}

double BuildingUpgrade::get_upgrade_cost() {
    return UPGRADE_COSTS[m_building_index][m_upgrade_index];
}

void BuildingUpgrade::buy() {
    if (!m_bought && m_game_manager.buy(get_upgrade_cost())) {
        std::cout << "Here" << m_building_index << m_upgrade_index << std::endl;
        m_bought = true;
        m_game_manager.get_all_buildings()[m_building_index]->m_multiplicative_buff *= get_buff();
    }
}

bool BuildingUpgrade::is_available() {
    return !m_bought && m_game_manager.get_all_buildings()[m_building_index]->get_level() >= get_req();
}

bool BuildingUpgrade::is_bought() {
    return m_bought;
}