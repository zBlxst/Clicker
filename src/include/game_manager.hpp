#pragma once

#include <memory>
#include <vector>
#include <thread>

#include "stat_tracker.hpp"

class Building;
class BuildingUpgrade;

class GameManager {
private:
    StatTracker& m_stat_tracker;

    double m_money;
    std::vector<std::shared_ptr<Building>> m_all_buildings;
    std::vector<std::shared_ptr<BuildingUpgrade>> m_all_building_upgrades;

    std::thread m_buildings_thread;

    bool m_running;

    void gain_function_for_thread();

public:
    GameManager(StatTracker& stat_tracker);
    
    void start();
    void stop();

    void click();
    double get_money();
    void add_money(double amount);
    void set_money(double value);
    bool buy(double cost);
    
    std::vector<std::shared_ptr<Building>>& get_all_buildings();
    std::vector<std::shared_ptr<BuildingUpgrade>>& get_all_upgrades();

    StatTracker& get_stat_tracker();

};