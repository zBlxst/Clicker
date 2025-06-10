#pragma once

#include <string>
#include <upgrade.hpp>

class GameManager;

class SaveManager {

private:
    static constexpr std::string DEFAULT_MISC_SAVE_FILE = "build/misc.save";
    static constexpr std::string DEFAULT_STAT_SAVE_FILE = "build/stat.save";

    GameManager& m_game_manager;
    std::string m_misc_file_name;
    std::string m_stat_file_name;

    void load_building(std::string object, std::string value);
    void load_upgrade(std::string object, std::string value, Upgrade::TYPES upgrade_type);


public:
    SaveManager(std::string misc_file_name, std::string stat_file_name, GameManager& game_manager);
    SaveManager(GameManager& game_manager);
    
    void load_misc_save();
    void store_misc_save();

    void load_stat_save();
    void store_stat_save();

    void load_save();
    void store_save();

};