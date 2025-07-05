#pragma once

#include "spells/spell.hpp"

#include <thread>
#include <memory>

class SpellCallToArmy : public Spell {

public:
    static constexpr double BASE_COST = 200;
    static constexpr int BASE_MAX_TIME = 30;
    static constexpr double BOOST_PER_BUILDING = 2;

private:
    void thread_function();
    std::shared_ptr<std::thread> m_thread;

public:
    SpellCallToArmy(int index, GameManager& game_manager);
    void callback();
    double get_buff();

};