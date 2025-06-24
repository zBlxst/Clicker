#include "spells/spell.hpp"

#include "game_manager.hpp"

#include "spells/spell_tax.hpp"
#include "spells/spell_call_to_army.hpp"

Spell::Spell(double cost, int index, GameManager& game_manager) :
    m_cost(cost),
    m_index(index),
    m_running(false),
    m_game_manager(game_manager) {}

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

std::vector<std::string> Spell::get_base_text_to_display() {
    return {};
}

std::vector<std::shared_ptr<Spell>> Spell::get_one_of_each(GameManager& game_manager) {
    int spell_index = 0;
    return {
        std::make_shared<SpellTax>(spell_index++, game_manager),
        std::make_shared<SpellCallToArmy>(spell_index++, game_manager)
    };
}

