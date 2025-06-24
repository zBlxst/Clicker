#include "game_manager.hpp"

#include "upgrades/upgrade.hpp"
#include "spells/spell.hpp"
#include "building.hpp"
#include "upgrades/building_upgrade.hpp"
#include "upgrades/click_upgrade.hpp"
#include "upgrades/money_upgrade.hpp"

#include <unistd.h>
#include <iostream>
#include <chrono>
#include <thread>


GameManager::GameManager(StatTracker& stat_tracker) :
    m_stat_tracker(stat_tracker),
    m_money(0),
    m_mana(500),
    m_all_buildings(),
    m_all_upgrades(),
    m_all_spells(Spell::get_one_of_each(std::ref(*this))),
    m_buildings_thread(&GameManager::money_gain_function_for_thread, this),
    m_assistants_thread(&GameManager::assistant_function_for_thread, this),
    m_mana_regen_thread(&GameManager::mana_gain_function_for_thread, this),
    m_money_multiplicative_upgrade(1),
    m_click_additive_upgrade(0),
    m_click_multiplicative_upgrade(1),
    m_click_percent_of_building_prod(0),
    m_mana_regen_additive_upgrade(0),
    m_mana_regen_multiplicative_upgrade(1),
    m_mana_max_additive_upgrade(0),
    m_mana_max_multiplicative_upgrade(1),
    m_assistants(0),
    m_running(false) {
        int n_upgrade;
        int n_spell;
        // Initialisation of upgrades vectors
        for (int i = 0; i < Upgrade::TYPES::N_ITEMS; i++) {
            m_all_upgrades.push_back(std::vector<std::shared_ptr<Upgrade>>());
        }

        // Initialisation of buildings
        for (int i = 0; i < Building::N_BUILDINGS; i++) {
            std::shared_ptr<Building> b = std::make_shared<Building>(i, std::ref(*this));
            m_all_buildings.push_back(b);
        }

        // Initialisation of building upgrades
        n_upgrade = 0;
        for (int i = 0; i < Building::N_BUILDINGS; i++) {
            for (int j = 0; j < BuildingUpgrade::N_UPGRADES; j++) {
                std::shared_ptr<BuildingUpgrade> b_up = std::make_shared<BuildingUpgrade>(i, j, n_upgrade++,std::ref(*this));
                m_all_upgrades[Upgrade::TYPES::BUILDING].push_back(b_up);
            }    
        }

        // Initialisation of misc upgrades
        n_upgrade = 0;
        for (int i = 0; i < ClickUpgrade::N_UPGRADES; i++) {
            std::shared_ptr<ClickUpgrade> c_up = std::make_shared<ClickUpgrade>(i, n_upgrade++, std::ref(*this));
            m_all_upgrades[Upgrade::TYPES::MISC].push_back(c_up);
        }
        for (int i = 0; i < MoneyUpgrade::N_UPGRADES; i++) {
            std::shared_ptr<MoneyUpgrade> c_up = std::make_shared<MoneyUpgrade>(i, n_upgrade++, std::ref(*this));
            m_all_upgrades[Upgrade::TYPES::MISC].push_back(c_up);
        }        
}

void GameManager::add_click_additive_upgrade(double amount) {
    m_click_additive_upgrade += amount;
}

void GameManager::add_click_multiplicative_upgrade(double amount) {
    m_click_multiplicative_upgrade *= amount;
}

void GameManager::add_mana_regen_additive_upgrade(double amount) {
    m_mana_regen_additive_upgrade += amount;
}

void GameManager::add_mana_regen_multiplicative_upgrade(double amount) {
    m_mana_regen_multiplicative_upgrade *= amount;
}

void GameManager::add_mana_max_additive_upgrade(double amount) {
    m_mana_max_additive_upgrade += amount;
}

void GameManager::add_mana_max_multiplicative_upgrade(double amount) {
    m_mana_max_multiplicative_upgrade *= amount;
}


void GameManager::add_money_multiplicative_upgrade(double amount) {
    m_money_multiplicative_upgrade *= amount;
}

void GameManager::add_click_percent_of_prod(double amount) {
    m_click_percent_of_building_prod += amount;
}

void GameManager::add_assistants(int amount) {
    m_assistants += amount;
}


double GameManager::get_money() {
    return m_money;
}

void GameManager::click(bool manual) {
    m_stat_tracker.m_clicks++;
    double gain;
    if (manual) {
        gain = get_click_gain();
    } else {
        gain = get_assistant_money_gain();;
    }
    m_money += gain;
    m_stat_tracker.m_click_gain += gain; 
}

double GameManager::get_prod() {
    double prod = 0;
    prod += get_building_prod();
    prod += get_assistant_money_gain()*get_assistants();
    return prod*m_money_multiplicative_upgrade;
}

double GameManager::get_building_prod() {
    double prod = 0;
    for (std::shared_ptr<Building> building: get_all_buildings()) {
        prod += building->get_gain();
    }
    return prod;
}



double GameManager::get_click_gain() {
    return (1+m_click_additive_upgrade)*m_click_multiplicative_upgrade + m_click_percent_of_building_prod*get_building_prod();
}

double GameManager::get_assistant_money_gain() {
    return get_click_gain()*0.05;
}

double GameManager::get_mana() {
    return m_mana;
}

double GameManager::get_mana_max() {
    return (DEFAULT_MANA_MAX+m_mana_max_additive_upgrade)*m_mana_max_multiplicative_upgrade;
}


double GameManager::get_mana_regen() {
    return (1+m_mana_regen_additive_upgrade)*m_mana_regen_multiplicative_upgrade;
}

int GameManager::get_assistants() {
    return m_assistants;
}

std::vector<std::shared_ptr<Building>>& GameManager::get_all_buildings() {
    return m_all_buildings;
}


std::vector<std::vector<std::shared_ptr<Upgrade>>>& GameManager::get_all_upgrades() {
    return m_all_upgrades;
}

std::vector<std::shared_ptr<Spell>>& GameManager::get_all_spells() {
    return m_all_spells;
}


void GameManager::add_money(double amount) {
    double gain = amount;
    m_money += gain;
    m_stat_tracker.m_total_gain += gain;
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

void GameManager::add_mana(double amount) {
    double gain = amount;
    if (gain >= get_mana_max() - get_mana()) 
        gain = get_mana_max() - get_mana();
    m_mana += gain;
    // m_stat_tracker.m_total_gain += gain;
}

void GameManager::set_mana(double value) {
    m_mana = value;
}


bool GameManager::cast_spell(double cost) {
    if (m_mana < cost) {
        return false;
    }
    m_mana -= cost;
    return true;
}


void GameManager::money_gain_function_for_thread() {
    // Wait for the game_manager to run
    while (!m_running) {}
    while (m_running) {
        add_money(get_prod() / 2);
        m_stat_tracker.m_last_second_gain = get_prod();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));;
    }
}

void GameManager::assistant_function_for_thread() {
    // Wait for the game_manager to run
    while (!m_running) {}
    while (m_running) {
        for (int i = 0; i < get_assistants(); i++) {
            click(false);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));;
    }
}

void GameManager::mana_gain_function_for_thread() {
    // Wait for the game_manager to run
    while (!m_running) {}
    while (m_running) {
        add_mana(get_mana_regen() / 3);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000/3));;
    }
}

void GameManager::start() {
    m_running = true;
}


void GameManager::stop() {
    m_running = false;
    m_buildings_thread.join();
    m_assistants_thread.join();
    m_mana_regen_thread.join();
}

bool GameManager::is_running() {
    return m_running;
}

StatTracker& GameManager::get_stat_tracker() {
    return m_stat_tracker;
}