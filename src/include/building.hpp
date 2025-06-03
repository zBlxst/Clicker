#pragma once

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

    unsigned int m_index;
    unsigned int m_level;

    
public:
    double m_multiplicative_buff;

    Building(int index, GameManager& game_manager);
    unsigned int get_level();
    double get_cost();
    double get_gain();
    void level_up();
};