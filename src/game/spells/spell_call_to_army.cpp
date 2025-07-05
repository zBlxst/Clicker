#include "spells/spell_call_to_army.hpp"

#include <thread>
#include <iostream>
#include <cmath>

#include "game_manager.hpp"

SpellCallToArmy::SpellCallToArmy(int index, GameManager& game_manager) : 
    Spell(BASE_COST, index, game_manager, BASE_MAX_TIME),
    m_thread(std::make_shared<std::thread>(&SpellCallToArmy::thread_function, this)) {
        m_game_manager.add_thread(m_thread);
    }

void SpellCallToArmy::thread_function() {
    m_remaining_time = m_max_time;
    while (m_game_manager.is_running()) {
        while (!m_running && m_game_manager.is_running()) {
            sleep(1);
        }
        double boost = get_buff();
        m_game_manager.add_money_multiplicative_upgrade(boost);
        while(m_remaining_time-- > 0 && m_game_manager.is_running()) {
            sleep(1);
        }
        m_running = false;
        m_game_manager.add_money_multiplicative_upgrade(1/boost);
    }
}

void SpellCallToArmy::callback() {
    m_running = true;
}

double SpellCallToArmy::get_buff() {
    return 1+0.01*pow(25 + 0.3*m_game_manager.get_all_buildings_level(), 0.975);
}