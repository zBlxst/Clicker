#pragma once

class GameManager;

class Building {

public:
    static constexpr int N_BUILDINGS = 11;
    static constexpr double BASE_COSTS[N_BUILDINGS] = {   10, 125, 600, 1800, 5600, 
                                                38000, 442000, 7300000,
                                                145000000, 3200000000,
                                                200000000000
                                            };

protected:
    GameManager& m_game_manager;

    unsigned int m_index;
    unsigned int m_level;

public:
    Building(int index, GameManager& game_manager);
    unsigned int get_level();
    double get_cost();
    void level_up();
};