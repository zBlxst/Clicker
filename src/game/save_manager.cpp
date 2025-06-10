#include "save_manager.hpp"

#include "game_manager.hpp"
#include "stat_tracker.hpp"
#include "building.hpp"
#include "upgrades/building_upgrade.hpp"

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
        } else if (type == "Building") {
            load_building(object, value);
        } else if (type == "BuildingUpgrade") {
            load_upgrade(object, value, Upgrade::TYPES::BUILDING);
        } else if (type == "ClickUpgrade") {
            load_upgrade(object, value, Upgrade::TYPES::CLICK);
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
    
    // Buildings
    for (std::shared_ptr<Building> building: m_game_manager.get_all_buildings()) {
        file_stream << std::format("Building : {} -> {}\n", building->get_index(), building->get_level());
    }

    // Building upgrades
    for (std::shared_ptr<Upgrade> b_up: m_game_manager.get_all_upgrades()[Upgrade::TYPES::BUILDING]) {
        file_stream << std::format("BuildingUpgrade : {} -> {}\n", b_up->m_index_in_gm, b_up->is_bought());
    }

    // Click upgrades
    for (std::shared_ptr<Upgrade> b_up: m_game_manager.get_all_upgrades()[Upgrade::TYPES::CLICK]) {
        file_stream << std::format("ClickUpgrade : {} -> {}\n", b_up->m_index_in_gm, b_up->is_bought());
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