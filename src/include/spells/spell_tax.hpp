#pragma once

#include "spells/spell.hpp"

class SpellTax : public Spell {

public:
    static constexpr double BASE_COST = 200;
    
private:

public:
    SpellTax(int index, GameManager& game_manager);
    void callback();
    double get_buff();

};