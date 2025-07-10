#pragma once

#include "upgrades/upgrade.hpp"



class ClickUpgrade : public Upgrade {

public:
    static constexpr int N_UPGRADES = 6;

private:
    static constexpr double UPGRADE_REQS[N_UPGRADES] = {100, 500, 2500, 10000, 50000, 100000};
    static constexpr double UPGRADE_COSTS[N_UPGRADES] = {500, 5000, 5e6, 5e9, 5e13, 5e16};
    static constexpr double UPGRADE_BUFFS[N_UPGRADES] = {4, 45, 4950, 500000, 5e7, 5e10};

    int m_index;
public:
    ClickUpgrade(int index, int index_in_gm, GameManager& game_manager);

    double get_cost();
    double get_buff();
    bool is_available();
    void buy_callback();


    std::vector<std::string> get_base_text_to_display();
};