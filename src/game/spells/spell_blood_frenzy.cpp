#include "spells/spell_blood_frenzy.hpp"

#include <thread>
#include <iostream>
#include <cmath>

#include "game_manager.hpp"
#include "building.hpp"

SpellBloodFrenzy::SpellBloodFrenzy(int index, GameManager& game_manager) : 
    Spell(BASE_COST, index, game_manager, BASE_MAX_TIME),
    m_thread(std::make_shared<std::thread>(&SpellBloodFrenzy::thread_function, this)) {
        m_game_manager.add_thread(m_thread);
    }

void SpellBloodFrenzy::thread_function() {
    while (m_game_manager.is_running()) {
        while (!m_running && m_game_manager.is_running()) {
            sleep(1);
        }
        std::shared_ptr<std::function<double(GameManager&)>> func_pointer = std::make_shared<std::function<double(GameManager&)>>(SpellBloodFrenzy::get_buff_static);
        for (std::shared_ptr<Building> building : m_game_manager.get_all_buildings()) {
            if (building->m_morality == Faction::MORALITY::BAD) {
                building->m_buff.m_multiplicative_buff_callbacks.push_back(func_pointer);
            }
        }
        while(m_remaining_time-- > 0 && m_game_manager.is_running()) {
            sleep(1);
        }
        m_running = false;
        for (std::shared_ptr<Building> building : m_game_manager.get_all_buildings()) {
            if (building->m_morality == Faction::MORALITY::BAD) {
                building->m_buff.remove_callback(func_pointer);
            }
        }
    }
}

void SpellBloodFrenzy::callback() {
    m_remaining_time = m_max_time;
    m_running = true;
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