#pragma once

#include <memory>
#include <vector>
#include <thread>

class Building;
class BuildingUpgrade;

class GameManager {
private:
    double m_money;
    std::vector<std::shared_ptr<Building>> m_all_buildings;
    std::vector<std::shared_ptr<BuildingUpgrade>> m_all_building_upgrades;

    std::thread m_buildings_thread;

    bool m_running;

    void building_gain_function();

public:
    GameManager();
    
    void start();
    void stop();

    void click();
    double get_money();
    void add_money(double amount);
    void set_money(double value);
    bool buy(double cost);
    
    std::vector<std::shared_ptr<Building>>& get_all_buildings();
    std::vector<std::shared_ptr<BuildingUpgrade>>& get_all_upgrades();

};