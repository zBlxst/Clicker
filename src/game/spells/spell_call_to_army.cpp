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
    while (m_game_manager.is_running()) {
        while (!m_running && m_game_manager.is_running()) {
            sleep(1);
        }
        std::shared_ptr<std::function<double(GameManager&)>> func_pointer = std::make_shared<std::function<double(GameManager&)>>(SpellCallToArmy::get_buff_static);
        m_game_manager.m_production_buff.m_multiplicative_buff_callbacks.push_back(func_pointer);
        while(m_remaining_time-- > 0 && m_game_manager.is_running()) {
            sleep(1);
        }
        m_running = false;
        m_game_manager.m_production_buff.remove_callback(func_pointer);
    }
}

void SpellCallToArmy::callback() {
    m_remaining_time = m_max_time;
    m_running = true;
}

bool SpellCallToArmy::is_available() {
    return true;
}

double SpellCallToArmy::get_buff() {
    return SpellCallToArmy::get_buff_static(m_game_manager);
}

double SpellCallToArmy::get_buff_static(GameManager& game_manager) {
    return 1+0.01*pow(25 + 0.3*game_manager.get_all_buildings_level(), 0.975);
}