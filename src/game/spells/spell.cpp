#include "spells/spell.hpp"

#include "game_manager.hpp"

#include "spells/spell_tax.hpp"
#include "spells/spell_call_to_army.hpp"
#include "spells/spell_holy_light.hpp"
#include "spells/spell_blood_frenzy.hpp"

#include <iostream>


Spell::Spell(double cost, int index, int max_time, std::shared_ptr<std::function<void(GameManager&)>> start_spell, std::shared_ptr<std::function<void(GameManager&)>> end_spell, GameManager& game_manager) :
    m_cost(cost),
    m_index(index),
    m_running(false),
    m_max_time(max_time),
    m_game_manager(game_manager),
    m_start_spell(start_spell),
    m_end_spell(end_spell),
    m_thread(std::make_shared<std::thread>(&Spell::thread_function, this)) {
        m_game_manager.add_thread(m_thread);
    }

void Spell::reset() {
    m_remaining_time = 0;
}

void Spell::cast() {
    if (m_game_manager.cast_spell(m_cost)) {
        callback();
    }    
}

double Spell::get_cost() {
    return m_cost;
}

bool Spell::is_running() {
    return m_running;
}

void Spell::callback() {
    m_remaining_time = m_max_time;
    m_running = true;
}

void Spell::thread_function() {
    // Wait for the GameManager to start
    while (!m_game_manager.is_running()) {}

    while (m_game_manager.is_running()) {
        while (!m_running && m_game_manager.is_running()) {
            sleep(1);
        }
        m_start_spell->operator()(m_game_manager);
        while(m_remaining_time-- > 0 && m_game_manager.is_running()) {
            sleep(1);
        }
        m_running = false;
        m_end_spell->operator()(m_game_manager);
    }
}

std::vector<std::string> Spell::get_base_text_to_display() {
    return {};
}

std::vector<std::shared_ptr<Spell>> Spell::get_one_of_each(GameManager& game_manager) {
    int spell_index = 0;
    return {
        std::make_shared<SpellTax>(spell_index++, game_manager),
        std::make_shared<SpellCallToArmy>(spell_index++, game_manager),
        std::make_shared<SpellHolyLight>(spell_index++, game_manager),
        std::make_shared<SpellBloodFrenzy>(spell_index++, game_manager),
    };
}

int Spell::get_max_time() {
    return m_max_time;
}

int Spell::get_remaining_time() {
    return m_remaining_time;
}