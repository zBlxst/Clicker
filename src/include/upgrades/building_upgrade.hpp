#pragma once

#include "building.hpp"
#include "upgrades/upgrade.hpp"

class GameManager;

class BuildingUpgrade : public Upgrade {

public:
    static constexpr int N_UPGRADES = 19;
    const int m_building_index;
    const int m_upgrade_index;
    
private:
    static constexpr double UPGRADE_REQS[N_UPGRADES] = {5, 25, 75, 150, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1250, 1500, 1750, 2000, 2500};
    static constexpr double UPGRADE_BUFFS[N_UPGRADES] = {2, 3, 4, 5, 6, 5, 4, 3, 2, 3, 4, 5, 6, 5, 4, 5, 6, 5, 4};
    static constexpr double UPGRADE_COSTS[Building::N_BUILDINGS][N_UPGRADES] = {
        {200, 6580, 10700000.0, 509000000000.0, 689500000000000.0, 9.716e+20, 1.331e+27, 1.786e+33, 2.36e+39, 3.08e+45, 3.978e+51, 5.096e+57, 6.438e+63, 8.199e+69, 1.118e+78, 1.782e+93, 2.829e+108, 4.477e+123, 1.055e+153},
        {2510, 82300, 133800000.0, 6363000000000.0, 8619000000000000.0, 1.215e+22, 1.663e+28, 2.233e+34, 2.95e+40, 3.849e+46, 4.973e+52, 6.37e+58, 8.103e+64, 1.025e+70, 1.397e+76, 2.27e+82, 3.573e+88, 5.596e+94, 1.319e+100},
        {12070, 395020, 642100000.0, 30540000000000.0, 4.137e+16, 5.829e+22, 7.987e+28, 1.071e+35, 1.416e+41, 1.848e+50, 2.387e+53, 3.058e+59, 3.89e+65, 4.919e+71, 6.707e+80, 1.069e+96, 1.698e+111, 2.686e+126, 6.331e+156},
        {36200, 1185000.0, 1926000000.0, 91620000000000.0, 1.241e+17, 1.749e+23, 2.396e+29, 3.216e+35, 4.248e+41, 5.543e+47, 7.16e+53, 9.173e+59, 1.167e+66, 1.476e+72, 2.012e+81, 3.207e+96, 5.093e+111, 8.058e+126, 1.899e+157},
        {112640, 3687000.0, 5993000000.0, 285100000000000.0, 3.861e+17, 5.441e+23, 7.455e+29, 1e+36, 1.322e+42, 1.725e+48, 2.228e+54, 2.854e+60, 3.631e+66, 4.591e+72, 6.26e+81, 9.979e+96, 1.584e+112, 2.507e+127, 5.909e+157},
        {764320, 25020000.0, 40670000000.0, 1934000000000000.0, 2.62e+18, 3.692e+24, 5.058e+30, 6.789e+36, 8.969e+42, 1.17e+49, 1.512e+55, 1.937e+61, 2.464e+67, 3.116e+73, 4.248e+82, 6.771e+97, 1.075e+113, 1.701e+128, 4.01e+158},
        {8890000.0, 291000000.0, 473000000000.0, 2.25e+16, 3.048e+19, 4.295e+25, 5.884e+31, 7.896e+37, 1.043e+44, 1.361e+50, 1.758e+56, 2.252e+62, 2.866e+68, 3.624e+74, 4.941e+83, 7.876e+98, 1.251e+114, 1.979e+129, 4.664e+159},
        {146800000.0, 4806000000.0, 7812000000000.0, 3.716e+17, 5.033e+20, 7.093e+26, 9.718e+32, 1.304e+39, 1.723e+45, 2.248e+51, 2.904e+57, 3.72e+63, 4.733e+69, 5.985e+75, 8.16e+84, 1.301e+100, 2.065e+115, 3.268e+130, 7.703e+160},
        {2916000000.0, 95460000000.0, 155200000000000.0, 7.381e+18, 9.998e+21, 1.409e+28, 1.93e+34, 2.59e+40, 3.422e+46, 4.465e+52, 5.768e+58, 7.389e+64, 9.401e+70, 1.189e+77, 1.621e+86, 2.584e+101, 4.102e+116, 6.491e+131, 1.53e+162},
        {64360000000.0, 2107000000000.0, 3425000000000000.0, 1.629e+20, 2.206e+23, 3.109e+29, 4.26e+35, 5.717e+41, 7.553e+47, 9.855e+53, 1.273e+60, 1.631e+66, 2.075e+72, 2.624e+78, 3.577e+87, 5.702e+102, 9.054e+117, 1.433e+133, 3.377e+163},
        {40000000000000.0, 1300000000000000.0, 2.1e+18, 1e+23, 1.4e+26, 1.95e+32, 2.65e+38, 3.57e+44, 4.72e+50, 6.16e+56, 7.96e+62, 1.02e+69, 1.3e+75, 1.64e+81, 2.24e+90, 3.56e+105, 5.66e+120, 8.95e+135, 2.11e+166},
    };


public:
    BuildingUpgrade(int building_index, int upgrade_index, int index_in_gm, GameManager& game_manager);
    int get_req();
    double get_buff();
    double get_cost();
    void buy_callback();

    bool is_available();

    std::vector<std::string> get_base_text_to_display();
};