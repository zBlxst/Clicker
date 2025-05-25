#include "game_manager.hpp"

#include "building.hpp"

GameManager::GameManager() : 
    m_money(0),
    m_all_buildings() {
        for (int i = 0; i < Building::N_BUILDINGS; i++) {
            std::shared_ptr<Building> b = std::make_shared<Building>(i, std::ref(*this));
            m_all_buildings.push_back(b);
        }
}

double GameManager::get_money() {
    return m_money;
}

void GameManager::click() {
    m_money += 1;
}

std::vector<std::shared_ptr<Building>>& GameManager::get_all_buildings() {
    return m_all_buildings;
}

void GameManager::add_money(double amount) {
    m_money += amount;
    if (m_money < 0) {
        exit(1);
    }
}
