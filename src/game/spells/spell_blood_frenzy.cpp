#include "spells/spell_blood_frenzy.hpp"

#include <thread>
#include <iostream>
#include <cmath>

#include "game_manager.hpp"
#include "building.hpp"

SpellBloodFrenzy::SpellBloodFrenzy(int index, GameManager& game_manager) : 
    Spell(BASE_COST, index, BASE_MAX_TIME, 
        std::make_shared<std::function<void(GameManager&)>>(start_spell),
        std::make_shared<std::function<void(GameManager&)>>(end_spell),
        game_manager) {
        func_pointer = std::make_shared<std::function<double(GameManager&)>>(SpellBloodFrenzy::get_buff_static);
    }

bool SpellBloodFrenzy::is_available() {
    return m_game_manager.get_morality() == Faction::MORALITY::BAD;
}


double SpellBloodFrenzy::get_buff() {
    return SpellBloodFrenzy::get_buff_static(m_game_manager);
}

double SpellBloodFrenzy::get_buff_static(GameManager& game_manager) {
    return 12.50;
}

void SpellBloodFrenzy::start_spell(GameManager& game_manager) {
    for (std::shared_ptr<Building> building : game_manager.get_all_buildings()) {
        if (building->m_morality == Faction::MORALITY::BAD) {
            building->m_buff.m_multiplicative_buff_callbacks.push_back(func_pointer);
        }
    }
}

void SpellBloodFrenzy::end_spell(GameManager& game_manager) {
    for (std::shared_ptr<Building> building : game_manager.get_all_buildings()) {
        if (building->m_morality == Faction::MORALITY::BAD) {
            building->m_buff.remove_callback(func_pointer);
        }
    }
}