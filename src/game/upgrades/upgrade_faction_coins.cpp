#include "upgrades/upgrade_faction_coins.hpp"

#include "game_manager.hpp"

#include <iostream>

UpgradeFactionCoins::UpgradeFactionCoins(int index_in_gm, std::vector<Faction::FACTION_COINS> faction_coins, GameManager& game_manager) :
    Upgrade(index_in_gm, game_manager),
    m_faction_coins(std::move(faction_coins)) {}

void UpgradeFactionCoins::buy() {
    if (is_available() && m_game_manager.buy_faction_coins(get_cost(), m_faction_coins)) {
        m_bought = true;
        buy_callback();
    }
}