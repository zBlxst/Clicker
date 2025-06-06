#pragma once

#include <string>

class GameManager;

class SaveManager {

private:
    static constexpr std::string DEFAULT_SAVE_FILE = "build/misc.save";

    GameManager& m_game_manager;
    std::string m_file_name;

    void load_building(std::string object, std::string value);
    void load_building_upgrade(std::string object, std::string value);


public:
    SaveManager(std::string file_name, GameManager& game_manager);
    SaveManager(GameManager& game_manager);
    
    void load_save();
    void store_save();

};