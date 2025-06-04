#pragma once

#include <string>

class GameManager;

class SaveManager {

private:
    static constexpr std::string default_save_file = "1.save";

    GameManager& m_game_manager;
    std::string m_file_name;

public:
    SaveManager(std::string file_name, GameManager& game_manager);
    SaveManager(GameManager& game_manager);
    
    void load_save();
    void store_save();

};