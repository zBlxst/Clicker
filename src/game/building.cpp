#include "building.hpp"

#include <cmath>

#include "faction.hpp"
#include "game_manager.hpp"

Building::Building(int index, GameManager& game_manager) : 
    m_index(index),
    m_game_manager(game_manager),
    m_level(0),
    m_multiplicative_buff(1) {}

unsigned int Building::get_level() {
    return m_level;
}

double Building::get_cost() {
    return BASE_COSTS[m_index]*pow(1.15, m_level);
}

void Building::level_up() {
    if (m_game_manager.buy(get_cost())) {
        m_level += 1;
    }
}

double Building::get_gain() {
    if (m_index <= 10) {
        return BASE_PRODS[m_index]*m_level*m_multiplicative_buff;
    } else {
        return BASE_PRODS[m_index]*m_level*m_game_manager.get_stat_tracker().m_n_achievements;
    }
}

int Building::get_index() {
    return m_index;
}

void Building::set_level(int value) {
    m_level = value;
}

bool Building::is_available() {
    if (m_index <= 2) {
        return true;
    }
    return m_game_manager.get_morality() != Faction::MORALITY::NONE;
}