#pragma once

#include <memory>
#include <vector>
#include <thread>

#include "stat_tracker.hpp"

class Building;
class Upgrade;

class GameManager {
private:
    StatTracker& m_stat_tracker;

    double m_money;
    std::vector<std::shared_ptr<Building>> m_all_buildings;
    std::vector<std::vector<std::shared_ptr<Upgrade>>> m_all_upgrades;

    std::thread m_buildings_thread;
    std::thread m_assistants_thread;

    double m_click_additive_upgrade;
    double m_click_multiplicative_upgrade;
    double m_money_multiplicative_upgrade;
    double m_click_percent_of_building_prod;
    int m_assistants;


    bool m_running;

    void gain_function_for_thread();
    void assistant_function_for_thread();

public:
    GameManager(StatTracker& stat_tracker);
    
    void start();
    void stop();

    void click(bool manual);
    double get_money();
    void add_money(double amount);
    void set_money(double value);
    bool buy(double cost);
    
    void add_click_additive_upgrade(double amount);
    void add_click_multiplicative_upgrade(double amount);
    void add_money_multiplicative_upgrade(double amount);
    void add_click_percent_of_prod(double amount);
    void add_assistants(int amount);

    double get_prod();
    double get_building_prod();
    double get_click_gain();
    double get_assistant_money_gain();
    int get_assistants();

    std::vector<std::shared_ptr<Building>>& get_all_buildings();
    std::vector<std::vector<std::shared_ptr<Upgrade>>>& get_all_upgrades();

    StatTracker& get_stat_tracker();

};