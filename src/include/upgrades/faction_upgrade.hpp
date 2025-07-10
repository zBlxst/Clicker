#pragma once

#include "upgrades/upgrade_faction_coins.hpp"
#include "faction.hpp"

class GameManager;

class FactionUpgrade : public UpgradeFactionCoins {

public:
    static constexpr double UPGRADE_COSTS[Faction::N_FACTIONS] = {20, 20, 20,
                                                                  20, 20, 20,
                                                                  250, 250, 250};
private:
    Faction::MORALITY m_morality;
    Faction::FACTION m_faction;
public:
    FactionUpgrade(Faction::MORALITY morality, Faction::FACTION faction, unsigned int index_in_gm, GameManager& game_manager);
    void buy_callback();
    bool is_available();
    double get_cost();
    double get_buff();

    std::vector<std::string> get_base_text_to_display();
};