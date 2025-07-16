#include "game_manager.hpp"

#include "upgrades/upgrade.hpp"
#include "spells/spell.hpp"
#include "building.hpp"
#include "upgrades/building_upgrade.hpp"
#include "upgrades/click_upgrade.hpp"
#include "upgrades/money_upgrade.hpp"
#include "upgrades/treasure_upgrade.hpp"

#include "upgrades/faction_upgrades/faction_picker.hpp"
#include "upgrades/faction_upgrades/morality_picker.hpp"
#include "upgrades/faction_upgrades/fairy_upgrade.hpp"
#include "upgrades/faction_upgrades/elven_upgrade.hpp"

#include "achievement.hpp"

#include <unistd.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <cmath>


GameManager::GameManager(StatTracker& stat_tracker) :
    m_stat_tracker(stat_tracker),
    m_money(0),
    m_mana(DEFAULT_MANA_MAX),
    m_faction_coins({}),
    m_royal_exchanges({}),
    m_all_buildings(),
    m_all_upgrades(),
    m_all_spells(Spell::get_one_of_each(std::ref(*this))),
    m_all_achievements(Achievement::get_all_achievements(std::ref(*this))),
    m_buildings_thread(std::make_shared<std::thread>(&GameManager::money_gain_function_for_thread, this)),
    m_assistants_thread(std::make_shared<std::thread>(&GameManager::assistant_function_for_thread, this)),
    m_mana_regen_thread(std::make_shared<std::thread>(&GameManager::mana_gain_function_for_thread, this)),
    m_achievement_thread(std::make_shared<std::thread>(&GameManager::achievement_function_for_thread, this)),
    
    m_production_buff(std::ref(*this)),
    m_click_buff(std::ref(*this)),
    m_mana_regen_buff(std::ref(*this)),
    m_mana_max_buff(std::ref(*this)),
    m_faction_coins_buff(std::ref(*this)),
    m_royal_exchange_buff(std::ref(*this)),
    m_assistants_buff(std::ref(*this)),
    m_assistant_faction_coins_buff(std::ref(*this)),

    m_real_assistants(0),
    m_morality(Faction::NO_MORALITY),
    m_faction(Faction::NO_FACTION),
    m_running(false) {
        // Same seed (to change)
        srand(0);

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

        // Initialisation of faction
        // Initialisation of morality pickers
        n_upgrade = 0;
        for (int i = 0; i < Faction::N_MORALITIES; i++) {
            std::shared_ptr<MoralityPicker> m_up = std::make_shared<MoralityPicker>((Faction::MORALITY)i, n_upgrade++, std::ref(*this));
            m_all_upgrades[Upgrade::TYPES::FACTION].push_back(m_up);
        }
        // Initialisation of faction pickers
        for (int i = 0; i < Faction::MORALITY::N_MORALITIES; i++) {
            for (int j = 0; j < Faction::N_BASE_FACTIONS_PER_MORALITY; j++) {
                std::shared_ptr<FactionPicker> f_up = std::make_shared<FactionPicker>((Faction::MORALITY)i, Faction::BASE_FACTION_PER_MORALITY[i][j], n_upgrade++, std::ref(*this));
                m_all_upgrades[Upgrade::TYPES::FACTION].push_back(f_up);
            }
        }
        // Initialisation of faction upgrades
        for (int i = 0; i < 9; i++) {
            std::shared_ptr<FairyUpgrade> f_up = std::make_shared<FairyUpgrade>(i, n_upgrade++, std::ref(*this));
            m_all_upgrades[Upgrade::TYPES::FACTION].push_back(f_up);
        }
        for (int i = 0; i < 9; i++) {
            std::shared_ptr<ElvenUpgrade> f_up = std::make_shared<ElvenUpgrade>(i, n_upgrade++, std::ref(*this));
            m_all_upgrades[Upgrade::TYPES::FACTION].push_back(f_up);
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
        for (int i = 0; i < TreasureUpgrade::N_UPGRADES; i++) {
            std::shared_ptr<TreasureUpgrade> c_up = std::make_shared<TreasureUpgrade>(i, n_upgrade++, std::ref(*this));
            m_all_upgrades[Upgrade::TYPES::MISC].push_back(c_up);
        }

        // Royal exchange buff
        m_production_buff.m_multiplicative_buff_callbacks.push_back(
          std::make_shared<std::function<double(GameManager&)>>([](GameManager& game_manager) {
            int n_exchanges = 0;
            for (int i = 0; i < Faction::FACTION_COINS::N_FACTIONS_COINS; i++) {
                n_exchanges += game_manager.get_royal_exchange((Faction::FACTION_COINS)i);
            }
            return 1 + game_manager.m_royal_exchange_buff.get_buffed_value(DEFAULT_FACTION_COIN_CHANCE) * n_exchanges;
          })  
        );

        // Put threads in all_threads
        add_thread(m_buildings_thread);
        add_thread(m_assistants_thread);
        add_thread(m_mana_regen_thread);
        add_thread(m_achievement_thread);

        // for (int i = 0; i < Faction::FACTION_COINS::N_FACTIONS_COINS; i++) {
        //     m_faction_coins[i] = 10000;
        // }
        // m_money = 100000;
        // m_production_buff.m_multiplicative_buff *= 100;
}

void GameManager::add_assistants(int amount) {
    m_real_assistants += amount;
}


double GameManager::get_money() {
    return m_money;
}

void GameManager::click(bool manual) {
    m_stat_tracker.m_clicks++;
    double gain = get_click_gain();
    m_stat_tracker.m_click_gain += gain;
    add_faction_coin(get_faction_coin_chance());
    add_money(gain);
}

double GameManager::get_prod() {
    double prod = 0;
    prod += get_building_prod();
    prod += get_assistant_money_gain()*get_assistants();
    return m_production_buff.get_buffed_value(prod);
}

double GameManager::get_faction_coin_chance() {
    return m_faction_coins_buff.get_buffed_value(DEFAULT_FACTION_COIN_CHANCE);
}

double GameManager::get_building_prod() {
    double prod = 0;
    for (std::shared_ptr<Building> building: get_all_buildings()) {
        prod += building->get_gain();
    }
    return prod;
}



double GameManager::get_click_gain() {
    return m_click_buff.get_buffed_value(1);
}

double GameManager::get_assistant_money_gain() {
    return get_click_gain()*0.05;
}

double GameManager::get_assistant_faction_coin_chance() {
    return m_assistant_faction_coins_buff.get_buffed_value(get_faction_coin_chance());
}

double GameManager::get_mana() {
    return m_mana;
}

double GameManager::get_mana_max() {
    return m_mana_max_buff.get_buffed_value(DEFAULT_MANA_MAX);
}


double GameManager::get_mana_regen() {
    return m_mana_regen_buff.get_buffed_value(1);
}

int GameManager::get_assistants() {
    return m_assistants_buff.get_buffed_value(m_real_assistants);
}

int GameManager::get_all_buildings_level() {
    int res = 0;
    for (std::shared_ptr<Building> building : get_all_buildings()) {
        res += building->get_level();
    }
    return res;
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

std::vector<std::shared_ptr<Achievement>>& GameManager::get_all_achievements() {
    return m_all_achievements;
}


void GameManager::add_money(double amount) {
    double gain = amount;
    m_money += gain;
    m_stat_tracker.m_total_gain += gain;
}

void GameManager::set_money(double value) {
    m_money = value;
}

double GameManager::get_faction_coin(Faction::FACTION_COINS faction) {
    return m_faction_coins[faction];
}
void GameManager::add_faction_coin(double chance) {
    Faction::FACTION_COINS target = (Faction::FACTION_COINS)(rand() % Faction::FACTION_COINS::N_FACTIONS_COINS);
    double amount = std::floor(chance) + ((rand() % 100) < std::round((chance - std::floor(chance)) * 100));
    m_faction_coins[target] += amount;
    m_stat_tracker.m_total_faction_coin_gain += amount;
}
void GameManager::set_faction_coin(Faction::FACTION_COINS faction, double amount) {
    m_faction_coins[faction] = amount;
}

int GameManager::get_royal_exchange(Faction::FACTION_COINS faction) {
    return m_royal_exchanges[faction];
}
void GameManager::add_royal_exchange(Faction::FACTION_COINS faction, int amount) {
    m_royal_exchanges[faction] += amount;
}

void GameManager::set_royal_exchange(Faction::FACTION_COINS faction, int amount) {
    m_royal_exchanges[faction] = amount;
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

bool GameManager::buy_faction_coins(double cost, std::vector<Faction::FACTION_COINS> faction_coin) {
    for (Faction::FACTION_COINS faction : faction_coin) {
        if (m_faction_coins[faction] < cost) {
            return false;
        }
    }
    for (Faction::FACTION_COINS faction : faction_coin) {
        m_faction_coins[faction] -= cost;
    }
    return true;
}


void GameManager::add_mana(double amount) {
    double gain = amount;
    if (gain >= get_mana_max() - get_mana()) 
        gain = get_mana_max() - get_mana();
    m_mana += gain;
    m_stat_tracker.m_mana_produced += gain;
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
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void GameManager::assistant_function_for_thread() {
    // Wait for the game_manager to run
    while (!m_running) {}
    while (m_running) {
        add_money(get_assistant_money_gain()*get_assistants());
        add_faction_coin(get_assistant_faction_coin_chance()*get_assistants());
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

void GameManager::mana_gain_function_for_thread() {
    // Wait for the game_manager to run
    while (!m_running) {}
    while (m_running) {
        add_mana(get_mana_regen() / 3);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000/3));
    }
}

void GameManager::achievement_function_for_thread() {
    // Wait for the game_manager to run
    while (!m_running) {}
    while (m_running) {
        for (std::shared_ptr<Achievement> achievement : m_all_achievements) {
            achievement->update();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

Faction::MORALITY GameManager::get_morality() {
    return m_morality;
}

void GameManager::set_morality(Faction::MORALITY morality) {
    m_morality = morality;
}

Faction::FACTION GameManager::get_faction() {
    return m_faction;
}

void GameManager::set_faction(Faction::FACTION faction) {
    m_faction = faction;
}

void GameManager::start() {
    m_running = true;
}


void GameManager::stop() {
    m_running = false;
    for (std::shared_ptr<std::thread> thread : m_all_threads) {
        if (thread->joinable()) {
            thread->join();
        }
    }
}

bool GameManager::is_running() {
    return m_running;
}

StatTracker& GameManager::get_stat_tracker() {
    return m_stat_tracker;
}

void GameManager::add_thread(std::shared_ptr<std::thread> thread) {
    m_all_threads.push_back(thread);
}