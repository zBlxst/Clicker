#include "upgrade.hpp"

#include "game_manager.hpp"

Upgrade::Upgrade(unsigned int index_in_gm, GameManager& game_manager) :
    m_index_in_gm(index_in_gm),
    m_game_manager(game_manager),
    m_bought(false) {}

bool Upgrade::is_bought() {
    return m_bought;
}

void Upgrade::buy() {
    if (!m_bought && m_game_manager.buy(get_cost())) {
        m_bought = true;
        buy_callback();
    }
}