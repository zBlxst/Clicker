#include "building.hpp"

#include <cmath>

#include "game_manager.hpp"

Building::Building(int index, GameManager& game_manager) : 
    m_index(index),
    m_game_manager(game_manager),
    m_level(0) {}

unsigned int Building::get_level() {
    return m_level;
}

double Building::get_cost() {
    return BASE_COSTS[m_index]*pow(1.15, m_level);
}

void Building::level_up() {
    if (m_game_manager.get_money() >= get_cost()) {
        m_game_manager.add_money(-get_cost());
        m_level += 1;
    }
}