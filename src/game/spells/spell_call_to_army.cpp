#include "spells/spell_call_to_army.hpp"

#include <thread>
#include <iostream>
#include <cmath>

#include "game_manager.hpp"

SpellCallToArmy::SpellCallToArmy(int index, GameManager& game_manager) : 
    Spell(BASE_COST, index, BASE_MAX_TIME, 
        std::make_shared<std::function<void(GameManager&)>>(start_spell),
        std::make_shared<std::function<void(GameManager&)>>(end_spell),
        game_manager) {
        func_pointer = std::make_shared<std::function<double(GameManager&)>>(SpellCallToArmy::get_buff_static);
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

void SpellCallToArmy::start_spell(GameManager& game_manager) {
    game_manager.m_production_buff.m_multiplicative_buff_callbacks.push_back(func_pointer);
}

void SpellCallToArmy::end_spell(GameManager& game_manager) {
    game_manager.m_production_buff.remove_callback(func_pointer);
}