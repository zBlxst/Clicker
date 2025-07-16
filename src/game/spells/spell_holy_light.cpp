#include "spells/spell_holy_light.hpp"

#include <thread>
#include <iostream>
#include <cmath>

#include "game_manager.hpp"

SpellHolyLight::SpellHolyLight(int index, GameManager& game_manager) : 
    Spell(BASE_COST, index, BASE_MAX_TIME, 
        std::make_shared<std::function<void(GameManager&)>>(start_spell),
        std::make_shared<std::function<void(GameManager&)>>(end_spell),
        game_manager) {
        func_pointer = std::make_shared<std::function<double(GameManager&)>>(SpellHolyLight::get_buff_static);
    }

bool SpellHolyLight::is_available() {
    return m_game_manager.get_morality() == Faction::MORALITY::GOOD;
}


double SpellHolyLight::get_buff() {
    return SpellHolyLight::get_buff_static(m_game_manager);
}

double SpellHolyLight::get_buff_static(GameManager& game_manager) {
    return 17.50;
}

void SpellHolyLight::start_spell(GameManager& game_manager) {
    game_manager.m_click_buff.m_multiplicative_buff_callbacks.push_back(SpellHolyLight::func_pointer);
}

void SpellHolyLight::end_spell(GameManager& game_manager) {
    game_manager.m_click_buff.remove_callback(SpellHolyLight::func_pointer);
}