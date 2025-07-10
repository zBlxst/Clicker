#pragma once

#include "upgrades/upgrade.hpp"



class TreasureUpgrade : public Upgrade {

public:
    static constexpr int N_UPGRADES = 5;

private:
    static constexpr double UPGRADE_REQS[N_UPGRADES] = {100000, 1e8, 1e11, 1e14, 1e17};
    static constexpr double UPGRADE_COSTS[N_UPGRADES] = {50000, 5e7, 5e10, 5e13, 5e16};
    static constexpr double UPGRADE_BUFFS[N_UPGRADES] = {0.01, 0.01, 0.01, 0.01, 0.01};

    int m_index;
public:
    TreasureUpgrade(int index, int index_in_gm, GameManager& game_manager);

    double get_cost();
    double get_buff();
    bool is_available();
    void buy_callback();


    std::vector<std::string> get_base_text_to_display();
};