#pragma once

#include "spells/spell.hpp"

#include <thread>
#include <memory>

class SpellHolyLight : public Spell {

public:
    static constexpr double BASE_COST = 900;
    static constexpr int BASE_MAX_TIME = 20;
    
    inline static std::shared_ptr<std::function<double(GameManager&)>> func_pointer = 0;

private:
    static void start_spell(GameManager& game_manager);
    static void end_spell(GameManager& game_manager);

public:
    SpellHolyLight(int index, GameManager& game_manager);
    double get_buff();
    static double get_buff_static(GameManager& game_manager);
    bool is_available();
};