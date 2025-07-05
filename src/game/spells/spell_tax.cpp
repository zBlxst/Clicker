#include "spells/spell_tax.hpp"

#include "game_manager.hpp"

SpellTax::SpellTax(int index, GameManager& game_manager) : Spell(BASE_COST, index, game_manager, 0) {}

void SpellTax::callback() {
    m_game_manager.add_money(get_buff()*m_game_manager.get_stat_tracker().m_last_second_gain);
}

double SpellTax::get_buff() {
    return 30;
}