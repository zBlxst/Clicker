#pragma once

#include "spells/spell.hpp"

class SpellTax : public Spell {

public:
    static constexpr double BASE_COST = 200;
    
private:
    static void start_spell(GameManager& game_manager) {};
    static void end_spell(GameManager& game_manager) {};
public:
    SpellTax(int index, GameManager& game_manager);
    void callback();
    double get_buff();
    bool is_available();
};