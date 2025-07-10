#pragma once

#include "buff.hpp"
#include "faction.hpp"

class GameManager;

class Building {

public:
    static constexpr int N_BUILDINGS = 11;
    static constexpr double BASE_COSTS[N_BUILDINGS] = {  
                                                10, 125, 600, 1800, 5600, 
                                                38000, 442000, 7300000,
                                                145000000, 3200000000,
                                                200000000000
                                            };
    static constexpr double BASE_PRODS[N_BUILDINGS] = {    
                                                2, 6, 20, 65, 200, 
                                                650, 2000, 8500,
                                                100000, 1200000,
                                                250000
                                            };


protected:
    GameManager& m_game_manager;

    int m_index;
    int m_level;

public:
    Buff m_buff;
    Faction::MORALITY m_morality;
    double m_cost_multiplier_buff;

    Building(int index, GameManager& game_manager);
    int get_level();
    int get_index();
    double get_cost();
    double get_gain();
    void level_up();
    bool is_available();
    void set_level(int value);
};