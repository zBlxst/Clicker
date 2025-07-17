#include "save_manager.hpp"

#include "game_manager.hpp"
#include "stat_tracker.hpp"
#include "building.hpp"
#include "upgrades/building_upgrade.hpp"
#include "faction.hpp"

#include <fstream>
#include <iostream>
#include <format>
#include <memory>
#include <vector>

SaveManager::SaveManager(std::string misc_file_name, std::string stat_file_name, GameManager& game_manager) : 
    m_game_manager(game_manager),
    m_misc_file_name(misc_file_name),
    m_stat_file_name(stat_file_name) {}

SaveManager::SaveManager(GameManager& game_manager) : 
    SaveManager(SaveManager::DEFAULT_MISC_SAVE_FILE, SaveManager::DEFAULT_STAT_SAVE_FILE, game_manager) {}


void SaveManager::load_building(std::string object, std::string value) {
    int building_index = std::stoi(object);
    int building_value = std::stoi(value);
    m_game_manager.get_all_buildings()[building_index]->set_level(building_value);
}

void SaveManager::load_upgrade(std::string object, std::string value, Upgrade::TYPES upgrade_type) {
    int index_in_gm = std::stoi(object);
    bool bought = value == "true";
    if (bought) {
        m_game_manager.get_all_upgrades()[upgrade_type][index_in_gm]->buy();
    }
}

void SaveManager::load_misc_save() {
    std::string buffer;
    std::ifstream file_stream(m_misc_file_name);

    while (std::getline(file_stream, buffer)) {
        int colon_index = buffer.find(" : ");
        int arrow_index = buffer.find(" -> ");
        std::string type = buffer.substr(0, colon_index);
        std::string object = buffer.substr(colon_index + 3, arrow_index-colon_index - 3);
        std::string value = buffer.substr(arrow_index + 4, buffer.size()-arrow_index - 4);
        
        // printf("Type : \"%s\" / Object : \"%s\" / Value : \"%s\"\n", type.c_str(), object.c_str(), value.c_str());

        if (type == "Gold") {
            m_game_manager.set_money(std::stod(value));
        } else if (type == "Mana") {
            m_game_manager.set_mana(std::stod(value));
        } else if (type == "Gems") {
            m_game_manager.set_gems(std::stod(value));
        } else if (type == "Morality") {
            m_game_manager.set_morality((Faction::MORALITY)std::stoi(value));
        } else if (type == "Faction") {
            m_game_manager.set_faction((Faction::FACTION)std::stoi(value));
        } else if (type == "FactionCoin") {
            m_game_manager.set_faction_coin((Faction::FACTION_COINS)std::stoi(object), std::stod(value));
        } else if (type == "Royal exchange") {
            m_game_manager.set_royal_exchange((Faction::FACTION_COINS)std::stoi(object), std::stod(value));
        } else if (type == "Building") {
            load_building(object, value);
        } else if (type == "FactionUpgrade") {
            load_upgrade(object, value, Upgrade::TYPES::FACTION);
        } else if (type == "BuildingUpgrade") {
            load_upgrade(object, value, Upgrade::TYPES::BUILDING);
        } else if (type == "MiscUpgrade") {
            load_upgrade(object, value, Upgrade::TYPES::MISC);
        } else {
            std::cout << std::format("Unknown misc type {}\n", type);
            exit(1);
        }
    }
    file_stream.close();
}

void SaveManager::store_misc_save() {
    std::ofstream file_stream(m_misc_file_name);
    file_stream << std::format("Gold : () -> {}\n", m_game_manager.get_money());
    file_stream << std::format("Gems : () -> {}\n", m_game_manager.get_gems());
    file_stream << std::format("Mana : () -> {}\n", m_game_manager.get_mana());
    
    file_stream << std::format("Morality : () -> {}\n", (int)m_game_manager.get_morality());
    file_stream << std::format("Faction : () -> {}\n", (int)m_game_manager.get_faction());

    // Faction coins
    for (int i = 0; i < Faction::FACTION_COINS::N_FACTIONS_COINS; i++) {
        file_stream << std::format("FactionCoin : {} -> {}\n", i, m_game_manager.get_faction_coin((Faction::FACTION_COINS)i));
    }

    // Royal exchanges
    for (int i = 0; i < Faction::FACTION_COINS::N_FACTIONS_COINS; i++) {
        file_stream << std::format("Royal exchange : {} -> {}\n", i, m_game_manager.get_royal_exchange((Faction::FACTION_COINS)i));
    }

    // Buildings
    for (std::shared_ptr<Building> building: m_game_manager.get_all_buildings()) {
        file_stream << std::format("Building : {} -> {}\n", building->get_index(), building->get_level());
    }

    // Misc upgrades
    for (std::shared_ptr<Upgrade> f_up: m_game_manager.get_all_upgrades()[Upgrade::TYPES::FACTION]) {
        file_stream << std::format("FactionUpgrade : {} -> {}\n", f_up->m_index_in_gm, f_up->is_bought());
    }

    // Building upgrades
    for (std::shared_ptr<Upgrade> b_up: m_game_manager.get_all_upgrades()[Upgrade::TYPES::BUILDING]) {
        file_stream << std::format("BuildingUpgrade : {} -> {}\n", b_up->m_index_in_gm, b_up->is_bought());
    }

    // Misc upgrades
    for (std::shared_ptr<Upgrade> b_up: m_game_manager.get_all_upgrades()[Upgrade::TYPES::MISC]) {
        file_stream << std::format("MiscUpgrade : {} -> {}\n", b_up->m_index_in_gm, b_up->is_bought());
    }


    file_stream.close();
}

void SaveManager::load_stat_save() {
    std::string buffer;
    std::ifstream file_stream(m_stat_file_name);

    while (std::getline(file_stream, buffer)) {
        int colon_index = buffer.find(" : ");
        int arrow_index = buffer.find(" -> ");
        std::string type = buffer.substr(0, colon_index);
        std::string object = buffer.substr(colon_index + 3, arrow_index-colon_index - 3);
        std::string value = buffer.substr(arrow_index + 4, buffer.size()-arrow_index - 4);
        
        // printf("Type : \"%s\" / Object : \"%s\" / Value : \"%s\"\n", type.c_str(), object.c_str(), value.c_str());

        if (type == "Clicks") {
            m_game_manager.get_stat_tracker().m_clicks = std::stoi(value);
        } else if (type == "Click gain") {
            m_game_manager.get_stat_tracker().m_click_gain = std::stod(value);
        } else if (type == "Total gain") {
            m_game_manager.get_stat_tracker().m_total_gain = std::stod(value); 
        } else {
            std::cout << std::format("Unknown stat type {}\n", type);
            exit(1);
        }
    }
    file_stream.close();
}

void SaveManager::store_stat_save() {
    std::ofstream file_stream(m_stat_file_name);

    file_stream << std::format("Clicks : () -> {}\n", m_game_manager.get_stat_tracker().m_clicks);
    file_stream << std::format("Click gain : () -> {}\n", m_game_manager.get_stat_tracker().m_click_gain);
    file_stream << std::format("Total gain : () -> {}\n", m_game_manager.get_stat_tracker().m_total_gain);

    file_stream.close();
}

void SaveManager::load_save() {
    load_stat_save();
    load_misc_save();
}


void SaveManager::store_save() {
    store_stat_save();
    store_misc_save();
}