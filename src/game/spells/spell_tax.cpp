#include "spells/spell_tax.hpp"

#include "game_manager.hpp"

SpellTax::SpellTax(int index, GameManager& game_manager) : Spell(BASE_COST, index, game_manager) 
    {}

void SpellTax::callback() {
    m_game_manager.add_money(30*m_game_manager.get_stat_tracker().m_last_second_gain);
}