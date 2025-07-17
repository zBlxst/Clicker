#include "building.hpp"

#include <cmath>

#include "faction.hpp"
#include "game_manager.hpp"

Building::Building(int index, GameManager& game_manager) : 
    m_index(index),
    m_game_manager(game_manager),
    m_level(0),
    m_buff(game_manager),
    m_cost_multiplier_buff(0),
    m_morality(Faction::MORALITY::NEUTRAL) {
        setup();
    }

void Building::reset() {
    m_level = 0;
    m_buff.reset();
    m_cost_multiplier_buff = 0;
    m_morality = Faction::MORALITY::NEUTRAL;
}

void Building::setup() {
    if (m_index == 10) {
        m_buff.m_multiplicative_buff_callbacks.push_back(
            std::make_shared<std::function<double(GameManager&)>>([](GameManager& game_manager) { return game_manager.get_stat_tracker().m_n_achievements; })
        );
    }
}

int Building::get_level() {
    return m_level;
}

double Building::get_cost() {
    return BASE_COSTS[m_index]*pow(1.15+m_cost_multiplier_buff, m_level);
}

void Building::level_up() {
    if (m_game_manager.buy(get_cost())) {
        m_level += 1;
    }
}

double Building::get_gain() {
    return m_buff.get_buffed_value(BASE_PRODS[m_index])*m_level;
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
    return m_game_manager.get_morality() != Faction::MORALITY::NO_MORALITY;
}