#pragma once

#include "upgrades/faction_upgrades/faction_upgrade.hpp"

class GameManager;

class FairyUpgrade : public FactionUpgrade {

public:
    static constexpr int N_UPGRADES = 9;

private:
    double BASE_COSTS[N_UPGRADES] = {5e7, 5e8, 5e9,
                                     5e11, 5e12, 5e13,
                                     5e15, 5e16, 5e17};

    void callback0();
    void callback1();
    void callback2();
    void callback3();
    void callback4();
    void callback5();
    void callback6();
    void callback7();
    void callback8();

public:
    FairyUpgrade(int index_in_faction, int index_in_gm, GameManager& game_manager);
    double get_cost();
    double get_buff();
    std::vector<std::string> get_base_text_to_display();
};

