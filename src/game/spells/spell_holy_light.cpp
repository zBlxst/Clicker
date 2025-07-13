#include "spells/spell_holy_light.hpp"

#include <thread>
#include <iostream>
#include <cmath>

#include "game_manager.hpp"

SpellHolyLight::SpellHolyLight(int index, GameManager& game_manager) : 
    Spell(BASE_COST, index, game_manager, BASE_MAX_TIME),
    m_thread(std::make_shared<std::thread>(&SpellHolyLight::thread_function, this)) {
        m_game_manager.add_thread(m_thread);
    }

void SpellHolyLight::thread_function() {
    while (m_game_manager.is_running()) {
        while (!m_running && m_game_manager.is_running()) {
            sleep(1);
        }
        std::shared_ptr<std::function<double(GameManager&)>> func_pointer = std::make_shared<std::function<double(GameManager&)>>(SpellHolyLight::get_buff_static);
        m_game_manager.m_click_buff.m_multiplicative_buff_callbacks.push_back(func_pointer);
        while(m_remaining_time-- > 0 && m_game_manager.is_running()) {
            sleep(1);
        }
        m_running = false;
        m_game_manager.m_click_buff.remove_callback(func_pointer);
    }
}

void SpellHolyLight::callback() {
    m_remaining_time = m_max_time;
    m_running = true;
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