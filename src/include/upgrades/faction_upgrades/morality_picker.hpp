#pragma once

#include "upgrades/upgrade.hpp"
#include "faction.hpp"

class GameManager;

class MoralityPicker : public Upgrade {

public:
    static constexpr double UPGRADE_COSTS[Faction::N_MORALITIES] = {25000, 25000, 1e16};
private:
    Faction::MORALITY m_morality;
public:
    MoralityPicker(Faction::MORALITY morality, int index_in_gm, GameManager& game_manager);
    void buy_callback();
    bool is_available();
    double get_cost();
    double get_buff();

    std::vector<std::string> get_base_text_to_display();
};