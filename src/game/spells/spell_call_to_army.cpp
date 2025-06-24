#include "spells/spell_call_to_army.hpp"

#include <thread>
#include <iostream>

#include "game_manager.hpp"

SpellCallToArmy::SpellCallToArmy(int index, GameManager& game_manager) : 
    Spell(BASE_COST, index, game_manager),
    m_thread(std::thread(&SpellCallToArmy::thread_function, this)) {}

void SpellCallToArmy::thread_function() {
    while (m_game_manager.is_running()) {
        while (!m_running) {
            sleep(1);
        }
        m_game_manager.add_money_multiplicative_upgrade(BASE_BOOST);
        sleep(BASE_TIME);
        m_game_manager.add_money_multiplicative_upgrade(1/BASE_BOOST);
        m_running = false;
    }
}

void SpellCallToArmy::callback() {
    m_running = true;
}