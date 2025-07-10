#pragma once

#include <string>
#include <vector>

#include "upgrades/upgrade.hpp"
#include "faction.hpp"
class GameManager;

class UpgradeFactionCoins : public Upgrade {

protected:
    std::vector<Faction::FACTION_COINS> m_faction_coins;

public:
    UpgradeFactionCoins(int index_in_gm, std::vector<Faction::FACTION_COINS> faction_coins, GameManager& game_manager);
    virtual void buy();
};