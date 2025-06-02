#pragma once

class GameManager;

class BuildingUpgrade {

private:
    GameManager& m_game_manager;

    unsigned int m_building_index;
    unsigned int m_upgrade_index;

public:
    BuildingUpgrade(unsigned int building_index, unsigned int upgrade_index, GameManager& game_manager);


};