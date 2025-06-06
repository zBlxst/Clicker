#include "game_manager.hpp"

#include "building.hpp"
#include "building_upgrade.hpp"
#include <unistd.h>

GameManager::GameManager() : 
    m_money(3000),
    m_all_buildings(),
    m_all_building_upgrades(),
    m_buildings_thread(&GameManager::building_gain_function, this),
    m_running(false) {
        for (int i = 0; i < Building::N_BUILDINGS; i++) {
            std::shared_ptr<Building> b = std::make_shared<Building>(i, std::ref(*this));
            m_all_buildings.push_back(b);
        }

        for (int i = 0; i < Building::N_BUILDINGS; i++) {
            for (int j = 0; j < BuildingUpgrade::N_UPGRADES; j++) {
                std::shared_ptr<BuildingUpgrade> b_up = std::make_shared<BuildingUpgrade>(i, j, std::ref(*this));
                m_all_building_upgrades.push_back(b_up);
            }    
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

std::vector<std::shared_ptr<BuildingUpgrade>>& GameManager::get_all_upgrades() {
    return m_all_building_upgrades;
}

void GameManager::add_money(double amount) {
    m_money += amount;
    if (m_money < 0) {
        exit(1);
    }
}

void GameManager::set_money(double value) {
    m_money = value;
}

bool GameManager::buy(double cost) {
    // If not running, it's probably loading a save
    if (!m_running) {
        return true;
    }
    if (m_money < cost) {
        return false;
    }
    m_money -= cost;
    return true;
}


void GameManager::building_gain_function() {
    // Wait for the game_manager to run
    while (!m_running) {}
    while (m_running) {
        for (std::shared_ptr<Building> building: get_all_buildings()) {
            add_money(building->get_gain() / 2);
        }
        sleep(1);
    }
}

void GameManager::start() {
    m_running = true;
}


void GameManager::stop() {
    m_running = false;
    m_buildings_thread.join();
}