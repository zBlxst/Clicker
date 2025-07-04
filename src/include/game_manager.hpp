#pragma once

#include <memory>
#include <vector>
#include <thread>

#include "stat_tracker.hpp"

class Building;
class Upgrade;
class Spell;
class Achievement;

class GameManager {
public:
    static constexpr double DEFAULT_MANA_MAX = 1000;

private:
    StatTracker& m_stat_tracker;

    double m_money;
    double m_mana;

    std::vector<std::shared_ptr<std::thread>> m_all_threads;

    std::vector<std::shared_ptr<Building>> m_all_buildings;
    std::vector<std::vector<std::shared_ptr<Upgrade>>> m_all_upgrades;
    std::vector<std::shared_ptr<Spell>> m_all_spells;
    std::vector<std::shared_ptr<Achievement>> m_all_achievements;
    

    std::shared_ptr<std::thread> m_buildings_thread;
    std::shared_ptr<std::thread> m_assistants_thread;
    std::shared_ptr<std::thread> m_mana_regen_thread;
    std::shared_ptr<std::thread> m_achievement_thread;

    // Boosts
    double m_money_multiplicative_upgrade;
    
    double m_click_additive_upgrade;
    double m_click_multiplicative_upgrade;
    double m_click_percent_of_building_prod;

    double m_mana_regen_additive_upgrade;
    double m_mana_regen_multiplicative_upgrade;
    double m_mana_max_additive_upgrade;
    double m_mana_max_multiplicative_upgrade;


    int m_assistants;


    bool m_running;

    void money_gain_function_for_thread();
    void mana_gain_function_for_thread();
    void assistant_function_for_thread();
    void achievement_function_for_thread();

public:
    GameManager(StatTracker& stat_tracker);
    
    void start();
    void stop();

    void click(bool manual);
    double get_money();
    void add_money(double amount);
    void set_money(double value);
    bool buy(double cost);
    
    void add_mana(double amount);
    void set_mana(double value);
    bool cast_spell(double cost);
    
    void add_money_multiplicative_upgrade(double amount);
    void add_click_additive_upgrade(double amount);
    void add_click_multiplicative_upgrade(double amount);
    void add_click_percent_of_prod(double amount);
    void add_mana_regen_additive_upgrade(double amount);
    void add_mana_regen_multiplicative_upgrade(double amount);
    void add_mana_max_additive_upgrade(double amount);
    void add_mana_max_multiplicative_upgrade(double amount);

    void add_assistants(int amount);

    double get_prod();
    double get_building_prod();
    double get_click_gain();
    double get_assistant_money_gain();
    double get_mana();
    double get_mana_max();
    double get_mana_regen();
    int get_assistants();

    bool is_running();

    std::vector<std::shared_ptr<Building>>& get_all_buildings();
    std::vector<std::vector<std::shared_ptr<Upgrade>>>& get_all_upgrades();
    std::vector<std::shared_ptr<Spell>>& get_all_spells();

    StatTracker& get_stat_tracker();

    void add_thread(std::shared_ptr<std::thread> thread);

};