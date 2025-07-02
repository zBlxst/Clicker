#include "achievements/achievement.hpp"

#include <iostream>

Achievement::Achievement(GameManager& game_manager) :
    m_obtained(false),
    m_game_manager(game_manager) {}

void Achievement::obtain() {
    std::cout << "Obtained" << std::endl;
    m_obtained = true;
}

bool Achievement::is_obtained() {
    return m_obtained;
}