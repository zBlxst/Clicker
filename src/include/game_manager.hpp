#pragma once

#include <memory>
#include <vector>
#include <thread>

class Building;

class GameManager {
private:
    double m_money;
    std::vector<std::shared_ptr<Building>> m_all_buildings;
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
    bool buy(double cost);
    
    std::vector<std::shared_ptr<Building>>& get_all_buildings();

};