#pragma once

#include "upgrades/upgrade.hpp"



class MoneyUpgrade : public Upgrade {

public:
    static constexpr int N_UPGRADES = 5;

private:
    static constexpr double UPGRADE_REQS[N_UPGRADES] = {5000, 5e6, 5e9, 5e12, 5e15};
    static constexpr double UPGRADE_COSTS[N_UPGRADES] = {10000, 5e7, 1e11, 1.5e14, 2e17};
    static constexpr double UPGRADE_BUFFS[N_UPGRADES] = {1.25, 1.25, 1.25, 1.25, 1.25};

    int m_index;
public:
    MoneyUpgrade(int index, int index_in_gm, GameManager& game_manager);

    double get_cost();
    double get_buff();
    bool is_available();
    void buy_callback();


    std::vector<std::string> get_base_text_to_display();
};