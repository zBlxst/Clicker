#include "save_manager.hpp"

#include "game_manager.hpp"

#include <building.hpp>
#include <fstream>
#include <format>

SaveManager::SaveManager(std::string file_name, GameManager& game_manager) : 
    m_game_manager(game_manager),
    m_file_name(file_name) {}

SaveManager::SaveManager(GameManager& game_manager) : 
    SaveManager(SaveManager::default_save_file, game_manager) {}

void SaveManager::load_save() {

}

void SaveManager::store_save() {
    std::ofstream file_stream(m_file_name);
    file_stream << std::format("Gold : {}\n", m_game_manager.get_money());
    for (std::shared_ptr<Building> building: m_game_manager.get_all_buildings()) {
        file_stream << std::format("Building {} : {}\n", building->get_index(), building->get_level());
    }
    
    file_stream.close();
}