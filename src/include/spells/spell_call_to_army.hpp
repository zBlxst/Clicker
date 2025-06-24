#pragma once

#include "spells/spell.hpp"

#include <thread>
#include <memory>

class SpellCallToArmy : public Spell {

public:
    static constexpr double BASE_COST = 200;
    static constexpr int BASE_TIME = 10;
    static constexpr double BASE_BOOST = 2;

private:
    void thread_function();
    std::shared_ptr<std::thread> m_thread;

public:
    SpellCallToArmy(int index, GameManager& game_manager);
    void callback();

};