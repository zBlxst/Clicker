#pragma once

#include "spells/spell.hpp"

#include <thread>
#include <memory>

class SpellBloodFrenzy : public Spell {

public:
    static constexpr double BASE_COST = 600;
    static constexpr int BASE_MAX_TIME = 20;
    
    inline static std::shared_ptr<std::function<double(GameManager&)>> func_pointer = nullptr;

private:
    static void start_spell(GameManager& game_manager);
    static void end_spell(GameManager& game_manager);

public:
    SpellBloodFrenzy(int index, GameManager& game_manager);
    double get_buff();
    static double get_buff_static(GameManager& game_manager);
    bool is_available();
};
