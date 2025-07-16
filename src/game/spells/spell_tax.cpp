#include "spells/spell_tax.hpp"

#include "game_manager.hpp"

SpellTax::SpellTax(int index, GameManager& game_manager) : Spell(BASE_COST, index, 0, 
        std::make_shared<std::function<void(GameManager&)>>(start_spell),
        std::make_shared<std::function<void(GameManager&)>>(end_spell),
        game_manager) {}

void SpellTax::callback() {
    m_game_manager.add_money(get_buff()*m_game_manager.get_stat_tracker().m_last_second_gain);
}

double SpellTax::get_buff() {
    return 30;
}

bool SpellTax::is_available() {
    return true;
}