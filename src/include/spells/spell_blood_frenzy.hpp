#pragma once

#include "spells/spell.hpp"

#include <thread>
#include <memory>

class SpellBloodFrenzy : public Spell {

public:
    static constexpr double BASE_COST = 600;
    static constexpr int BASE_MAX_TIME = 20;

private:
    void thread_function();
    std::shared_ptr<std::thread> m_thread;

public:
    SpellBloodFrenzy(int index, GameManager& game_manager);
    void callback();
    double get_buff();
    static double get_buff_static(GameManager& game_manager);
    bool is_available();
};