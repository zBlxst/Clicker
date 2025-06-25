#include "spells/spell_call_to_army.hpp"

#include <thread>
#include <iostream>

#include "game_manager.hpp"

SpellCallToArmy::SpellCallToArmy(int index, GameManager& game_manager) : 
    Spell(BASE_COST, index, game_manager),
    m_thread(std::make_shared<std::thread>(&SpellCallToArmy::thread_function, this)) {
        m_game_manager.add_thread(m_thread);
    }

void SpellCallToArmy::thread_function() {
    while (m_game_manager.is_running()) {
        while (!m_running && m_game_manager.is_running()) {
            sleep(1);
        }
        m_game_manager.add_money_multiplicative_upgrade(BASE_BOOST);
        for (int i = 0; i < BASE_TIME; i++) {
            if (!m_game_manager.is_running()) {
                return;
            }
            sleep(1);
        }
        m_running = false;
        m_game_manager.add_money_multiplicative_upgrade(1/BASE_BOOST);
    }
}

void SpellCallToArmy::callback() {
    m_running = true;
}