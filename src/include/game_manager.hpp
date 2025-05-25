#pragma once

#include <memory>
#include <vector>

class Building;

class GameManager {
private:
    double m_money;
    std::vector<std::shared_ptr<Building>> m_all_buildings;

public:
    GameManager();
    
    void click();
    double get_money();
    void add_money(double amount);
    
    std::vector<std::shared_ptr<Building>>& get_all_buildings();

};