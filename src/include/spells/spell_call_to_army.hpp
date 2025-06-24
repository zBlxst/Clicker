#pragma once

#include "spells/spell.hpp"

#include <thread>

class SpellCallToArmy : public Spell {

public:
    static constexpr double BASE_COST = 0;
    static constexpr int BASE_TIME = 3;
    static constexpr double BASE_BOOST = 2;

private:
    void thread_function();
    std::thread m_thread;

public:
    SpellCallToArmy(int index, GameManager& game_manager);
    void callback();

};