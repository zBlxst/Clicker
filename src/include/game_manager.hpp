#pragma once

#include <memory>
#include <vector>
#include <thread>

#include "stat_tracker.hpp"
#include "faction.hpp"
#include "buff.hpp"

class Building;
class Upgrade;
class Spell;
class Achievement;

class GameManager {
public:
    static constexpr double DEFAULT_MANA_MAX = 1000;
    static constexpr double DEFAULT_FACTION_COIN_CHANCE = 0.1;

private:
    StatTracker& m_stat_tracker;

    double m_money;
    double m_mana;
    double m_faction_coins[Faction::FACTION_COINS::N_FACTIONS_COINS];

    std::vector<std::shared_ptr<std::thread>> m_all_threads;

    std::vector<std::shared_ptr<Building>> m_all_buildings;
    std::vector<std::vector<std::shared_ptr<Upgrade>>> m_all_upgrades;
    std::vector<std::shared_ptr<Spell>> m_all_spells;
    std::vector<std::shared_ptr<Achievement>> m_all_achievements;
    

    std::shared_ptr<std::thread> m_buildings_thread;
    std::shared_ptr<std::thread> m_assistants_thread;
    std::shared_ptr<std::thread> m_mana_regen_thread;
    std::shared_ptr<std::thread> m_achievement_thread;

    int m_real_assistants;
    Faction::MORALITY m_morality;
    Faction::FACTION m_faction;
    
    
    bool m_running;
    
    void money_gain_function_for_thread();
    void mana_gain_function_for_thread();
    void assistant_function_for_thread();
    void achievement_function_for_thread();
    
public:
    GameManager(StatTracker& stat_tracker);
    
    Buff m_production_buff;
    Buff m_click_buff;
    Buff m_mana_regen_buff;
    Buff m_mana_max_buff;
    Buff m_faction_coins_buff;
    Buff m_assistants_buff;
    Buff m_assistant_faction_coins_buff;

    void start();
    void stop();
    
    void click(bool manual);
    double get_money();
    void add_money(double amount);
    void set_money(double value);
    bool buy(double cost);
    
    double get_faction_coin(Faction::FACTION_COINS faction);
    void add_faction_coin(double chance);
    void set_faction_coin(Faction::FACTION_COINS faction, double chance);
    bool buy_faction_coins(double cost, std::vector<Faction::FACTION_COINS> faction_coins);
    
    
    void add_mana(double amount);
    void set_mana(double value);
    bool cast_spell(double cost);
    
    void add_assistants(int amount);

    double get_prod();
    double get_building_prod();
    double get_click_gain();
    double get_assistant_money_gain();
    double get_assistant_faction_coin_chance();
    double get_mana();
    double get_mana_max();
    double get_mana_regen();
    int get_assistants();
    int get_all_buildings_level();
    double get_faction_coin_chance();

    Faction::MORALITY get_morality();
    void set_morality(Faction::MORALITY morality);

    Faction::FACTION get_faction();
    void set_faction(Faction::FACTION faction);

    bool is_running();

    std::vector<std::shared_ptr<Building>>& get_all_buildings();
    std::vector<std::vector<std::shared_ptr<Upgrade>>>& get_all_upgrades();
    std::vector<std::shared_ptr<Spell>>& get_all_spells();
    std::vector<std::shared_ptr<Achievement>>& get_all_achievements();

    StatTracker& get_stat_tracker();

    void add_thread(std::shared_ptr<std::thread> thread);

};