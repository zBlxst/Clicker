#include "upgrade.hpp"

#include "game_manager.hpp"

#include <iostream>

Upgrade::Upgrade(int index_in_gm, GameManager& game_manager) :
    m_index_in_gm(index_in_gm),
    m_game_manager(game_manager),
    m_bought(false) {}

void Upgrade::reset() {
    m_bought = false;
}

bool Upgrade::is_bought() {
    return m_bought;
}

bool Upgrade::is_available() {
    return !m_bought;
}

void Upgrade::buy() {
    if (is_available() && m_game_manager.buy(get_cost())) {
        m_bought = true;
        buy_callback();
    }
}